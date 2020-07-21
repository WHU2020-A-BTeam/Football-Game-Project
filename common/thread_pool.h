#ifndef _THREAD_POOL_H 
#define _THREAD_POLL_H

struct task_queue {
	int size; //size of queue
	int epollfd; //owner msg
	int total;
	struct User **team;
	int head;
	int tail;
	pthread_mutex_t mutex;
	pthread_cond_t cond;
};

void task_queue_init(struct task_queue *taskQueue, int size,int epollfd);
void task_queue_push(struct task_queue *taskQueue, struct User *user);
struct User *task_queue_pop(struct task_queue *taskQueue);
void *thread_run(void *arg);
void do_with(struct User *user);

#endif
