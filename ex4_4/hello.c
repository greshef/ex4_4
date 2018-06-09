#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include<WinSock2.h>
#include <Windows.h>
#include <sys/types.h>
#include "hello.h"
#define PORT 5555
#define LOCAL_HOST "127.0.0.1"


int open_socket_fail(SOCKET winSocket)
{
	return winSocket < 0;
}

void main() {

	#ifdef WIN32
		// Initialize Winsock
		int iResult;
		WSADATA wsaData;
		iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (iResult != 0) {
			return;
		}
	#endif
	



	SOCKET winSocket = 0;
	int port = 0, client_lengh = 0, sentence_len = 0, bind_success;
	char buffer[256];
	struct sockaddr_in LB, server;

	winSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (open_socket_fail(winSocket))
	{
		printf(TEXT("open socket failed. Error: %d"), WSAGetLastError());
		closesocket(winSocket);
		return FALSE;
	}
	else {
		printf("port open success\n");
	}
	
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(LOCAL_HOST);
	server.sin_port = htons(PORT);
	bind_success = bind(winSocket, (SOCKADDR*)&server, sizeof(server));
	if (bind_success == SOCKET_ERROR)
	{
		printf( TEXT("Binding socket failed. Error: %d"),WSAGetLastError());
		closesocket(winSocket);
		return FALSE;
	}
	else
	{
		printf("bind succeeded\n");
	}


}