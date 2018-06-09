#include <stdio.h>
#include<WinSock2.h>
#include <winsock.h>
#include <sys/types.h>
#include "hello.h"
#define PORT 5555
#define LOCAL_HOST "127.0.0.1"



int open_socket_fail(SOCKET winSocket)
{
	return winSocket < 0;
}

void main() {

	SOCKET winSocket = 0;
	int port = 0, client_lengh = 0, sentence_len = 0, bind_success;
	char buffer[256];
	struct sockaddr_in LB, server;

	winSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (open_socket_fail(winSocket))
	{
		printf("Error in opening Socket");
	}
	else {
		printf("port open success");
	}
	
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(LOCAL_HOST);
	server.sin_port = htons(PORT);
	bind_success = bind(winSocket, (SOCKADDR*)&server, sizeof(server));
	if (bind_success < 0)
	{
		printf("Error in bind");
	}
	else
	{
		printf("bind succeeded");
	}


}