/*************************************************************************
	> File Name: server_re_draw.c
	> Author: 
	> Mail: 
	> Created Time: Wed 22 Jul 2020 09:56:12 PM CST
 ************************************************************************/

 #include "head.h"
 #include<stdio.h>
 #include"head.h" 
 extern struct Map court;
 extern struct User *rteam, *bteam;
 extern WINDOW *Football, *Football_t;
 extern struct BallStatus ball_status;
 extern struct Bpoint ball;
 int time1 = 2;
 extern struct Point op;
 struct Point pnt = { 0,0  };
 extern struct Score score;
 int search_player(struct User *team, char *name) {
     for (int i = 0; i < MAX; i++) {
         if (team[i].online == 1) {
             if (strcmp(name, team[i].name) == 0) {
                                return i;

                            
             }

                    
         }

            
     }
        return -1;


 }
 void re_draw_gate(){
     for (int i = court.heigth/2 + 1 - 4; i <= court.heigth/2 + 1 + 4; i++){
                 mvwprintw(Football_t, i, 1, "x");
                 mvwprintw(Football_t, i, court.width + 2, "x");
             
     }
 }
 void re_drew_ball() {
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
                        ball.x = rteam[ret].loc.x - op.x - 2;
                        ball.y = rteam[ret].loc.y - op.y - 1;
                    
         }
         if ((ret = search_player(bteam, ball_status.name)) != -1) {
                        ball.x = bteam[ret].loc.x - op.x - 2;
                        ball.y = bteam[ret].loc.y - op.y - 1;
                    
         }
                ball_status.a.x = 0;
                ball_status.a.y = 0;
                ball_status.v.x = 0;
                ball_status.v.x = 0;
            
     }
     else {
                v_x += a_x * 0.1;
                v_y += a_y * 0.1;

               // sprintf(buff, "speed : %lf %lf aspeed : %lf %lf name : %s", v_x, v_y, a_x, a_y, ball_status.name);
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
     if (ball.x >= court.width - 0.001) {
         if (ball.y >= court.heigth / 2 - 4 && ball.y <= court.heigth / 2 + 4) {
                        score.red++;
                        ball.x = court.width - 3;
                        ball.y = court.heigth / 2;
                        struct FootBallMsg msg;
                        msg.type = FT_WALL;
                        sprintf(msg.msg, "%s of %s team, get 1 score", ball_status.name, ball_status.by_team ? "blue" : "red");

                        w_gotoxy_puts(Message, 0, 2, msg.msg);
                        
                            werase(Help);
                            wattron(Help,COLOR_PAIR(3));
                            box(Help,0,0);
                            char scores[20];
                            sprintf(scores,"score %d : %d",score.red,score.blue);
                            w_gotoxy_puts(Help,1,1,scores);

         }
         else {
                        ball.x = court.width - 1;
                    
         }
                a_x = a_y = 0;
                v_x = v_y = 0;
                ball_status.if_carry = 0;
            
     }
     if (ball.x <= 0.001) {
         if (ball.y >= court.heigth / 2 - 4 && ball.y <= court.heigth / 2 + 4) {
                        score.blue++;
                        ball.x = 2.0;
                        ball.y = court.heigth / 2;
                        struct FootBallMsg msg;
                        msg.type = FT_WALL;
                        sprintf(msg.msg, "%s of %s team, get 1 score", ball_status.name, ball_status.by_team ? "blue" : "red");
                        w_gotoxy_puts(Message, 0, 2, msg.msg);
                    
                            werase(Help);
                            wattron(Help,COLOR_PAIR(3));
                            box(Help,0,0);
                            char scores[20];
                            sprintf(scores,"score %d : %d",score.red,score.blue);
                            w_gotoxy_puts(Help,1,1,scores);
         }
         else {
                        ball.x = 1;
                    
         }
                a_x = a_y = 0;
                v_x = v_y = 0;
                ball_status.if_carry = 0;
            
     }
     if (ball.y <= 0) {
                ball.y = 0;
                v_x = v_y = 0;
                a_x = a_y = 0;
                ball_status.if_carry = 0;
            
     }
     if (ball.y >= court.heigth) {
                ball.y = court.heigth - 1;
                v_x = v_y = 0;
                a_x = a_y = 0;
                ball_status.if_carry = 0;
            
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
                                                if (ball_status.by_team == 1) {
                                                            wattron(Football, COLOR_PAIR(6));
                                                        
                                                }
                                                    else {
                                                                wattron(Football, COLOR_PAIR(7));
                                                            
                                                    }
                                                        w_gotoxy_putc(Football, ball.x, ball.y, 'o');

 }



 void  re_drew_player(int team, char *name, struct Point *loc) {
        
     if (team == 1) {
                for (int i = 0; i < MAX; i++) { 
                            if (bteam[i].online == 1) { 
                                if (strcmp(bteam[i].name, name) == 0) {
                                                      
                                                        wattron(Football_t, COLOR_PAIR(6));
                                                        w_gotoxy_putc(Football_t, loc->x, loc->y, 'K');
                                                        w_gotoxy_puts(Football_t, loc->x + 1, loc->y - 1, name);
                                                    
                                }
                                        }
                        }
            
     }
     else {
                for (int i = 0; i < MAX; i++) { 
                            if (rteam[i].online == 1) { 
                                if (strcmp(rteam[i].name, name) == 0) {
                                                        wattron(Football_t, COLOR_PAIR(2));
                                                        w_gotoxy_putc(Football_t, loc->x, loc->y, 'T');
                                                        w_gotoxy_puts(Football_t, loc->x + 1, loc->y - 1, name);
                                                    
                                }
                                        }
                        }
            
     }

 }
 void re_drew_team(struct User *team, int rb) {
     for (int i = 0; i < MAX; i++) {
         if (team[i].online) {
                 
                        re_drew_player(rb, team[i].name, &team[i].loc);
                    
         }
            
     }
        

 }
 void re_draw() {
     
        werase(Football_t);
        box(Football_t, 0, 0);
        re_drew_team(rteam, 0);
        re_drew_team(bteam, 1);
        re_drew_ball();
        re_draw_gate();
        
        wrefresh(Football_t);


 }
