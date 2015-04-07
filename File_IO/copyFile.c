#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

void copyFileData(int src_fd,int dest_fd)
{
	unsigned char buf[1024];
	int r_len,w_len;

	while(1){
		memset(buf,0,sizeof(buf));
		r_len = read(src_fd,buf,sizeof(buf));
		if(r_len < 0){
			perror("read");
			return ;
		}
		if(r_len == 0){
			printf("read src over!\n");
			return ;
		}

		w_len = write(dest_fd,buf,r_len);
		if(w_len != r_len){
			perror("write");
			return ;
		}
	}
}
int main(int argc,char *argv[])
{
	int src_fd,dest_fd;

	if(argc != 3){
		fprintf(stderr,"Usage %s srcFileName destFileName format.\n",argv[0]);
		return -1;
	}

	src_fd = open(argv[1],O_RDONLY);
	if(src_fd < 0){
		fprintf(stderr,"Open %s failed: %s\n",argv[1],strerror(errno));
		exit(errno);
	}

	dest_fd = open(argv[2],O_CREAT | O_TRUNC | O_WRONLY,0666);
	if(dest_fd < 0){
		fprintf(stderr,"Open %s failed: %s\n",argv[2],strerror(errno));
		exit(errno);
	}

	copyFileData(src_fd,dest_fd);

	close(src_fd);
	close(dest_fd);

	return 0;
}

