from django.shortcuts import render
from .models import BookInfo

def index(request):
   #�� List ���ҵ���  ���ݸ�ǰ��
   #������
   booklist = BookInfo.objects.all()
   return render(request, 'booktest/index.html', {'booklist': booklist})