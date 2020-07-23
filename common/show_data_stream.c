/*************************************************************************
	> File Name: show_data_stream.c
	> Author: 
	> Mail: 
	> Created Time: Thu 23 Jul 2020 10:31:01 AM CST
 ************************************************************************/

#include"head.h"
extern char data_stream[20];
extern WINDOW *Help;
extern struct Map court;

void show_data_stream(int type){
    for(int i=2;i<20;i++){
        data_stream[i] = data_stream[i-1];
    }
    data_stream[1] = type;
    for(int i=1; i<19 ;i++){
        if(type =='l'){
            //char blank[]="zzq";
             wattron(Help, COLOR_PAIR(8));//login
        }
        else if(type == 'c'){  //carry 
             wattron(Help, COLOR_PAIR(12));//carry
        }
        else if(type == 'k'){
            
             wattron(Help, COLOR_PAIR(11));//kick
        }
        else if(type == 's'){
            wattron(Help, COLOR_PAIR(9));// STOP
        }
        else if(type == 'n'){
        
            wattron(Help, COLOR_PAIR(12));// normal
        }
        else if(type =='e'){
            wattron(Help, COLOR_PAIR(10));// exit 
        }
        w_gotoxy_putc(Help,i,25 , ' ');
    }
}
