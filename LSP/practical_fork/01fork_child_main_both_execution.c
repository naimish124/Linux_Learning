#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main()
{
	pid_t childpid;
	childpid=fork();
	printf("%s function and PID is %d\n",__func__,getpid());
	getchar();
}
