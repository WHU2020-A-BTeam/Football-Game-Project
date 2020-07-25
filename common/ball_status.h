/*************************************************************************
	> File Name: ball_status.h
	> Author: 
	> Mail: 
	> Created Time: Sat 25 Jul 2020 10:12:27 PM CST
 ************************************************************************/

#ifndef _BALL_STATUS_H
#define _BALL_STATUS_H
int can_kick(struct Point *loc, int strength);
int can_carry(struct Point *loc);
int can_stop(struct Point*);
#endif
