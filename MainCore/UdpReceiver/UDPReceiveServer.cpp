// UDPReceiveServer.cpp: define el punto de entrada de la aplicación de consola.
// json source library https://github.com/open-source-parsers/jsoncpp
#include "GlobInclude.h"
#include "UDPReceiveServer.h"

//global variables instantiation
WSADATA wsaData;
SOCKET Socket;
char recvbuf[DEFAULT_BUFLEN];
int recvbuflen, RecvResult, slen;
struct sockaddr_in service, si_other;

UDPReceiveServer::UDPReceiveServer(int argc, char *argv[]) {
	//----------------------
	// Constructor
	Socket = INVALID_SOCKET;
	recvbuflen = DEFAULT_BUFLEN;

	// The socket address to be passed to bind
	slen = sizeof(si_other);

	//----------------------
	// Initialize Winsock
	RecvResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (RecvResult != NO_ERROR) {
		printf("Error at WSAStartup()\n");
		exit;
	}
	//----------------------
	// Create a SOCKET for listening for 
	// incoming connection requests
	Socket = socket(AF_INET, SOCK_DGRAM, 0);
	if (Socket == INVALID_SOCKET) {
		printf("socket function failed with error: %u\n", WSAGetLastError());
		WSACleanup();
		exit;
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
		printf("bind failed with error %u\n", WSAGetLastError());
		closesocket(Socket);
		WSACleanup();
		exit;
	}
	else
		printf("bind returned success\n");

	printf("Server Start\n");
}

int UDPReceiveServer::StartServer() {
	//----------------------
	// Receive Metod

	controlmodule _cmod(CoordinatesXY((GetSystemMetrics(SM_CXSCREEN) - 1) / 2, (GetSystemMetrics(SM_CYSCREEN) - 1) / 2));

	do {
		RecvResult = recvfrom(Socket, recvbuf, recvbuflen, 0, (struct sockaddr *) &si_other, &slen);
		if (RecvResult > 0) {
			printf("recived");
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
				_cmod.input(coordinates);
				// ..
				// ..
				printf("x:%f, y:%f, z:%f\n", coordinates.x, coordinates.y, coordinates.z);
			} else { printf("Error on json parsing: %s \n", reader.getFormattedErrorMessages()); }
		} else { printf("recv failed: %d\n", WSAGetLastError()); }
	} while (true);

	printf("Server Stop\n");

	// cleanup
	closesocket(Socket);
	WSACleanup();

	return 0;
}
