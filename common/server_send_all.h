/*************************************************************************
	> File Name: server_send_all.h
	> Author: 
	> Mail: 
	> Created Time: Fri 24 Jul 2020 01:06:35 PM CST
 ************************************************************************/

#ifndef _SERVER_SEND_ALL_H
#define _SERVER_SEND_ALL_H

void send_team(struct User *team, struct FootBallMsg *msg);
void send_all(struct FootBallMsg *msg);
#endif
