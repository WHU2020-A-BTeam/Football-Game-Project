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

struct Bpoint {
    double x;
    double y;
};

struct User{
    int team;//0 RED 1 BLUE
    int fd; //玩家对应的链接
    char name[20];
    int online;//1 在线 0 不在线
	int flag; //未响应次数
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

struct Map{
    int width;
    int height;
    struct Point start;
    int gate_width;
    int gate_height;
};

struct Aspeed{
    double x;
    double y;
};

struct Speed{
    double x;
    double y;
};

struct BallStatus{
    struct Speed v;
    struct Aspeed a;
    int t;
    int who;
    char name[20];
    //pthread_mutex_t mutex;
};

struct Score{
    int red;
    int blue;
};

//action value
#define ACTION_KICK 0x01
#define ACTION_CARRY 0x02
#define ACTION_STOP 0x04

struct Ctl{
    int action;
    int dirx;
    int diry;
    int strength;
};

//type value
#define FT_HEART 0x01 
#define FT_ACK 0x02
#define FT_MSG 0x04  //私聊
#define FT_WALL 0x08
#define FT_CTL 0x10
#define FT_MAP 0x20 //场地
#define FT_FIN 0x40
#define FT_SCORE 0x80
#define FT_GAMEOVER 0x100

#define MAX_MSG 1024

struct FootBallMsg{
    int type;
    int size;
    int team;
    char name[20];
    char Msg[MAX_MSG];
    struct Ctl ctl;
};
#endif
