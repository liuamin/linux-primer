#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<errno.h>
int main(int argc,char *argv[])
{
   if(argc!=2)
   {
      printf("Usage: %s <string>\n",argv[0]);
      exit(-1);
   }
   int pipefd[2];
   pid_t pid;
   char buf[1024];
   if(pipe(pipefd)<0){
     perror("pipe");
     exit(1);
    }
   pid =fork();
   if(pid<0){
     perror("fork");
     exit(2);
   }
   //父写子读
   else if(pid==0){
   //在子进程中,关闭子写
     int len,flags;
     close(pipefd[1]);
     //设置非阻塞属性
     flags=fcntl(pipefd[0],F_GETFL);
     flags|=O_NONBLOCK;
     fcntl(pipefd[0],F_SETFL,flags);
tryagain:
     len=read(pipefd[0],buf,sizeof(buf));
     if(len==-1)//可能读取失败或者非阻塞没数据
     {
        if(errno==EAGAIN)
        {
          //非阻塞没有数据,会返回-1,且errno为EAGAIN
          printf("try again\n");
          sleep(1);
          goto tryagain; 
        }
        else
        {
          perror("read");
          exit(1);
        } 
     }
     write(STDOUT_FILENO,buf,len);
     write(STDOUT_FILENO,"\n",1);
     close(pipefd[1]);
   }
  else{
  //在父进程中,关闭父读
    close(pipefd[0]);
    sleep(5);//先睡5s,写段没有写数据,如果read时会阻塞.可设置非阻塞属性
    write(pipefd[1],argv[1],strlen(argv[1]));
    close(pipefd[1]);
    wait(NULL);
  }
   
   return 0;
}
