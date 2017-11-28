#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
int main(int argc,char* argv[])
{
    char buf[1024]="hello world!\n";
    if(argc!=2)
    {
       printf("Usage: ./filename fifoname\n");
       exit(1);
    }
    int fi,flag;
    flag=access(argv[1],F_OK);
    if(flag==-1)
    {
	 fi= mkfifo(argv[1],0666);
	 if(fi<0)
	  {
	      perror("mkfifo");
	      exit(1);
	  }
    }
   int fd;
   fd=open(argv[1],O_WRONLY);
   if(fd<0)
   {
      perror("open");
      exit(1);
   }
   
   write(fd,buf,strlen(buf));
   close(fd);
   return 0;
   
}
