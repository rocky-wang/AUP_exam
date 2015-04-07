#include <stdio.h>

/*****************************************************
 *根据传递的FILE指针所保存的_flags标志进行缓存类型的判断
 *根据FILE指针中缓存区的收尾地址值的差来计算缓存的大小
 *这里要注意，每个FILE的缓存大小一定要在IO请求后才能计算出来
 *原因请各位同学分析并讨论。
******************************************************/
void get_stream_info(FILE *fp)
{
    if(fp->_flags & _IO_UNBUFFERED){
        printf("\tThe IO type is unbuffer!\n");
    }
    else if(fp->_flags & _IO_LINE_BUF){
        printf("\tThe IO type is line buffer!\n");
    }
    else{
        printf("\tThe IO type is full buffer!\n");
    }

    printf("\tThe IO buf size is %ld\n",fp->_IO_buf_end - fp->_IO_buf_base);
}

int main()
{
	FILE *fp;

    fprintf(stdout,"the stdout info :\n");
    get_stream_info(stdout);

	fprintf(stderr,"the stderr info :\n");
    get_stream_info(stderr);
    
    fp = fopen("test.txt","w+");
    fgetc(fp);
	fprintf(stdout,"the File buf info :\n");
    get_stream_info(fp);
    fclose(fp);

	return 0;
}

