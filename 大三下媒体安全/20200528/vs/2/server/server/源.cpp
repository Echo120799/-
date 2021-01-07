
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
using namespace std;
#pragma comment( lib, "ws2_32.lib" )

/*所有需要的参数信息都在此处以#define的形式提供*/
#define CERTF   "server-cert.pem" /*服务端的证书(需经CA签名)*/  
#define KEYF   "server-key.pem"  /*服务端的私钥(建议加密存储)*/  
#define CACERT "ca-cert.pem" /*CA 的证书*/  
#define PORT   1111   /*准备绑定的端口*/  

#define CHK_NULL(x) if ((x)==NULL) exit (1)  
#define CHK_ERR(err,s) if ((err)==-1) { perror(s); exit(1); }  
#define CHK_SSL(err) if ((err)==-1) { ERR_print_errors_fp(stderr); exit(2); }  

int main()
{
	int err;
	int listen_sd;
	int sd;
	struct sockaddr_in sa_serv;
	struct sockaddr_in sa_cli;
	int client_len;
	SSL_CTX* ctx;
	SSL*     ssl;
	X509*    client_cert;
	char*    str;
	char     buf[4096];
	const SSL_METHOD *meth;
	WSADATA wsaData;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		printf("WSAStartup()fail:%d\n", GetLastError());
		return -1;
	}

	OpenSSL_add_ssl_algorithms(); /*初始化*/
	SSL_load_error_strings();     /*为打印调试信息作准备*/
	SSLeay_add_ssl_algorithms();
	ERR_load_BIO_strings();

	meth = SSLv23_server_method();
	//meth = const_cast<SSL_METHOD *>(TLSv1_server_method());  /*采用什么协议(SSLv2/SSLv3/TLSv1)在此指定*/  

	ctx = SSL_CTX_new(meth);
	CHK_NULL(ctx);

	//SSL_CTX_set_verify(ctx,SSL_VERIFY_PEER,NULL);   /*验证与否*/  
	// 服务器端不需要验证客户端的ca，改下就好了，见 https://bbs.csdn.net/topics/390222065
	// 如果选择SSL_VERIFY_PEER，则SSL_accept处会返回-1，一直报错
	SSL_CTX_set_verify(ctx, SSL_VERIFY_NONE, NULL);   /*验证与否*/

	if (!SSL_CTX_load_verify_locations(ctx, CACERT, NULL)) /*若验证,则放置CA证书*/
	{
		ERR_print_errors_fp(stderr);
		exit(3);
	}
	if (SSL_CTX_use_certificate_file(ctx, CERTF, SSL_FILETYPE_PEM) <= 0) {
		ERR_print_errors_fp(stderr);
		exit(3);
	}
	if (SSL_CTX_use_PrivateKey_file(ctx, KEYF, SSL_FILETYPE_PEM) <= 0) {
		ERR_print_errors_fp(stderr);
		exit(4);
	}

	if (!SSL_CTX_check_private_key(ctx)) {
		printf("Private key does not match the certificate public key\n");
		exit(5);
	}

	SSL_CTX_set_cipher_list(ctx, "RC4-MD5");

	/*开始正常的TCP socket过程.................................*/
	printf("Begin TCP socket...\n");

	listen_sd = socket(AF_INET, SOCK_STREAM, 0);
	CHK_ERR(listen_sd, "socket");

	/********设置套接字非阻塞******/
	ULONG ul = 1;
	int nRet = ioctlsocket(listen_sd, FIONBIO, (unsigned long*)&ul);
	if (nRet == SOCKET_ERROR)
	{
		printf("设置套接字选项--非阻塞失败！\n");
		closesocket(listen_sd);
		//WSACleanup();
		return 0;
	}

	memset(&sa_serv, '\0', sizeof(sa_serv));
	sa_serv.sin_family = AF_INET;
	sa_serv.sin_addr.s_addr = INADDR_ANY;
	sa_serv.sin_port = htons(PORT);

	err = bind(listen_sd, (struct sockaddr*) &sa_serv,

		sizeof(sa_serv));

	CHK_ERR(err, "bind");

	/*接受TCP链接*/
	err = listen(listen_sd, 5);
	CHK_ERR(err, "listen");

	client_len = sizeof(sa_cli);
	while (true)
	{
		sd = accept(listen_sd, (struct sockaddr*) &sa_cli, &client_len);
		if (sd == SOCKET_ERROR)
		{
			err = WSAGetLastError();
			if ((err != WSAEWOULDBLOCK))
			{
				cout << "recvfrom()调用失败，错误码：" << WSAGetLastError() << endl;
				break;
			}
			else
			{
				continue;
			}
		}
		else
			break;
	}

	cout << "连接成功！" << endl;
	closesocket(listen_sd);

	printf("Connection from %lx, port %x\n",
		sa_cli.sin_addr.s_addr, sa_cli.sin_port);

	/*TCP连接已建立,进行服务端的SSL过程. */
	printf("Begin server side SSL\n");

	ssl = SSL_new(ctx);
	CHK_NULL(ssl);
	SSL_set_fd(ssl, sd);
	SSL_set_accept_state(ssl);

	bool isContinue = true;
	while (isContinue)
	{
		isContinue = false;
		if (SSL_accept(ssl) != 1)
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

	/*这一段不要采用，因为前面设置的是SSL_VERIFY_NONE，服务器不读取客户端的证书。*/
	client_cert = SSL_get_peer_certificate(ssl);
	if (client_cert != NULL) {
		printf("Client certificate:\n");

		str = X509_NAME_oneline(X509_get_subject_name(client_cert), 0, 0);
		CHK_NULL(str);
		printf("\t subject: %s\n", str);
		free(str);

		str = X509_NAME_oneline(X509_get_issuer_name(client_cert), 0, 0);
		CHK_NULL(str);
		printf("\t issuer: %s\n", str);
		free(str);

		X509_free(client_cert);/*如不再需要,需将证书释放 */
	}
	else
		printf("Client does not have certificate.\n");


	/* 数据交换开始,用SSL_write,SSL_read代替write,read */

	int ires = 0, count = 0;;
	bool isCoutinue = true;
	while (true)
	{
		memset(buf, '\0', sizeof(buf));
		count = 0;
		while (isCoutinue)
		{
			ires = SSL_read(ssl, buf + count, 12 - count);
			int nRes = SSL_get_error(ssl, ires);
			if (nRes == SSL_ERROR_NONE)
			{
				if (ires > 0)
				{
					count += ires;
					if (count >= 12)
					{
						cout << buf << endl;
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

	/* 收尾工作*/
	shutdown(sd, 2);
	SSL_free(ssl);
	SSL_CTX_free(ctx);

	getchar();
	return 0;
}
