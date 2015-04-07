#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

/*********************************************
 *文件拷贝测试程序，以字符形式fgetc/fputc内容拷贝
 *分析对比不同形式拷贝方式的区别
**********************************************/
int fileCopy_Char(FILE *srcFile,FILE *destFile)
{
	int c;
	int count = 0;

	while( (c = fgetc(srcFile)) != EOF){
		fputc(c,destFile);
		count++;
	}

	return count;
}

int main(int argc,char *argv[])
{
	FILE *srcFile = NULL;
	FILE *destFile = NULL;
	int count;

	if(argc != 3){
		fprintf(stderr,"Using %s SrcFileName DestFileName\n",argv[0]);
		exit(1);
	}

	srcFile = fopen(argv[1],"r");
	if(srcFile == NULL){
		fprintf(stderr,"open %s file failed: %s\n",argv[1],strerror(errno));
		exit(errno);
	}

	destFile = fopen(argv[2],"w");
	if(destFile == NULL){
		fprintf(stderr,"open %s file failed: %s\n",argv[2],strerror(errno));
		exit(errno);
	}
	
	count = fileCopy_Char(srcFile,destFile);
	fprintf(stdout,"file copy %d Bytes!\n",count);

	fclose(srcFile);
	fclose(destFile);

	return 0;
}

