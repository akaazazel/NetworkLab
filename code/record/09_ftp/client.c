#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUF_SIZE 1024

int main()
{
    int sock;
    struct sockaddr_in serv_addr;

    char buffer[BUF_SIZE];
    char filename[100], newfile[100];

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Connect to localhost
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
    {
        perror("invalid address");
        exit(EXIT_FAILURE);
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("connection failed");
        exit(EXIT_FAILURE);
    }

    printf("Connected to server\n");

    printf("Enter file to request: ");
    scanf("%s", filename);

    printf("Enter output file name: ");
    scanf("%s", newfile);

    FILE *fp = fopen(newfile, "w");
    if (!fp)
    {
        perror("file open failed");
        exit(EXIT_FAILURE);
    }

    // Send filename
    send(sock, filename, strlen(filename), 0);

    while (1)
    {
        int n = recv(sock, buffer, BUF_SIZE - 1, 0);

        if (n <= 0)
            break;

        buffer[n] = '\0';

        if (strcmp(buffer, "ERROR") == 0)
        {
            printf("File not found on server\n");
            break;
        }

        if (strcmp(buffer, "EOF") == 0)
        {
            printf("File transfer completed\n");
            break;
        }

        fputs(buffer, fp);
        printf("%s", buffer);
    }

    fclose(fp);
    close(sock);

    return 0;
}
