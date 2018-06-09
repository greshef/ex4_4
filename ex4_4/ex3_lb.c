#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <limits.h>
#include <windows.h>
#include <stdbool.h>
#include <time.h>

#define PORTSRANGE 62976
#define MINPORT 1024
#define BUFFERLENGTH 1024
#define NUMOFSERVERS 3

void writeFile(char* file_name, int port) {
	FILE *new_file;
	new_file = fopen(file_name, "w");
	fprintf(new_file, "%d", port);
	fclose(new_file);
}

int GetConnectionPort(SOCKET cur_socket) {
	int port, bind_res;
	bool port_valid = false;
	while (!port_valid) {
		port = rand() % PORTSRANGE + MINPORT;
		struct sockaddr_in service_server;
		service_server.sin_family = AF_INET;
		service_server.sin_addr.s_addr = inet_addr("127.0.0.1");
		service_server.sin_port = htons(port);
		bind_res = bind(cur_socket, (SOCKADDR*)&service_server, sizeof(service_server));
		if (bind_res != SOCKET_ERROR)
			port_valid = true;
	}
	return port;
}

void CloseSocket(SOCKET cur_socket, SOCKET servers_sockets[NUMOFSERVERS], SOCKET client_socket) {
	shutdown(cur_socket, SD_BOTH);
	shutdown(client_socket, SD_BOTH);
	for (int i = 0; i<NUMOFSERVERS; i++)
		shutdown(servers_sockets[i], SD_BOTH);
}

void main() {
	int port_server, port_http, listen_res, server_index = 0;
	bool port_server_valid = false, port_http_valid = false;
	time_t t;
	SOCKET server_socket_connect, http_socket, server_socket[NUMOFSERVERS];
	char buffer[BUFFERLENGTH];
	srand((unsigned)time(&t));
	server_socket_connect = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	http_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	port_server = GetConnectionPort(server_socket_connect);
	writeFile("port_server", port_server);

	port_http = GetConnectionPort(server_socket_connect);
	writeFile("port_http", port_http);
	listen_res = listen(server_socket_connect, NUMOFSERVERS);
	listen_res = listen(http_socket, 1);

	for (int num_of_connections = 0; num_of_connections < NUMOFSERVERS; num_of_connections++) {
		server_socket[num_of_connections] = accept(server_socket_connect, NULL, NULL);
	}
	while (1) {
		while (strstr(buffer, "\r\n\r\n") != NULL) {
			recv(http_socket, buffer, strlen(buffer), 0);
			send(server_socket[server_index % NUMOFSERVERS], buffer, strlen(buffer), 0);
		}
		while (strstr(buffer, "\r\n\r\n") != NULL) {
			recv(server_socket[server_index % NUMOFSERVERS], buffer, strlen(buffer), 0);
			send(http_socket, buffer, strlen(buffer), 0);
		}
		server_index++;
	}
}