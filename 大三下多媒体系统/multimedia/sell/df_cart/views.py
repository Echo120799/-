from django.shortcuts import render,redirect
from django.http import JsonResponse
from .models import *
# Create your views here.
def cart(request):
    uid = request.session['user_id']
    carts = CartInfo.objects.filter(user_id=uid)
    context = {'title': '购物车',
               'page_name': 1,
               'carts': carts}
    return render(request, 'df_cart/cart.html', context)

def add(request,id):
    uid = request.session['user_id']
    gid = int(id)
    count=1
    carts = CartInfo.objects.filter(user_id=uid, goods_id=gid)
    if len(carts) >= 1:
        cart = carts[0]
        cart.count = cart.count + count
    else:
        cart = CartInfo()
        cart.user_id = uid
        cart.goods_id = gid
        cart.count = count
    cart.save()
    # 如果是ajax请求则返回json，否则转向购物车
    if request.is_ajax():
        count = CartInfo.objects.filter(user_id=request.session['user_id']).count()
        return JsonResponse({'cart_id': cart.id, 'count': count})
    else:
        return redirect('/cart/')