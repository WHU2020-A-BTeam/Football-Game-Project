#include "head.h"
extern pthread_mutex_t bmutex;
extern pthread_mutex_t rmutex;
extern int bepollfd, repollfd;
void add_event_ptr(int epollfd, int fd, int events, struct User *user){
	struct epoll_event ev;
	ev.events = events;
	ev.data.ptr = (void *)user;
	epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
	//ev.data.ptr = (void *)user;
	//struct User *msg = (struct User *)ev.data.ptr;
	//printf("success : %d\n", msg->fd);
	return;
}

void del_event(int epollfd, int fd){
	epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, NULL);
	return;
}

extern int port;
extern struct User *rteam, *bteam;
int udp_connect(struct sockaddr_in *client){
	int sockfd;
	socklen_t len = sizeof(*client);
	//printf("port : %d", port);
	if((sockfd = socket_create_udp(port)) < 0){
		printf("socket_create_udp()");
		return -1;
	}
	if((connect(sockfd, (struct sockaddr *)client, len)) < 0){
		perror("connect()");
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
	//printf("yess\n");
    ret = recvfrom(fd, (void *)&request, sizeof(request), 0, (struct sockaddr *)&client, &len);
    //printf("good\n");
    if (ret != sizeof(request)){
		//printf("error!\n");
        response.Type = 1;
        strcpy(response.msg, "Login failed with Data errors!");
        sendto(fd, (void *)&response, sizeof(response), 0, (struct sockaddr *)&client, len);
        return -1;   
    }
    /*response.Type = 0;
	strcpy(response.msg, "Login, Please Wait......");
	sendto(fd, (void *)&response, sizeof(response), 0, (struct sockaddr *)&client, len);*/

	while(1){
    	new_fd = udp_connect((struct sockaddr_in *)&client);
		if(new_fd > 0){
			break;
		}
	}
    if (new_fd < 0){
		printf("error\n");
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
int find_sub(struct User *team){
	for(int i =0 ; i < MAX; i++){
		if(!team[i].online ) return i;
	}
	return -1;
}

void add_to_sub_reactor(struct User *user){
	struct User *team = (user->team ? bteam : rteam);
	if(user->team)
		pthread_mutex_lock(&bmutex);
	else
		pthread_mutex_lock(&rmutex);
	int sub = find_sub(team);
	if(sub < 0) return ;
	team[sub] = *user;
	team[sub].online = 1;
	team[sub].flag = 10;
	if(user->team)
		pthread_mutex_unlock(&bmutex);
	else
		pthread_mutex_unlock(&rmutex);

	if(user->team)
		add_event_ptr(bepollfd, team[sub].fd, EPOLLIN | EPOLLET, &team[sub]);
	else 
		add_event_ptr(repollfd, team[sub].fd, EPOLLIN | EPOLLET, &team[sub]);


}
