import base64

from Crypto.Cipher import AES
from Crypto.Cipher import DES

#补足字符串长度为16的倍数
def add_to_16(s):
    while len(s) % 16 != 0:
        s += '\0'
    return str.encode(s)

def AESEncrypt():
    key=input("请输入密钥（密钥长度必须为16、24或32位）：")
    p=input("请选择加密模式（1.ECB 2.CBC 3.CFB 4.OFB）：")
    iv = key.encode("utf-8")
    aes_cipher = AES.new(str.encode(key), AES.MODE_ECB)
    aes_plain = AES.new(str.encode(key), AES.MODE_ECB)
    if int(p)==1:
        aes_cipher = AES.new(str.encode(key),AES.MODE_ECB)
        aes_plain =AES.new(str.encode(key),AES.MODE_ECB)
    elif int(p)==2:
        aes_cipher = AES.new(str.encode(key),AES.MODE_CBC,iv)
        aes_plain =AES.new(str.encode(key),AES.MODE_CBC,iv)
    elif int(p)==3:
        aes_cipher = AES.new(str.encode(key), AES.MODE_CFB, iv)
        aes_plain = AES.new(str.encode(key), AES.MODE_CFB, iv)
    elif int(p)==4:
        aes_cipher = AES.new(str.encode(key), AES.MODE_OFB, iv)
        aes_plain = AES.new(str.encode(key), AES.MODE_OFB, iv)
    else:
        print("输入错误！")
    encrypted_text = str(base64.encodebytes(aes_cipher.encrypt(add_to_16(datastr))), encoding='utf8').replace('\n', '')  # 加密
    decrypted_text = str(
        aes_plain.decrypt(base64.decodebytes(bytes(encrypted_text, encoding='utf8'))).rstrip(b'\0').decode("utf8"))  # 解密
    f1 = open("encrypt.txt", "w")
    print(encrypted_text, file=f1)#加密结果保存到encrypt。txt
    f1.close()
    f2 = open("decrypt.txt", "w")
    print(decrypted_text, file=f2)#解密结果保存到encrypt。txt
    f2.close()

def DESEncrypt():
    key = input("请输入密钥(数字或字母，共8位)：")
    #keybytes=bytes(key,encoding="utf-8")
    p = input("请选择加密模式（1.ECB 2.CBC 3.CFB 4.OFB）：")
    iv = key.encode("utf-8")
    des_cipher = DES.new(str.encode(key), DES.MODE_ECB)
    des_plain = DES.new(str.encode(key), DES.MODE_ECB)
    if int(p) == 1:
        des_cipher = DES.new(str.encode(key), DES.MODE_ECB)
        des_plain = DES.new(str.encode(key), DES.MODE_ECB)
    elif int(p) == 2:
        des_cipher = DES.new(str.encode(key), DES.MODE_CBC, iv)
        des_plain = DES.new(str.encode(key), DES.MODE_CBC, iv)
    elif int(p) == 3:
        des_cipher = DES.new(str.encode(key), DES.MODE_CFB, iv)
        des_plain = DES.new(str.encode(key), DES.MODE_CFB, iv)
    elif int(p) == 4:
        des_cipher = DES.new(str.encode(key), DES.MODE_OFB, iv)
        des_plain = DES.new(str.encode(key), DES.MODE_OFB, iv)
    else:
        print("输入错误！")
    encrypted_text = str(base64.encodebytes(des_cipher.encrypt(add_to_16(datastr))), encoding='utf8').replace('\n',
                                                                                                              '')  # 加密
    decrypted_text = str(
        des_plain.decrypt(base64.decodebytes(bytes(encrypted_text, encoding='utf8'))).rstrip(b'\0').decode(
            "utf8"))  # 解密
    f1 = open("encrypt.txt", "w")
    print(encrypted_text, file=f1)  # 加密结果保存到encrypt。txt
    f1.close()
    f2 = open("decrypt.txt", "w")
    print(decrypted_text, file=f2)  # 解密结果保存到encrypt。txt
    f2.close()

if __name__ == '__main__':
    # 读取ts文件
    ts_file = open("test.ts", "rb")
    data = ts_file.read()
    datastr = str(data)
    ts_file.close()
    f3 = open("source.txt", "w")
    print(datastr, file=f3)
    f3.close()
    a=input("请选择加密方式（1.DES 2.AES）：")
    if int(a)==1:
        DESEncrypt()
    elif int(a)==2:
        AESEncrypt()
    else:
        print("输入错误！")
