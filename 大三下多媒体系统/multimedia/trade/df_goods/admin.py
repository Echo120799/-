from django.contrib import admin
from .models import *
# Register your models here.
class TypeInfoAdmin(admin.ModelAdmin):
    list_display = ['id','tname']


admin.site.register(TypeInfo,TypeInfoAdmin)
