//C file
/******************************************************
*
* Filename      : sigprocmask.c
* Author        : Liuamin
* Email         : 502935795@qq.com
* Create        :2017-12-16 15:26:55
* Last modified :2017-12-16 15:26:55
* Description   :设置阻塞信号集（信号屏蔽字）对应位为1，也就是阻塞
* ****************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
void printsigset(const sigset_t *set)
{
	int i;
	for(i=1;i<32;++i)
	{
		if(sigismember(set,i)==0)
			printf("0");
		else
			printf("1");
	}	
	printf("\n");
}
int main(int argc,char *argv[])
{
	sigset_t s,p;
	sigemptyset(&s);
	sigaddset(&s,SIGINT);
	sigaddset(&s,SIGQUIT);
	if(sigprocmask(SIG_BLOCK,&s,NULL)<0)
	{
		perror("sigprocmask");
		exit(1);
	}
	while(1)
	{
		sigpending(&p);
		printsigset(&p);
		sleep(1);
	}
	return 0;
}
