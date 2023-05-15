#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>

#define BUF_SIZE 500

int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "usage: client <IP> <PORT>\n");
        return -1;
    }

    char buffer[BUF_SIZE];
    struct sockaddr_in servinfo;
    servinfo.sin_family = AF_INET;
    servinfo.sin_port = htons(atoi(argv[2]));
    inet_pton(servinfo.sin_family, argv[1], &(servinfo.sin_addr));
    int sfd = socket(servinfo.sin_family, SOCK_STREAM, getprotobyname("tcp")->p_proto);

    if (connect(sfd, (struct sockaddr *) &servinfo, sizeof(servinfo)) == -1) {
        close(sfd);
        perror("connect");
        return 1;
    }

    printf("Connected to %s.\n", argv[1]);
    int recvbytes = 0;

    do {
        memset(buffer, '\0', BUF_SIZE);
        if ((recvbytes = recv(sfd, buffer, BUF_SIZE - 1, 0)) == -1) {
            perror("recv");
            break;
        }

        buffer[recvbytes] = '\0';
        printf("Server: %s\n", buffer);

        memset(buffer, '\0', BUF_SIZE);
        printf("Enter a message: ");
        scanf("%s", buffer);
        
        if (send(sfd, buffer, BUF_SIZE, 0) == -1)
            perror("send");

        printf("Client: %s\n", buffer);
    } while (strcmp(buffer, "bye") != 0);

    close(sfd);
    return 0;
}