#include "head.h"

extern struct User *rteam, *bteam;
extern int repollfd, bepollfd;

void heart_beat_team(struct User *team){
	struct FootballMsg msg;
	for(int i = 0; i < MAX; i++){
		if(team[i].online == 1){
			bzero(&msg, sizeof(msg));
			msg.type = FT_HEART;
			msg.team = team[i].team;
			send(team[i].fd, (void *)&msg, sizeof(msg), 0);
			printf("send!\n");
            printf("flag: %d\n", team[i].flag);
            recv(team[i].fd, (void *)&msg, sizeof(msg), 0);
            if (!(msg.type & FT_ACK)) {
                team[i].flag--;
            }
			if(team[i].flag == 0){
				team[i].online = 0;
				del_event(team[i].team ? bepollfd : repollfd, team[i].fd);
				printf("failed!\n");
			}
		}
	}
	return ;
}

void *heart_beat(void *arg){
		pthread_detach(pthread_self());
		/*signal(SIGALRM, heart_beat_team(rteam));
		signal(SIGALRM, heart_beat_team(bteam));
		struct itimerval itimer;
		itimer.it_interval.tv_sec = 0;
		itimer.it_interval.tv_usec = 10000;
		itimer.it_value.tv_sec = 0;
		itimer.it_value.tv_usec = 200;
		
		setitimer(ITIMER_REAL, &itimer, NULL);*/

	while(1) {
		clock_t timer = clock();
		if(timer % 1000000 == 0){
			heart_beat_team(rteam);
			heart_beat_team(bteam);
			//printf("BEAT!\n");
		}
	}
}

