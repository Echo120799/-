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
	//1.����һ��socket����һ��������ipv4���׽��֣��ڶ������������������������ͣ�����������������ʲôЭ��
	SOCKET sock= socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//2.�����ڽ��տͻ������ӵ�����˿�
	sockaddr_in sin = {};
	sin.sin_family = AF_INET;//���ͣ������������ӵ�ipv4��ַ
	sin.sin_port = htons(4567);//�˿ں� host to net unsigned short
	sin.sin_addr.S_un.S_addr = INADDR_ANY;//Ĭ��ip��ַ����������ip��ַ�����Է���
	bind(sock, (sockaddr*)&sin, sizeof(sin));
	//3.��������˿�
	listen(sock, 5);
	//4.�ȴ��ͻ�������
	sockaddr_in clientAddr = {};
	printf("%s\n", "welcome,the serve is started...");
	int nAddrLen = sizeof(sockaddr_in);//�����socket���ݵĳ���
	SOCKET cSock = INVALID_SOCKET;//�ͻ���socket
	char msgBuf[] = "helloworld";//Ҫ���������
	while (true)
	{
		cSock=accept(sock, (sockaddr*)&clientAddr, &nAddrLen);
		printf("�¿ͻ��˼��룺IP=%s\n", inet_ntoa(clientAddr.sin_addr));
		//5.��ͻ��˷�һ������
		//��һ���������ͻ���socket���ڶ�������������ָ�룬���������������ݳ���
		send(cSock, msgBuf, strlen(msgBuf) + 1, 0);
	}
	//6.�ر��׽���
	closesocket(sock);
	return 0;
}