#include <stdio.h>

/**
 *测试标准IO中的stdout和stderr的缓存类型
 *Author: 	Rocky
 *Version:	V1.0
*/

int main()
{
	fprintf(stdout,"stdout:hello world!");

	fprintf(stderr,"stderr:what's error?");

	sleep(3);

	fprintf(stdout,"stdout:\n");

	return 0;
}

