#include<stdio.h>
#include<unistd.h>
int main()
{
printf("%s    \n",__func__);
printf("%s : pid %u",__func__,getpid());
getchar();
return 0;
}
