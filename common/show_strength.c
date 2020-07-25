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

    int maxx, maxy, strength;
    getmaxyx(Write, naxy, maxx);
    struct FootballMsg msg;
    bzero(&msg, sizeof(msg));
    for(int i = 2; i < maxx - 2; i++) {
        if(i < maxx / 5 || i > (maxx - maxx / 5)) {
            wattron(Write, COLOR_PAIR(8));
        } else if (i < 2 * maxx / 5 || i > 3 * maxx / 5) {
            wattron(Write, COLOR_PAIR(9));
        } else  {
            wattron(Write, COLOR_PAIR(10));
        }
        mvwaddch(Write, 2, i, ' ');
    }
    wattron(Football, COLOR_PAIR(3));
    int tmp[5] = {1,2,3,2,1};
    int oddset = 1;
    int tmp_x = 2;
    make_non_block(sockfd);  　//非阻塞
    char a;
    while((a = getchar()) != 'k' && (a != ' ')) {
	    usleep(5000);
        mvwaddch(Write, 1, tmp_x, ' ');
        mvwaddch(Write, 3, tmp_x, ' ');
        tmp_x += offset;        
        mvwaddch(Write, 1, tmp_x, ' ');
        mvwaddch(Write, 3, tmp_x, ' ');
        mvwaddch(Write, 4, tmp_x, ' ');
        if(tmp_x >= maxx - 2) offset = -1;
        if(tmp_x <= 2) offset = -1;
        wrefresh(Write);
        mvwaddch(Write, 3, tmp_x, ' ');
    }
    mvwaddch(Write, 1, tmp_x, ' ');
    mvwaddch(Write, 3, tmp_y, ' ');
    make_block(0);
    char info[512] = {0};
    sprintf(info, "strength = %d", tmp[tmp_x / (maxx / 5)]);
	msg.ctl.action = ACTION_KICK;
    msg.ctl.strength = tmp[tmp_x / (maxx / 5)];
    send(sockfd, (void *)&msg, sizeof(msg), 0);
    
}
