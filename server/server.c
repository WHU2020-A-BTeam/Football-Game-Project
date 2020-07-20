#include "head.h"
#include "udp_epoll.h"
#define MAX 10
char *conf = "./footballd.conf";

int main(int argc, char **argv){
	int opt, listener, epollfd;
	pthread_t red_t, blue_t;
	while((opt = getopt(argc, argv, "p:")) != -1){
		switch (opt) {
			case 'p':
				port = atoi(optarg);
				break;
			default:
				fprintf(stderr, "Usage : %s -p port\n", argv[0]);
				exit(1);
		}
	}
	char *str = get_conf_value(conf,"PORT");
	if(str == NULL){
		perror("get_conf_value()");
		exit(1);
	}
	printf("%s\n", str);
	if(!port) port = atoi(str);

	if((listener = socket_create_udp(port)) < 0){
		perror("socket_create_udp()");
		exit(1);
	}

	if ((epollfd = epoll_create(1))<0){
        perror("epoll_create()");
        exit(1);
    }

	struct epoll_event ev, events[MAX];
	ev.events = EPOLLIN;
	ev.data.fd = listener;

	if (epoll_ctl(epollfd, EPOLL_CTL_ADD, listener, &ev) < 0){
        perror("epoll_ctl");
        exit(1);
    }

	while(1){
		int nfds = epoll_wait(epollfd, events, MAX, -1);
		if(nfds < 0) {
			perror("epoll_wait()");
			exit(1);
		}
		for(int i = 0; i < nfds; i++){
			struct User user;
			bzero(&user, sizeof(user));
			if(events[i].data.fd == listener) {
				int new_fd = udp_accept(listener, &user);
				if(new_fd > 0){
					printf("New Connection!\n");

				}
			}
		}
	}
	return 0;

}
