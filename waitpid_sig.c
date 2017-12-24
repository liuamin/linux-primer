//C file
/******************************************************
*
* Filename      : waitpid_sig.c
* Author        : Liuamin
* Email         : 502935795@qq.com
* Create        :2017-12-24 10:55:59
* Last modified :2017-12-24 10:55:59
* Description   :之前回收子进程，利用wait函数（阻塞）或waitpid函数（轮询）进行回收僵尸进程，现在采用信号（SIGCHLD）回收子进程
* ****************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
void sys_err(char *str,int errno)
{
	perror(str);
	exit(errno);
}
void sig_do_child(int signo)
{
	int status;
	pid_t pid;
	while((pid=waitpid(0,&status,WNOHANG))>0)
	{
		if(WIFEXITED(status))
			printf("child %d exit %d\n",pid,WEXITSTATUS(status));
		if(WIFSIGNALED(status))
			printf("child %d signal %d\n",pid,WTERMSIG(status));
	}
}
int main()
{
	pid_t pid;
	int i;
	for(i=0;i<10;++i)
	{
		pid=fork();
		if(pid==0)
			break;
		else if(pid<0)
			sys_err("fork",1);
	}
	/*in child*/
	if(pid==0)
	{
		int n=18;
		while(n--)
		{
			printf("child PID:%d\n",getpid());
			sleep(1);
		}
		 return i;
		
	}
	/*in parent*/
	else if(pid>0)
	{
		//设置SIGCHLD捕捉函数
		struct sigaction act;
		act.sa_handler=sig_do_child;
		sigemptyset(&act.sa_mask);
		act.sa_flags=0;

		sigaction(SIGCHLD,&act,NULL);

		while(1)
		{
			printf("parent PID:%d\n",getpid());
			sleep(1);
		}
	}
	return 0;
}
