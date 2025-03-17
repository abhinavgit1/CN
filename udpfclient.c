#include <stdio.h>
#include <netinet/in.h> 
#include <netdb.h> 
#include <arpa/inet.h>
#include <unistd.h>
#include <strings.h> 

int main() { 
    int clientsocket, port; 
    struct sockaddr_in serveraddr; 
    socklen_t len;  
    char message[50];
    int num; 

    clientsocket = socket(AF_INET, SOCK_DGRAM, 0); 

    bzero((char*)&serveraddr, sizeof(serveraddr)); 
    len = sizeof(serveraddr); 
    serveraddr.sin_family = AF_INET; 

    printf("Enter the port number: "); 
    scanf("%d", &port); 
    serveraddr.sin_port = htons(port); 
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Use server's IP address
    scanf("%d",&num); 
    printf("\nSending message for server connection\n"); 
    num=htonl(num);
    sendto(clientsocket,&num, sizeof(num), 0, 
           (struct sockaddr*)&serveraddr, sizeof(serveraddr)); 

    printf("\nReceiving message from server.\n"); 

    recvfrom(clientsocket,&num, sizeof(num), 0, 
             (struct sockaddr*)&serveraddr, &len); 

    printf("\nMessage received:\t%d\n",num); 

    close(clientsocket); 
} 
