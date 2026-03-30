#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    char buffer[1024];
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t addr_len = sizeof(cli_addr);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    printf("Listening...\n");

    while (1)
    {

        recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&cli_addr, &addr_len);

        if (buffer != "0")
        {
            printf("Message: %s\n", buffer);
        }
    }
    close(sockfd);
    return 0;
}
