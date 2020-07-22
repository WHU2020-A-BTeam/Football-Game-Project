#include "head.h"

extern struct User *rteam, *bteam;
extern WINDOW *Football, *Football_t;
extern struct BallStatus ball_status;
extern struct Bpoint ball;

void re_draw_ball(){
}

void re_draw_player(int team, char *name, struct Point *loc){
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
	if(team == 1){
		wattron(Football, COLOR_PAIR(6));
		w_gotoxy_putc(Football_t, loc->x, loc->y, 'K');
		w_gotoxy_puts(Football_t, loc->x, loc->y + 1, name);
	}
	else{
		wattron(Football, COLOR_PAIR(7));
		w_gotoxy_putc(Football_t, loc->x, loc->y, 'K');
		w_gotoxy_puts(Football_t, loc->x, loc->y + 1, name);
	}

}

void re_draw_team(struct User *team){
	for (int i = 0; i < MAX ; i++){
		if(team[i].online == 1){
			re_draw_player(team[i].team, team[i].name, &team[i].loc);
		}
	}
}

void re_draw(){
	//re_draw_ball();
	re_draw_team(rteam);
	re_draw_team(bteam);
}

