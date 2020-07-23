#include "head.h"

void server_exit(int signum) {
	struct FootballMsg msg;
	 msg.type = FT_FIN;
	 for (int i = 0 ; i < MAX; i++){
		if(rteam[i].online) send(rteam[i].fd, (void *)&msg, sizeof(msg), 0);
		if(bteam[i].online) send(bteam[i].fd, (void *)&msg, sizeof(msg), 0);
	 }
	 endwin();
	 exit(0);
}
