from django.contrib import admin
from .models import *
# Register your models here.
class TypeInfoAdmin(admin.ModelAdmin):
    list_display = ['id','tname']

class GoodsInfoAdmin(admin.ModelAdmin):
    list_display = ['id','gname','gprice','gtype']

admin.site.register(TypeInfo,TypeInfoAdmin)
admin.site.register(GoodsInfo,GoodsInfoAdmin)
