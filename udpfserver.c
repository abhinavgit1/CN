#include <stdio.h>
#include <arpa/inet.h>
#include <sys/types.h> 
#include <netinet/in.h> 
#include <netdb.h>
#include<string.h>
#include <unistd.h> 

int fact(int n){
	if(n==0||n==1)
		return 1;
	return n*fact(n-1);
}
int main() { 
    int serversocket, port; 
    struct sockaddr_in serveraddr, clientaddr; 
    socklen_t len; 
    int num; 

    serversocket = socket(AF_INET, SOCK_DGRAM, 0); 

    bzero((char*)&serveraddr, sizeof(serveraddr)); 
    serveraddr.sin_family = AF_INET; 

    printf("Enter the port number: "); 
    scanf("%d", &port); 
    serveraddr.sin_port = htons(port); 
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 

    bind(serversocket, (struct sockaddr*)&serveraddr, sizeof(serveraddr)); 

    printf("\nWaiting for the client connection\n"); 

    memset(&clientaddr,0, sizeof(clientaddr)); 
    len = sizeof(clientaddr); 

    recvfrom(serversocket, &num, sizeof(num), 0, (struct sockaddr*)&clientaddr, &len); 
    num=ntohl(num);
    printf("\nConnection received from client.\n"); 
    
    num=fact(num);
	
    printf("\nSending message to the client.\n"); 
    sendto(serversocket,&num, 
           sizeof(num), 0, (struct sockaddr*)&clientaddr, sizeof(clientaddr)); 

    close(serversocket); 
} 
