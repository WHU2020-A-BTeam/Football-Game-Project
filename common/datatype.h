/*************************************************************************
	> File Name: datatype.h
	> Author:zhangsheng 
	> Mail: 
	> Created Time: Mon 20 Jul 2020 03:25:47 PM CST
 ************************************************************************/

#ifndef _DATATYPE_H
#define _DATATYPE_H

struct Point {
    int x;
    int y;
};


struct User{
    int team;//0 RED 1 BLUE
    int fd //玩家对应的链接
    char name[20];
    int online;//1 在线 0 不在线
    struct Point loc;
};

//登录相关
struct LogRequest{
    char name[20];
    int team;
    char msg[512];
};

struct LogResponse{
    int Type; //0 OK 1 No
    char msg[512];
};



#endif
