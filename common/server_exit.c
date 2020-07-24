/*************************************************************************
	> File Name: server_exit.c
	> Author: 
	> Mail: 
	> Created Time: Fri 24 Jul 2020 12:06:54 PM CST
 ************************************************************************/

#include<stdio.h>
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
