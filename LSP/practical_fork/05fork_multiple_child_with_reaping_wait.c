#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>

int main()
{
	int i,loop,childstatus;
	pid_t childpid,cpid2;
		
	childpid=fork();
	
	if(childpid == 0)
	{
		//main_after_child variable will not be visible here

		printf("\n----->First child execution started %d PID %s  PPID %d \n",getpid(),__func__,getppid());
		sleep(2);
		printf("----->First child state from running to exit state <----- \n");	
	}
	else
	{
		cpid2=fork();
		if(cpid2==0)
		{
			printf("\n---------->Second child execution started %d PID %s PPID %d\n",getpid(),__func__,getppid());
			sleep(6);
			printf("---------->Second child state from running to exit state <---------- \n");
		}
		else
		{
			for(loop=0;loop<2;loop++)
			{
				//wait(NULL);
				wait(&childstatus);
				
				if(WIFEXITED(childstatus))
					printf("\texited, status = %d\n",WEXITSTATUS(childstatus));
				else if(WIFSIGNALED(childstatus))
					printf("\tkilled by signed status %d\n",WIFSIGNALED(childstatus));
				else if(WIFSTOPPED(childstatus))
					printf("\tstopped by signal status %d\n",WSTOPSIG(childstatus));
				else if(WIFCONTINUED(childstatus))
					printf("\tContinue\n");
				printf("child state from exit to terminate state loop %d\n",loop);
			}
			
		
			printf("-->Main thread execution start once child execution done child thread will go to exit status not terminate state \n");
		
			
			for(i=0;i<10;i++)
			{
				printf("-->main thread execution %s function and PID is %d loop number %d\n",__func__,getpid(),i);
				sleep(2);
			}
		}
		//getchar();
	}
	return 0;
}
