#include "head.h"

void *heart_beat_client(void *arg){
	int sockfd = *(int *)arg;
	//pthread_detach(pthread_self());	
	while(1){
		struct FootballMsg msg;
		bzero(&msg, sizeof(msg));
		recv(sockfd, (void *)&msg, sizeof(msg), 0);
		if(msg.type & FT_HEART){
			msg.type = FT_ACK;
			send(sockfd, (void *)&msg, sizeof(msg), 0);
			printf("answer!!\n");
		}
	}
}
