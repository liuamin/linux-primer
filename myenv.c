//C file
/******************************************************
*
* Filename      : myenv.c
* Author        : Liuamin
* Email         : 502935795@qq.com
* Create        :2017-11-23 11:14:26
* Last modified :2017-11-23 11:14:26
* Description   :与env的命令一样，都是打印当前进程的环境变量，environ是一个全局变量，没有在任何头文件中，所以要extern声明。environ指向环境变量表。
* ****************************************************/
#include<stdio.h>

int main()
{
  extern char **environ;
  int i;
  for(i=0;environ[i]!=NULL;++i)
 {
    printf("%s\n",environ[i]);
 }
  return 0;
}
