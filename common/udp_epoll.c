#include"udp_epoll.h"
void add_event_ptr(int epollfd, int fd, int events, struct User *user){
	struct epoll_event ev;
	ev.events = events;
	ev.data.ptr = user ;
    if( epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev)  < 0)
    {
        perror("epoll ctl ");
        exit(1);
    }
	return;
}

void del_event(int epollfd, int fd){
	epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, NULL);
	return;
}


