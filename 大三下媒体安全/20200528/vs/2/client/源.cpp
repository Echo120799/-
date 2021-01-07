
#include <stdio.h>  
#include <stdlib.h>  
#include <memory.h>  
#include <errno.h>  
#include <sys/types.h>  
#include <iostream>
#include <winsock2.h>  

#include "openssl/rsa.h"        
#include "openssl/crypto.h"  
#include "openssl/x509.h"  
#include "openssl/pem.h"  
#include "openssl/ssl.h"  
#include "openssl/err.h"  
#include "openssl/rand.h"  
using namespace std;


#pragma comment( lib, "ws2_32.lib" )
/*所有需要的参数信息都在此处以#define的形式提供*/
#define CERTF  "client-crt.pem"  /*客户端的证书(需经CA签名)*/  
#define KEYF  "client-key.pem"   /*客户端的私钥(建议加密存储)*/  
#define CACERT "ca-crt.pem"      /*CA 的证书*/  
#define PORT   1111          /*服务端的端口*/  
#define SERVER_ADDR "127.0.0.1"  /*服务段的IP地址*/  

#define CHK_NULL(x) if ((x)==NULL) exit (-1)  
#define CHK_ERR(err,s) if ((err)==-1) { perror(s); exit(-2); }  
#define CHK_SSL(err) if ((err)==-1) { ERR_print_errors_fp(stderr); exit(-3); }  

int main()
{
	int err;
	int sd;
	struct sockaddr_in sa;
	SSL_CTX* ctx;
	SSL*     ssl;
	X509*    server_cert;
	char*    str = new char[1000];
	char     buf[4096];
	const SSL_METHOD *meth;
	int       seed_int[100]; /*存放随机序列*/

	WSADATA wsaData;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		printf("WSAStartup()fail:%d/n", GetLastError());
		return -1;
	}

	OpenSSL_add_ssl_algorithms(); /*初始化*/
	SSL_load_error_strings();     /*为打印调试信息作准备*/
	SSLeay_add_ssl_algorithms();
	ERR_load_BIO_strings();

	meth = SSLv23_client_method();
	//meth = const_cast<SSL_METHOD*>(TLSv1_client_method()); /*采用什么协议(SSLv2/SSLv3/TLSv1)在此指定*/  
	ctx = SSL_CTX_new(meth);
	CHK_NULL(ctx);

	SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER, NULL);   /*验证与否*/
	if (!SSL_CTX_load_verify_locations(ctx, CACERT, NULL)) /*若验证,则放置CA证书*/
	{
		ERR_print_errors_fp(stderr);
		exit(3);
	}

	if (SSL_CTX_use_certificate_file(ctx, CERTF, SSL_FILETYPE_PEM) <= 0) {
		ERR_print_errors_fp(stderr);
		exit(-2);
	}
	if (SSL_CTX_use_PrivateKey_file(ctx, KEYF, SSL_FILETYPE_PEM) <= 0) {
		ERR_print_errors_fp(stderr);
		exit(-3);
	}

	if (!SSL_CTX_check_private_key(ctx)) {
		printf("Private key does not match the certificate public key/n");
		exit(-4);
	}

	/*构建随机数生成机制,WIN32平台必需*/
/*
	srand( (unsigned)time( NULL ) );
	for( int i = 0;   i < 100;i++ )
		seed_int[i] = rand();
	RAND_seed(seed_int, sizeof(seed_int));  */

	/*以下是正常的TCP socket建立过程 .............................. */
	printf("Begin tcp socket...\n");

	sd = socket(AF_INET, SOCK_STREAM, 0);       CHK_ERR(sd, "socket");
	//********设置套接字非阻塞******
	ULONG ul = 1;
	int nRet = ioctlsocket(sd, FIONBIO, (unsigned long*)&ul);
	if (nRet == SOCKET_ERROR)
	{
		printf("设置套接字选项--非阻塞失败！\n");
		closesocket(sd);
		//WSACleanup();
		return 0;
	}

	memset(&sa, '\0', sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = inet_addr(SERVER_ADDR);   /* Server IP */
	sa.sin_port = htons(PORT);          /* Server Port number */

	int nSize;

	while (true)
	{
		nSize = connect(sd, (struct sockaddr*) &sa, sizeof(sa));
		if (nSize == 0)
		{
			cout << "连接成功！" << endl;
			break;

		}
		if (nSize < 0)
		{
			err = WSAGetLastError();
			if (err == WSAEWOULDBLOCK)
			{
				Sleep(100);
				continue;
			}
			else if (err == WSAEISCONN)
			{
				cout << "连接成功！" << endl;
				break;
			}
			else
			{
				cout << "连接失败！错误代码：" << WSAGetLastError() << endl;
				closesocket(sd);
				WSACleanup();
				return 0;
			}
		}
	}

	/* TCP 链接已建立.开始 SSL 握手过程.......................... */
	printf("Begin SSL negotiation \n");

	ssl = SSL_new(ctx);
	CHK_NULL(ssl);

	SSL_set_fd(ssl, sd);
	SSL_set_connect_state(ssl);


	bool isContinue = true;
	while (isContinue)
	{
		isContinue = false;
		if (SSL_connect(ssl) == -1)
		{
			int icode = -1;
			int iret = SSL_get_error(ssl, icode);
			if ((iret == SSL_ERROR_WANT_WRITE) || (iret == SSL_ERROR_WANT_READ))
			{
				isContinue = true;
			}
			else
			{
				SSL_CTX_free(ctx);
				SSL_free(ssl);
				ctx = NULL;
				ssl = NULL;

				break;
			}
		}
		else
		{
			cout << "SSL连接成功！" << endl;
			break;
		}
	}


	/*打印所有加密算法的信息(可选)*/
	printf("SSL connection using %s\n", SSL_get_cipher(ssl));

	/*得到服务端的证书并打印些信息(可选) */
	server_cert = SSL_get_peer_certificate(ssl);
	CHK_NULL(server_cert);
	printf("Server certificate:\n");

	str = X509_NAME_oneline(X509_get_subject_name(server_cert), 0, 0);
	CHK_NULL(str);
	printf("\t subject: %s\n", str);
	//free (str);  

	str = X509_NAME_oneline(X509_get_issuer_name(server_cert), 0, 0);
	CHK_NULL(str);
	printf("\t issuer: %s\n", str);
	//free (str);  

	X509_free(server_cert);  /*如不再需要,需将证书释放 */

	/* 数据交换开始,用SSL_write,SSL_read代替write,read */
	printf("Begin SSL data exchange\n");

	const char* buffer = "Hello World!";
	int ilen = strlen("Hello World!");
	int ires = 0, count = 0;;
	bool isCoutinue = true;
	while (true)
	{
		count = 0;
		while (isCoutinue)
		{
			ires = SSL_write(ssl, buffer + count, ilen - count);
			int nRes = SSL_get_error(ssl, ires);
			if (nRes == SSL_ERROR_NONE)
			{
				if (ires > 0)
				{
					count += ires;
					if (count >= ilen)
					{
						printf("Write finished!\n");

						break;
					}
					continue;
				}
			}
			else if (nRes == SSL_ERROR_WANT_READ)
			{
				continue;
			}
			else
			{
				break;
			}
		}
		Sleep(500);
	}


	SSL_shutdown(ssl);  /* send SSL/TLS close_notify */

	/* 收尾工作 */
	shutdown(sd, 2);
	SSL_free(ssl);
	SSL_CTX_free(ctx);
	getchar();

	return 0;
}
