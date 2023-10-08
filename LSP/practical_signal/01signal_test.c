#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

// while running code we can create signal by some keyboard combo (ctrl+c) 
// sudo kill -Signal_number PID_number
// sudo kill -4 1234

int main()
{
	printf("PID %d",getpid());
	while(1)
	{
		printf(" in loop\n");
		sleep(1);
	}
	return 0;
}
