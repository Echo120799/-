from django.contrib import admin

# Register your models here.
from django.contrib import admin
from .models import BookInfo
from .models import HeroInfo


class HeroInfoInline(admin.StackedInline):
    model=HeroInfo
    extra=3

class BookInfoAdmin(admin.ModelAdmin):
    list_display=['pk', 'btitle', 'bpub_date']
    list_filter = ['bpub_date']
    search_fields = ['btitle']
    list_per_page = 10
    inlines=[HeroInfoInline]



admin.site.register(BookInfo, BookInfoAdmin)
admin.site.register(HeroInfo)



