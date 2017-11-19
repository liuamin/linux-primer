#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>

#define SIZE 8192
int main(int argc, char *argv[])
{
    if(argc<3)
    {
      perror("./mycp src dest");
      exit(1);
    }
    char buf[SIZE];
    int fd_src,fd_dest,len;
    fd_src=open(argv[1],O_RDONLY);
    if(fd_src<0)
    {
       perror("src open");
       exit(1);
    } 
    fd_dest=open(argv[2],O_CREAT |O_RDWR|O_TRUNC,0666);
    if(fd_dest<0)
    {
       perror("dest open");
       exit(1);
    }

    while(len=read(fd_src,buf,sizeof(buf)))
    {
      write(fd_dest,buf,len);
    }

    close(fd_src);
    close(fd_dest);

    return 0;
}
