#include <iostream>
#include <WinSock2.h>  // 소켓을 사용하기 위한 헤더파일

#pragma comment(lib, "ws2_32")  // 소켓 헤더 파일을 가져다 쓰기 위한 링크

#define PORT 5352  // 포트 번호, 포트번호는 2바이트안에서 표현할 수 있는 수로 정한다.
#define PACKET_SIZE 1024  // 패킷사이즈, 1024가 제일 적당하다

int main(void) {
	WSADATA wsaData;  // WSADATA 구조체 타입 변수 생성, 소켓의 초기화 정보를 저장
	
	// 이 함수를 가장 먼저 호출, 윈도우즈에서 사용할 소켓을 정함
	// 2.2 버전, WORD(unsigned short)타입으로 넣어줘야하여 MAKEWORD함수를 사용하여 넣어준다.
	WSAStartup(MAKEWORD(2, 2), &wsaData);   

	SOCKET hListen;  // 소켓객체 생성
	// IPv4타입의 주소를 사용, 연결지향형 소켓, 프로토콜을 TCP로 사용
	hListen = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN tListenAddr = {};  // 소켓의 구성요소를 담을 구조체 생성
	tListenAddr.sin_family = AF_INET;  // 주소체계:IPv4
	// htons함수를 이용해 포트번호를 빅엔디안방식(메모리에 데이터 저장방식, 네트워크 표준)으로 변환
	tListenAddr.sin_port = htons(PORT); 
	// 서버의 IP주소, INADDR_ANY는 현재 동작되는 컴퓨터의 IP주소
	// tListenAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	tListenAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // 아이피 지정할때

	// 소켓에 설정한 주소정보를 묶는다. 소켓, 소켓 구성요소 구조체의 주소, 그 구조체의 크기
	bind(hListen, (SOCKADDR*)&tListenAddr, sizeof(tListenAddr));
	// 소켓을 접속대기 상태로 만듬, SOMAXCONN는 한꺼번에 요청 가능한 최대 접속승인 수 
	listen(hListen, SOMAXCONN);  

	// 클라이언트가 접속 요청을 하면 승인
	SOCKADDR_IN tClntAddr = {}; // 클라이언트 측 소켓 정보를 담을 구조체 생성
	int iClntSize = sizeof(tClntAddr);  // 구조체의 크기
	// accept함수는 동기화된 방식으로 동작한다. 즉 요청이 들어오기 전까지 이 함수를 안빠져나온다.
	// 연결될 소켓, 클라이언트의 주소정보 구조체의 주소, 그 구조체의 크기를 저장해둔 변수의 주소
	SOCKET hClient = accept(hListen, (SOCKADDR*)&tClntAddr, &iClntSize);

	// 클라이언트로부터 정보를 받아오고 출력, 클라이언트에 정보 전송
	char cBuffer[PACKET_SIZE] = {};  // 패킷크기만큼 버퍼 생성, 클라이언트가 보낸 데이터를 수신하기위해
	// 소켓, 수신정보를 담을 배열주소, 배열의 크기, flag
	// 데이터를 받을때까지 대기
	recv(hClient, cBuffer, PACKET_SIZE, 0);  
	printf("Recv Msg : %s\n", cBuffer);

	char cMsg[] = "Server Send";
	send(hClient, cMsg, strlen(cMsg), 0);  // 클라이언트에게 데이터 전송

	closesocket(hClient);  // 클라이언트 소켓을 닫는다
	closesocket(hListen);  // 서버 소켓을 닫는다.

	WSACleanup();  // 보통 가장 마지막에 오는 함수, WSAStartup을 하면서 지정한 내용을 지운다.

	return 0;
}