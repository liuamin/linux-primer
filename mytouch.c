#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>

int main(int argc ,char *argv[])
{
    int fd;
    if(argc<2)
    {
      perror("./mytouch filename");
      exit(1);
    }
    //这里当文件存在时，更新文件存在的时间，没有实现？？
    fd=open(argv[1],O_CREAT|O_RDWR|O_APPEND,0666);
    if(fd<0)
    {
      perror("main open");
      exit(1);
    }
    close(fd);
    
    return 0;
 
}

