#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
int global = 10; //DATA segment variable

int main()
{
	int i;
	int local = 1;//STACK segment
	pid_t childpid;
	
	childpid=fork();

	if(childpid == 0)
	{
		printf("**In child global var %d, local var =%d\n",global,local); 
		//main_after_child variable will not be visible here
		
		printf("----->child execution started %d PID\n",getpid());
		sleep(4);
		local =100;  //COW copy on write
		printf("**In child global var %d, local var =%d\n",global,local);
		printf("----->child state from running to exit state \n");	
	}
	else
	{
		global =20;  //COW copy on write
		printf(" Main thread execution start once child execution done child thread will go to exit status not terminate state \n");
		printf("**In main global var %d, local var =%d\n",global,local);
		for(i=0;i<5;i++)
		{
			printf("main thread execution PID is %d\n",getpid());
			sleep(2);
		}
		getchar();
	}
}
