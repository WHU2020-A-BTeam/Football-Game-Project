#ifndef _UDP_EPOLL_H
#define _UDP_EPOLL_H

//int port, bepollfd, repollfd;
//struct User *rteam, *bteam;
//pthread_mutex_t bmutex = PTHREAD_MUTEX_INITIALIZER;
//pthread_mutex_t rmutex = PTHREAD_MUTEX_INITIALIZER;


void add_event_ptr(int epollfd, int fd, int events, struct User *user);
void del_event(int epoll, int fd);
int check_online(struct LogRequest *request);
int udp_connect(struct sockaddr_in *client);
int udp_accept(int fd, struct User *user);
int find_sub(struct User *team);
void add_to_sub_reactor(struct User *user);
#endif
