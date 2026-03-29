#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 8080
#define BUF_SIZE 1024

int main()
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);

    char buffer[BUF_SIZE];

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    memset(&address, 0, sizeof(address));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen
    if (listen(server_fd, 5) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    // Accept
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen)) < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    printf("Client connected\n");

    // Receive filename
    int n = recv(new_socket, buffer, BUF_SIZE - 1, 0);
    if (n <= 0)
    {
        perror("recv");
        close(new_socket);
        exit(EXIT_FAILURE);
    }
    buffer[n] = '\0';

    FILE *fp = fopen(buffer, "r");

    if (fp == NULL)
    {
        send(new_socket, "ERROR", 5, 0);
        close(new_socket);
        close(server_fd);
        return 0;
    }

    // Send file content
    while (fgets(buffer, BUF_SIZE, fp))
    {
        send(new_socket, buffer, strlen(buffer), 0);
    }

    // End marker
    send(new_socket, "EOF", 3, 0);

    printf("File sent successfully\n");

    fclose(fp);
    close(new_socket);
    close(server_fd);

    return 0;
}
