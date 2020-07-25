/*************************************************************************
	> File Name: client_recv.c
	> Author: 
	> Mail: 
	> Created Time: Sat 25 Jul 2020 10:42:18 PM CST
 ************************************************************************/

#include"head.h"
extern int sockfd;
extern WINDOW * Football;
void *client_recv(void * arg){
    struct FootBallMsg msg;
    recv(sockfd, (void *)&msg, sizeof(msg), 0);
    if(msg.type & FT_FIN){
        w_gotoxy_puts(Football, 10, 10, "SERVER CLOSED!") ;
        close(sockfd);
        endwin();
    } else if(msg.type & FT_HEART) {
        msg.type = FT_ACK;
        send(sockfd, (void *)&msg, sizeof(msg), 0);    
    }
}
