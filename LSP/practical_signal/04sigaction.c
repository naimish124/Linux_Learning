#include<stdio.h>
#include<signal.h>
#include<string.h>
#include<unistd.h>

void handler(int signum)
{
	printf("Signal handler invoked\n");
	sleep(4);
	printf("Signal handler execution done\n");
}

int main()
{
	struct sigaction act;
	memset(&act,0,sizeof(act));
	
	printf("PID %d",getpid());
		
	/* Install signal handlers */
	act.sa_handler= handler;
	sigaction(SIGINT,&act,NULL);
		
	while(1)
	{
		printf(" in loop\n");
		sleep(1);
	}
	return 0;
}

