#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    char msg[] = "Hello from client!\0";
    struct sockaddr_in serv_addr;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    sendto(sockfd, msg, strlen(msg), 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    printf("Message sent!");
    close(sockfd);

    return 0;
}
