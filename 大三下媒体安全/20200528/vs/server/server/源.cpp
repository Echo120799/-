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
	//1.建立一个socket，第一个参数：ipv4的套接字，第二个参数：面向数字流的类型，第三个参数：创建什么协议
	SOCKET sock= socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//2.绑定用于接收客户端连接的网络端口
	sockaddr_in sin = {};
	sin.sin_family = AF_INET;//类型：面向网络连接的ipv4地址
	sin.sin_port = htons(4567);//端口号 host to net unsigned short
	sin.sin_addr.S_un.S_addr = INADDR_ANY;//默认ip地址，本机所有ip地址都可以访问
	bind(sock, (sockaddr*)&sin, sizeof(sin));
	//3.监听网络端口
	listen(sock, 5);
	//4.等待客户端连接
	sockaddr_in clientAddr = {};
	printf("%s\n", "welcome,the serve is started...");
	int nAddrLen = sizeof(sockaddr_in);//传入的socket数据的长度
	SOCKET cSock = INVALID_SOCKET;//客户端socket
	char msgBuf[] = "helloworld";//要传输的数据
	while (true)
	{
		cSock=accept(sock, (sockaddr*)&clientAddr, &nAddrLen);
		printf("新客户端加入：IP=%s\n", inet_ntoa(clientAddr.sin_addr));
		//5.向客户端发一条数据
		//第一个参数：客户端socket，第二个参数：数据指针，第三个参数：数据长度
		send(cSock, msgBuf, strlen(msgBuf) + 1, 0);
	}
	//6.关闭套接字
	closesocket(sock);
	return 0;
}