#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>

#define BUF_SIZE 500
#define BACKLOG  10

int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "usage: server <IP> <PORT>\n");
        return -1;
    }

    char buffer[BUF_SIZE], client[INET_ADDRSTRLEN];
    struct sockaddr_in servinfo, clientinfo;
    servinfo.sin_family = AF_INET;
    servinfo.sin_port = htons(atoi(argv[2]));
    inet_pton(servinfo.sin_family, argv[1], &(servinfo.sin_addr));
    int sfd = socket(servinfo.sin_family, SOCK_STREAM, getprotobyname("tcp")->p_proto);

    if (sfd == -1) {
        perror("socket");
        return 1;
    }

    if (bind(sfd, (struct sockaddr *) &servinfo, sizeof(servinfo)) == -1) {
        perror("bind");
        return 2;
    }

    if (listen(sfd, BACKLOG) == -1) {
        perror("listen");
        return 3;
    }

    printf("server: waiting for connections...\n");
    socklen_t sin_size = sizeof clientinfo;
    int new_fd = accept(sfd, (struct sockaddr *) &clientinfo, &sin_size);

    if (new_fd == -1) {
        perror("accept");
        return 4;
    }

    inet_ntop(clientinfo.sin_family, &clientinfo.sin_addr, client, sizeof(client));
    printf("Server: Got connection from %s.\n", client);
    int recvbytes = 0;

    do {
        memset(buffer, '\0', BUF_SIZE);
        printf("Enter a message: ");
        scanf("%s", buffer);
        
        if (send(new_fd, buffer, BUF_SIZE, 0) == -1)
            perror("send");

        printf("Server: %s\n", buffer);
        memset(buffer, '\0', BUF_SIZE);
        
        if ((recvbytes = recv(new_fd, buffer, BUF_SIZE - 1, 0)) == -1) {
            perror("recv");
            break;
        }

        buffer[recvbytes] = '\0';
        printf("Client: %s\n", buffer);
    } while (strcmp(buffer, "bye") != 0);

    close(new_fd);
    close(sfd);
    return 0;
}