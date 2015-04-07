#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

pid_t pid;

void seller_handler(int signo)
{
   switch ( signo )
   {
      case SIGINT:
			kill(getppid(), SIGUSR1);
	        break;
      case SIGQUIT:
	        kill(getppid(), SIGUSR2);
			break;
      case SIGUSR1:
			printf("please get off the bus\n");
          	exit(0);
          	break;
   }

   return;
}


void driver_handler(int signo)
{
   switch ( signo )
   {
      case SIGUSR1:
      		printf("let's gogogo\n");
            break;
      case SIGUSR2:
            printf("stop the bus\n");
            break;
      case SIGTSTP:
            kill(pid, SIGUSR1);
            wait(NULL);
			exit(0);
            break;
   }

   return;
}

int main(int argc, char *argv[])
{

   if ((pid = fork()) < 0)
   {
      perror("fail to fork");
      exit(-1);
   }
   else if (pid == 0)
   {
      signal(SIGTSTP, SIG_IGN);
      signal(SIGINT, seller_handler);
      signal(SIGQUIT, seller_handler);
      signal(SIGUSR1, seller_handler);
      while ( 1 );
   }
   else  // driver
   {
      signal(SIGINT, SIG_IGN);
      signal(SIGQUIT, SIG_IGN);
      signal(SIGTSTP, driver_handler);
      signal(SIGUSR1, driver_handler);
      signal(SIGUSR2, driver_handler);
      while ( 1 );
   }

   return 0; 
}
