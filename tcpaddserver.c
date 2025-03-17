#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int serversocket, clientsocket, port;
    struct sockaddr_in serveraddr, clientaddr;
    socklen_t len;
    int nums[10],sum=0;
    struct serveraddr;

    serversocket = socket(AF_INET, SOCK_STREAM, 0);
    bzero((char*) &serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    printf("enter the port number");
    scanf("%d", &port);
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    bind(serversocket, (struct sockaddr*) &serveraddr, sizeof(serveraddr));
    bzero((char*) &clientaddr, sizeof(clientaddr));
    len = sizeof(clientaddr);
    listen(serversocket, 5);
    printf("\n waiting for client connection \n");
    clientsocket = accept(serversocket, (struct sockaddr*) &clientaddr, &len);
    printf("\n clinet connectivity recieved\n");
    printf("\n Reading message from the client \n ");
    read(clientsocket,nums, sizeof(nums));
    sum=nums[0]+nums[1];
    printf("\n sending message to the client.\n");
    write(clientsocket,&sum, sizeof(sum));
    close(clientsocket);
    close(serversocket);
}


