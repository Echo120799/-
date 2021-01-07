#ifndef __AESMODE_H__
#define __AESMODE_H__

#include "AES.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef true
#define true	1
#endif
#ifndef false
#define false	0
#endif

//cipher mode
#define AES_CBC	1
#define AES_OFB	2
#define AES_CFB	3
#define AES_CTR	4
#define AES_ECB	5


//encrypt and decrypt
#define ENCRYPT	1
#define DECRYPT	2

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GenerateKey();//密钥生成函数
int ParaValidate();//参数合法性验证函数

void CBCEcrProcess16Byte();//CBC编码处理加密数据函数
void OFBEcrProcess16Byte();//OFB编码处理加密数据函数
void CBCDcrProcess16Byte();//CBC编码处理解密数据函数
void OFBDcrProcess16Byte();//OFB编码处理解密数据函数

void CBCEncrypt();//CBC编码加密函数
void OFBEncrypt();//OFB编码加密函数
void CBCDecrypt();//CBC编码解密函数
void OFBDecrypt();//OFB编码解密函数

void ECBEcrProcess16Byte();//ECB编码处理加密数据函数
void CFBEcrProcess16Byte();//CFB编码处理加密数据函数
void ECBDcrProcess16Byte();//ECB编码处理解密数据函数
void CFBDcrProcess16Byte();//CFB编码处理解密数据函数

void ECBEncrypt();//ECB编码加密函数
void CFBEncrypt();//CFB编码加密函数
void ECBDecrypt();//ECB编码解密函数
void CFBDecrypt();//CFB编码解密函数

/* 接口定义：
	resbuffer:源缓冲区地址
	desbuffer:目的缓冲区地址
	key:密钥存放地址，为一个32位无符号字符数组
	iv:加密用初始随机数组，为一个16字节无符号字符数组
	cryptlabel:加密还是解密的指示变量,加密指示值为1，解密指示值为2
	codelabel:用何种编码模式来加解密数据，可选CBC(指示值为1）或OFB(指示值为2)，默认为CBC模式
	klen:加解密密钥长度，可选128位、192位和256位，默认位128位
*/
int AES(unsigned char *resbuffer,unsigned char *desbuffer,unsigned long buflen, u1byte *key,u1byte *iv,
		u2byte cryptlabel,u2byte codelabel,u4byte klen);

#ifdef __cplusplus
}
#endif

#endif
