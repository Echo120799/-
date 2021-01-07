#加密
def encrypt():
    word=input("请输入要加密的文字：")
    first=[]
    second=[]
    for x in word:
        if word.index(x)%2==0:
            first.append(x)
        else:
            second.append(x)
    print("加密后的文字为：",''.join(first)+''.join(second))
#解密
def decrypt():
    word=input("请输入要解密的文字：")
    l=len(word)
    first = []
    second = []
    plain=[]#明文
    for x in word:
        if word.index(x)<=round(l/2):
            first.append(x)
        else:
            second.append(x)
    for a in range(l):
        if a%2==0:
            plain.append(first[a//2])
        else:
            plain.append(second[a//2])
    print("解密后的文字是：",''.join(plain))

while True:
    choice=input("请选择操作（1.加密  2.解密  3.退出）：")
    if int(choice)==1:
        encrypt()
    elif int(choice)==2:
        decrypt()
    elif int(choice)==3:
        break
    else:
        print("输入无效！")