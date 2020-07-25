/*************************************************************************
	> File Name: common.c
	> Author: 
	> Mail: 
	> Created Time: Sat 25 Jul 2020 06:06:22 PM CST
 ************************************************************************/

#include "head.h"
extern char conf_ans[512];

char *get_conf_value(const char *path, const char *key){
	FILE *fp =NULL;
	if(strcmp(key, "LINES") != 0 && strcmp(key, "COLS") != 0 && strcmp(key, "PORT") != 0 && strcmp(key, "NAME") != 0 && strcmp(key, "TEAM") != 0 && strcmp(key, "SERVERIP") != 0 && strcmp(key, "SERVERPORT") != 0 && strcmp(key, "LOGMSG") != 0){
		printf("illegal key!\n");
		return NULL;
	}

	if((fp = fopen(path, "r")) == NULL){
		printf("illegal path!\n");
		return NULL;
	}
    char *find_key = NULL;
	char *line = NULL;
	size_t size = 0;
	ssize_t read = 0;
	memset(conf_ans, '\0', sizeof(conf_ans));
	while((read = getline(&line, &size, fp)) != -1){
		if(strstr(line, key) != NULL){
			for(int i = 0; i < read; i++){
				if(line[i] == '='){
					strncpy(conf_ans, line + i + 1, read - i - 2);
					conf_ans[read - i - 2] = '\0';
					return conf_ans;
				}
			}
		}
		free(line);
		line = NULL;
	}
	return NULL;
}

void make_non_block(int fd) {
    unsigned long ul = 1;
    ioctl(fd, FIONBIO, &ul);
}

void make_block(int fd) {
    unsigned long ul = 0;
    ioctl(fd, FIONBIO, &ul);
}

int socket_create_udp(int port){
	int listener;
	if ((listener = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
		perror("socket()");
		return -1;
	}
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(port);
	unsigned long opt = 1;
	setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	
	make_non_block(listener);

	if(bind(listener, (struct sockaddr *)&server, sizeof(server)) < 0){
		perror("bind()");
		return -1;
	}
	return listener;

}

int socket_udp(){
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        perror("socket()");
        return -1;
    }
    return sockfd;
}
