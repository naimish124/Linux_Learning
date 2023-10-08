#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/wait.h>

int main()
{
	int fd;
	pid_t cpid;
	char buf[2];
	int childstatus;
	//cpid=fork(); 
	//When this is enable, o/p will be ab ab because fd is created for both child and main thread
	fd=open("./fork_test",O_RDONLY);
	if(fd < 0)
	{
		perror("Open fail");
		exit(1);
	}
	cpid=fork();
	//When this is enable, o/p will be ab cd because fd is already is there and state change is not done so same offset will use
	if(cpid==0)
	{
		printf("-----> Child process %d PID\n",getpid());
		read(fd,buf,2);
		printf("%c  %c\n",buf[0],buf[1]);
		close(fd);
	}
	else
	{
		wait(&childstatus);
		printf("main thread %d PID\n",getpid());
		read(fd,buf,2);
		printf("%c  %c\n",buf[0],buf[1]);
		close(fd);

	}

	return 0;
}
