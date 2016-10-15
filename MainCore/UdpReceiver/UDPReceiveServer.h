#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <ws2tcpip.h>
#include "include\json\json.h"
// Link with ws2_32.lib
#pragma once
#pragma comment(lib, "Ws2_32.lib")
#define DEFAULT_BUFLEN 128

class UDPReceiveServer
{
private:
	WSADATA wsaData;
	SOCKET Socket;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen, RecvResult, slen;
	struct sockaddr_in service, si_other;

public:
	UDPReceiveServer(int argc, char *argv[]);
	int UDPReceiveServer::StartServer();
};