from django.conf.urls import url
from . import views

urlpatterns = [
    url(r'^$',views.cart),
    url(r'^add/([0-9]+)/$',views.add,name="add"),
]