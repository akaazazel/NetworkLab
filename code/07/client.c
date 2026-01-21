#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    struct sockaddr_in server;
    int sd;
    char buffer[200];
    ssize_t n;

    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <IP> <PORT>\n", argv[0]);
        exit(1);
    }

    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket failed");
        exit(1);
    }

    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[2]));

    if (inet_pton(AF_INET, argv[1], &server.sin_addr) <= 0)
    {
        perror("Invalid address");
        close(sd);
        exit(1);
    }

    if (connect(sd, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("Connection failed");
        close(sd);
        exit(1);
    }

    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';

    write(sd, buffer, strlen(buffer));

    n = read(sd, buffer, sizeof(buffer) - 1);
    if (n > 0)
    {
        buffer[n] = '\0';
        printf("%s\n", buffer);
    }

    close(sd);
    return 0;
}
