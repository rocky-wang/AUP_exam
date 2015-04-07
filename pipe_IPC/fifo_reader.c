#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

#define FIFO_NAME	"./myfifo"
int main(int argc, char **argv)
{
	char buf[64];
	int fd;
	int n;
	int ret;

	ret = mkfifo(FIFO_NAME,0666);
	if(ret < 0 && (errno != EEXIST)){
		perror("mkfifo");
		return errno;
	}

	if(( fd = open(FIFO_NAME,O_RDONLY) ) < 0 ){
		perror("open failed");
		exit(0);
	}

	printf("open fifo for read...\n");
	while(1){
		memset(buf,0,sizeof(buf));
		if(( n = read(fd,buf,sizeof(buf)) )== 0 ){
			printf("close fifo\n");
			break;
		}
		printf("buf:%s",buf);
	}
	exit(0);
}
