#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080

int main(int argc, char const *argv[]){
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *hello = "Hello from client";
    char buffer[1024] = {0};
    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("Socket creation error");
        return -1;
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    // Convert IP address
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0){
        perror("Invalid address / Address not supported");
        return -1;
    }
    // FIXED: struct sockaddr (missing space before)
    if (connect(sock, (struct sockaddr *)&serv_addr,
                sizeof(serv_addr)) < 0){
        perror("Connection Failed");
        return -1;
    }
    // Send
    send(sock, hello, strlen(hello), 0);
    printf("Hello message sent\n");
    // Read
    valread = read(sock, buffer, 1024);
    printf("%s\n", buffer);
    close(sock);
    return 0;
}
