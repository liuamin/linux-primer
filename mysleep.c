//C file
/******************************************************
*
* Filename      : mysleep.c
* Author        : Liuamin
* Email         : 502935795@qq.com
* Create        :2017-12-23 15:25:37
* Last modified :2017-12-23 15:25:37
* Description   :利用pause和alarm函数实现sleep函数，但是pause函数会产生时序竞态，所以pause函数用sigsuspend函数代替
* ****************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>

void sig_do(int n)
{
	/*nothing to do*/
}

unsigned int mysleep(unsigned int sec)
{
	struct sigaction newact,oldact;
	sigset_t newmask, oldmask,susmask;
    unsigned int unsleep;

	/*set handler function and save previous oldact*/
	newact.sa_handler=sig_do;
	sigemptyset(&newact.sa_mask);
	newact.sa_flags=0;
	if(sigaction(SIGALRM,&newact,&oldact)<0)
	{
		perror("sigaction");
		exit(1);
	}

	/*Block SIGALRM set mask and save pervious mask*/
	sigemptyset(&newmask);
	sigaddset(&newmask,SIGALRM);
	sigprocmask(SIG_BLOCK,&newmask,&oldmask);

	alarm(sec);
	
	susmask=oldmask;
	sigdelset(&susmask,SIGALRM);
	sigsuspend(&susmask);

	unsleep=alarm(0);

	/*restore previous handler function and mask*/
    sigaction(SIGALRM,&oldact, NULL);

	sigprocmask(SIG_SETMASK,&oldmask,NULL);

	return unsleep;
}
int main()
{
	while(1)
	{
		 printf("two seconds passed\n");
		 mysleep(2);
	}
	return 0;
}
