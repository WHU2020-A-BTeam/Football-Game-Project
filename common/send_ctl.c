/*************************************************************************
	> File Name: send_ctl.c
	> Author: 
	> Mail: 
	> Created Time: Thu 23 Jul 2020 04:39:22 PM CST
 ************************************************************************/
#include"head.h"
#include<stdio.h>
extern int sockfd;
extern struct FootBallMsg ctl_msg;
void send_ctl(){

    if(ctl_msg.ctl.dirx || ctl_msg.ctl.diry)
        send(sockfd,(void*)&ctl_msg, sizeof(ctl_msg),0);
    ctl_msg.ctl.dirx=ctl_msg.ctl.diry=0;

}
