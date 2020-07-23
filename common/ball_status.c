#include "head.h"
extern struct Bpoint ball;
extern struct BallStatus ball_status;
double cos_cal(double x, double y){
	return x * sqrt(pow(x, 2) + pow(y, 2)) / (pow(x, 2) + pow(y, 2));
}
double sin_cal(double x, double y){
	return y * sqrt(pow(x, 2) + pow(y, 2)) / (pow(x, 2) + pow(y, 2));
}
int can_kick(struct Point *loc, int strength){
	const double a_speed = 4.0;;

	//if(loc->x == ball.x || loc->y == ball.y){
	if(abs(loc->x - ball.x) <= 2 && abs(loc->y - ball.y) <= 2){
		if(loc->x == ball.x){//同在垂直线上，力沿y轴方向
			ball_status.a.y = ((ball.y - loc->y) > 0 ? 1 : -1) * a_speed * strength;
			ball_status.a.x = 0;
			//ball_status.v.y = ball_status.a.y * 0.2;
			//ball_status.v.x = 0;
		}
		else if (loc->y == ball.y){//同在水平线上，力沿x轴方向
			ball_status.a.x = ((ball.x - loc->x) > 0 ? 1 : -1) * a_speed * strength;
			ball_status.a.y = 0;
		}
		else {
			cos_value = cos_cal(abs(loc->x - ball.x, abs(loc->y - ball.y)));//计算余弦
			sin_value = sin_cal(abs(loc->x - ball.x, abs(loc->y - ball.y)));//计算正弦
			ball_status.a.x = ((ball.x - loc->x) > 0 ? 1 : -1) * (a_speed * cos_value) * strength;
			ball_status.a.y = ((ball.y - loc->y) > 0 ? 1 : -1) * (a_speed * sin_value) * strength;
		}
		//获得初速度
		ball_status.v.y = ball_status.a.y * 0.2;
		ball_status.v.x = ball_status.a.x * 0.2;
		//加速度取反，此后做匀减速运动
		ball_status.a.x = - ball_status.a.x;
		ball_status.a.y = - ball_status.a.y;

		return 1;
	}
	//不能踢，返回0
	return 0;
}


