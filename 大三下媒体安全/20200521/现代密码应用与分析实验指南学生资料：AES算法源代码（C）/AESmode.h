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
	resbuffer:Դ��������ַ
	desbuffer:Ŀ�Ļ�������ַ
	key:��Կ��ŵ�ַ��Ϊһ��32λ�޷����ַ�����
	iv:�����ó�ʼ������飬Ϊһ��16�ֽ��޷����ַ�����
	cryptlabel:���ܻ��ǽ��ܵ�ָʾ����,����ָʾֵΪ1������ָʾֵΪ2
	codelabel:�ú��ֱ���ģʽ���ӽ������ݣ���ѡCBC(ָʾֵΪ1����OFB(ָʾֵΪ2)��Ĭ��ΪCBCģʽ
	klen:�ӽ�����Կ���ȣ���ѡ128λ��192λ��256λ��Ĭ��λ128λ
*/
int AES(unsigned char *resbuffer,unsigned char *desbuffer,unsigned long buflen, u1byte *key,u1byte *iv,
		u2byte cryptlabel,u2byte codelabel,u4byte klen);

#ifdef __cplusplus
}
#endif

#endif
