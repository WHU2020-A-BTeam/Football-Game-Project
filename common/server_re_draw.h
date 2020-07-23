#ifndef _SERVER_RE_DRAW_H
#define _SERVER_RE_DRAW_H

void re_draw_ball();
void re_draw_player(int team, char *name, struct Point *loc);
void re_draw_team(struct User *team);
void re_draw(int m);

#endif

