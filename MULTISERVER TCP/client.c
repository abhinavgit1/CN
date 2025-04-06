
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 4444
#define BUF_SIZE 2000

int main(int argc, char *argv[]) {
    int sockfd, ret;
    struct sockaddr_in addr;
    char buffer[BUF_SIZE];

    if (argc < 2) {
        printf("Usage: %s <server_ip>\n", argv[0]);
        exit(1);
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = inet_addr(argv[1]);

    if (connect(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("Connection failed");
        exit(1);
    }

    printf("Connected to server. Type 'exit' to quit.\n");

    while (1) {
        printf("You: ");
        fgets(buffer, BUF_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = 0;

        ret = send(sockfd, buffer, strlen(buffer), 0);
        if (ret <= 0) break;

        if (strcmp(buffer, "exit") == 0) break;

        memset(buffer, 0, BUF_SIZE);
        ret = recv(sockfd, buffer, BUF_SIZE, 0);
        if (ret <= 0) break;

        buffer[ret] = '\0';
        printf("Server: %s\n", buffer);
    }

    close(sockfd);
    printf("Disconnected.\n");
    return 0;
}
