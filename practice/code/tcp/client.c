// tcp_client.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);

    char buffer[1024];
    struct sockaddr_in serv_addr;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    write(sock_fd, "Hello from client!!!", 18);

    read(sock_fd, buffer, sizeof(buffer));
    printf("Server: %s\n", buffer);

    close(sock_fd);
}
