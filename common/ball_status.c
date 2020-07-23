#include "head.h"
extern struct Bpoint ball;
extern struct BallStatus ball_status;


int can_kick(struct Point *loc, int strength){
	const double a_speed = 4.0;
	const double para = sqrt(2);
	//if(loc->x == ball.x || loc->y == ball.y){
	if(abs(loc->x - ball.x) <= 2 && abs(loc->y - ball.y) <= 2){
		if(loc->x == ball.x){
			ball_status.a.y = ((ball.y - loc->y) > 0 ? 1 : -1) * a_speed * strength;
			ball_status.a.x = 0;
			//ball_status.v.y = ball_status.a.y * 0.2;
			//ball_status.v.x = 0;
		}
		else if (loc->y == ball.y){
			ball_status.a.x = ((ball.x - loc->x) > 0 ? 1 : -1) * a_speed * strength;
			ball_status.a.y = 0;
		}
		else {
			ball_status.a.x = ((ball.x - loc->x) > 0 ? 1 : -1) * (a_speed * 0.5 * para) * strength;
			ball_status.a.y = ((ball.y - loc->y) > 0 ? 1 : -1) * (a_speed * 0.5 * para) * strength;
		}
		ball_status.v.y += ball_status.a.y * 0.2;
		ball_status.v.x += ball_status.a.x * 0.2;
		return 1;
	}
	return 0;
}


