#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

#define FIFO_NAME "./myfifo"
int main(int argc, char **argv)
{
	char buf[64];
	int fd;
	int ret;
	int n;

	ret = mkfifo(FIFO_NAME,0666);
	if(ret < 0 && (errno != EEXIST)){
		perror("mkfifo");
		return errno;
	}
	
	if(( fd = open(FIFO_NAME,O_WRONLY) ) < 0){
		perror("open failed");
		exit(0);
	}

	printf("open fifo for write...\n");
	while(1){
		printf("input:");
		fgets(buf,sizeof(buf),stdin);
		if( strncmp(buf,"quit",4) == 0 ){
			close(fd);
			break;
		}
		if ( (n = write(fd,buf,strlen(buf))) == 0){
			printf("close fifo\n");
			break;
		}
	}
	exit(0);
}

