from django.shortcuts import render
from django.views.generic.base import View
from django.contrib.auth.hashers import make_password
from .forms import RegisterForm, LoginForm  #导入注册表单类和登录表单类
from .models import UserProfile             #从数据模型modles中导入用户信息类UserProfile
from django.contrib.auth import authenticate, login, logout #导入django自带用户系统模板的authenticate类中的login方法
from django.urls import reverse
from django.http import HttpResponse, HttpResponseRedirect#导入http响应类
from django.contrib.auth.backends import ModelBackend
from django.db.models import Q
from django.contrib.auth.models import Group#导入django自带的用户模板中的组类Gruop
from django.contrib.auth.decorators import login_required
from django.core.files.base import ContentFile
import json

class LoginRequiredMixin(object):
    """
    登陆限定，并指定登陆url
    """
    @classmethod
    def as_view(cls, **initkwargs):
        view = super(LoginRequiredMixin, cls).as_view(**initkwargs)
        return login_required(view, login_url='/custom-user/login')


# Create your views here.
class RegisterView(View):
    def get(self, request):
        return render(request, "register.html")

    def post(self, request):
        register_form = RegisterForm(request.POST)
        if register_form.is_valid():#判断用户输入的表单信息格式是否正确

            user_name = request.POST.get("uname")#获取用户名
            if UserProfile.objects.filter(username=user_name):#判断用户名是否重复
                return render(request, "register.html", {"register_form": register_form, "msg": "用户已经存在"})
            email = request.POST.get("email")
            mobile = request.POST.get("mobile")
            pwd = request.POST.get("pwd")
            '''保存用户信息'''
            user_profile = UserProfile()
            user_profile.username = user_name
            user_profile.email = email
            user_profile.mobile = mobile
            #将用户设置成激活
            user_profile.is_active = True
            user_profile.set_password(pwd)
            # user_profile.password = make_password(pwd)
            user_profile.save()
            return render(request, "login.html")
        else:
            return render(request, "register.html", {"register_form": register_form})


class LogoutView(View):
    """
    用户登出
    """
    def get(self, request):
        logout(request)
        return HttpResponseRedirect(reverse("home"))


class CustomBackend(ModelBackend):
    def authenticate(self, username=None, password=None, **kwargs):
        try:
            user = UserProfile.objects.get(Q(username=username) | Q(email=username))
            if user.check_password(password):
                return user
        except Exception as e:
            return None


class LoginView(View):
    def get(self, request):
        return render(request, "login.html", {})

    def post(self, request):
        login_form = LoginForm(request.POST)#获取用户填写的登录信息
        if login_form.is_valid():#判断用户输入的表单信息格式是否正确
            user_name = request.POST.get("uname", "")
            pass_word = request.POST.get("pwd", "")
            user = authenticate(username=user_name, password=pass_word)
            if user is not None:
                if user.is_active:
                    login(request, user)
                    return HttpResponseRedirect(reverse("home"))
                else:
                    return render(request, "login.html", {"msg": "用户未激活！"})
            else:
                return render(request, "login.html", {"msg": "用户名或密码错误！"})
        else:
            return render(request, "login.html", {"login_form": login_form})


# 用户信息模块
class ProfileView(LoginRequiredMixin, View):
    def get(self, request):
        return render(request, 'detail.html')

    def post(self, request):
        user_id = request.POST.get("id")
        last_name = request.POST.get("name")
        interest = request.POST.get("interest")
        sex = request.POST.get("sex")
        address = request.POST.get("address")
        phone = request.POST.get("phone")
        email = request.POST.get("email")
        obj = UserProfile.objects.get(id=int(user_id))
        obj.last_name = last_name
        obj.interest = interest
        obj.sex = int(sex)
        obj.address = address
        obj.mobile = phone
        obj.email = email
        obj.save()
        return HttpResponseRedirect(reverse("detail"))


# 修改头像模块
class ChangeAvatarView(LoginRequiredMixin, View):

    def post(self, request):
        obj = UserProfile.objects.get(id=request.user.id)
        pic = ContentFile(request.FILES['file'].read())
        obj.image.save(request.FILES['file'].name, pic)
        obj.save()
        return HttpResponse(json.dumps({'code':0, "avatar": obj.image.url}))


# 重置密码
class ResetPasswordView(LoginRequiredMixin, View):
    def post(self, request):
        obj = UserProfile.objects.get(id=request.user.id)
        password = request.POST.get("password")
        obj.set_password(password)
        obj.save()
        return HttpResponse(json.dumps({'code':0, "avatar": obj.image.url}), content_type="application/json")