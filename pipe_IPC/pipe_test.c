#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

/*******************************************
 *如果考虑先后关系，需要引入信号量，否则使用睡眠，但效率差
********************************************/
int main()
{
	pid_t child1,child2;
	int fd[2];
	char buf[32];
	int ret;

	pipe(fd);
	ret = fork();
	if(ret < 0){
		perror("child1 fork");
		exit(1);
	}
	if(ret == 0){
		/* child1 */
		close(fd[0]);
		memset(buf,0,sizeof(buf));
		sprintf(buf,"Child 1 is sending a message!");
		write(fd[1],buf,32);
		exit(0);
	}
	else{
		/* 父进程 */
		child1 = ret;
		ret = fork();
		if(ret < 0){
			perror("child2 fork");
			exit(1);
		}
		if(ret == 0){
			/* child2 */
			close(fd[0]);
			memset(buf,0,sizeof(buf));
			sprintf(buf,"Child 2 is sending a message!");
			write(fd[1],buf,32);
			exit(0);
		}
		else{
			child2 = ret;
			close(fd[1]);
			wait(NULL);
			wait(NULL);
			
			while( (ret = read(fd[0],buf,32)) != 0){
				printf("the read buf is %s\n",buf);
			}
			
			exit(0);
		}
	}
}
