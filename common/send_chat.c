/*************************************************************************
	> File Name: send_chat.c
	> Author: 
	> Mail: 
	> Created Time: Thu 23 Jul 2020 06:58:57 PM CST
 ************************************************************************/

#include "head.h"
extern int sockfd;
extern WINDOW *Write;
extern WINDOW *Football;
extern struct FootBallMsg chat_msg;
void send_chat(){
    echo();
    //keypad(stdscr,TRUE);
   // nocbreak();
    bzero(chat_msg.msg, sizeof(chat_msg.msg));
    w_gotoxy_puts(Write,1,1,"Input Message: ");
   // mvwscanw(Write,2,1,"%s",chat_msg.msg);*/  
    for(int i=0;i<50;i++){
        chat_msg.msg[i] = wgetch(Write);
        if(chat_msg.msg[i]==10){
            chat_msg.msg[i]=0; break;
        }
    }
   // wgetch(Write);
    chat_msg.type = FT_MSG;
    if(strlen(chat_msg.msg)!=0)
      //  printf("tttt!!");     
        send(sockfd,(void *)&chat_msg,sizeof(chat_msg),0);
    wclear(Write);
    box(Write,0,0);
    //wrefresh(Write);
   // wgetch(Football);
    noecho();
  //  cbreak; 
}
