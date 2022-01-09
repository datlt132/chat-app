#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "util.h"

int sendToServer(int newSocket,char buffer[1024]){
	int iSend;
	iSend = send(newSocket, buffer, strlen(buffer)+1, 0);
	if(iSend < 0){
		printf("Send error! \n");
	}
	return iSend;
}

int recvFromServer(int newSocket,char buffer[1024]){
	int iRecv;
	iRecv = recv(newSocket, buffer, 1024, 0);
		if(iRecv < 0) {
			printf("Recv error! \n");
		}
	return iRecv;
}

int main(int argc,char *argv[]){

	if (argc != 3){
		printf("Wrong number of parameters\n");
		return 0;
	}

	if( !validate_ip(argv[1])){
		printf("Invalid IP address!\n\n");
		return 0;
	}

	int clientSocket, iConnect, iSend, iRecv;
	struct sockaddr_in serverAddr;
	char buffer[1024];

	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(clientSocket < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Client Socket is created.\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(atoi(argv[2]));
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	iConnect = connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(iConnect < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Connected to Server.\n");


	while(strcmp(buffer,"OK")!=0){
		printf("Username: ");
		scanf("%s", buffer);

		iSend = send(clientSocket, buffer, strlen(buffer)+1, 0);
		if(iSend < 0){
			printf("[-]Send error! \n");
			exit(1);
		}

		if(strcmp(buffer, "bye") == 0){
			close(clientSocket);
			printf("[-]Disconnected from server.\n");
			exit(1);
		}

		printf("Password: ");
		scanf("%s", buffer);

		iSend = send(clientSocket, buffer, strlen(buffer)+1, 0);
		if(iSend < 0){
			printf("[-]Send error! \n");
			exit(1);
		}

		if(strcmp(buffer, "bye") == 0){
			close(clientSocket);
			printf("[-]Disconnected from server.\n");
			exit(1);
		}

		iRecv = recv(clientSocket, buffer, 1024, 0);
		if(iRecv < 0){
			printf("[-]Error in receiving data.\n");
			exit(1);
		}else{
			printf("Server: %s\n", buffer);
		}
	}

	char newPassword[1024] ="";
	while(1){
		printf("Insert: ");
		while(getchar()!='\n');
		scanf("%[^\n]s", newPassword);

		if(validate_alphanumber(newPassword) == 0){
			printf("Password only accept alphabet and number! \n");
			continue;
		}

		iSend = sendToServer(clientSocket, newPassword);

		if (strcmp(newPassword,"bye") == 0){
			printf("[-]Disconnect to server...\n");
			return 0;
		}
		
		iRecv = recvFromServer(clientSocket, buffer);
		printf("Alphabet: %s\n",buffer);
		iSend = sendToServer(clientSocket, " ");
		iRecv = recvFromServer(clientSocket, buffer);
		printf("Number: %s\n",buffer);
	}
	return 0;
}