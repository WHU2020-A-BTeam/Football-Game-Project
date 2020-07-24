#include "head.h"

extern struct User *rteam, *bteam;
extern WINDOW *Football, *Football_t;
extern struct BallStatus ball_status;
extern struct Bpoint ball;
extern struct Map court;

struct Point pnt = {0,0};

int force_to_stop(struct User *team, int x, int y){
	for(int i = 0; i < MAX; i++){
		if(team[i].online == 1){
			if(x == team[i].loc.x && y == team[i].loc.y){
				return 1;
			}
		}
	}
	return 0;
}

void re_draw_ball(){
    w_gotoxy_putc(Football, (int )ball.x, (int)ball.y, ' ');
    double a_x = ball_status.a.x;
    double a_y = ball_status.a.y;
    double v_x = ball_status.v.x;
    double v_y = ball_status.v.y;
	double last_x = ball.x;
	double last_y = ball.y;
    double time = 0.1;  
    double itime = 0.0;
    /*while(1){
        itime += 0.001;//间隔时间为0.001s
        if (itime == time){
            break;
        }
        v_x = v_x + a_x * 0.001;
        v_y = v_y + a_y * 0.001;
    
        if (fabs(v_x) <= 1 && fabs(v_y - 0) <= 1){
            a_x = a_y = 0;
            v_x = v_y = 0;
            break;
        }
        else if (fabs(v_x) <= 1 && v_y > 0){
            a_x = 0;
            v_x = 0;
        }
        else if (v_x > 0 && v_y <= 0){
            a_y = v_y = 0;
        }
        ball.x += v_x * 0.001 - 0.5 * a_x * 0.001 * 0.001;
        ball.y += v_y *0.001 -0.5 * a_y *0.001*0.001;
        
        if (ball.x > court.width - 1){
            ball.x = court.width - 1;
            a_x = a_y = 0;
            v_x = v_y = 0;
            break;
        }
        if (ball.x < 1){
            ball.x = 1;
            a_x = a_y = 0;
            v_x = v_y = 0;
            break;
        }
        if (ball.y > court.heigth-1){
            ball.y = court.heigth - 1;
            a_x = a_y = 0;
            v_x = v_y = 0;
            break;
        }
        if (ball.y < 1){
            ball.y = 1;
            a_x = a_y = 0;
            v_x = v_y = 0;
            break;
        }
    }*/
	if((v_x == 0) && (v_y == 0)){
		a_x = 0;
		a_y = 0;
	}
	else{
		v_x += a_x * 0.1;
		v_y += a_y * 0.1;
		//printf("%lf %lf\n", v_x, v_y);
		double flag_x = v_x * ball_status.v.x;
		double flag_y = v_y * ball_status.v.y;
		if(flag_x <= 0 && flag_y <= 0){
			v_x = 0;
			v_y = 0;
			a_x = 0;
			a_y = 0;
		}
		else if(flag_x <= 0 && flag_y > 0.1){
			v_x = 0;
			a_x = 0;
		}
		else if(flag_x > 0.1 && flag_y <= 0){
			v_y = 0;
			a_x = 0;
		}
	
		ball.x += v_x * 0.1 - 0.5 * a_x * 0.01;

		ball.y += v_y * 0.1 - 0.5 * a_y * 0.01;
	
	
		if(force_to_stop(rteam, ball.x, ball.y) == 1 || force_to_stop(bteam, ball.x, ball.y) == 1){
			ball.x = last_x;
			ball.y = last_y;
			v_x = 0;
			v_y = 0;
			a_x = 0;
			a_y = 0;
		}
		if (ball.x >= court.width){
			//printf("sss\n");
      		ball.x = court.width - 1;
      		a_x = a_y = 0;
      		v_x = v_y = 0;
       	}
    	if (ball.x <= 0){
			//printf("sss\n");
   			ball.x = 0;
			a_x = a_y = 0;
        	v_x = v_y = 0;
   		}
		if (ball.y >= court.heigth){
			//printf("sss\n");
      		ball.y = court.heigth - 1;
       		a_x = a_y = 0;
       		v_x = v_y = 0;
   		}
    	if (ball.y <= 0){
			//printf("sss\n");
        	ball.y = 0;
       		a_x = a_y = 0;
        	v_x = v_y = 0;
        }
	}

    ball_status.a.x = a_x;
    ball_status.a.y = a_y;
    ball_status.v.x = v_x;
    ball_status.v.y = v_y;

//    printf("yes/n");
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
    wattron(Football, COLOR_PAIR(rand()%7));
    w_gotoxy_putc(Football, ball.x, ball.y, 'o');
//    w_gotoxy_puts(Football, ball.x, ball.y + 2, "hahaha");
}


void re_draw_player(int team, char *name, struct Point *loc){

	
	w_gotoxy_putc(Football, pnt.x, pnt.y, ' ');
	//w_gotoxy_puts(Football_t, pnt.x, pnt.y + 1, "               ");  
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
    init_pair(8, COLOR_BLACK, COLOR_GREEN);
    init_pair(9, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(10, COLOR_BLACK, COLOR_RED);
    init_pair(11, COLOR_BLACK, COLOR_BLUE);
    init_pair(12, COLOR_BLACK, COLOR_YELLOW);
    
    pnt = *loc;

	if(team == 1){
		wattron(Football, COLOR_PAIR(6));
		w_gotoxy_putc(Football, loc->x, loc->y, 'K');
		//w_gotoxy_puts(Football_t, loc->x, loc->y + 1, name);
	}
	else{
		wattron(Football, COLOR_PAIR(7));
		w_gotoxy_putc(Football, loc->x, loc->y, 'K');
		//w_gotoxy_puts(Football_t, loc->x, loc->y + 1, name);
	}

}

void re_draw_team(struct User *team){
	for (int i = 0; i < MAX ; i++){
		if(team[i].online == 1){
			re_draw_player(team[i].team, team[i].name, &team[i].loc);
		}
	}
}

void re_draw(int m){
	


	re_draw_ball();
	re_draw_team(rteam);
	re_draw_team(bteam);
}

