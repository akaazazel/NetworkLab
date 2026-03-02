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
    int i, j, n;
    int sock_fd;
    struct sockaddr_in servaddr;

    int matrix_1[MAX][MAX], matrix_2[MAX][MAX], matrix_product[MAX][MAX];
    int size[2][2];
    int num_rows_1, num_cols_1, num_rows_2, num_cols_2;

    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <ServerIP> <Port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    printf("Enter rows of first matrix (<=10): ");
    scanf("%d", &num_rows_1);
    printf("Enter columns of first matrix (<=10): ");
    scanf("%d", &num_cols_1);

    if (num_rows_1 > MAX || num_cols_1 > MAX)
    {
        printf("Matrix size exceeds limit\n");
        exit(EXIT_FAILURE);
    }

    printf("Enter values of first matrix:\n");
    for (i = 0; i < num_rows_1; i++)
        for (j = 0; j < num_cols_1; j++)
            scanf("%d", &matrix_1[i][j]);

    size[0][0] = num_rows_1;
    size[0][1] = num_cols_1;

    printf("Enter rows of second matrix (<=10): ");
    scanf("%d", &num_rows_2);
    printf("Enter columns of second matrix (<=10): ");
    scanf("%d", &num_cols_2);

    if (num_cols_1 != num_rows_2)
    {
        printf("Matrices cannot be multiplied\n");
        exit(EXIT_FAILURE);
    }

    if (num_rows_2 > MAX || num_cols_2 > MAX)
    {
        printf("Matrix size exceeds limit\n");
        exit(EXIT_FAILURE);
    }

    printf("Enter values of second matrix:\n");
    for (i = 0; i < num_rows_2; i++)
        for (j = 0; j < num_cols_2; j++)
            scanf("%d", &matrix_2[i][j]);

    size[1][0] = num_rows_2;
    size[1][1] = num_cols_2;

    sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_fd < 0)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(atoi(argv[2]));

    if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
    {
        perror("inet_pton");
        exit(EXIT_FAILURE);
    }

    sendto(sock_fd, size, sizeof(size), 0,
           (struct sockaddr *)&servaddr, sizeof(servaddr));

    sendto(sock_fd, matrix_1,
           num_rows_1 * num_cols_1 * sizeof(int), 0,
           (struct sockaddr *)&servaddr, sizeof(servaddr));

    sendto(sock_fd, matrix_2,
           num_rows_2 * num_cols_2 * sizeof(int), 0,
           (struct sockaddr *)&servaddr, sizeof(servaddr));

    recvfrom(sock_fd, matrix_product,
             num_rows_1 * num_cols_2 * sizeof(int),
             0, NULL, NULL);

    printf("\nProduct Matrix:\n");
    for (i = 0; i < num_rows_1; i++)
    {
        for (j = 0; j < num_cols_2; j++)
            printf("%d ", matrix_product[i][j]);
        printf("\n");
    }

    close(sock_fd);
    return 0;
}
