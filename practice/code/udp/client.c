// udp_client.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int sockfd;
    char message[] = "Hello from client";
    struct sockaddr_in server_addr;

    // 1. Create socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    // 2. Fill server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // localhost

    // 3. Send message
    sendto(sockfd, message, strlen(message), 0,
           (struct sockaddr *)&server_addr, sizeof(server_addr));

    printf("Message sent\n");

    close(sockfd);
    return 0;
}
