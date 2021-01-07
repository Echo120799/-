#ifndef __AES_H__
#define __AES_H__

/* 1.�����������Ͷ���*/

typedef unsigned char   u1byte; /* 8λ�޷����ַ��� */
typedef unsigned short  u2byte; /* 16λ�޷�������  */
typedef unsigned long   u4byte; /* 32λ�޷���������*/
typedef signed char     s1byte; /* 8λ�����ַ���   */
typedef signed short    s2byte; /* 16λ����������  */
typedef signed long     s4byte; /* 32λ����������  */

#ifdef WIN32
#define	LITTLE_ENDIAN
#endif

#ifdef __cplusplus
extern "C" {
#endif

void set_key(const u1byte key[], const u4byte key_bits);
void encrypt(const u1byte in_blk[16], u1byte out_blk[16]);
void decrypt(const u1byte in_blk[16], u1byte out_blk[16]);

#ifdef __cplusplus
}
#endif
/* 2.Ϊ���ٲ�������Ļ�����             */

/* 32λֵѭ����λ                       */

#ifdef _MSC_VER

#  include <stdlib.h>
#  pragma intrinsic(_lrotr,_lrotl)
#  define rotr(x,n) _lrotr(x,n)
#  define rotl(x,n) _lrotl(x,n)

#else

#define rotr(x,n)   (((x) >> ((int)(n))) | ((x) << (32 - (int)(n))))
#define rotl(x,n)   (((x) << ((int)(n))) | ((x) >> (32 - (int)(n))))

#endif

/* 32λ����λ˳��ת��                          */

#define bswap(x)    (rotl(x, 8) & 0x00ff00ff | rotr(x, 8) & 0xff00ff00)

/* ��32λ�ı�����ȡ�ֽ�    */ 

#define byte(x,n)   ((u1byte)((x) >> (8 * n)))

/* �Ի���˳����������һ��32λֵ				*/

#ifdef	LITTLE_ENDIAN

#define	u4byte_in(x)		(*(u4byte*)(x))
#define	u4byte_out(x, v)	(*(u4byte*)(x) = (v)) 

#else

#define	u4byte_in(x)		bswap(*(u4byte)(x))
#define	u4byte_out(x, v)	(*(u4byte*)(x) = bswap(v)) 

#endif

#endif
