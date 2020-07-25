/*************************************************************************
	> File Name: ball_status.c
	> Author: 
	> Mail: 
	> Created Time: Sat 25 Jul 2020 10:13:07 PM CST
 ************************************************************************/

#include "head.h"
extern struct Point op;
extern struct Bpoint ball;
extern struct BallStatus ball_status;
extern WINDOW *Message;

double cos_cal(double x, double y) {
    return x * sqrt(pow(x, 2) + pow(y, 2)) / (pow(x, 2) + pow(y, 2));
}

double sin_cal(double x, double y) {
    return y * sqrt(pow(x, 2) + pow(y, 2)) / (pow(x, 2) + pow(y, 2));
}

int can_kick(struct Point *loc, int strength) {
    const double a_speed = 40.0;
    const double a_speed_ = 10.0;
    double cos_value, sin_value;
    char buff[512] = { 0  };
    int locx = loc->x - 2;
    int locy = loc->y - 1;
    if (locx == ball.x && locy == ball.y) {
        return 0;    
    }
    ball.x = (double)(int)ball.x;
    ball.y = (double)(int)ball.y;
    if (abs(locx - ball.x) <= 2 && abs(locy - ball.y) <= 2) {
        bzero(&ball_status, sizeof(ball_status));
        if (locx == ball.x && locy == ball.y) {
            return 0;        
        }
        cos_value = cos_cal(abs(locx - ball.x), abs(locy - ball.y));
        sin_value = sin_cal(abs(locx - ball.x), abs(locy - ball.y));
        ball_status.a.x = ((ball.x - locx) > 0 ? 1 : -1) * (a_speed * cos_value) * strength;
        ball_status.a.y = ((ball.y - locy) > 0 ? 1 : -1) * (a_speed * sin_value) * strength;
        ball_status.v.y = ball_status.a.y * 0.2;
        ball_status.v.x = ball_status.a.x * 0.2;        
        ball_status.a.x = ((ball.x - locx) > 0 ? -1 : 1) * (a_speed_ * cos_value);
        ball_status.a.y = ((ball.y - locy) > 0 ? -1 : 1) * (a_speed_ * sin_value);
        sprintf(buff, "loc : %d %d ball %lf %lf apeed : %lf %lf", locx, locy, ball.x, ball.y, ball_status.a.x, ball_status.a.y);
        w_gotoxy_puts(Message, 0, 0, buff);
        return 1;    
    }
	return 0;
}

int can_carry(struct Point *loc) {
    ball.x = (double)(int)ball.x;
    ball.y = (double)(int)ball.y;
    int locx = loc->x - 2;
    int locy = loc->y - 1;

    if (abs(locx - ball.x) <= 2 && abs(locy - ball.y) <= 2) {
        op.x = locx - ball.x;
        op.y = locy - ball.y;
        ball_status.if_carry = 1;
        return 1;    
    }
    return 0;
}

int can_stop(struct Point *loc) {
    ball.x = (double)(int)ball.x;
    ball.y = (double)(int)ball.y;
    int locx = loc->x - 2;
    int locy = loc->y - 1;
    if (locx == ball.x && locy == ball.y) {
        return 0;    
    }
    if (abs(locx - ball.x) <= 2 && abs(locy - ball.y) <= 2) {
        if (ball_status.if_carry == 1) {
            srand(time(NULL));
            int i = rand() % 3;
            if (i == 0 || i == 1) {
                ball_status.if_carry = 0;            
            } else {
                return 0;            
            }          
        }
        ball_status.a.x = 0;
        ball_status.a.y = 0;
        ball_status.v.x = 0;
        ball_status.v.y = 0;
        return 1;    
    }
    return 0;
}
