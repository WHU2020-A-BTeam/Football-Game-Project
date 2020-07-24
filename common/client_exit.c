/*************************************************************************
	> File Name: client_exit.c
	> Author: 
	> Mail: 
	> Created Time: Fri 24 Jul 2020 01:10:44 PM CST
 ************************************************************************/

#include<stdio.h>
#include"head.h"
extern int  sockfd;
extern struct LogRequest request;
void client_exit(){

    struct FootBallMsg msg;
    msg.type = FT_FIN;
    msg.team= request.team;
    strcpy(msg.name , request.name);
    send(sockfd,(void*)&msg,sizeof(msg),0);
    close(sockfd);
    endwin();
    exit(0);
}
