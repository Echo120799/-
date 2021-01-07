#include <Winsock2.h>
#include <stdio.h>
#include <WS2tcpip.h>

#pragma comment(lib,"ws2_32.lib")

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
	//1.����һ��socket
	SOCKET sock=socket(AF_INET, SOCK_STREAM, 0);
	//2.���ӷ�����
	sockaddr_in sin = {};
	sin.sin_family = AF_INET;//���ͣ������������ӵ�ipv4��ַ
	sin.sin_port = htons(4567);//�˿ں�
	sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");//������ַ
	connect(sock, (sockaddr*)&sin, sizeof(sockaddr_in));
	//3.���ܷ�������Ϣ
	char recvBuf[256] = {};//����������
	recv(sock, recvBuf, 256, 0);
	printf("���յ�������Ϊ��%s", recvBuf);
	//4.�ر�socket
	closesocket(sock);
	getchar();
	return 0;
}