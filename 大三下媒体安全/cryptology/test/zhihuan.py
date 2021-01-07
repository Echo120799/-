import numpy as np
letter1=[]#小写字母表
letter2=[]#大写字母表
#生成小写字母表
for a in range(97,123):
    letter1.append(chr(a))
print(letter1)
#生成（大写）置换表
for a in range(65,90):
    letter2.append(chr(a))
#print(letter2)
key=np.random.permutation(letter2)#置换表
print("随机生成的置换表为：",key)
#加密
def encrypt():
    plain=input("请输入需要加密的文字（小写）：")#输入要加密的文字
    cipher=[]#密文
    for m in plain:
        if m in letter1:
            n=key[letter1.index(m)]
            cipher.append(n)
    cipher_word=''.join(cipher)#列表元素合并成字符串
    print("加密后的文字为：",cipher_word)
#解密
def decrypt():
    cipher=input("请输入需要解密的文字（大写）：")#输入要解密的文字
    plain=[]#明文
    for m in cipher:
        if m in key:
            n=letter1[key.tolist().index(m)]
            plain.append(n)
    plain_word=''.join(plain)#列表元素合并成字符串
    print("解密后的文字为：",plain_word)
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


