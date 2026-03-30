#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    char buffer[1024];
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t addr_len = sizeof(cli_addr);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    listen(sockfd, 5);
    printf("waiting...");

    int new_sock = accept(sockfd, (struct sockaddr *)&cli_addr, &addr_len);
    read(new_sock, buffer, sizeof(buffer));
    printf("Message: %s\n", buffer);

    write(new_sock, "Hello from server!", 18);

    close(new_sock);
    close(sockfd);
}
