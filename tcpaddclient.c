#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int main() {
    int clientsocket, port;
    struct sockaddr_in serveraddr;
    socklen_t len;
    int nums[10],sum=0;

    scanf("%d%d",&nums[0],&nums[1]);
    clientsocket = socket(AF_INET, SOCK_STREAM, 0);
    bzero((char*) &serveraddr, sizeof(serveraddr));
    len = sizeof(serveraddr);
    serveraddr.sin_family = AF_INET;

    printf("enter the port number");
    scanf("%d", &port);
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr= inet_addr("127.0.0.1");
    printf("\n Trying to connect to the server. \n");
    connect(clientsocket, (struct sockaddr*) &serveraddr, sizeof(serveraddr));
    printf("\n connected to the server\n");

    printf("\n sending messge from server connection\n");
    send(clientsocket,nums, sizeof(nums), 0);

    printf("\n Recieving message from server. \n");
    recv(clientsocket,&sum, sizeof(sum), 0);
    printf("\n message recieved\t%d\n",sum);

    close(clientsocket);
}
