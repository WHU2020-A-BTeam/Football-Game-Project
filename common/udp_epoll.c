#include "head.h"

void add_event_ptr(int epollfd, int fd, int events, struct User *user){
	struct epoll_event ev;
	ev.events = events;
	ev.data.fd = fd;
	epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
	ev.data.ptr = user;
	return;
}

void del_event(int epollfd, int fd){
	epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, NULL);
	return;
}

extern int port;

int udp_connect(struct sockaddr_in *client){
	int sockfd;
	socklen_t len = sizeof(client);
	if((sockfd = socket_create_udp(port)) < 0){
		return -1;
	}
	if((connect(sockfd, (struct sockaddr *)&client, len)) < 0){
		return -1;
	}
	
	return sockfd;
}

int udp_accept(int fd, struct User *user){
	return -1;
}
