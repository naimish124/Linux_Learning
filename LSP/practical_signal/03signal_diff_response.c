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
	printf("PID %d",getpid());
	
	signal(SIGINT, SIG_IGN);
	printf("%s: signal 2 now set to be ignored \n", __func__);
	getchar();

	signal(SIGINT, handler);
	printf("%s: Application specific handler registerd \n", __func__);
	getchar();

	signal(SIGINT, SIG_DFL);
	printf( "%s: Default handler enabled \n", __func__);
	getchar();
	
	return 0;
}
