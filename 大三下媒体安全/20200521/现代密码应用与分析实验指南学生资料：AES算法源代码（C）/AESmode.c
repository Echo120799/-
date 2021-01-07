#include "AESmode.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define BlkLen	16 /*16bytes*/
u4byte  k_len;//密钥长度
u4byte  e_key[64];//加密扩展密钥
u4byte  d_key[64];//解密扩展密钥

u1byte  *Key;//初始密钥
u1byte  *pIV;
u1byte  IV[16];//密码编码初始数组
u1byte * InBlock;//输入块
u1byte * OutBlock;//输出块
u1byte  tmpBlock[16];

u2byte  CodeLabel;//编码类型
u2byte  CryptLabel;//使用加解密类型
u2byte  Cp;//循环变量

unsigned char *ResBuffer;//源文件路径
unsigned char *DesBuffer;//目的文件路径
unsigned long BufLen;

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
	resfilename:源文件路径地址
	desfilename:目的文件路径地址
	key:密钥存放地址，为一个32字节无符号字符数组
	iv:加密用初始随机数组，为一个16字节无符号字符数组
	cryptlabel:加密还是解密的指示变量,加密指示值为1，解密指示值为2
	codelabel:用何种编码模式来加解密数据，可选CBC(指示值为1）或OFB(指示值为2)，默认为CBC模式
	klen:加解密密钥长度，可选128位、192位和256位，默认位128位
*/

int AES(unsigned char *resbuffer,unsigned char *desbuffer,unsigned long buflen, u1byte *key,u1byte *iv,
		u2byte cryptlabel,u2byte codelabel,u4byte klen)
{
	int i;
	int ret=0;

	CryptLabel=cryptlabel;
	CodeLabel=codelabel;
	k_len=klen;
	ResBuffer=resbuffer;
	DesBuffer=desbuffer;
	BufLen=buflen;
	Key=(u1byte*)key;
	for (i=0;i<16;i++)	IV[i]=iv[i];
  // printf("this is the %d times \n",ParaValidate());
	if(ParaValidate())
	{
	 
		if(CryptLabel==1)
		{
			set_key(Key,k_len);
		
		switch((int)codelabel)
		{
		case 1: CBCEcrProcess16Byte();break;
		case 2: OFBEcrProcess16Byte();break;
		case 3: CFBEcrProcess16Byte();break;
		case 5: ECBEcrProcess16Byte();break;
		}
		}
		else
		{
		set_key(Key,k_len);
		switch(CodeLabel)
		{
		case 1: CBCDcrProcess16Byte();break;
		case 2: OFBDcrProcess16Byte();break;
		case 3: CFBDcrProcess16Byte();break;
		case 5: ECBDcrProcess16Byte();break;
		}
		}
	}
	else
		ret=1;

	return ret;
}
	
int ParaValidate()//参数合法性验证函数
{
	if(!(ResBuffer)||!(DesBuffer))
	{
#ifdef _DEBUG
		printf("[CRYPT] res buffer or des buffer point is failed.\n");
#endif
		return false;
	}
	else 
		if(CryptLabel!=1&&CryptLabel!=2)
		{
#ifdef _DEBUG
			printf("[CRYPT] encrypt or decrypt selection is failed, must be 1 or 2, now is %d.\n",CryptLabel);
#endif
			return false;
		}
		else
			if(CodeLabel!=1&&CodeLabel!=2&&CodeLabel!=3&&CodeLabel!=5)
			{
#ifdef _DEBUG
				printf("[CRYPT] encrypt or decrypt mode is failed, must be 1 ~ 5, now is %d.\n",CodeLabel);
#endif
				return false;
			}
			else
				if(k_len!=128&&k_len!=192&&k_len!=256)
				{
#ifdef _DEBUG
					printf("[CRYPT] key length is failed, must be 128,192 or 256, now is %d.\n",k_len);
#endif
					return false;
				}
				else
					return true;
}


void CBCEcrProcess16Byte()//CBC编码处理加密数据函数
{	
	u1byte tmpbuf[BlkLen];
	unsigned long BufLeninBlks=(unsigned long)floor(BufLen/BlkLen)*BlkLen;
	unsigned long i;

	InBlock=ResBuffer;
	OutBlock=DesBuffer;

	while (InBlock<ResBuffer+BufLeninBlks)
	{
		CBCEncrypt();
		InBlock+=BlkLen;
		OutBlock+=BlkLen;
	}
	//deal with the last block whose length is not the multiple of BlkLen
	if (BufLeninBlks<BufLen)
	{
		
		encrypt(OutBlock-BlkLen,tmpbuf);
		for (i=0; i<BufLen-BufLeninBlks; i++)
			OutBlock[i]=InBlock[i]^tmpbuf[i];
	}
}



void CBCDcrProcess16Byte()//CBC编码处理解密数据函数
{	
	u1byte tmpbuf[BlkLen];
	unsigned long BufLeninBlks=(unsigned long)floor(BufLen/BlkLen)*BlkLen;
	unsigned long i;

	InBlock=ResBuffer;
	OutBlock=DesBuffer;

	while (InBlock<ResBuffer+BufLeninBlks)
	{
		CBCDecrypt();
		InBlock+=BlkLen;
		OutBlock+=BlkLen;
	}
	//deal with the last block whose length is not the multiple of BlkLen
	if (BufLeninBlks<BufLen)
	{
		encrypt(InBlock-BlkLen,tmpbuf);
		for (i=0; i<BufLen-BufLeninBlks; i++)
			OutBlock[i]=InBlock[i]^tmpbuf[i];
	}
}



void OFBEcrProcess16Byte()//OFB编码处理加密数据函数
{	
	unsigned long BufLeninBlks=(unsigned long)floor(BufLen/BlkLen)*BlkLen;
	unsigned long i;

	InBlock=ResBuffer;
	OutBlock=DesBuffer;

	while (InBlock<ResBuffer+BufLeninBlks)
	{
		OFBEncrypt();
		InBlock+=BlkLen;
		OutBlock+=BlkLen;
	}
	//deal with the last block whose length is not the multiple of BlkLen
	if (BufLeninBlks<BufLen)
	{
		encrypt(IV,IV);
		for (i=0; i<BufLen-BufLeninBlks; i++)
			OutBlock[i]=IV[i]^InBlock[i];
	}
}


void OFBDcrProcess16Byte()//OFB编码处理解密数据函数
{	
	unsigned long BufLeninBlks=(unsigned long)floor(BufLen/BlkLen)*BlkLen;
	unsigned long i;

	InBlock=ResBuffer;
	OutBlock=DesBuffer;

	while (InBlock<ResBuffer+BufLeninBlks)
	{
		OFBEncrypt();
		InBlock+=BlkLen;
		OutBlock+=BlkLen;
	}
	//deal with the last block whose length is not the multiple of BlkLen
	if (BufLeninBlks<BufLen)
	{
		encrypt(IV,IV);
		for (i=0; i<BufLen-BufLeninBlks; i++)
			OutBlock[i]=IV[i]^InBlock[i];
	}
}



void CBCEncrypt()//CBC编码加密函数
{
	for(Cp=0;Cp<16;Cp++)	
		tmpBlock[Cp]=IV[Cp]^InBlock[Cp];
	encrypt(tmpBlock,OutBlock);
	for(Cp=0;Cp<16;Cp++)	
		IV[Cp]=OutBlock[Cp];
}


void CBCDecrypt()//CBC编码解密函数
{
	decrypt(InBlock,OutBlock);
	for(Cp=0;Cp<16;Cp++)	
		OutBlock[Cp]=IV[Cp]^OutBlock[Cp];
	for(Cp=0;Cp<16;Cp++)	
		IV[Cp]=InBlock[Cp];
}


void OFBEncrypt()//OFB编码加密函数
{
	encrypt(IV,IV);
	for(Cp=0;Cp<16;Cp++)
		OutBlock[Cp]=IV[Cp]^InBlock[Cp];
}


void OFBDecrypt()//OFB编码解密函数
{
	OFBEncrypt();
}


void ECBEcrProcess16Byte()//ECB编码处理加密数据函数
{	
	u1byte tmpbuf[BlkLen];
	unsigned long BufLeninBlks=(unsigned long)floor(BufLen/BlkLen)*BlkLen;
	unsigned long i;

	InBlock=ResBuffer;
	OutBlock=DesBuffer;
	
	while (InBlock<ResBuffer+BufLeninBlks)
	{
		ECBEncrypt();
		InBlock+=BlkLen;
		OutBlock+=BlkLen;
	}

	//deal with the last block whose length is not the multiple of BlkLen
	if (BufLeninBlks<BufLen)
	{
		/*for (i=0; i<BufLen-BufLeninBlks; i++)
			tmpbuf[i]=InBlock[i];
		encrypt(tmpbuf,OutBlock);*/
		encrypt(OutBlock-BlkLen,tmpbuf);
		for (i=0; i<BufLen-BufLeninBlks; i++)
			OutBlock[i]=InBlock[i]^tmpbuf[i];
	}
}


void ECBDcrProcess16Byte()//ECB编码处理解密数据函数
{	
	u1byte tmpbuf[BlkLen];
	unsigned long BufLeninBlks=(unsigned long)floor(BufLen/BlkLen)*BlkLen;
	unsigned long i;

	InBlock=ResBuffer;
	OutBlock=DesBuffer;

	while (InBlock<ResBuffer+BufLeninBlks)
	{
		ECBDecrypt();
		InBlock+=BlkLen;
		OutBlock+=BlkLen;
	}
	//deal with the last block whose length is not the multiple of BlkLen
	if (BufLeninBlks<BufLen)
	{
		/*for (i=0; i<BufLen-BufLeninBlks; i++)
		tmpbuf[i]=InBlock[i];
		decrypt(tmpbuf,OutBlock);*/
		encrypt(InBlock-BlkLen,tmpbuf);
		for (i=0; i<BufLen-BufLeninBlks; i++)
		OutBlock[i]=InBlock[i]^tmpbuf[i];
	}
}	

void CFBEcrProcess16Byte()//CFB编码处理加密数据函数
{	
	unsigned long BufLeninBlks=(unsigned long)floor(BufLen/BlkLen)*BlkLen;
	unsigned long i;

	InBlock=ResBuffer;
	OutBlock=DesBuffer;

	while (InBlock<ResBuffer+BufLeninBlks)
	{
		CFBEncrypt();
		InBlock+=BlkLen;
		OutBlock+=BlkLen;
	}
	//deal with the last block whose length is not the multiple of BlkLen
	if (BufLeninBlks<BufLen)
	{
		encrypt(IV,IV);
		for (i=0; i<BufLen-BufLeninBlks; i++)
			OutBlock[i]=IV[i]^InBlock[i];
	}
}


void CFBDcrProcess16Byte()//CFB编码处理解密数据函数
{	
	unsigned long BufLeninBlks=(unsigned long)floor(BufLen/BlkLen)*BlkLen;
	unsigned long i;

	InBlock=ResBuffer;
	OutBlock=DesBuffer;

	while (InBlock<ResBuffer+BufLeninBlks)
	{
		CFBDecrypt();
		InBlock+=BlkLen;
		OutBlock+=BlkLen;
	}
	//deal with the last block whose length is not the multiple of BlkLen
	if (BufLeninBlks<BufLen)
	{
		encrypt(IV,IV);
		for (i=0; i<BufLen-BufLeninBlks; i++)
			OutBlock[i]=IV[i]^InBlock[i];
	}
}



void ECBEncrypt()//ECB编码加密函数
{
	encrypt(InBlock,OutBlock);
	
}


void ECBDecrypt()//ECB编码解密函数
{
	decrypt(InBlock,OutBlock);
}


void CFBEncrypt()//CFB编码加密函数
{
	encrypt(IV,IV);
	for(Cp=0;Cp<16;Cp++)	
	{OutBlock[Cp]=IV[Cp]^InBlock[Cp];
	IV[Cp]=OutBlock[Cp];}
}
	

void CFBDecrypt()//CFB编码解密函数
{
	encrypt(IV,IV);
	for(Cp=0;Cp<16;Cp++)
	{OutBlock[Cp]=IV[Cp]^InBlock[Cp];
	 IV[Cp]=InBlock[Cp];
	}
}
