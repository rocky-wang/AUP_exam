#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netdb.h>

static int create_tcp_server(int port)
{
	int sockfd;
	struct sockaddr_in self;
	int ret;
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1){
		perror("socket");
		return -1;
	}
	
	memset(&self,0,sizeof(self));
	self.sin_family = AF_INET;
	self.sin_port	= htons(port);
	self.sin_addr.s_addr = htonl(INADDR_ANY);
	ret = bind(sockfd,(struct sockaddr *)&self,sizeof(self));
	if(ret == -1){
		perror("bind");
		return -1;
	}
	
	listen(sockfd,5);
	printf("listen...\n");
	
	return sockfd;
}

int main(int argc,char *argv[])
{
	int listenfd;
	int port;
	int ret;
	int newfd;
	char *msg = "Weclome to My server!\n";

	if(argc != 2){
		fprintf(stderr,"Usage port...\n");
		exit(1);
	}

	port = atoi(argv[1]);
	
	listenfd = create_tcp_server(port);

	while(1){
		newfd = accept(listenfd,NULL,NULL);
		if(newfd == -1){
			perror("accept");
			return -1;
		}
		printf("New connection...\n");
		/*****************************************
		 *实际工程中的发送方法需要考虑阻塞性 
		 *请大家思考和改进
		******************************************/
		send(newfd,msg,strlen(msg));
		close(newfd);
	}
}

