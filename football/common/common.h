/*************************************************************************
	> File Name: common.h
	> Author:zhangsheng 
	> Mail: 
	> Created Time: Mon 20 Jul 2020 03:30:57 PM CST
 ************************************************************************/

#ifndef _COMMON_H
#define _COMMON_H
char conf_ans[512];
char *get_conf_value(const char *path, const char *key);
int socket_create_udp(int port);


#endif
