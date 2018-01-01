//C file
/******************************************************
*
* Filename      : test.c
* Author        : Liuamin
* Email         : 502935795@qq.com
* Create        :2017-11-25 11:57:06
* Last modified :2017-11-25 11:57:06
* Description   :exec时，替换原有的程序，打开火狐，exec之后的代码将不会执行，因为原有的程序彻底被替换，但是pid号并未改变
* ****************************************************/
#include<stdio.h>
#include<unistd.h>

int main()
{
   printf("hello\n");
   execl("/usr/bin/firefox","firefox","www.baidu.com",NULL);
   printf("world!");
   return 0;
}
