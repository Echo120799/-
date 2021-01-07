from django.shortcuts import render,redirect,HttpResponseRedirect
from hashlib import sha1
from.models import *
from df_goods.models import *
# Create your views here.
def register(request):
    context = {}
    return render(request, 'df_user/register.html', context)

def register_handle(request):
    post=request.POST
    uname=post.get('user_name')
    upwd=post.get('pwd')
    upwd2=post.get('cpwd')
    uemail=post.get('email')
    uphone=post.get('phone')
    if upwd!=upwd2:
        return redirect('/user/register')
    s1=sha1()
    s1.update(upwd.encode('utf-8'))
    upwd3=s1.hexdigest()
    user=UserInfo()
    user.uname=uname
    user.upwd=upwd3
    user.uemail=uemail
    user.uphone=uphone
    user.save()
    return redirect('/')

def login(request):
    uname=request.COOKIES.get('uname','')
    context={'uname':uname}
    return render(request,'df_user/login.html',context)

def login_handle(request):
    post=request.POST
    uname=post.get('username')
    upwd=post.get('pwd')
    jizhu=post.get('jizhu',0)
    users=UserInfo.objects.filter(uname=uname)
    print(uname)
    if len(users)==1:
        s1=sha1()
        s1.update(upwd.encode('utf-8'))
        if s1.hexdigest()==users[0].upwd:
            red=HttpResponseRedirect('/user/info/')
            if jizhu!=0:
                red.set_cookie('uname',uname)
            else:
                red.set_cookie('uname','',max_age=-1)
            request.session['user_id']=users[0].id
            request.session['user_name'] = uname
            return red
        else:
            context={'title':'用户登录','error_name':0,
                     'error_pwd': 1,'uname':uname,'upwd':upwd
                     }
            return render(request,'df_user/login.html',context)
    else:
        context={'title':'用户登录','error_name':1,
                'error_pwd': 0,'uname':uname,'upwd':upwd}
        return render(request, 'df_user/login.html', context)

def info(request):
    user_email=UserInfo.objects.get(id=request.session['user_id']).uemail
    user_phone = UserInfo.objects.get(id=request.session['user_id']).uphone
    goodlist = GoodsInfo.objects.all()
    goods_new = goodlist.order_by('-id')[0:2]
    context={
        'user_email':user_email,
        'user_name':request.session['user_name'],
        'user_phone':user_phone,
        'goods_new': goods_new
    }
    return render(request,'df_user/user_center_info.html',context)