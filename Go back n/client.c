#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 7500

void main() {
	int clientsocket;
	struct sockaddr_in serveraddr;
	socklen_t len;
	int wait = 3, first_time = 1, current;
	char buffer[100];

	memset(&serveraddr,0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = PORT;
	serveraddr.sin_addr.s_addr = INADDR_ANY;

	clientsocket = socket(AF_INET, SOCK_STREAM, 0);

	connect(clientsocket, (struct sockaddr*)&serveraddr, sizeof(serveraddr));

	//memset(buffer, 0, sizeof(buffer));
	sprintf(buffer, "REQUEST");
	send(clientsocket, buffer, 100, 0);

	do {
		recv(clientsocket, buffer, 100,0);
		current = atoi(&buffer[0]);
		printf("\nRecieved Packet%d",current);
		if(current == 3 && first_time) {
			printf("\nSimulation: Packet lost or damaged.\nSending Retransmission message...");
			sprintf(buffer, "R1");
			send(clientsocket, buffer, 100, 0);
			first_time = 0;
		}
		else{
			wait--;
			if(!wait) {
				printf("\nSending acknowledgement for Packet%d",current);
				buffer[0] = 'A';
				buffer[1] = (char)(current + 48);
				buffer[2] = '\0';
				send(clientsocket, buffer, 100, 0);
				wait = 3;
			}
		}
	}while(current != 9);

	close(clientsocket);
	printf("\nFinished. Exiting...");
}
