#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <fcntl.h>

#define PORT 7500

void itoa(int n, char buffer[]){
	buffer[0] = (char)(n + 48);
	buffer[1] = '\0';
}


void main() {
	int serversocket, clientsocket;
	struct sockaddr_in serveraddr, clientaddr;
	socklen_t len;
	int window_start = 1, current_window = 1, window_end = 4, old_window;
	char buffer[100];

	memset(&serveraddr, 0, sizeof(serveraddr));
	memset(&clientaddr, 0, sizeof(clientaddr));

	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = PORT;
	serveraddr.sin_addr.s_addr = INADDR_ANY;

	serversocket = socket(AF_INET, SOCK_STREAM, 0);
	bind(serversocket, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
	printf("\nBinding done.");

	listen(serversocket, 1);
	len = sizeof(clientaddr);
	clientsocket = accept(serversocket, (struct sockaddr*)&clientaddr, &len);

	memset(buffer, 0, sizeof(buffer));
	recv(clientsocket, buffer, 100, 0);
	printf("\nRecieved request from client. Starting to send packets...");
	fcntl(clientsocket, F_SETFL,O_NONBLOCK);

	do {
		if(current_window != window_end) {
			printf("\nSending packet %d",current_window);
			itoa(current_window, buffer);
			send(clientsocket, buffer, 100,0);
			current_window ++;
		}

		recv(clientsocket, buffer, 100, 0);

		if(buffer[0] == 'R') {
			printf("\nRetransmission for Packet%c recieved.",buffer[1]);
			printf("\nSending Packet %c",buffer[1]);

			strcpy(buffer,buffer[1]);
			send(clientsocket, buffer, 100, 0);
			current_window = atoi(&buffer[0]) + 1;
		}
		else if(buffer[0] == 'A') {
			printf("\nAcknowledgement recieved for Packet%c. Moving the window...",buffer[1]);
			old_window = window_start;
			window_start = atoi(&buffer[1]) + 1;
			window_end += (window_start - old_window);
		}
	}while(current_window != 10);

	close(clientsocket);
	close(serversocket);
	printf("\nFinished sending. Exiting...");
}
