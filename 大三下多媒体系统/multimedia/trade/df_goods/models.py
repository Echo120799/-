from django.db import models

# Create your models here.
class TypeInfo(models.Model):
    tname=models.CharField(max_length=20)
    def __str__(self):
        return self.tname

class GoodInfo(models.Model):
    gname=models.CharField(max_length=20)
    gpic= models.ImageField(upload_to='goods')
    gprice=models.DecimalField(max_digits=5,decimal_places=2)
    gtext=models.CharField(max_length=140)
    gtype=models.ForeignKey(TypeInfo)
    def __str__(self):
        return self.gname




