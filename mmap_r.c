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
	fd=open(argv[1],O_RDWR);
	if(fd<0)
		sys_err("open",2);

    mm=mmap(NULL,LEN,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	if(mm==MAP_FAILED)
	{
		perror("mmap");
		exit(5);
	}
	
	close(fd);//即使文件描述符关闭,但是mmapy映射仍然存在

	
	while(1)
	{
		printf("%d\n",mm->id);
		printf("%s\n",mm->name);
		printf("%c\n",mm->sex);
		sleep(1);
	}
	munmap(mm,LEN);
    return 0;

}
