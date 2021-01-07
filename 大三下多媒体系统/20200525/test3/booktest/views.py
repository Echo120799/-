from django.shortcuts import render
from .models import BookInfo

def index(request):
   #用 List 将我的书  传递给前端
   #查找书
   booklist = BookInfo.objects.all()
   return render(request, 'booktest/index.html', {'booklist': booklist})