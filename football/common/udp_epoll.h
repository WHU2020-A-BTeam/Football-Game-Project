#ifndef _UDP_EPOLL_H
#define _UDP_EPOLL_H
#include "../football/common/datatype.h"
int port;
void add_event_ptr(int epollfd, int fd, int events, struct User *user);
void del_event(int epoll, int fd);
int udp_connect(struct sockaddr_in *client);
int udp_accept(int fd, struct User *user);

#endif
