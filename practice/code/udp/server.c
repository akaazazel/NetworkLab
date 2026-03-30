// udp_server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int sockfd;
    char buffer[1024];
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    // 1. Create socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    // 2. Fill server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5000);       // Port number
    server_addr.sin_addr.s_addr = INADDR_ANY; // Accept from any IP

    // 3. Bind socket to IP + Port
    bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    printf("Server listening on port 5000...\n");

    // 4. Receive data
    recvfrom(sockfd, buffer, sizeof(buffer), 0,
             (struct sockaddr *)&client_addr, &addr_len);

    printf("Message received: %s\n", buffer);

    close(sockfd);
    return 0;
}
