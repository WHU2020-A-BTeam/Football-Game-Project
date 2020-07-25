/*************************************************************************
	> File Name: sub__reactor.c
	> Author: 
	> Mail: 
	> Created Time: Sat 25 Jul 2020 08:14:48 PM CST
 ************************************************************************/

#include "head.h"

void *sub_reactor(void *arg){
//	printf("in thread : %lu\n", pthread_self());
	struct task_queue *taskQueue = (struct task_queue *)arg;
	pthread_t *tid = (pthread_t *)calloc(NWORKER, sizeof(pthread_t));
	for (int i = 0; i< NWORKER; i++){
		pthread_create(&tid[i], NULL, thread_run, (void *)taskQueue);
	}
    make_non_block(taskQueue->epollfd);
	struct epoll_event ev, events[MAX];
	while(1) {
		int nfds = epoll_wait(taskQueue->epollfd, events, MAX, -1);
		if(nfds < 0) {
            if(errno != EINTR){
			perror("epoll_wait()");
			exit(1);
		} }
		//printf("nfds = %d\n", nfds);
		for (int i = 0; i < nfds; i++){
			struct User *user = (struct User *)events[i].data.ptr;
	//		printf("name = %s\n", user->name);
			if (events[i].events & EPOLLIN) {
				task_queue_push(taskQueue, user);
			}
		}
	}
	return NULL;
}
