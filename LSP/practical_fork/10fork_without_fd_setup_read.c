#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/wait.h>

int main()
{
	int fd,ret;
	int childstatus;
	pid_t cpid;
	char buf[2];

	cpid=fork();
	if(cpid==0)
	{
		printf("-----> Child process %d PID\n",getpid());
		ret = read(fd,buf,2);
		//fd have garbage data with that it will try to read and due to that it will fail
		if(ret <0)
		{
			perror("read fail\n");
			exit(1);
		}
		printf("chile process %c  %c %d\n",buf[0],buf[1],ret);
		close(fd);
	}
	else
	{
		wait(&childstatus);
		fd=open("./fork_test",O_RDONLY);
		printf("main thread %d PID\n",getpid());
		read(fd,buf,2);
		printf("main thread %c  %c\n",buf[0],buf[1]);
		close(fd);

	}

	return 0;
}
