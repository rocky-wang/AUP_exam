#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>

/**************************************************
 *列出目录下的文件信息
***************************************************/
int dir_info(const char *dir_name)
{
	DIR *pdir;
	struct dirent *ditem;

	pdir = opendir(dir_name);
	if(pdir == NULL){
		fprintf(stderr,"opendir %s failed :%s!\n",dir_name,strerror(errno));
		return errno;
	}
	
	while( (ditem = readdir(pdir)) != NULL){
		if( strncmp(ditem->d_name,".",1) == 0 )
			continue;
		fprintf(stdout,"%s\n",ditem->d_name);
	}

	return 0;
}

int main(int argc,char *argv[])
{
	if(argc != 2){
		fprintf(stderr,"Usage %s DIR_Name format!\n",argv[0]);
		exit(-1);
	}

	dir_info(argv[1]);

	return 0;
}

