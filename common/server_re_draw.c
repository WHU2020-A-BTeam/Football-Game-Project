/*************************************************************************
	> File Name: server_re_draw.c
	> Author: 
	> Mail: 
	> Created Time: Wed 22 Jul 2020 09:56:12 PM CST
 ************************************************************************/

#include<stdio.h>
#include"head.h" 
extern struct Map court;
extern struct User *rteam, *bteam;
extern WINDOW *Football, *Football_t;
extern struct BallStatus ball_status;
extern struct Bpoint ball;
int time1=2;
void re_drew_ball() {
    ball.x = ball.x+ ball_status.v.x * time1 + 0.5*ball_status.a.x * time1 * time1;
    ball.y = ball.y+ ball_status.v.y * time1 + 0.5*ball_status.a.y * time1 * time1;
    ball_status.v.x = ball_status.v.x + ball_status.a.x*time1;
    ball_status.v.y = ball_status.v.y + ball_status.a.y*time1;
    if(ball_status.v.x == 0){    //还需要处理！
        ball_status.a.x = 0;
        ball_status.v.x = 0;
    }
    if(ball_status.v.y ==0 ){
        ball_status.a.y = 0;
        ball_status.v.y = 0;
    }
    if( !(ball.x <court.width && ball.x>0 )){
        if(ball.x>=court.width) ball.x = court.width;
        else if(ball.x <= 0) ball.x =0;
    }
    if( !(ball.y <court.heigth && ball.y>0 )){
        if(ball.x>=court.width) ball.y = court.heigth;
        else if(ball.y <= 0) ball.y =0;
    }
    //根据ball_status里记录的加速度，和上次re_drew时的速度，算出本次球应该移动的时间
    //加速度保持不变，速度更新
    //需要注意的是，当判断到速度减为0，ball_status里的速度和加速度都清空
    //同样需要注意的时，球如果超过球场边界，则判定为出界，球停止到边界即可
}
void  re_drew_player(int team, char *name, struct Point *loc) {
    //根据team，切//在loc位置打印player，并显示姓名
    if(team){
        for(int i=0; i<MAX; i++){
            if(bteam[i].online == 1){
                if(strcmp(bteam[i].name, name)==0){
                   // printf("new!!!\n")                    
                    wattron(Football_t, COLOR_PAIR(2));
                    w_gotoxy_putc(Football_t,loc->x,loc->y,'K');
                    w_gotoxy_puts(Football_t,loc->x+1,loc->y-1,name);
                }
            }
        }
    }
    else{
        for(int i=0; i<MAX; i++){
            if(rteam[i].online == 1){
                if(strcmp(rteam[i].name, name)==0){
                    wattron(Football_t, COLOR_PAIR(6));
                    w_gotoxy_putc(Football_t,loc->x,loc->y,'T');
                    w_gotoxy_puts(Football_t,loc->x+1,loc->y-1,name);
                }
            }
        
          }
      }
}
void re_drew_team(struct User *team,int rb) {
    for(int i=0;i<MAX;i++){
        if(team[i].online) {
           // printf("%s",team[i].name);       
            re_drew_player(rb,team[i].name,&team[i].loc);
    }
    }
    //在team数组中，循环遍历用户，调用re_drew_palyer
}
void re_draw(){
        //printf("zqzqe");
    //    werase(Football);
        werase(Football_t);
        box(Football_t, 0, 0); 
        re_drew_team(rteam,0);
        re_drew_team(bteam,1);
        re_drew_ball();
        //sleep(1);
     
    //分别调用re_drew_team、re_drew_ball
}







