#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void child1_process(int signum)
{
	return ;
}

void child2_process(int signum)
{
	return ;
}

void parent_process(int signum)
{
	return ;	
}

int main()
{
	pid_t child1,child2;
	int ret;
	
	signal(SIGINT,SIG_IGN);
	signal(SIGUSR1,SIG_IGN);
	signal(SIGUSR2,SIG_IGN);

	ret = fork();
	if(ret < 0){
		perror("fork child1");
		exit(1);
	}
	if(ret == 0){
		/* child1 */
		signal(SIGUSR1,child1_process);
		pause();
		printf("Child process 1 is killed by parent!\n");
		exit(0);
	}
	else{
		/* 父进程 */
		child1 = ret;
		ret = fork();
		if(ret < 0){
			perror("fork child2");
			exit(1);
		}
		if(ret == 0){
			/* child2 */
			signal(SIGUSR2,child2_process);
			pause();
			printf("Child process 2 is killed by parent!\n");
			exit(0);
		}
		else{
			child2 = ret;
			signal(SIGINT,parent_process);
			pause();
			kill(child1,SIGUSR1);
			wait(NULL);
			kill(child2,SIGUSR2);
			wait(NULL);
			printf("Parent process exit!\n");
		}
	}
}

