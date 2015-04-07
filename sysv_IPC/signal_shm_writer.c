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
	if((key = ftok(".", 'a')) < 0){
		perror("fail to ftok");
		exit(-1);
	}
	
	if((shmid = shmget(key, sizeof(shmbuf), IPC_CREAT|IPC_EXCL|0666)) < 0){
		if(errno == EEXIST) {
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
		shmaddr = (shmbuf *)shmat(shmid, NULL, 0);
		shmaddr->pid = getpid();
		pause();
		pid = shmaddr->pid;
	}

	while( 1 ){
		printf("please input : ");
		fgets(shmaddr->buf, N, stdin);
		kill(pid, SIGUSR1);
		if(strncmp(shmaddr->buf, "quit", 4) == 0){
			break;
		}
		pause();
	}
	sleep(1);
	shmdt(shmaddr);
	shmctl(shmid, IPC_RMID, NULL);

	return 0;
}

