/*************************************************************************
	> File Name: show_strength.c
	> Author: 
	> Mail: 
	> Created Time: Thu 23 Jul 2020 05:14:41 PM CST
 ************************************************************************/

#include "head.h"
extern WINDOW *Write;
extern int sockfd;
void show_strength() {
    wattron(Football, COLOR_PAIR(8));
    w_gotoxy_puts(Write, 9, 1, "          ");
	make_non_block(sockfd);  　//非阻塞
	char a;
    while((a = getch()) != 'k' && (a != ' ')) {
	printf("hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh\n");
}
	struct FootBallMsg msg;
	bzero();
    send(sockfd, (void *)&chat_msg, sizeof(chat_msg), 0);
    wclear(Write);
    box(Write, 0, 0);
    wrefresh(Write);
    noecho();
    cbreak();
}
