/*************************************************************************
	> File Name: server_send_all.c
	> Author: 
	> Mail: 
	> Created Time: Sat 25 Jul 2020 10:56:43 PM CST
 ************************************************************************/

#include"head.h"

extern struct User *rteam, *bteam;

void send_team(struct User *team, struct FootBallMsg *msg){
    for (int i = 0; i < MAX; i++) {
        if (team[i].online) send(team[i].fd, (void *)msg, sizeof(struct FootBallMsg), 0);          
    }
}
void send_all(struct FootBallMsg *msg) {
    send_team(rteam, msg);
    send_team(bteam, msg);
}


