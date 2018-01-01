#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#define LEN 0x1000
void sys_err(char *str,int exitno)
{
    perror(str);
    exit(exitno);
}
int main(void)
{
	int *p;
	int fd = open("hello", O_RDWR|O_CREAT,0666);
	if (fd < 0) {
		perror("open hello");
		exit(1);
	}
        //拓展一个文件大小为4k,如果文件为空,mmap时会报总线错误.
        if(lseek(fd,LEN-1,SEEK_END)<0)
           sys_err("lseek",2);
        
        if(write(fd,"\0",1)<0)
           sys_err("write",3);
        
        
	p = mmap(NULL,LEN, PROT_WRITE, MAP_SHARED, fd, 0);
	if (p == MAP_FAILED) {
		perror("mmap");
		exit(1);
	}
	close(fd);
	p[0] = 0x30313233;
	munmap(p, LEN);
	return 0;
}
