from django.shortcuts import render
from .models import BookInfo
from .models import HeroInfo
# Create your views here.
#coding:utf-8
from django.http import HttpResponse

def index(request):
    booklist = BookInfo.objects.all()
    return render(request, 'booktest/index.html', {'booklist': booklist})

def detail(request, id):
    book = BookInfo.objects.get(pk=id)
    return render(request, 'booktest/detail.html')

