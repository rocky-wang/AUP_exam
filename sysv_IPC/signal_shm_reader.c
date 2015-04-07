#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

#define N 64

typedef struct{
	int pid;
	char buf[N];
}shmbuf;

void handler(int signo)
{
	return;
}

int main(int argc, char *argv[])
{
	int shmid;
	key_t key;
	pid_t pid;
	shmbuf *shmaddr;

	signal(SIGUSR1, handler);

	if ((key = ftok(".", 'a')) < 0){
		perror("fail to ftok");
		exit(-1);
	}

	if((shmid = shmget(key, sizeof(shmbuf), IPC_CREAT|IPC_EXCL|0666)) < 0){
		/* 共享内存已经存在，取出pid号*/
		if(errno == EEXIST){
			shmid = shmget(key, sizeof(shmbuf), 0666);
			shmaddr = (shmbuf *)shmat(shmid, NULL, 0);
			pid = shmaddr->pid;
			shmaddr->pid = getpid();
			kill(pid, SIGUSR1);
		}
		else{
			perror("fail to shmget");
			exit(-1);
		}
	}
	else{
		/* 共享内存不存在，创建后，填入数据等待建立通信 */
		shmaddr = (shmbuf *)shmat(shmid, NULL, 0);
		shmaddr->pid = getpid();
		pause();
		pid = shmaddr->pid;
	}

	while ( 1 ){
		pause();
		if ( strncmp(shmaddr->buf, "quit", 4) == 0){
			break;
		}
		printf("message from shm : %s", shmaddr->buf);
		kill(pid, SIGUSR1);
	}
	
	shmdt(shmaddr);
	return 0;
}

