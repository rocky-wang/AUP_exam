#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/*********************************************
 *文件拷贝测试程序，以字符串形式fgets/fputs内容拷贝
 *这里的拷贝只能支持文本文件拷贝，对于非文本方式请自行测试并讨论
 *分析对比不同形式的拷贝方式区别
**********************************************/
int fileCopy_Line(FILE *srcFile,FILE *destFile)
{
	char buf[1024];
	int count = 0;

	while(fgets(buf,sizeof(buf),srcFile) != NULL){
		fputs(buf,destFile);
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
		fprintf(stderr,"open %s file failed:%s\n",argv[1],strerror(errno));
		exit(errno);
	}

	destFile = fopen(argv[2],"w");
	if(destFile == NULL){
		fprintf(stderr,"open %s file failed:%s\n",argv[2],strerror(errno));
		exit(errno);
	}
	
	count = fileCopy_Line(srcFile,destFile);
	fprintf(stdout,"the copy %d line!\n",count);

	fclose(srcFile);
	fclose(destFile);

	return 0;
}

