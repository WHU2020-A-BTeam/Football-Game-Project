/*************************************************************************
	> File Name: send_chat.c
	> Author: 
	> Mail: 
	> Created Time: Sat 25 Jul 2020 10:34:20 PM CST
 ************************************************************************/

#include "head.h"
extern int sockfd;
extern WINDOW *Write;
extern WINDOW *Football;
extern struct FootBallMsg chat_msg;
void send_chat(){
    echo();
    bzero(chat_msg.msg, sizeof(chat_msg.msg));
    w_gotoxy_puts(Write,1,1,"Input Message: ");  
    for(int i = 0; i < 50; i++){
        chat_msg.msg[i] = wgetch(Write);
        if(chat_msg.msg[i] == 10){
            chat_msg.msg[i] = 0; 
			break;
        }
    }

    chat_msg.type = FT_MSG;
    if(strlen(chat_msg.msg)!=0)     
        send(sockfd, (void *)&chat_msg, sizeof(chat_msg), 0);
    wclear(Write);
    box(Write,0,0);
    noecho();
}
