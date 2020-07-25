/*************************************************************************
	> File Name: thread_pool.c
	> Author: 
	> Mail: 
	> Created Time: Sat 25 Jul 2020 08:17:56 PM CST
 ************************************************************************/

#include "head.h"

extern struct User *rteam;
extern struct User *bteam;
extern char talk[5][50];
extern WINDOW *Message;
extern int bepollfd;
extern int repollfd;

int find(struct User * team,char * name){
    for(int i = 0; i < MAX; i++){
        if(team[i].online){
            if(strcmp(team[i].name,name) == 0)
                return i;
        }
    }
    return -1;
}
void do_with(struct User *user) {
    struct FootBallMsg msg;
    recv(user->fd, (void*)&msg, sizeof(msg), 0);
   // printf("%d\n",msg.type);
    if (msg.type & FT_FIN){
        show_data_stream('e');
        if(msg.team == 0){
            int num =find(rteam,msg.name);
            rteam[num].online = 0;
            // printf("zzqzqzq\n");
            del_event(repollfd, rteam[num].fd);
            close(rteam[num].fd); 
        } else {
            int num =find(bteam,msg.name);
            bteam[num].online = 0;
            del_event(bepollfd, bteam[num].fd);
            close( bteam[num].fd ); 
        }
    } else if(msg.type & FT_WALL){
        user->flag = 10;
    } else if(msg.type & FT_ACK){

    } else if(msg.type & FT_CTL){
        if(msg.ctl.action & ACTION_DFL){
            show_data_stream('n');
            struct User * team = NULL;
            if(msg.team == 0) 
                team=rteam;
            else team =bteam;
            int num = find(team,msg.name);
            if(num < 0){  
                printf(" not find \n");
                exit(1);
            }
            if(msg.ctl.dirx=='d'){
                team[num].loc.x++;
            } else if(msg.ctl.dirx == 'a'){
                team[num].loc.x--;
            } else if(msg.ctl.diry == 'w'){
                team[num].loc.y--;
            } else if(msg.ctl.diry == 's' ){
                team[num].loc.y++;
            }
        } else if(msg.ctl.action & ACTION_KICK){ 
            show_data_stream('k');
            int ret = can_kick(&(user->loc), 1);
            if(ret == 1){
                ball_status.by_team = user->team;
                bzero(ball_status.name,sizeof(ball_status.name));
                ball_status.if_carry = 0;    
            }
        } else if (msg.ctl.action & ACTION_CARRY){ 
            show_data_stream('c');
            int ret = can_carry(&(user->loc));
            if(ret == 1){
                strcpy(ball_status.name, user->name);
                //w_gotoxy_puts(Message, 0, 2, ball_status.name);
                ball_status.by_team = user->team; 
            }
        } else if (msg.ctl.action & ACTION_STOP){
            int ret = can_stop(&(user->loc));
            //printf("stop!\n");            
        }
    } else if(msg.type & FT_MSG){
        for(int i = 1; i < 5; i++){
            strcpy(talk[i - 1], talk[i]);
        }
        strcpy(talk[4], user->name);
        strcat(talk[4], ": ");
        strcat(talk[4], msg.msg);
        werase(Message);
        //box(Message, 1, 1);
        for(int i = 4; i >= 0; i--){
            w_gotoxy_puts(Message, 2, i, talk[i]);
        }
    }
}

void task_queue_init(struct task_queue *taskQueue, int size, int epollfd){
	taskQueue->size = size;
	taskQueue->epollfd = epollfd;
	taskQueue->total = 0;
	taskQueue->team = calloc(size, sizeof(void *));
	taskQueue->head = taskQueue->tail = 0;
	pthread_mutex_init(&taskQueue->mutex, NULL);
	pthread_cond_init(&taskQueue->cond, NULL);

}

void task_queue_push(struct task_queue *taskQueue, struct User *user){
	pthread_mutex_lock(&taskQueue->mutex);
	
	if(taskQueue->total == taskQueue->size){
		pthread_mutex_unlock(&taskQueue->mutex);
		return;
	}

	taskQueue->team[taskQueue->tail] = user;
	taskQueue->total++;
//	printf("queue add user %s\n", user->name);
	if(++taskQueue->tail == taskQueue->size) {
		taskQueue->tail = 0;
	}
	pthread_cond_signal(&taskQueue->cond);
	pthread_mutex_unlock(&taskQueue->mutex);
}


struct User *task_queue_pop(struct task_queue *taskQueue){

	pthread_mutex_lock(&taskQueue->mutex);
	//printf("Pop\n");
	while(taskQueue->tail == taskQueue->head){
		pthread_cond_wait(&taskQueue->cond, &taskQueue->mutex);
	}
	struct User *user = taskQueue->team[taskQueue->head];
	taskQueue->total--;
	//printf("pop user : %s\n", user->name);
	if (++taskQueue->head == taskQueue->size) {
		taskQueue->head = 0;
	}
	pthread_mutex_unlock(&taskQueue->mutex);
	return user;
}

void *thread_run(void *arg){
	pthread_detach(pthread_self());
	struct task_queue *taskQueue = (struct task_queue *)arg;
	while (1){
		struct User *user = task_queue_pop(taskQueue);
		do_with(user);
	}
}
