/*************************************************************************
	> File Name: send_ctl.c
	> Author:zhangsheng 
	> Mail: 
	> Created Time: Thu 23 Jul 2020 02:20:31 PM CST
 ************************************************************************/

#include "head.h"

extern int sockfd;
extern struct FootballMsg ctl_msg;

void send_ctl(){
    if (ctl_msg.ctl.dirx || ctl_msg.ctl.diry)
        send(sockfd, (void *)&ctl_msg, sizeof(ctl_msg), 0);
    ctl_msg.ctl.dirx = ctl_msg.ctl.diry = 0;
}

