//C file
/******************************************************
*
* Filename      : sigaction.c
* Author        : Liuamin
* Email         : 502935795@qq.com
* Create        :2017-12-23 14:01:41
* Last modified :2017-12-23 14:01:41
* Description   :自定义信号（SIGINT）的处理函数，利用sigcation函数实现
* ****************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>

void sig_do(int n)
{
	printf("kill SIGINT signal\n");
}
int main()
{
	struct sigaction act;

	act.sa_handler=sig_do;
	sigemptyset(&act.sa_mask);
	act.sa_flags=0;
	
	 if(sigaction(SIGINT,&act,NULL)<0)
	 {
		 perror("sigaction");
		 exit(1);
	 } 
	 while(1)
	 {
		 printf("**********\n");
		 sleep(2);
	 }

	 return 0;
}
