#ifndef __AES_H__
#define __AES_H__

/* 1.基本数据类型定义*/

typedef unsigned char   u1byte; /* 8位无符号字符类 */
typedef unsigned short  u2byte; /* 16位无符号整型  */
typedef unsigned long   u4byte; /* 32位无符号整型类*/
typedef signed char     s1byte; /* 8位符号字符类   */
typedef signed short    s2byte; /* 16位符号整型类  */
typedef signed long     s4byte; /* 32位符号整型类  */

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
/* 2.为加速操作定义的基本宏             */

/* 32位值循环移位                       */

#ifdef _MSC_VER

#  include <stdlib.h>
#  pragma intrinsic(_lrotr,_lrotl)
#  define rotr(x,n) _lrotr(x,n)
#  define rotl(x,n) _lrotl(x,n)

#else

#define rotr(x,n)   (((x) >> ((int)(n))) | ((x) << (32 - (int)(n))))
#define rotl(x,n)   (((x) << ((int)(n))) | ((x) >> (32 - (int)(n))))

#endif

/* 32位变量位顺序转换                          */

#define bswap(x)    (rotl(x, 8) & 0x00ff00ff | rotr(x, 8) & 0xff00ff00)

/* 从32位的变量抽取字节    */ 

#define byte(x,n)   ((u1byte)((x) >> (8 * n)))

/* 以机器顺序输入或输出一个32位值				*/

#ifdef	LITTLE_ENDIAN

#define	u4byte_in(x)		(*(u4byte*)(x))
#define	u4byte_out(x, v)	(*(u4byte*)(x) = (v)) 

#else

#define	u4byte_in(x)		bswap(*(u4byte)(x))
#define	u4byte_out(x, v)	(*(u4byte*)(x) = bswap(v)) 

#endif

#endif
