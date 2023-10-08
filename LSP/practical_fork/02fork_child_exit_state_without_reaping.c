#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main()
{
	int i;
	pid_t childpid;
	
	int common_var=0;
	
	childpid=fork();
	int main_thread_var=0;
	
	if(childpid == 0)
	{
		common_var=main_thread_var=2;
		
		//main_after_child variable will not be visible here
		
		printf("----->child execution started %d PID %s\n",getpid(),__func__);
		printf("----->child common_var = %d , main_thread_var = %d \n",common_var,main_thread_var);
		sleep(4);
		printf("----->child state from running to exit state \n");	
	}
	else
	{
		int main_after_child = 0 ;
		common_var=main_thread_var=4;
		printf(" Main thread execution start once child execution done child thread will go to exit status not terminate state \n");
		printf("-->main thread common_var = %d , main_thread_var = %d , main_after_child = %d \n",common_var,main_thread_var,main_after_child);
		
		for(i=0;i<5;i++)
		{
			printf("main thread execution %s function and PID is %d\n",__func__,getpid());
			sleep(2);
		}
		getchar();
	}
}
