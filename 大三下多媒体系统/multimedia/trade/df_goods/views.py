from django.shortcuts import render
from .models import *
# Create your views here.
def index(request):
    '''
    typelist=TypeInfo.objects.all()
    type0 = typelist[0].goodinfo_set.order_by('-id')[0:4]
    type1 = typelist[1].goodinfo_set.order_by('-id')[0:4]
    context={'type0':type0,'type1':type1}

    '''
    context={}
    return render(request,'df_goods/index.html',context)


