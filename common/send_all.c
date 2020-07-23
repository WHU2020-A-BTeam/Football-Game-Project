#include "head.h"

extern User *rteam, *bteam;

void send_team(struct User *team, struct FootballMsg *msg){
	for(int i = 0; i < MAX; i++){
		if(team[i].online) send(team[i].fd, (void *)msg, sizeof(struct Football Msg), 0);
	}

}

void send_all(struct FootballMsg *msg){
	send_team(rteam, msg);
	send_team(bteam, msg);
}
