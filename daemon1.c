//C file
/******************************************************
*
* Filename      : daemon1.c
* Author        : Liuamin
* Email         : 502935795@qq.com
* Create        :2017-12-24 19:37:59
* Last modified :2017-12-24 19:37:59
* Description   :编写一个守护进程，每隔10s在dameon.log文件中写入当前时间
* ****************************************************/
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<time.h>
#include<string.h>
void sys_err(char *str,int errno)
{
	perror(str);
	exit(errno);
}
void daemon1()
{
	pid_t pid;
	pid=fork();
	if(pid<0)
		sys_err("fork",1);
	/*终止父进程*/
	else if(pid>0)
		exit(7);
    /*in child*/
	//创建新会话
	if(setsid()==-1)
		sys_err("setsid",2);
	//改变当前目录的工作路径
	if(chdir("/home/liuamin")==-1)
		sys_err("chdir",3);
	
	umask(0);
	//关闭无效的文件描述符
	close(0);
	open("/dev/null",O_RDWR);//此时/dev/null对应的文件描述符为0
    //表示复制文件描述符，另新的文件描述符指向旧的文件描述符，共用一个
	//此时，0,1,2 三个文件描述符都指向/dev/null
	dup2(0,1);
	dup2(0,2);
    
}
int main(int argc,char *argv[])
{
	if(argc!=2)
		printf("Usage: ./daemon1 file\n");
	daemon1();
	int fd;
	time_t t;
	char buf[1024];
	while(1)
	{
		if((fd=open(argv[1],O_CREAT | O_RDWR | O_APPEND,0666))==-1)
			sys_err("open",4);
		time(&t);
		ctime_r(&t,buf);
        write(fd,buf,strlen(buf));
		sleep(10);
		printf("sleep 10s\n");
	}
	return 0;
}
