import random
a=input("请输入：剪刀（0）石头（1）布（2）")
b=random.randint(0,2)
a=int(a)
if a-b==1 or a-b==-2:
    print("你赢了")
elif a-b==0:
    print("平局")
else :
    print("你输了")