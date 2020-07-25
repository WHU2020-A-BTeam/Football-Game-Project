/*************************************************************************
	> File Name: common.h
	> Author: 
	> Mail: 
	> Created Time: Sat 25 Jul 2020 03:48:08 PM CST
 ************************************************************************/

#ifndef _COMMON_H
#define _COMMON_H
char conf_ans[512];
char *get_conf_value(const char *path, const char *key);
void make_non_block(int fd);
void make_block(int fd);
int socket_create_udp(int port);
int socket_udp();
#endif
