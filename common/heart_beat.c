/*************************************************************************
	> File Name: heart_beat.c
	> Author: 
	> Mail: 
	> Created Time: Sat 25 Jul 2020 09:27:49 PM CST
 ************************************************************************/

#include "head.h"

extern struct User *rteam,*bteam;
extern int repollfd ,bepollfd;

void heart_beat_team(struct User *team){
    struct FootBallMsg tem;
    bzero(&tem, sizeof(struct FootBallMsg));
    tem.type = FT_HEART;
    for(int i = 0; i < MAX; i++){
        if(team[i].online){ 
			send(team[i].fd,(void*)&tem,sizeof(struct FootBallMsg), 0);
            team[i].flag--;
        	if(team[i].flag == 0){
             	team[i].online = 0;
             	if(team[i].team)
             		del_event(bepollfd,team[i].fd);
             	else 
             		del_event(repollfd,team[i].fd);
         	}
        }
    }
}

void *heart_beat(void *arg){
    while(1){
        sleep(1);
        heart_beat_team(rteam);
        heart_beat_team(bteam);
    }
}
