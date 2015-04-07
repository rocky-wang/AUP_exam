#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

/**************************************************
 *模拟ls -l命令，只保留文件属性和大小及文件名
***************************************************/
int show_info(const char *name)
{
	struct stat buf;
	int n;

	memset(&buf,0,sizeof(buf));

	if( lstat(name,&buf) < 0 ){
		perror("lstat");
		return -1;
	}

	switch(buf.st_mode & S_IFMT)
	{
		case S_IFREG:	
			printf("-");
			break;
		case S_IFDIR:	
			printf("d");
			break;
		case S_IFCHR:	
			printf("c");
			break;
		case S_IFBLK:	
			printf("b");
			break;
		case S_IFIFO:	
			printf("p");
			break;
		case S_IFLNK:	
			printf("l");
			break;
		case S_IFSOCK:	
			printf("s");
			break;
	}

	for( n = 8; n >= 0; n-- ){
		if(buf.st_mode&(1<<n)){
			switch(n%3){
				case 2:
					printf("r");
					break;
				case 1:
					printf("w");
					break;
				case 0:
					printf("x");
					break;
				default:
					break;

			}
		}
		else{
			printf("-");
		}
	}

	printf("\t%ld",buf.st_size);
	printf("\t\t%s\n",name);

	return 0;
}

int dir_info(const char *dir_name)
{
	DIR *pdir;
	struct dirent *ditem;
	char buf[1024];

	pdir = opendir(dir_name);
	if(pdir == NULL){
		fprintf(stderr,"opendir %s failed :%s!\n",dir_name,strerror(errno));
		return errno;
	}
	
	while( (ditem = readdir(pdir)) != NULL){
		if( strncmp(ditem->d_name,".",1) == 0 )
			continue;
		show_info(ditem->d_name);
	}

	return 0;
}

int list_info(const char *name)
{
	struct stat buf;

	if(lstat(name,&buf) < 0 ){
		perror("lstat");
		return -1;
	}

	if(S_ISDIR(buf.st_mode)){
		chdir(name);
		dir_info(name);
	}
	else{
		show_info(name);
	}
}

int main(int argc,char *argv[])
{
	if(argc != 2){
		fprintf(stderr,"Usage %s DIR_Name format!\n",argv[0]);
		exit(-1);
	}

	list_info(argv[1]);

	return 0;
}

