#include "../common/head.h"
char *conf = "./footballd.conf";
int bepollfd, repollfd;
struct User *rteam, *bteam;
struct Map court;
struct Bpoint ball;
struct Point op;
extern struct BallStatus ball_status;
pthread_mutex_t bmutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t rmutex = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char **argv){
	//printf("yes\n");
	int opt, listener, epollfd;
	pthread_t red_t, blue_t, heart_t;
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
	bzero(&court, sizeof(court));
	bzero(&ball, sizeof(ball));
	bzero(&ball_status, sizeof(ball_status));
	bzero(&op, sizeof(op));
	ball.x = 20;
	ball.y = 20;

	if(!port){ 
		port = atoi(get_conf_value(conf, "PORT"));
	}
	court.heigth = atoi(get_conf_value(conf, "LINES"));
	court.width = atoi(get_conf_value(conf, "COLS"));
	court.start.x = 3;
	court.start.y = 3;
	court.gate_width = 5;
	court.gate_heigth = 10;
	initfootball();

	if((listener = socket_create_udp(port)) < 0){
		perror("socket_create_udp()");
		exit(1);
	}
	repollfd = epoll_create(1);
	bepollfd = epoll_create(1);
	if ((epollfd = epoll_create(1)) < 0 || repollfd < 0 || bepollfd < 0){
        perror("epoll_create()");
        exit(1);
    }
	
	rteam = (struct User *)calloc(MAX, sizeof(struct User));
	bteam = (struct User *)calloc(MAX, sizeof(struct User));
	
	struct task_queue redQueue;
	struct task_queue blueQueue;
	task_queue_init(&redQueue, MAX, repollfd);
	task_queue_init(&blueQueue, MAX, bepollfd);
	pthread_create(&red_t, NULL, sub_reactor, (void *)&redQueue);
	pthread_create(&blue_t, NULL, sub_reactor, (void *)&blueQueue);
	pthread_create(&heart_t, NULL, heart_beat, NULL);
	struct epoll_event ev, events[MAX];
	ev.events = EPOLLIN;
	ev.data.fd = listener;

	if (epoll_ctl(epollfd, EPOLL_CTL_ADD, listener, &ev) < 0){
        perror("epoll_ctl");
        exit(1);
    }


	signal(14, re_draw);

	struct itimerval itimer;
	itimer.it_interval.tv_sec = 0;
	itimer.it_interval.tv_usec = 100000;
	itimer.it_value.tv_sec = 2;
	itimer.it_value.tv_usec = 0;
	setitimer(ITIMER_REAL, &itimer, NULL);

	while(1){
		int nfds = epoll_wait(epollfd, events, MAX, -1);
		//printf("no connect\n");
/*		if(nfds < 0) {
			perror("epoll_wait()");
			exit(1);
		}*/
		//printf("nfds = %d\n", nfds);
		for(int i = 0; i < nfds; ++i){
			struct User user;
			bzero(&user, sizeof(user));
			if(events[i].data.fd == listener) {
		//		printf("Connecting\n");
				int new_fd = udp_accept(listener, &user);

				//printf("yes %d\n", new_fd);
				if(new_fd > 0){
					printf("New Connection!\n");
					user.fd = new_fd;
					add_to_sub_reactor(&user);
				}

			}


		}
	}
	return 0;

}
