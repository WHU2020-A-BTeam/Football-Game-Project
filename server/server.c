#include "../common/head.h"

#include "../common/datatype.h"
#include "../common/udp_epoll.h"
#define MAX 10
char *conf = "./footballd.conf";

int main(int argc, char **argv){
        int opt, listener, epollfd;
    pthread_t red_t, blue_t;
    /*
    while((opt = getopt(argc, argv, "p:")) != -1){
        switch (opt) {
                        case 'p':
                            port = atoi(optarg);
                            break;
                        default:
                            fprintf(stderr, "Usage : %s -p port\n", argv[0]);
                            exit(1);
                    
        }
            
    } */ 
    

//    printf("\n\ntttt\n");
        char *str = get_conf_value(conf,"PORT");
    if(str == NULL){
                perror("get_conf_value()");
                exit(1);
            
    }
        if(!port) port = atoi(str);
         //   printf("%d\n",port);
    if((listener = socket_create_udp(port)) < 0){
                perror("socket_create_udp()");
                exit(1);
            
    }

    if ((epollfd = epoll_create(1))<0){
                perror("epoll_create()");
                exit(1);
            
    }

        struct User user;
        bzero(&user, sizeof(user)) ; user.fd=listener;

        struct epoll_event ev, events[MAX];
        ev.events = EPOLLIN;
        ev.data.ptr = &user;
        
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, listener, &ev) < 0){
                perror("epoll_ctl");
                exit(1);
            
    }
            struct User *zzq;
          //  zzq.fd=0;
    while(1){
                int nfds = epoll_wait(epollfd, events, MAX,-1 );
       // printf("zqzqzq");
        if(nfds < 0) {
                        perror("epoll_wait()");
                        exit(1);
                    
        }  printf("%d\n",nfds);
        for(int i = 0; i < nfds; i++){
            if( ((struct User*)events[i].data.ptr )->fd == listener) {
                        //printf("zzq\n");
                        struct User *user; user =(struct User*)malloc(sizeof(struct User));
                        bzero(user, sizeof(user));
                                int new_fd = udp_accept(listener, user);

                if(new_fd > 0){
                                        printf("New Connection!%d  \n",new_fd);
                                user->fd = new_fd;
                                add_event_ptr(epollfd,new_fd,EPOLLIN,user);
                 }
            }else{
                if(events[i].events & EPOLLIN){
                    char buff[512]={0};
                    recv(((struct User*)events[i].data.ptr)->fd,buff,sizeof(buff),0);
                   // sleep(3);
                   //printf("**%d**\n", ((struct User*)events[i].data.ptr)->fd);
                   printf("recv: %s**\n",buff );
                   // send(((struct User*)events[i].data.ptr)->fd,buff,strlen(buff),0);
                }
            }
                    
        }   
            
    }
    return 0;
}
