#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<signal.h>

int childstatus;

void handler(int signum)
{
	wait(&childstatus);	
	if(WIFEXITED(childstatus))
	printf("\texited, status = %d\n",WEXITSTATUS(childstatus));
	else if(WIFSIGNALED(childstatus))
		printf("\tkilled by signed status %d\n",WIFSIGNALED(childstatus));
	else if(WIFSTOPPED(childstatus))
		printf("\tstopped by signal status %d\n",WSTOPSIG(childstatus));
	else if(WIFCONTINUED(childstatus))
		printf("\tContinue\n");
	printf("---->child state from exit to terminate dtate \n");
}

int main()
{
	int i;
	pid_t cpid;
	
	cpid=fork();
	
	if(cpid == 0)
	{
		printf("---->child execution started %d PID\n",getpid());
		sleep(12);
		printf("---->child state from running to exit state \n");	
	}
	else
	{
		//Trigger event once Child thread state change
		//It will execute handler once event trigger
		signal(SIGCHLD,handler);
		
		printf("\n---main thread execution start %d\n",getpid());
		for(i=0;i<10;i++)
		{
			printf("main thread execution PID is %d\n",getpid());
			sleep(2);
		}
		printf("---Main thread execution done\n");
		
		getchar();
	}
	return 0;
}
