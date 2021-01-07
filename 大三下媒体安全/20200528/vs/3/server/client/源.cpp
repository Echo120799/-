#include <Winsock2.h>
#include <stdio.h>
#include <WS2tcpip.h>
#include <conio.h>  
#include <stdio.h>  
#include "openssl/x509.h"  
#include "openssl/ssl.h"  
#include "openssl/err.h"  
#include "openssl/rand.h" 

#pragma comment(lib,"ws2_32.lib")
#define CACERT     "ca-cert.pem"  
#define MYCERTF    "client-cert.pem"  
#define MYKEYF     "client-key.pem"  
int main()
{

	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(1, 1);

	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
	{
		exit(0);
	}

	if (LOBYTE(wsaData.wVersion) != 1 ||
		HIBYTE(wsaData.wVersion) != 1)
	{
		WSACleanup();
		exit(0);
	}
	 
	SSL *ssl;
	SSL_CTX* ctx;
	const SSL_METHOD *meth;
	meth = SSLv23_client_method();
	ctx = SSL_CTX_new(meth);
	ssl = SSL_new(ctx);

	//1.����һ��socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	//2.���ӷ�����
	sockaddr_in sin = {};
	sin.sin_family = AF_INET;//���ͣ������������ӵ�ipv4��ַ
	sin.sin_port = htons(4567);//�˿ں�
	sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");//������ַ
	connect(sock, (sockaddr*)&sin, sizeof(sockaddr_in));
	int fd = sock;
	SSL_set_fd(ssl, fd);
	SSL_connect(ssl);
	SSL_write(ssl, "���ǿͻ���", strlen("���ǿͻ���"));
	//3.���ܷ�������Ϣ
	//char recvBuf[256] = {};//����������
	//recv(sock, recvBuf, 256,0);
	//printf("���յ�������Ϊ��%s", recvBuf);
	//4.�ر�socket
	closesocket(sock);
	SSL_free(ssl);
	getchar();
	return 0;
}