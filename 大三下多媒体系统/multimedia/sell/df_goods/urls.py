from django.conf.urls import url
from . import views

urlpatterns = [
    url(r'^$',views.index),
    url(r'^list/([0-9]+)/$',views.list,name="list"),
    url(r'^([0-9]+)/$',views.detail,name="detail"),

]