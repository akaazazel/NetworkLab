#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{

	int sock_fd, n, max_fd, nready;
	char line[100];
	fd_set rset;
	struct sockaddr_in servaddr;

	if (argc != 3)
	{
		fprintf(stderr, "Usage: ./client <IP> <port>\n");
		exit(1);
	}

	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_fd < 0)
	{
		perror("Socket creation failed");
		exit(1);
	}

	memset(&servaddr, 0, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(atoi(argv[2]));
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	if (connect(sock_fd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
	{
		perror("Connection failed");
		exit(1);
	}

	max_fd = sock_fd;

	while (1)
	{

		FD_ZERO(&rset);
		FD_SET(0, &rset);		// stdin
		FD_SET(sock_fd, &rset); // socket

		nready = select(max_fd + 1, &rset, NULL, NULL, NULL);

		if (FD_ISSET(0, &rset))
		{
			n = read(0, line, sizeof(line));
			if (n > 0)
			{
				write(sock_fd, line, n);
			}
		}

		if (FD_ISSET(sock_fd, &rset))
		{
			n = read(sock_fd, line, sizeof(line) - 1);
			if (n <= 0)
			{
				printf("Server closed connection\n");
				close(sock_fd);
				exit(0);
			}
			line[n] = '\0';
			printf("%s", line);
		}
	}
}