a=1
while a<10:
    b=1
    while b<=a:
        print("%d*%d=%d"%(b,a,b*a),"",end='')
        b=b+1
    print()
    a=a+1