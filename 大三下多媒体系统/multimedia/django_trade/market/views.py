from django.shortcuts import render
import uuid
import json
from django.shortcuts import render
from django.core import serializers
from django.views.generic.base import View
from django.http import HttpResponse, HttpResponseRedirect #导入http响应类重定向转视图实现页面跳转
from .models import *
from common.custom_paginator import CustomPaginator
from django.core.paginator import EmptyPage, PageNotAnInteger
from django.views.decorators.csrf import csrf_exempt
from django.urls import reverse
from django.core.files.base import ContentFile
from custom_user.views import LoginRequiredMixin


class HomeView(View):

    def get(self, request):
        goods = Item.objects.all().order_by("-has_sale")
        return render(request, 'index.html', {'obj': goods})#页面渲染


class SortView(View):
    def get(self, request):
        good_type = int(request.GET.get('type', 0))  # get方法获取商品类型从数据库中匹配
        goods = Item.objects.filter(classification=good_type + 1)  # 从数据库中取得匹配的结果返回一个对象列表列表名
        commends = CommentModel.objects.all()[0:8]  # 1

        return render(request, 'sort.html', {'goods': goods, "commends": commends})  # 页面渲染

    def post(self, request):
        q = request.POST.get("q")
        goods = Item.objects.filter(description__contains=q)
        commends = CommentModel.objects.all()[0:8]
        return render(request, 'sort.html', {'goods': goods, "commends": commends})


class GoodsDetail(View):
    def get(self, request):
        good_id = int(request.GET.get("id"))#获取用户id
        good_item = Item.objects.get(id = good_id)#获取商品id
        return render(request, 'good_item.html', {'good_item': good_item})#渲染商品信息页面

    def post(self, request):
        _type = int(request.POST.get("type"))#获取商品类型
        good_id = int(request.POST.get("good_id"))#获取商品id
        adress = request.POST.get("adress")#获取用户收货地址
        phone_number = request.POST.get("phone_number")#获取用户手机号
        buy_count = int(request.POST.get("buy_count"))#获取购买数量
        good_item = Item.objects.get(id = good_id)#获取商品id
        # good_item.counts -= buy_count
        # good_item.has_sale += buy_count
        user = request.user
        price = good_item.price*buy_count
        order_id = uuid.uuid1()
        data = {"order_id": order_id, "good_item": good_item, "status": _type, "count": buy_count, "address": adress,
                "phone": phone_number, "user": user, "price": price}
        try:
            OrderModel.objects.create(**data)
            if _type == 1:
                good_item.counts -= buy_count
                good_item.has_sale += buy_count
                good_item.save()
        except Exception as e:
            import traceback
            print(traceback.format_exc())
            return HttpResponse(json.dumps({"code": -1, "msg": "%s" % e}), content_type = 'application/json')
        if _type == 0:
            return HttpResponse(json.dumps({"code": 0, "msg": "添加购物车成功"}), content_type = 'application/json')
        return HttpResponse(json.dumps({"code": 0, "msg": "购买成功,请等待发货"}), content_type = 'application/json')


class GouWuCheView(LoginRequiredMixin, View):
    def get(self, request):
        user = request.user
        goods_records = user.orders.order_by('-create_at').all().filter(status=0)
        return render(request, 'gouwuche.html', {"goods_records": goods_records})

    def delete(self, request):
        good_id = request.GET.get("id")  # 获取商品id
        OrderModel.objects.filter(id=good_id).delete()  # 购物车中删除商品
        return HttpResponse(json.dumps({"code": 0, "msg": "success"}),content_type = 'application/json')

    def post(self, request):
        ids = request.POST.get("ids").split("|")
        goodRecords = OrderModel.objects.filter(id__in=ids)#
        for item in goodRecords:
            item.status = 1
            item.save()
            good = item.good_item
            good.has_sale += 1
            good.counts -= item.count
            good.save()
        return HttpResponse(json.dumps({"code": 0, "msg": "success"}),content_type = 'application/json')

    @csrf_exempt
    def dispatch(self, *args, **kwargs):
        return super(GouWuCheView, self).dispatch(*args, **kwargs)


class DingDanView(LoginRequiredMixin, View):
    def get(self, request):
        user = request.user
        orders =OrderModel.objects.filter(user=user, status__in=(-1,1,2)).order_by('-create_at').all()
        current_page = request.GET.get("page", '1')
        paginator = CustomPaginator(current_page, 9, orders, 10)
        try:
            paginator = paginator.page(current_page)  #获取前端传过来显示当前页的数据
        except PageNotAnInteger:
            # 如果有异常则显示第一页
            paginator = paginator.page(1)
        except EmptyPage:
            # 如果没有得到具体的分页内容的话,则显示最后一页
            paginator = paginator.page(paginator.num_pages)
        return render(request, 'dingdan.html', {"paginator":paginator})


class CommentView(View):
    def get(self, request):
        # comment_id = int(request.GET.get("id"))
        # commends = CommentModel.objects.filter(id__gt=comment_id)
        commends = CommentModel.objects.all()[0:8]
        json_data = serializers.serialize("json", commends)
        return HttpResponse(json.dumps(json_data), content_type = 'application/json')

    @csrf_exempt
    def dispatch(self, *args, **kwargs):
        return super(CommentView, self).dispatch(*args, **kwargs)

    def post(self, request):
        try:
            user_name = "游客"
            if request.user.is_authenticated:
                user_name = request.user.username
            des = request.POST.get("des")
            CommentModel.objects.create(user=user_name, description = des)
        except Exception as e:
            return HttpResponse(json.dumps({"code": -1, "msg": "error:%s" % e}), content_type = 'application/json')
        return HttpResponse(json.dumps({"code": 0, "msg": "success"}), content_type = 'application/json')


class OrderDetailView(LoginRequiredMixin, View):#用户中心订单页
    def get(self, request):
        _id = int(request.GET.get("id"))
        order_item = OrderModel.objects.get(id = _id)#数据库获取订单信息
        return render(request, "order_item.html", {'order_item': order_item})

    def post(self, request):
        _id = int(request.GET.get("id"))#获取订单id
        order_item = OrderModel.objects.get(id = _id)#匹配商品id
        comment = CommentDetailModel()#查看评论
        comment.order = order_item#评论商品信息
        comment.user = request.user#评论用户信息
        content = request.POST['remark']
        comment.description = content#评论描述
        pic = ContentFile(request.FILES['img'].read())
        comment.pic.save(request.FILES['img'].name, pic)
        comment.save()
        return HttpResponseRedirect(reverse("dingdan"))#跳转到订单页面


class HelpView(LoginRequiredMixin, View):
    def get(self, request):
        return render(request, "help.html")


