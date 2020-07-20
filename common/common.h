/*************************************************************************
	> File Name: common.h
	> Author: 
	> Mail: 
	> Created Time: Mon 20 Jul 2020 09:29:45 PM CST
 ************************************************************************/

#ifndef _COMMON_H
#define _COMMON_H
void make_non_block(int fd); //设置为非阻塞套接字
void make_block(int fd); //设置为阻塞套接字
int socket_create_udp(int port); //创建绑定端口的UDP套接字
int socket_udp(); //创建一个主动的UDP套接字
#endif
