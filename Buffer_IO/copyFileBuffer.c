#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/*********************************************
 *文件拷贝测试程序，以非格式化缓存形式fread/fwrite内容拷贝
 *分析对比不同形式的拷贝方式区别
**********************************************/
int fileCopy_Buffer(FILE *srcFile,FILE *destFile)
{
	unsigned char buf[1024];
	int read_len;
	int write_len;

	while( (read_len = fread(buf,sizeof(char),1024,srcFile)) != 0){
		if(read_len < 0){
			perror("fread:");
			return -1;
		}
		write_len = fwrite(buf,sizeof(char),read_len,destFile);
		if(write_len != read_len){
			perror("fwrite:");
			return -1;
		}
	}

	return 0;
}

int main(int argc,char *argv[])
{
	FILE *srcFile = NULL;
	FILE *destFile = NULL;
	int ret;

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
	
	ret = fileCopy_Buffer(srcFile,destFile);
	if(ret != 0 ){
		fprintf(stderr,"file copy failed!\n");
	}
	fprintf(stdout,"file copy success!\n");

	fclose(srcFile);
	fclose(destFile);

	return 0;
}

