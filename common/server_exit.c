/*************************************************************************
	> File Name: server_exit.c
	> Author: 
	> Mail: 
	> Created Time: Sat 25 Jul 2020 10:55:30 PM CST
 ************************************************************************/

#include"head.h"
extern struct User *rteam,*bteam;
void server_exit(){

    struct FootBallMsg msg;
    msg.type = FT_FIN;
    for(int i = 0; i < MAX; i++){
        if(rteam[i].online) send(rteam[i].fd, (void*)&msg, sizeof(msg), 0);
        if(bteam[i].online) send(bteam[i].fd, (void*)&msg, sizeof(msg), 0);
        
    }
    endwin();
    exit(0);
}

