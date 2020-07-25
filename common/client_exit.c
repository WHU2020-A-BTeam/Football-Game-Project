/*************************************************************************
	> File Name: client_exit.c
	> Author: 
	> Mail: 
	> Created Time: Sat 25 Jul 2020 10:47:02 PM CST
 ************************************************************************/

#include"head.h"
extern int  sockfd;
extern struct LogRequest request;
void client_exit(){
    struct FootBallMsg msg;
    msg.type = FT_FIN;
    msg.team= request.team;
    strcpy(msg.name, request.name);
    send(sockfd, (void *)&msg, sizeof(msg), 0);
    close(sockfd);
    endwin();
    exit(0);
}
