#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <errno.h>
#include "shm_sem.h"

int main()
{
	int	semid, shmid;
	char	*shmaddr;
	
	if ((shmid = createshm(".", 'm', SHM_SIZE)) == -1){
		exit (1);
	}
	
	if((shmaddr = shmat (shmid, (char *)0, 0)) == (char *)-1){
		perror ("attach shared memory error!\n");
		exit (1);
	}
	
	if((semid = opensem("." ,'s')) == -1){
		exit (1);
	}
	
	while(1){
		printf("reader: ");
		sem_p(semid,0);			/* P操作 */
		
		printf("%s", shmaddr);
		
		sem_v(semid,0);			/* V操作 */
	}
}

