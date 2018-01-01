//C file
/******************************************************
*
* Filename      : maxthread.c
* Author        : Liuamin
* Email         : 502935795@qq.com
* Create        :2018-01-01 21:51:23
* Last modified :2018-01-01 21:51:23
* Description   :所在平台能创建线程的最大数目
* ****************************************************/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void *fun_th(void *arg)
{
	while(1)
       sleep(1);
}
int main()
{
	int err,i=1;
	pthread_t tid;
    while(1)
	{
		err=pthread_create(&tid,NULL,fun_th,NULL);
		if(err!=0)
		{
			printf("%s\n",strerror(err));
			exit(1);
		}
		printf("create thread %d\n",i++);

	}
	return 0;
}
