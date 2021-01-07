from django.contrib import admin                                     #导入admin模板
from .models import Item, OrderModel,CommentModel, CommentDetailModel#导入数据模型
from django.forms import TextInput, Textarea
from django.db import models                                         #导入数据库
from django.utils.html import format_html
# Register your models here.



'''商品后台管理'''
class GoodsAdmin(admin.ModelAdmin):
    #列表页面显示商品信息
    list_display = ('classification', 'name', 'description', 'has_sale', 'show_image', 'price', 'counts', 'create_at')
    #按商品名检索
    search_fields = ('name',)
    #过滤掉的信息
    list_filter = ('classification', 'create_at')
    #分页的每页数量
    list_per_page = 20
    #按照创建时间排序
    ordering = ('-create_at',)
    #可编辑的信息
    list_editable = ('name', 'description')
    formfield_overrides = {
        models.CharField: {'widget': TextInput(attrs={'size': '20'})},
        models.TextField: {'widget': Textarea(attrs={'rows': 3, 'cols': 40})},
    }

    def show_image(self, obj):
        """自定义列表字段"""
    show_image.short_description = '图片'





class OrderModelAdmin(admin.ModelAdmin):
    list_display = ('order_id', 'good_item', 'count',
                    'status', 'address', 'phone', 'user', 'create_at')
    search_fields = ('user__username',)
    list_filter = ('create_at',)
    list_per_page = 20
    ordering = ('-create_at',)
    list_editable = ('status',)
    formfield_overrides = {
        models.CharField: {'widget': TextInput(attrs={'size': '20'})},
        models.TextField: {'widget': Textarea(attrs={'rows': 3, 'cols': 30})},
    }




class CommentModelAdmin(admin.ModelAdmin):
    list_display = ('description', 'user', 'create_at')
    class Meta:
        verbose_name = '留言'
        verbose_name_plural = verbose_name



class CommentDetailModelAdmin(admin.ModelAdmin):
    list_display = ('user', 'description','show_image', 'order')

    def show_image(self, obj):
        """自定义列表字段"""
        return format_html("<a href='{0}'><img src='{0}' style='width:50px;height:50px;'></img> </a>".format(obj.pic.url))
    show_image.short_description = '图片'

admin.site.site_header = '二手交易管理后台'
admin.site.site_title = '二手交易管理后台'
admin.site.register(Item, GoodsAdmin)
admin.site.register(OrderModel, OrderModelAdmin)
admin.site.register(CommentModel, CommentModelAdmin)
admin.site.register(CommentDetailModel, CommentDetailModelAdmin)


