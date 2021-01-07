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
	//1.建立一个socket
	SOCKET sock=socket(AF_INET, SOCK_STREAM, 0);
	//2.连接服务器
	sockaddr_in sin = {};
	sin.sin_family = AF_INET;//类型：面向网络连接的ipv4地址
	sin.sin_port = htons(4567);//端口号
	sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");//本机地址
	connect(sock, (sockaddr*)&sin, sizeof(sockaddr_in));
	//3.接受服务器信息
	char recvBuf[256] = {};//缓冲区长度
	recv(sock, recvBuf, 256, 0);
	printf("接收到的数据为：%s", recvBuf);
	//4.关闭socket
	closesocket(sock);
	getchar();
	return 0;
}