from django.db import models
from custom_user.models import UserProfile


# Create your models here.
class Item(models.Model):

    classification = models.IntegerField(choices = ((1, "家电"), (2, "衣服"),
                                                    (3, "百货"), (4, "文具"), (5, "其他")),
                                         verbose_name = "分类")
    name = models.CharField(verbose_name = "名称", max_length = 256)
    description = models.TextField(verbose_name = "描述", blank = True, null = True)
    has_sale = models.IntegerField(verbose_name = '付款人数', default = 0)
    pic = models.ImageField(upload_to = "img", verbose_name = "图片")
    price = models.FloatField(verbose_name = "价格", max_length = 100)
    counts = models.IntegerField(verbose_name = "库存",db_column='counts')
    phone = models.CharField(verbose_name="卖家手机号", max_length=11)
    create_at = models.DateTimeField(verbose_name = "创建时间", auto_now_add = True, auto_created = True)

    class Meta:
        verbose_name = '物品'
        verbose_name_plural = verbose_name

    def __str__(self):
        return self.name


class OrderModel(models.Model):
    """
    每购买一次商品的记录
    """
    order_id = models.CharField(verbose_name = "订单编号", max_length = 128, unique = True)
    good_item = models.ForeignKey(Item, verbose_name = "商品", related_name = "orders", on_delete=models.CASCADE)
    status = models.IntegerField(verbose_name = "状态", choices = ((-1, "支付失败"), (1, "已支付"), (3, "已发货")), default=0)
    count = models.IntegerField(verbose_name = "购买数量")
    price = models.FloatField(verbose_name = "总价格")
    address = models.CharField(verbose_name = "交易地址", max_length = 256, default = '')
    phone = models.CharField(verbose_name = "联系人手机号", max_length = 11)
    create_at = models.DateTimeField(verbose_name = "购买时间", auto_now_add = True)
    user = models.ForeignKey(UserProfile, related_name="orders", on_delete=models.CASCADE)

    class Meta:
        verbose_name = '购买记录'
        verbose_name_plural = verbose_name
        db_table = "market_order"



class CommentModel(models.Model):
    user = models.CharField(verbose_name = "评论人", max_length = 256,default = "游客")
    description = models.TextField(verbose_name = "描述", blank = False)
    create_at = models.DateTimeField(verbose_name = "创建时间", auto_now_add = True)

    class Meta:
        verbose_name = '留言'
        verbose_name_plural = verbose_name
        ordering = ['-create_at']

    def __str__(self):
        return self.description


class CommentDetailModel(models.Model):
    user = models.ForeignKey(UserProfile, related_name="comment", on_delete=models.CASCADE)
    pic = models.ImageField(upload_to = "img", verbose_name = "图片")
    description = models.TextField(verbose_name = "描述", blank = False)
    create_at = models.DateTimeField(verbose_name = "创建时间", auto_now_add = True)
    order = models.ForeignKey(OrderModel, related_name="comment", on_delete=models.CASCADE)

    class Meta:
        verbose_name = '评论'
        verbose_name_plural = verbose_name
        ordering = ['-create_at']

    def __str__(self):
        return self.description




