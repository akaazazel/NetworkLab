#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
    FILE *fp;
    int sd, newsd, port, bd, n;
    socklen_t clilen;

    char fileread[100], rcv[100];

    struct sockaddr_in servaddr, cliaddr;

    printf("Enter the port address: ");
    scanf("%d",&port);

    sd = socket(AF_INET, SOCK_STREAM, 0);

    if(sd < 0)
    {
        printf("Socket creation failed\n");
        exit(1);
    }
    else
        printf("Socket created\n");

    memset(&servaddr,0,sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);

    bd = bind(sd,(struct sockaddr *)&servaddr,sizeof(servaddr));

    if(bd < 0)
    {
        printf("Bind failed\n");
        exit(1);
    }
    else
        printf("Bind successful\n");

    listen(sd,5);
    printf("Server waiting for connection...\n");

    clilen = sizeof(cliaddr);

    newsd = accept(sd,(struct sockaddr *)&cliaddr,&clilen);

    if(newsd < 0)
    {
        printf("Accept failed\n");
        exit(1);
    }
    else
        printf("Client connected\n");

    n = recv(newsd, rcv, sizeof(rcv)-1, 0);

    if(n <= 0)
    {
        printf("Error receiving filename\n");
        close(newsd);
        return 0;
    }

    rcv[n] = '\0';

    printf("Client requested file: %s\n", rcv);

    fp = fopen(rcv,"r");

    if(fp == NULL)
    {
        send(newsd,"error",5,0);
        close(newsd);
        printf("File not found\n");
    }
    else
    {
        while(fgets(fileread,sizeof(fileread),fp) != NULL)
        {
            if(send(newsd,fileread,strlen(fileread),0) < 0)
            {
                printf("Can't send file contents\n");
                break;
            }
            sleep(1);
        }

        send(newsd,"completed",9,0);

        printf("File transfer completed\n");

        fclose(fp);
        close(newsd);
    }

    close(sd);

    return 0;
}
