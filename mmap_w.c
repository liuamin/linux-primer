#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/mman.h>

#define LEN 0x1000
struct Stu
{
	int id;
	char name[20];
	char sex;
};
void sys_err(char *str,int exitno)
{
	perror(str);
	exit(exitno);
}
int main(int argc,char *argv[])
{
	if(argc!=2)
	{
		printf("Usage: ./a.out filename");
		exit(1);
	}
	int fd;
	struct Stu *mm;
	fd=open(argv[1],O_CREAT|O_RDWR,0666);
	if(fd<0)
		sys_err("open",2);
	
	//此时创建出的文件argv[1]为空的文件,大小为0,因为没有向里面写数据
	//这里使用lseek函数拓展文件,lseek之后要进行一次write操作,才会拓展成功
	if(lseek(fd,LEN-1,SEEK_SET)<0)
		sys_err("lseek",3);
	if(write(fd,"\0",1)<0)
		sys_err("write",4);
	
    mm=mmap(NULL,LEN,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	if(mm==MAP_FAILED)
	{
		perror("mmap");
		exit(5);
	}
	
	close(fd);//即使文件描述符关闭,但是mmapy映射仍然存在

	int j=0;
    while(1)
	{
		mm->id=j;
		sprintf(mm->name,"liu %d",j);
		if(j%2)
			mm->sex='F';
		else
			mm->sex='M';
        j++;
		sleep(1);
	}
	munmap(mm,LEN);
	return 0;
}
