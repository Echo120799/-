from django.shortcuts import render
from django.http import response
from .models import *
# Create your views here.
def index(request):
    #typelist=TypeInfo.objects.all()
    #type0 = typelist[0].goodsinfo_set.order_by('-id')[0:4]
    #type1 = typelist[1].goodsinfo_set.order_by('-id')[0:4]
    #context={'type0':type0,'type1':type1}
    typelist=TypeInfo.objects.all()
    types = typelist.order_by('id')
    goodlist = GoodsInfo.objects.all()
    goods=goodlist.order_by('-id')[0:3]
    context={'goods':goods,'types':types}
    return render(request,'df_goods/index2.html',context)

def list(request,id):
    typelist = TypeInfo.objects.all()
    goods=typelist[int(id)-1].goodsinfo_set.order_by('-id')
    goodlist = GoodsInfo.objects.all()
    goods_new = goodlist.order_by('-id')[0:2]
    context={'goods':goods,'goods_new':goods_new,'types':typelist}
    return render(request, 'df_goods/list.html', context)

def detail(request,id):
    typelist = TypeInfo.objects.all()
    goodlist=GoodsInfo.objects.all()
    goods=goodlist[int(id)-3]
    goods_new=goodlist.order_by('-id')[0:2]
    context={'goods':goods,'goods_new':goods_new,'types':typelist}
    return render(request, 'df_goods/detail.html', context)


