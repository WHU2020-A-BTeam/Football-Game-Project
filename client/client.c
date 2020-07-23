#include "head.h"
struct Map court;
struct Bpoint ball;
pthread_mutex_t bmutex, rmutex;
int server_port = 0;
char server_ip[20] = {0};
int team = -1;
char *conf = "./football.conf";
int sockfd = -1;

int main(int argc, char **argv){
	int opt;
	pthread_t heart_t;
	struct LogRequest request;
	struct LogResponse response;
	bzero(&request, sizeof(request));
	bzero(&response, sizeof(response));
	while((opt = getopt(argc, argv, "h:p:t:m:n:")) != -1){
		switch (opt) {
			case 't':
				request.team = atoi(optarg);
				break;
			case 'h':
				strcpy(server_ip, optarg);
				break;
			case 'p':
				server_port = atoi(optarg);
				break;
			case 'm':
				strcpy(request.msg, optarg);
				break;

			case 'n':
				strcpy(request.name, optarg);
				break;
			default:
				fprintf(stderr, "Usage : %s [-hptmn]!\n", argv[0]);
				exit(1);
		}
	}
	if (!server_port) server_port = atoi(get_conf_value(conf, "SERVERPORT"));
	if (!request.team) request.team = atoi(get_conf_value(conf, "TEAM"));
	if (!strlen(server_ip)) strcpy(server_ip, get_conf_value(conf, "SERVERIP"));
	if (!strlen(request.name)) strcpy(request.name, get_conf_value(conf, "NAME"));
	if (!strlen(request.msg)) strcpy(request.msg, get_conf_value(conf, "LOGMSG"));
	court.width = atoi(get_conf_value(conf, "COLS"));
	court.heigth = atoi(get_conf_value(conf, "LINES"));
	court.start.x = (court.width + 1) / 2;
	court.start.y = (court.heigth + 1) / 2;
	court.gate_width = 5;
	court.gate_heigth = 10;
//	printf("PORT:%d \nTEAM:%d \nIP:%s\n NAME:%s\nLOGMSG:%s\n", server_port, request.team, server_ip, request.name, request.msg);
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(server_port);
	server.sin_addr.s_addr = inet_addr(server_ip);

	socklen_t len = sizeof(server);
	
	//initfootball();

	if((sockfd = socket_udp()) < 0){
		perror("socket_udp()");
		exit(1);
	}
	
	sendto(sockfd, (void *)&request, sizeof(request), 0, (struct sockaddr *)&server, len);
	printf("send success!\n");
	fd_set set;
	FD_ZERO(&set);
	FD_SET(sockfd, &set);
	struct timeval tv;
	tv.tv_sec = 5;
	tv.tv_usec = 0;
	int retval = select(sockfd + 1, &set, NULL, NULL, &tv);
	if(retval < 0) {
		perror("select()");
		exit(1);
	}
	else if (retval){
		int ret = recvfrom(sockfd, (void *)&response, sizeof(response), 0, (struct sockaddr *)&server, &len);
		if(ret != sizeof(response)){
			printf("The Game Server refused your login.\n\tThis May be helpful:%s\n", request.msg);
			exit(1);
		}
	}
	if (retval == 0) {
		printf("The Game Server is out of service!.\n");
		exit(1);
	}
	printf("Server : %s\n", response.msg);
	connect(sockfd, (struct sockaddr *)&server, len);
	struct FootballMsg msg;
	//pthread_create(&heart_t, NULL, heart_beat_client, &sockfd);
	while(1){
		/*char buff[512] = {0};
		scanf("%[^\n]s", buff);
		getchar();
		send(sockfd, buff, strlen(buff), 0);
		printf("Send : %s\n" , buff);
		bzero(buff, sizeof(buff));
		recv(sockfd, buff, sizeof(buff), 0);
		printf("Server : %s\n", buff);*/
		//struct FootballMsg msg;
		bzero(&msg, sizeof(msg));
		recv(sockfd, (void *)&msg, sizeof(msg), 0);
		printf("MSG!\n");
		if(msg.type & FT_HEART){
			msg.type = FT_ACK;
			send(sockfd, (void *)&msg, sizeof(msg), 0);
			printf("answer!!\n");
		}

	}
	return 0;
}
