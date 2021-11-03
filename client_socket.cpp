#include <iostream>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32")

#define PORT 5352
#define PACKET_SIZE 1024
#define SEVER_IP "127.0.0.1"  // 辑滚 IP林家

int main(void) {
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET hSocket;
	hSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN tAddr = {};
	tAddr.sin_family = AF_INET;
	tAddr.sin_port = htons(PORT);
	tAddr.sin_addr.s_addr = inet_addr(SEVER_IP);

	// 家南, 家南 备己夸家 备炼眉狼 林家, 弊 备炼眉狼 农扁
	connect(hSocket, (SOCKADDR*)&tAddr, sizeof(tAddr));

	char cMsg[] = "Client Send";
	send(hSocket, cMsg, strlen(cMsg), 0);

	char cBuffer[PACKET_SIZE] = {};
	recv(hSocket, cBuffer, PACKET_SIZE, 0);

	printf("Recv Msg : %s\n", cBuffer);
	
	closesocket(hSocket);

	WSACleanup();
	return 0;
}