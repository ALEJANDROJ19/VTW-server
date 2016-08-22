// UDPReceiveServer.cpp: define el punto de entrada de la aplicación de consola.
// json source library https://github.com/open-source-parsers/jsoncpp

#include "stdafx.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <ws2tcpip.h>
#include "lib\include\json\json.h"
#include "JoistickThread.h"

// Link with ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")
#define DEFAULT_BUFLEN 128

int main() {
	//----------------------
	// Constructor
	WSADATA wsaData;
	int RecvResult;
	SOCKET Socket = INVALID_SOCKET;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;

	// The socket address to be passed to bind
	struct sockaddr_in service, si_other;
	int slen = sizeof(si_other);

	//----------------------
	// Initialize Winsock
	RecvResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (RecvResult != NO_ERROR) {
		wprintf(L"Error at WSAStartup()\n");
		return 1;
	}
	//----------------------
	// Create a SOCKET for listening for 
	// incoming connection requests
	Socket = socket(AF_INET, SOCK_DGRAM, 0);
	if (Socket == INVALID_SOCKET) {
		wprintf(L"socket function failed with error: %u\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}
	//----------------------
	// The sockaddr_in structure specifies the address family,
	// IP address, and port for the socket that is being bound.
	service.sin_family = AF_INET;
	service.sin_addr.s_addr = INADDR_ANY;
	//service.sin_addr.s_addr = inet_addr("127.0.0.1");
	service.sin_port = htons(27015);

	//----------------------
	// Bind the socket.
	RecvResult = bind(Socket, (SOCKADDR *)&service, sizeof(service));
	if (RecvResult == SOCKET_ERROR) {
		wprintf(L"bind failed with error %u\n", WSAGetLastError());
		closesocket(Socket);
		WSACleanup();
		return 1;
	}
	else
		wprintf(L"bind returned success\n");

	printf("Server Start\n");

	//----------------------
	// Receive Metod
	do {
		RecvResult = recvfrom(Socket, recvbuf, recvbuflen, 0, (struct sockaddr *) &si_other, &slen);
		if (RecvResult > 0) {
			CoordinatesXYZ coordinates;
			std::string JsonString = recvbuf;
			Json::Value JsonData;
			Json::Reader reader;
			if (reader.parse(JsonString, JsonData)) {
				coordinates.x = JsonData.get("x", "UTF-8").asDouble();
				coordinates.y = JsonData.get("y", "UTF-8").asDouble();
				coordinates.z = JsonData.get("z", "UTF-8").asDouble();
				//TODO: call movement function passing coordinates
				// ..
				// ..
				// ..
				printf("x:%f, y:%f, z:%f\n", coordinates.x, coordinates.y, coordinates.z);
			} else { printf("Error on json parsing: %s \n", reader.getFormattedErrorMessages()); }
		} else { printf("recv failed: %d\n", WSAGetLastError()); }
	} while (true); //TODO: while no stop

	printf("Server Stop\n");

	// cleanup
	closesocket(Socket);
	WSACleanup();

	return 0;
}
