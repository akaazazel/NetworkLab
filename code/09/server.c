#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_CLIENTS 10
#define BUFFER_SIZE 1000

int main(int argc, char *argv[])
{

	int listen_fd, connfd, sockfd;
	int max_fd, maxi, nready;
	int client[MAX_CLIENTS];
	fd_set allset, rset;

	struct sockaddr_in servaddr, cliaddr;
	socklen_t len;

	char buffer[BUFFER_SIZE];
	int i, n;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: ./server <port>\n");
		exit(1);
	}

	listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_fd < 0)
	{
		perror("Socket creation failed");
		exit(1);
	}

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(atoi(argv[1]));
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(listen_fd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
	{
		perror("Bind failed");
		exit(1);
	}

	listen(listen_fd, 5);

	max_fd = listen_fd;
	maxi = -1;

	for (i = 0; i < MAX_CLIENTS; i++)
		client[i] = -1;

	FD_ZERO(&allset);
	FD_SET(listen_fd, &allset);

	while (1)
	{

		rset = allset;
		nready = select(max_fd + 1, &rset, NULL, NULL, NULL);

		// New connection
		if (FD_ISSET(listen_fd, &rset))
		{

			len = sizeof(cliaddr);
			connfd = accept(listen_fd, (struct sockaddr *)&cliaddr, &len);

			for (i = 0; i < MAX_CLIENTS; i++)
			{
				if (client[i] < 0)
				{
					client[i] = connfd;
					break;
				}
			}

			if (i == MAX_CLIENTS)
			{
				printf("Too many clients\n");
				close(connfd);
				continue;
			}

			FD_SET(connfd, &allset);
			if (connfd > max_fd)
				max_fd = connfd;
			if (i > maxi)
				maxi = i;

			sprintf(buffer, "New client connected\n");
			write(connfd, buffer, strlen(buffer));

			if (--nready <= 0)
				continue;
		}

		// Handle client data
		for (i = 0; i <= maxi; i++)
		{

			if ((sockfd = client[i]) < 0)
				continue;

			if (FD_ISSET(sockfd, &rset))
			{

				n = read(sockfd, buffer, sizeof(buffer));

				if (n <= 0)
				{
					close(sockfd);
					FD_CLR(sockfd, &allset);
					client[i] = -1;
				}
				else
				{
					// Broadcast to all clients
					for (int j = 0; j <= maxi; j++)
					{
						if (client[j] >= 0 && client[j] != sockfd)
						{
							write(client[j], buffer, n);
						}
					}
				}

				if (--nready <= 0)
					break;
			}
		}
	}
}