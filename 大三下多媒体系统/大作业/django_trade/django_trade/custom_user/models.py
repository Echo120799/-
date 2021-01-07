from django.db import models
from django.contrib.auth.models import AbstractUser
# Create your models here.


class UserProfile(AbstractUser):
    sex = models.IntegerField(verbose_name="性别", choices=((0, '男'), (1, '女')), default=0)
    mobile = models.CharField(max_length=11, null=True, blank=True, verbose_name = "手机号")
    image = models.ImageField(upload_to="img", default="img/default.jpg", max_length=100)
    address = models.CharField(default="", max_length=100)
    interest = models.CharField(max_length=255, null=True)
    class Meta:
        verbose_name = "用户信息"
        verbose_name_plural = verbose_name

    def __unicode__(self):
        return self.username