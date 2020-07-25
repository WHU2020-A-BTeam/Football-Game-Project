/*************************************************************************
	> File Name: udp_epoll.h
	> Author: 
	> Mail: 
	> Created Time: Sat 25 Jul 2020 06:14:52 PM CST
 ************************************************************************/

#ifndef _UDP_EPOLL_H
#define _UDP_EPOLL_H

int port, bepollfd, repollfd;

struct User *rteam, *bteam;

int check_online(struct LogRequest *request);
void add_event_ptr(int epollfd, int fd, int events, struct User *user);
void del_event(int epoll, int fd);
int udp_connect(struct sockaddr_in *client);
int udp_accept(int fd, struct User *user);
int find_sub(struct User *team);
void add_to_sub_reactor(struct User *user);

#endif
