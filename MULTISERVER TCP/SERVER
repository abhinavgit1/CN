#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 4444
#define BUF_SIZE 2000

int main() {
    int sockfd, newsockfd, ret;
    struct sockaddr_in addr, cl_addr;
    socklen_t len;
    char buffer[BUF_SIZE];
    char clientIP[INET_ADDRSTRLEN];
    pid_t childpid;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);

    if (bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("Bind failed");
        exit(1);
    }

    listen(sockfd, 5);
    printf("Server listening on port %d...\n", PORT);

    while (1) {
        len = sizeof(cl_addr);
        newsockfd = accept(sockfd, (struct sockaddr*)&cl_addr, &len);
        if (newsockfd < 0) {
            perror("Accept failed");
            continue;
        }

        inet_ntop(AF_INET, &cl_addr.sin_addr, clientIP, sizeof(clientIP));
        printf("Connection accepted from %s\n", clientIP);

        if ((childpid = fork()) == 0) {
            close(sockfd);  // Child does not need the listening socket

            while (1) {
                memset(buffer, 0, BUF_SIZE);
                ret = recv(newsockfd, buffer, BUF_SIZE, 0);
                if (ret <= 0) break;
                buffer[ret]='\0';
                buffer[strcspn(buffer, "\n")] = 0;  // Remove newline
                if (strcmp(buffer, "exit") == 0) break;

                printf("Client %s: %s\n", clientIP, buffer);
                send(newsockfd, buffer, strlen(buffer), 0);
            }

            printf("Client %s disconnected.\n", clientIP);
            close(newsockfd);
            exit(0); // Exit child process
        }

        close(newsockfd); // Parent closes the client socket
    }

    return 0;
}
