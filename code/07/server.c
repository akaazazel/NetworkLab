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
    struct sockaddr_in server, cli;
    socklen_t cli_len;
    int sd, data, i, len;
    char buffer[100];

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <PORT>\n", argv[0]);
        exit(1);
    }

    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket failed");
        exit(1);
    }

    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[1]));
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sd, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("Bind failed");
        close(sd);
        exit(1);
    }

    listen(sd, 5);

    cli_len = sizeof(cli);
    if ((data = accept(sd, (struct sockaddr *)&cli, &cli_len)) < 0)
    {
        perror("Accept failed");
        close(sd);
        exit(1);
    }

    len = read(data, buffer, sizeof(buffer) - 1);
    if (len > 0)
    {
        buffer[len] = '\0';

        for (i = 0; i < len / 2; i++)
        {
            char temp = buffer[i];
            buffer[i] = buffer[len - 1 - i];
            buffer[len - 1 - i] = temp;
        }

        write(data, buffer, len);
    }

    close(data);
    close(sd);

    return 0;
}
