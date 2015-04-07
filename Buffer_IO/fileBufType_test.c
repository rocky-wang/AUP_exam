#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE *fp = NULL;

	fp = fopen("test.txt","w+");
	if(fp == NULL){
		perror("fopen");
		exit(1);
	}

	fprintf(fp,"hello world!\n");

	fprintf(stdout,"wirte a string to test.txt file!\n");
	/*这里的getchar可以暂停程序，
	 *此时我们再通过另外一个终端，去读取test.txt文件内容
	 *如果发现该文件是空的，说明前面的字符串并没有写入到文件中
	 *即使有\n的换行符来刷新。
	**/
	fprintf(stdout,"Please open another Termial,use \'cat test.txt\' to see and analyse.\n");
	fprintf(stdout,"After press any key to continue...\n");
	getchar();

	/*
	 *此时关闭fp，系统会将缓存区内容刷新到文件里
	**/
	fclose(fp);

	return 0;
}

