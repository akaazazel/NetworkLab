#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>

int main()
{
    FILE *fp;
    int csd, s, cport;
    char name[100], rcvg[100], fname[100];

    struct sockaddr_in servaddr;

    printf("Enter the port: ");
    scanf("%d", &cport);

    csd = socket(AF_INET, SOCK_STREAM, 0);

    if(csd < 0)
    {
        printf("Socket creation error\n");
        exit(1);
    }
    else
        printf("Socket created\n");

    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(cport);

    // connect to localhost server
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(connect(csd,(struct sockaddr *)&servaddr,sizeof(servaddr)) < 0)
    {
        printf("Error in connection\n");
        exit(1);
    }
    else
        printf("Connected to server\n");

    printf("Enter the existing file name: ");
    scanf("%s", name);

    printf("Enter the new file name: ");
    scanf("%s", fname);

    fp = fopen(fname, "w");

    if(fp == NULL)
    {
        printf("File creation failed\n");
        close(csd);
        exit(1);
    }

    send(csd, name, sizeof(name), 0);

    while(1)
    {
        s = recv(csd, rcvg, sizeof(rcvg)-1, 0);

        if(s <= 0)
            break;

        rcvg[s] = '\0';

        if(strcmp(rcvg, "error") == 0)
        {
            printf("File is not available\n");
            break;
        }

        if(strcmp(rcvg, "completed") == 0)
        {
            printf("File transfer completed\n");
            break;
        }

        fputs(rcvg, fp);
        printf("%s", rcvg);
    }

    fclose(fp);
    close(csd);

    return 0;
}
