/*************************************************************************
	> File Name: client1.c
	> Author: 
	> Mail: 
	> Created Time: Mon 20 Jul 2020 11:25:44 PM CST
 ************************************************************************/

#include<stdio.h>
#include "../common/head.h"

int main(int argc, char **argv) {
    if (argc != 3) {
                fprintf(stderr, "Usage : %s ip port\n", argv[0]);
                exit(1);
            
    }
        char ip[20] = {0};
        int sockfd, port;
        strcpy(ip, argv[1]);
        port = atoi(argv[2]);

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
                perror("socket()");
                exit(1);
            
    }
        struct sockaddr_in server;
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = inet_addr(ip);
        server.sin_port = htons(port);
        socklen_t len = sizeof(server);
        char buff[512] = {0};
        sprintf(buff, "Can we connect?");
        sendto(sockfd, buff, strlen(buff), 0, (struct sockaddr *)&server, sizeof(server));
        bzero(buff, sizeof(buff));
        recvfrom(sockfd, buff, sizeof(buff), 0, (struct sockaddr*)&server, &len);
        printf("Server : %s\n", buff);
        connect(sockfd, (struct sockaddr *)&server, len);

    while (1) {
                bzero(buff, sizeof(buff));
                scanf("%[^\n]s", buff);
                getchar();
                send(sockfd, buff, strlen(buff), 0);
            
    }

        return 0;

}
