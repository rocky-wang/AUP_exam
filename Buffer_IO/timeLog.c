#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <signal.h>

/******************************************
 *日志更新程序，由于要获取行号，而且日志为文本文件，
 *可以使用fgets进行行号获取的标志。
*******************************************/
#define LOG_NAME	"test.log"
FILE *log_fp;

void process_handler(int sig)
{
	printf("ready to quit...\n");
	fclose(log_fp);
	exit(0);
}

int fileGetLine(FILE *fp)
{
	int count = 0;
	char buf[32];

	while(fgets(buf,sizeof(buf),fp) != NULL){
		count++;
	}

	return count;
}

void fill_upFile(FILE *fp)
{
	static int line_count;
	time_t now;
	struct tm *t1;

	line_count = fileGetLine(fp);
	if(line_count < 0){
		fprintf(stderr,"Get file line number failed!\n");
		return ;
	}
	
	while(1){
		time(&now);
		t1 = localtime(&now);
		fprintf(fp,"%03d,  %04d-%02d-%02d %02d:%02d:%02d\n",++line_count,t1->tm_year+1900,
											t1->tm_mon+1,t1->tm_mday,
											t1->tm_hour,t1->tm_min,t1->tm_sec);
		fflush(fp);
		sleep(1);
	}
}

int main()
{
	FILE *fp;
	int line_count = 0;
	
	signal(SIGINT,process_handler);

	fp = fopen(LOG_NAME,"a+");
	if(fp == NULL){
		fprintf(stderr,"fopen %s failed: %s\n",LOG_NAME,strerror(errno));
		exit(errno);
	}
	log_fp = fp;

	fill_upFile(fp);

	fclose(fp);

	return 0;
}
