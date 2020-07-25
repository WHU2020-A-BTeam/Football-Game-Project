/*************************************************************************
	> File Name: game_ui.h
	> Author: 
	> Mail: 
	> Created Time: Sat 25 Jul 2020 08:39:35 PM CST
 ************************************************************************/

#ifndef _GAME_UI_H
#define _GAME_UI_H

WINDOW *Football, *Football_t, *Message, *Help, *Score, *Write;
struct Bpoint ball;  //球的位置
struct BallStatus ball_status;

WINDOW *create_newwin(int width, int heigth, int startx, int starty);
void destroy_win(WINDOW *win);
void gotoxy(int x, int y);
void gotoxy_putc(int x, int y, int c);
void gotoxy_puts(int x, int y, char* s);
void w_gotoxy_putc(WINDOW *win, int x, int y, int c);
void w_gotoxy_puts(WINDOW *win, int x, int y, char *s);
void initfootball();

#endif
