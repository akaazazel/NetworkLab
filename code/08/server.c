#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX 10

int main(int argc, char *argv[])
{
    int sock_fd, n;
    int i, j, k;

    int row_1, col_1, row_2, col_2;
    int matrix_1[MAX][MAX], matrix_2[MAX][MAX], matrix_product[MAX][MAX];
    int size[2][2];

    struct sockaddr_in servaddr, cliaddr;
    socklen_t len = sizeof(cliaddr);

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_fd < 0)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(atoi(argv[1]));
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sock_fd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    recvfrom(sock_fd, size, sizeof(size), 0,
             (struct sockaddr *)&cliaddr, &len);

    row_1 = size[0][0];
    col_1 = size[0][1];
    row_2 = size[1][0];
    col_2 = size[1][1];

    if (row_1 > MAX || col_1 > MAX || row_2 > MAX || col_2 > MAX)
    {
        printf("Matrix size exceeds server limits\n");
        close(sock_fd);
        exit(EXIT_FAILURE);
    }

    recvfrom(sock_fd, matrix_1,
             row_1 * col_1 * sizeof(int), 0,
             (struct sockaddr *)&cliaddr, &len);

    recvfrom(sock_fd, matrix_2,
             row_2 * col_2 * sizeof(int), 0,
             (struct sockaddr *)&cliaddr, &len);

    for (i = 0; i < row_1; i++)
        for (j = 0; j < col_2; j++)
        {
            matrix_product[i][j] = 0;
            for (k = 0; k < col_1; k++)
                matrix_product[i][j] += matrix_1[i][k] * matrix_2[k][j];
        }

    sendto(sock_fd, matrix_product,
           row_1 * col_2 * sizeof(int), 0,
           (struct sockaddr *)&cliaddr, len);

    close(sock_fd);
    return 0;
}
