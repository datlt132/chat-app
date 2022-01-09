#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>
#include "util.h"

int sendToClient(int newClientSocket, char buffer[1024])
{
	int iSend;
	iSend = send(newClientSocket, buffer, strlen(buffer) + 1, 0);
	if (iSend < 0)
	{
		printf("Send error! \n");
	}
	return iSend;
}

int recvFromClient(int newClientSocket, char buffer[1024])
{
	int iRecv;
	iRecv = recv(newClientSocket, buffer, 1024, 0);
	if (iRecv < 0)
	{
		printf("Recv error! \n");
	}
	return iRecv;
}

void *client_handler(void *socket_desc)
{
	int newClientSocket = *(int *)socket_desc;
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		puts("Wrong number of parameter!");
		exit(-1);
	}
	int iSocket, iBind;
	struct sockaddr_in serverAddr;
	struct sockaddr_in newAddr;

	int newClientSocket;

	socklen_t addr_size;

	pthread_t tid;

	iSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (iSocket < 0)
	{
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Server Socket is created.\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(atoi(argv[1]));
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	iBind = bind(iSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
	if (iBind < 0)
	{
		printf("[-]Error in binding.\n");
		exit(1);
	}
	printf("[+]Bind to port %s\n", argv[1]);

	if (listen(iSocket, 10) == 0)
	{
		printf("[+]Listening....\n");
	}
	else
	{
		printf("[-]Error in binding.\n");
	}

	while (1)
	{
		newClientSocket = accept(iSocket, (struct sockaddr *)&newAddr, &addr_size);
		if (newClientSocket < 0)
		{
			printf("Accept fail!\n");
			exit(1);
		}
		printf("[+]Connection accept on port: %s\n", argv[1]);

		if (pthread_create(&tid, NULL, client_handler, (void *)&newClientSocket) == 0)
		{
			printf("Pthread created successfully!\n");
		}
		else
		{
			printf("Cloudn't create thread!\n");
			exit(1);
		}
	}

	close(newClientSocket);

	return 0;
}