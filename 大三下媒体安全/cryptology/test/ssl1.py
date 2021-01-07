
import rsa

(pubkey, privkey) = rsa.newkeys(1024)

pub = pubkey.save_pkcs1()
pri = privkey.save_pkcs1()

file = open("plaintext.txt")
message = file.read()
print("原文为：",message)
message=bytes(message,encoding='utf8')
# 用公钥加密、再用私钥解密
crypto = rsa.encrypt(message, pubkey)
print("加密后文字为：",crypto)
message1 = rsa.decrypt(crypto, privkey)
message1=str(message1,encoding='utf8')
print("解密后文字为：",message1)
