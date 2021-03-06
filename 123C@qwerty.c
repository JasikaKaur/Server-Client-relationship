#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
 
/* Handle all communication with the client */
void *hanle_client(void *arg){
	char buff_in[1024];
	int rlen;
 
	int fd = *(int *)arg;
 
	printf("<<ACCEPT\n");
 
	/* Receive input from client */
	while((rlen = read(fd, buff_in, sizeof(buff_in)-1)) > 0){
        buff_in[rlen] = '\0';
 
        printf("<< %s\n", buff_in);
    }
 
	printf("<<LEAVE\n");
	close(fd);
 
	pthread_detach(pthread_self());
}
 
int main(int argc, char *argv[]){
	int listenfd = 0, connfd = 0, n = 0;
	struct sockaddr_in serv_addr;
	struct sockaddr_in cli_addr;
    pthread_t tid;
 
	/* Socket settings */
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(8000); 
 
	/* Bind */
    if(bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0){
    	perror("Socket binding failed");
    	return 1;
    }
 
	/* Listen */
	if(listen(listenfd, 10) < 0){
		perror("Socket listening failed");
		return 1;
    }
 
	printf("<[SERVER STARTED]>\n");
 
	/* Accept clients */
    while(1){
    	int clilen = sizeof(cli_addr);
        connfd = accept(listenfd, (struct sockaddr*)&cli_addr, &clilen);
 
		/* Fork thread */
		pthread_create(&tid, NULL, &hanle_client, (void*)&connfd);
 
		/* Reduce CPU usage */
        sleep(1);
     }
}
