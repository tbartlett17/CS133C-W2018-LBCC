//********************************************************************************************
// Author: Tyler Bartlett
// Files: sockets.c, webpage.txt
// Date: 03/18/18
// Course: CS 133C
// Class time: 8am, M/W/F
// Project: 7
// Desc: 
//		
//********************************************************************************************
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <string.h>

#pragma comment(lib, "Ws2_32.lib")

#define DEFAULT_PORT "80"
#define DEFAULT_BUFLEN 512
#define BUFF_SIZE 256000

struct addrinfo *result = NULL, *ptr = NULL, hints;
SOCKET ConnectSocket = INVALID_SOCKET;

int main()
{
	WSADATA wsaData;
	int iResult;

	int recvbuflen = DEFAULT_BUFLEN;
	const char *sendbuf = "test";
	char recvbuf[DEFAULT_BUFLEN];

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
		return 1;
	}

	printf("WSAStartup success\n");

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	/* get website from user */
	char *websiteURL = malloc(256);
	printf("Please enter a HTTP website URL (include the www. and .com) (ex: www.cplusplus.com):");
	scanf("%s", websiteURL);
	//printf("%s is what you entered.\n", websiteURL);
	char address[256];
	strcpy(address, websiteURL);
	//printf("address: %s", address);

	// Resolve the server address and port
	iResult = getaddrinfo(address, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed: %d\n", iResult);
		WSACleanup();
		return 1;
	}

	printf("getaddrinfo success\n");


	SOCKET Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	struct hostent *host;
	host = gethostbyname(websiteURL);

	SOCKADDR_IN SockAddr;
	SockAddr.sin_port = htons(80);
	SockAddr.sin_family = AF_INET;
	SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);

	if (connect(Socket, (SOCKADDR*)(&SockAddr), sizeof(SockAddr)) != 0)
	{
		printf("Connection Error\n");
		return 1;
	}

	char *sendCodePart1 = "GET / HTTP/1.1\r\nHost: ";
	char *sendCodePart2 = "\r\nConnection: close\r\n\r\n";
	char *sendCode;
	if ((sendCode = malloc(strlen(sendCodePart1) + strlen(websiteURL) + strlen(sendCodePart2) + 1)) != NULL) {
		sendCode[0] = '\0';   // ensures the memory is an empty string
		strcat(sendCode, sendCodePart1);
		strcat(sendCode, websiteURL);
		strcat(sendCode, sendCodePart2);
	}
	else {
		printf("malloc failed!\n");
		// exit?
	}
	//printf("send code is: %s\n", sendCode);

	send(Socket, sendCode, strlen(sendCode), 0);
	char buffer[BUFF_SIZE];

	FILE *fpOut = fopen("webpage.txt", "w");

	printf("working...\n");
	int nDataLength;
	while ((nDataLength = recv(Socket, buffer, BUFF_SIZE, 0)) > 0)
	{
		// process the information

		for (int i = 0; i < strlen(buffer); i++)
		{
			//fprintf(fpOut, "%c", buffer[i]);
			if (buffer[i] == '<' && buffer[i + 1] == 'i' && buffer[i + 2] == 'm' && buffer[i + 3] == 'g')
			{
				for (int j = i; buffer[j] != '>'; j++)
				{
					if (buffer[j] == 's' && buffer[j + 1] == 'r' && buffer[j + 2] == 'c')
					{
						int quoteCount = 0;
						printf("Found an image! ");
						for (int k = j; quoteCount != 2; k++)
						{
							printf("%c", buffer[k]);
							if (buffer[k] == '"')
							{
								quoteCount++;
							}

						}
						quoteCount = 0;
						printf("\n");
					}
				}
			}
			//filter out some of the garbage in the buffer
			if (buffer[i] != 'Ì' && buffer[i] != '¿' && buffer[i] != 'Ø' && buffer[i] != 'Â' && buffer[i] != 'Æ' && buffer[i] != 'ô'
				&& buffer[i] != 'è' && buffer[i] != 'ð' && buffer[i] != 'à' && buffer[i] != 'û' && buffer[i] != '£')
			{
				fprintf(fpOut, "%c", buffer[i]);
			}
		}
		//fprintf(fpOut, "%s", buffer);
		
	}
	printf("\nReceive complete. Check \"webpage.txt\" for contents of webiste.\n");

	// cleanup
	closesocket(ConnectSocket);
	WSACleanup();

	getchar();

	return 0;
}
