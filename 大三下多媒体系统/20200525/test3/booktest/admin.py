from django.contrib import admin
from .models import *
# Register your models here.
#table == class

class HeroInfoInline(admin.StackedInline):
    model = HeroInfo
    extra = 3

class BookInfoAdmin(admin.ModelAdmin):
    list_display = ['pk', 'btitle', 'bpub_date']
    list_filter = ['bpub_date']
    inlines = [HeroInfoInline]


admin.site.register(BookInfo,BookInfoAdmin)
admin.site.register(HeroInfo)