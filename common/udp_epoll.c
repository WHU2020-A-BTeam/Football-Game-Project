void add_event_ptr(int epollfd, int fd, int events, struct User *user){
	struct epoll_event ev;
	ev.events = EPOLLIN;
	ev.data.fd = fd;
	epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev) < 0;
	return;
}

void del_event(int epollfd, int fd){
	epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, NULL);
	return;
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
 
