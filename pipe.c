#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>

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
     int len;
     close(pipefd[1]);
     while((len=read(pipefd[0],buf,sizeof(buf)))>0)
        write(STDOUT_FILENO,buf,len);
     write(STDOUT_FILENO,"\n",1);
     close(pipefd[1]);
   }
  else{
  //在父进程中,关闭父读
    close(pipefd[0]);
    write(pipefd[1],argv[1],strlen(argv[1]));
    close(pipefd[1]);
    wait(NULL);
  }
   
   return 0;
}
