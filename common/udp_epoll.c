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
	int new_fd, ret;
    struct sockaddr_in client;
    struct LogRequest request;
    struct LogResponse response;
    socklen_t len = sizeof(client);
    
    bzero(&client, len);
    bzero(&request, sizeof(request));
    bzero(&response, sizeof(response));

    ret = recvfrom(fd, (void *)&request, sizeof(request), 0, (struct sockaddr *)&client, &len);
    
    if (ret != sizeof(request)){
        response.Type = 1;
        strcpy(response.msg, "Login failed with Data errors!");
        sendto(fd, (void *)&response, sizeof(response), 0, (struct sockaddr *)&client, len);
        return -1;   
    }
    
    new_fd = udp_connect(&client);
    
    if (new_fd < 0){
        return -1;    
    }
    strcpy(user->name, request.name);
    user->team = request.team;
    user->fd = new_fd;
   
    response.Type = 0;
    strcpy(response.msg, "Login Success, Enjoy Yourself");
    send(new_fd, (void *)&response, sizeof(response), 0);
    
    return new_fd; 
}
