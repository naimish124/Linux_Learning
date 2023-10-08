#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<signal.h>

// while running code we can create signal by some keyboard combo (ctrl+c) 
// sudo kill -Signal_number PID_number
// sudo kill -2 1234
// Signal 2 is for SIGINT

void handler(int signum)
{
	printf("user define signal handler invoked\n");
	printf("Signal number %d\n",signum);
	sleep(2);
}

int main()
{
	signal(SIGINT,handler);
	printf("PID %d",getpid());
	while(1)
	{
		printf(" in loop\n");
		sleep(1);
	}
	return 0;
}
