/*************************************************************************
	> File Name: head.h
	> Author:zhangsheng 
	> Mail: 
	> Created Time: Tue 14 Jul 2020 01:47:24 PM CST
 ************************************************************************/

#ifndef _HEAD_H
#define _HEAD_H

#include <arpa/inet.h>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/file.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdarg.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>
#include <sys/epoll.h>
#include "datatype.h"
#include "common.h"
#include "udp_epoll.h"
#include "thread_pool.h"
#include "sub_reactor.h"
#include <curses.h>
#include <ncurses.h>
#include "color.h"
#include "game_ui.h"
#include "heart_beat.h"
#include"server_re_draw.h"
#include"show_data_stream.h"
#include "send_ctl.h"
#include"send_chat.h"
#include "server_exit.h"
#include"client_recv.h"
#include"server_send_all.h"
#include"client_exit.h"
#include"ball_status.h"
#include<math.h>

#define MAX 20
#define NWORKER 5
#endif
