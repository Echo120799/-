from django.shortcuts import render

# Create your views here.
def index(request):
    context={}
    return render(request,'df_goods/index.html',context)