from django.shortcuts import render,redirect,HttpResponseRedirect
from hashlib import sha1
from .models import *

# Create your views here.
def login(request):
    uname=request.COOKIES.get('uname','')
    context={'uname':uname}
    return render(request,'df_user/login.html',context)

def register(request):
    context={}
    return render(request,'df_user/register.html',context)

def register_handle(request):
    post = request.POST
    uname = post.get('user_name')
    upwd = post.get('pwd')
    upwd2 = post.get('cpwd')
    uemail = post.get('email')
    if upwd != upwd2:
        return redirect('/usr/register/')
    s1 = sha1()
    s1.update(upwd.encode('utf8'))
    upwd3 = s1.hexdigest()
    user = UserInfo()
    user.uname = uname
    user.upwd = upwd3
    user.uemail = uemail
    user.save()
    return redirect('/user/login/')

def login_handle(request):
    post=request.POST
    uname=post.get('username')
    upwd=post.get('pwd')
    jizhu=post.get('jizhu',0)
    users=UserInfo.objects.filter(uname=uname)
    print(uname)
    if len(users)==1:
        s1=sha1()
        s1.update(upwd.encode('utf8'))
        if s1.hexdigest()==users[0].upwd:
            red=HttpResponseRedirect('/user/info')
            if jizhu!=0:
                red.set_cookie('uname',uname)
            else:
                red.set_cookie('uname', '',max_age=-1)
            request.session['user_id']=users[0].id
            request.session['user_name']=uname
            return red
        else:
            context={'title':'用户登录','error_name':0,'error_pwd':1,'uname':uname,'upwd':upwd}
            return render(request,'df_user/login.html',context)
    else:
        context={'title':'用户登录','error_name':1,'error_pwd':0,'uname':uname,'upwd':upwd}
        return render(request, 'df_user/login.html', context)

def info(request):
    user_email=UserInfo.objects.get(id = request.session['user_id']).uemail
    context={'user_email':user_email,
             'user_name':request.session['user_name']}
    return render(request,'df_user/user_center_info.html',context)