#include "AESmode.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define BlkLen	16 /*16bytes*/
u4byte  k_len;//��Կ����
u4byte  e_key[64];//������չ��Կ
u4byte  d_key[64];//������չ��Կ

u1byte  *Key;//��ʼ��Կ
u1byte  *pIV;
u1byte  IV[16];//��������ʼ����
u1byte * InBlock;//�����
u1byte * OutBlock;//�����
u1byte  tmpBlock[16];

u2byte  CodeLabel;//��������
u2byte  CryptLabel;//ʹ�üӽ�������
u2byte  Cp;//ѭ������

unsigned char *ResBuffer;//Դ�ļ�·��
unsigned char *DesBuffer;//Ŀ���ļ�·��
unsigned long BufLen;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GenerateKey();//��Կ���ɺ���
int ParaValidate();//�����Ϸ�����֤����

void CBCEcrProcess16Byte();//CBC���봦��������ݺ���
void OFBEcrProcess16Byte();//OFB���봦��������ݺ���
void CBCDcrProcess16Byte();//CBC���봦��������ݺ���
void OFBDcrProcess16Byte();//OFB���봦��������ݺ���

void CBCEncrypt();//CBC������ܺ���
void OFBEncrypt();//OFB������ܺ���
void CBCDecrypt();//CBC������ܺ���
void OFBDecrypt();//OFB������ܺ���

void ECBEcrProcess16Byte();//ECB���봦��������ݺ���
void CFBEcrProcess16Byte();//CFB���봦��������ݺ���
void ECBDcrProcess16Byte();//ECB���봦��������ݺ���
void CFBDcrProcess16Byte();//CFB���봦��������ݺ���

void ECBEncrypt();//ECB������ܺ���
void CFBEncrypt();//CFB������ܺ���
void ECBDecrypt();//ECB������ܺ���
void CFBDecrypt();//CFB������ܺ���

/* �ӿڶ��壺
	resfilename:Դ�ļ�·����ַ
	desfilename:Ŀ���ļ�·����ַ
	key:��Կ��ŵ�ַ��Ϊһ��32�ֽ��޷����ַ�����
	iv:�����ó�ʼ������飬Ϊһ��16�ֽ��޷����ַ�����
	cryptlabel:���ܻ��ǽ��ܵ�ָʾ����,����ָʾֵΪ1������ָʾֵΪ2
	codelabel:�ú��ֱ���ģʽ���ӽ������ݣ���ѡCBC(ָʾֵΪ1����OFB(ָʾֵΪ2)��Ĭ��ΪCBCģʽ
	klen:�ӽ�����Կ���ȣ���ѡ128λ��192λ��256λ��Ĭ��λ128λ
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
	
int ParaValidate()//�����Ϸ�����֤����
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


void CBCEcrProcess16Byte()//CBC���봦��������ݺ���
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



void CBCDcrProcess16Byte()//CBC���봦��������ݺ���
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



void OFBEcrProcess16Byte()//OFB���봦��������ݺ���
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


void OFBDcrProcess16Byte()//OFB���봦��������ݺ���
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



void CBCEncrypt()//CBC������ܺ���
{
	for(Cp=0;Cp<16;Cp++)	
		tmpBlock[Cp]=IV[Cp]^InBlock[Cp];
	encrypt(tmpBlock,OutBlock);
	for(Cp=0;Cp<16;Cp++)	
		IV[Cp]=OutBlock[Cp];
}


void CBCDecrypt()//CBC������ܺ���
{
	decrypt(InBlock,OutBlock);
	for(Cp=0;Cp<16;Cp++)	
		OutBlock[Cp]=IV[Cp]^OutBlock[Cp];
	for(Cp=0;Cp<16;Cp++)	
		IV[Cp]=InBlock[Cp];
}


void OFBEncrypt()//OFB������ܺ���
{
	encrypt(IV,IV);
	for(Cp=0;Cp<16;Cp++)
		OutBlock[Cp]=IV[Cp]^InBlock[Cp];
}


void OFBDecrypt()//OFB������ܺ���
{
	OFBEncrypt();
}


void ECBEcrProcess16Byte()//ECB���봦��������ݺ���
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


void ECBDcrProcess16Byte()//ECB���봦��������ݺ���
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

void CFBEcrProcess16Byte()//CFB���봦��������ݺ���
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


void CFBDcrProcess16Byte()//CFB���봦��������ݺ���
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



void ECBEncrypt()//ECB������ܺ���
{
	encrypt(InBlock,OutBlock);
	
}


void ECBDecrypt()//ECB������ܺ���
{
	decrypt(InBlock,OutBlock);
}


void CFBEncrypt()//CFB������ܺ���
{
	encrypt(IV,IV);
	for(Cp=0;Cp<16;Cp++)	
	{OutBlock[Cp]=IV[Cp]^InBlock[Cp];
	IV[Cp]=OutBlock[Cp];}
}
	

void CFBDecrypt()//CFB������ܺ���
{
	encrypt(IV,IV);
	for(Cp=0;Cp<16;Cp++)
	{OutBlock[Cp]=IV[Cp]^InBlock[Cp];
	 IV[Cp]=InBlock[Cp];
	}
}
