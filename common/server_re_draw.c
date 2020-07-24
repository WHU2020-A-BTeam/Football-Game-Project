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
extern struct Point op;
struct Point pnt = {0,0};

int search_player(struct User *team, char *name){
    for(int i = 0; i < MAX; i++){
        if(team[i].online == 1){
            if(strcmp(name, team[i].name) == 0){
                                return i;
                            
            }
                    
        }
            
    }
        return -1;

}


void re_drew_ball() {
        w_gotoxy_putc(Football, (int)ball.x, (int)ball.y, ' ');
        double a_x = ball_status.a.x;
        double a_y = ball_status.a.y;
        double v_x = ball_status.v.x;
        double v_y = ball_status.v.y;
        double last_x = ball.x;
            double last_y = ball.y;
                double time = 0.1;
                    char buff[512] = { 0  };
        int ret = -1;
    if (ball_status.if_carry == 1) {
        if ((ret = search_player(rteam, ball_status.name)) != -1) {
                        ball.x = rteam[ret].loc.x - op.x;
                        ball.y = rteam[ret].loc.y - op.y;
                    
        }
        if ((ret = search_player(bteam, ball_status.name)) != -1) {
                        ball.x = bteam[ret].loc.x - op.x;
                        ball.y = bteam[ret].loc.y - op.y;
                    
        }
                ball_status.a.x = 0;
                ball_status.a.y = 0;
                ball_status.v.x = 0;
                ball_status.v.x = 0;
            
    }
    else {
                v_x += a_x * 0.1;
                v_y += a_y * 0.1;

                sprintf(buff, "speed : %lf %lf aspeed : %lf %lf name : %s", v_x, v_y, a_x, a_y, ball_status.name);
                w_gotoxy_puts(Message, 0, 1, buff);
                double flag_x = v_x * ball_status.v.x;
                double flag_y = v_y * ball_status.v.y;
        if (flag_x <= 0 && flag_y <= 0) {
            
                        v_x = 0;
                        v_y = 0;
                        a_x = 0;
                        a_y = 0;
                    
        }
        else if (flag_x <= 0 && flag_y > 0.1) {
                        v_x = 0;
                        a_x = 0;
                    
        }
        else if (flag_x > 0.1 && flag_y <= 0) {
                        v_y = 0;
                        a_y = 0;
                    
        }

                ball.x += v_x * 0.1 - 0.5 * a_x * 0.01;

                        ball.y += v_y * 0.1 - 0.5 * a_y * 0.01;


                                
        if (ball.x >= court.width) {
                
                        ball.x = court.width - 1;
                        a_x = a_y = 0;
                        v_x = v_y = 0;
                    
        }
        if (ball.x <= 0) {
                    
                        ball.x = 0;
                        a_x = a_y = 0;
                        v_x = v_y = 0;
                    
            }
        if (ball.y >= court.heigth) {
                        
                        ball.y = court.heigth - 1;
                        a_x = a_y = 0;
                        v_x = v_y = 0;
                    
        }
if (ball.y <= 0) {
                
                ball.y = 0;
                a_x = a_y = 0;
                v_x = v_y = 0;
            
}
    
    }

        ball_status.a.x = a_x;
            ball_status.a.y = a_y;
                ball_status.v.x = v_x;
                    ball_status.v.y = v_y;


                        if (!has_colors() || start_color() == ERR) {
                                    endwin();
                                    fprintf(stderr, "终端不支持颜色!\n");
                                    exit(1);
                                
                        }

                            init_pair(1, COLOR_GREEN, COLOR_BLACK); //绿色
                                init_pair(2, COLOR_RED, COLOR_BLACK);//红色
                                    init_pair(3, COLOR_WHITE, COLOR_BLACK);//白色
                                        init_pair(4, COLOR_YELLOW, COLOR_BLACK);//黄色
                                            init_pair(5, COLOR_CYAN, COLOR_BLACK);//青色
                                                init_pair(6, COLOR_BLUE, COLOR_BLACK);//蓝色
                                                    init_pair(7, COLOR_MAGENTA, COLOR_BLACK); //洋红
                                                        wattron(Football, COLOR_PAIR(rand() % 7));
                                                            w_gotoxy_putc(Football, ball.x, ball.y, 'o');


}
    
    
    
    /*
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
    }*/
    //根据ball_status里记录的加速度，和上次re_drew时的速度，算出本次球应该移动的时间
    //加速度保持不变，速度更新
    //需要注意的是，当判断到速度减为0，ball_status里的速度和加速度都清空
    //同样需要注意的时，球如果超过球场边界，则判定为出界，球停止到边界即可

void  re_drew_player(int team, char *name, struct Point *loc) {
    //根据team，切//在loc位置打印player，并显示姓名
    if(team==1){
        for(int i=0; i<MAX; i++){ //bteam[i].online =0;
            if(bteam[i].online == 1){ //bteam[i].online =0;
                if(strcmp(bteam[i].name, name)==0){
                   // printf("new!!!\n")                    
                    wattron(Football_t, COLOR_PAIR(6));
                    w_gotoxy_putc(Football_t,loc->x,loc->y,'K');
                    w_gotoxy_puts(Football_t,loc->x+1,loc->y-1,name);
                }
            }
        }
    }
    else{
        for(int i=0; i<MAX; i++){ //rteam[i].online =0;
            if(rteam[i].online == 1){ //rteam[i].online=0;
                if(strcmp(rteam[i].name, name)==0){
                    wattron(Football_t, COLOR_PAIR(2));
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
        wrefresh(Football_t);
        //sleep(1);
     
    //分别调用re_drew_team、re_drew_ball
}







