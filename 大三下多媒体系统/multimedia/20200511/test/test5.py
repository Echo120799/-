a=input("请输入字符串：")
dec={}
for x in a:
    if x in dec:
        dec[x]=dec[x]+1
    else:dec[x]=1
print(dec)


