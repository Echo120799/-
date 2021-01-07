def strEncrypt(first,second,key,result):
    result = []
    for x in range(4):

        m=(ord(second[x])+ord(key[x]))%26+97
        temp = ord(first[x]) ^ m
        temp=temp%26+97
        result += chr(temp)
    return result


def Encrypt(word,key,cipher):
    #对要加密的内容进行分组，8个字节一组
    n = int(len(word) / 8)
    cipher=[]
    result=[]
    for x in range(n):
        t = [word[x * 8], word[x * 8 + 1], word[x * 8 + 2], word[x * 8 + 3], word[x * 8 + 4], word[x * 8 + 5],
             word[x * 8 + 6], word[x * 8 + 7]]
        L = t[:4]
        R = t[4:]
        #左边换成右边，右边进行enigma加密
        temp=R
        R=strEncrypt(L,R,key,result)
        L=temp
        cipher +=L+R
    return cipher



if __name__ == '__main__':
    word=input("请输入要加密的明文（字符个数为8的整数倍）：")
    word_wrong=input("请输入要改动的明文（字符个数为8的整数倍，和正确明文只差一比特）：")
    n=int(len(word)/8)
    key = input("请输入密钥：")
    #对密钥进行分组，4个字节一组
    keylist=[]
    for x in range(len(key)//4):
        t = [key[x * 4], key[x * 4 + 1], key[x * 4 + 2], key[x * 4 + 3]]
        keylist.append(t)
    cipher = []
    cipher_wrong = []
    for x in range(len(key)//4):
        cipher=Encrypt(word, keylist[x], cipher)
        cipher_wrong=Encrypt(word_wrong, keylist[x], cipher_wrong)
        print("第%d轮正确："%(x+1),cipher)
        print("第%d轮错误："%(x+1),cipher_wrong)

        h=0
        for b in range(len(cipher)):
            if cipher[b]!=cipher_wrong[b]:
                h=h+1#错误字符个数
                '''
                p=bin(ord(cipher[b]))
                q=bin(ord(cipher_wrong[b]))
                for i in range(len(p)):
                    if p[i]!=q[i]:
                        s=s+1
                '''

        xxx = h / len(cipher)
        print("第%d轮雪崩率为：" % (x + 1), "%.2f%%" % (xxx * 100))
        word=cipher
        word_wrong=cipher_wrong









