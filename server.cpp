#include <iostream>
#include <WinSock2.h>  // ������ ����ϱ� ���� �������

#pragma comment(lib, "ws2_32")  // ���� ��� ������ ������ ���� ���� ��ũ

#define PORT 5352  // ��Ʈ ��ȣ, ��Ʈ��ȣ�� 2����Ʈ�ȿ��� ǥ���� �� �ִ� ���� ���Ѵ�.
#define PACKET_SIZE 1024  // ��Ŷ������, 1024�� ���� �����ϴ�

int main(void) {
	WSADATA wsaData;  // WSADATA ����ü Ÿ�� ���� ����, ������ �ʱ�ȭ ������ ����
	
	// �� �Լ��� ���� ���� ȣ��, ��������� ����� ������ ����
	// 2.2 ����, WORD(unsigned short)Ÿ������ �־�����Ͽ� MAKEWORD�Լ��� ����Ͽ� �־��ش�.
	WSAStartup(MAKEWORD(2, 2), &wsaData);   

	SOCKET hListen;  // ���ϰ�ü ����
	// IPv4Ÿ���� �ּҸ� ���, ���������� ����, ���������� TCP�� ���
	hListen = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN tListenAddr = {};  // ������ ������Ҹ� ���� ����ü ����
	tListenAddr.sin_family = AF_INET;  // �ּ�ü��:IPv4
	// htons�Լ��� �̿��� ��Ʈ��ȣ�� �򿣵�ȹ��(�޸𸮿� ������ ������, ��Ʈ��ũ ǥ��)���� ��ȯ
	tListenAddr.sin_port = htons(PORT); 
	// ������ IP�ּ�, INADDR_ANY�� ���� ���۵Ǵ� ��ǻ���� IP�ּ�
	// tListenAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	tListenAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // ������ �����Ҷ�

	// ���Ͽ� ������ �ּ������� ���´�. ����, ���� ������� ����ü�� �ּ�, �� ����ü�� ũ��
	bind(hListen, (SOCKADDR*)&tListenAddr, sizeof(tListenAddr));
	// ������ ���Ӵ�� ���·� ����, SOMAXCONN�� �Ѳ����� ��û ������ �ִ� ���ӽ��� �� 
	listen(hListen, SOMAXCONN);  

	// Ŭ���̾�Ʈ�� ���� ��û�� �ϸ� ����
	SOCKADDR_IN tClntAddr = {}; // Ŭ���̾�Ʈ �� ���� ������ ���� ����ü ����
	int iClntSize = sizeof(tClntAddr);  // ����ü�� ũ��
	// accept�Լ��� ����ȭ�� ������� �����Ѵ�. �� ��û�� ������ ������ �� �Լ��� �Ⱥ������´�.
	// ����� ����, Ŭ���̾�Ʈ�� �ּ����� ����ü�� �ּ�, �� ����ü�� ũ�⸦ �����ص� ������ �ּ�
	SOCKET hClient = accept(hListen, (SOCKADDR*)&tClntAddr, &iClntSize);

	// Ŭ���̾�Ʈ�κ��� ������ �޾ƿ��� ���, Ŭ���̾�Ʈ�� ���� ����
	char cBuffer[PACKET_SIZE] = {};  // ��Ŷũ�⸸ŭ ���� ����, Ŭ���̾�Ʈ�� ���� �����͸� �����ϱ�����
	// ����, ���������� ���� �迭�ּ�, �迭�� ũ��, flag
	// �����͸� ���������� ���
	recv(hClient, cBuffer, PACKET_SIZE, 0);  
	printf("Recv Msg : %s\n", cBuffer);

	char cMsg[] = "Server Send";
	send(hClient, cMsg, strlen(cMsg), 0);  // Ŭ���̾�Ʈ���� ������ ����

	closesocket(hClient);  // Ŭ���̾�Ʈ ������ �ݴ´�
	closesocket(hListen);  // ���� ������ �ݴ´�.

	WSACleanup();  // ���� ���� �������� ���� �Լ�, WSAStartup�� �ϸ鼭 ������ ������ �����.

	return 0;
}