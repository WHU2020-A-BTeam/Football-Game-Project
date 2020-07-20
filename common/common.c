/*************************************************************************
	> File Name: common.c
	> Author: 
	> Mail: 
	> Created Time: Mon 20 Jul 2020 09:28:13 PM CST
 ************************************************************************/

#include "head.h"

void make_non_block(int fd) {
    unsigned long u1 = 1;
    ioctl(fd, FIONBIO, &u1);
}

void make_block(int fd) {
    unsigned long u1 = 0;
    ioctl(fd, FIONBIO, &u1);
}

int socket_create_udp(int port) {
    //创建SOCK_DGRAM套接字
    int listener;
    if ((listener = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket()");
        return -1;
    }
    //设置地址重用
    unsigned long opt = 1;
    setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
    //设置为非阻塞套接字
    make_non_block(listener);
    
    //绑定INADDR_ANY & port
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(port);

    if (bind(listener, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("bind()");
        return -1;
    }
    
    return listener;
}

int socket_udp() {
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("sockfd()");
        return -1;
    }
    return sockfd;
}
