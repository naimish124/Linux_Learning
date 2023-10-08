#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/wait.h>

int main()
{
	int fd,flags;
	pid_t cpid;
	char buf[3]={'n','a','i'};
	char template[]="/tmp/testXXXXXX";
	fd=mkstemp(template);
	if (fd == -1) 
	{
		perror("mkstemp");
		exit(1);
	}
	cpid=fork();
	switch(cpid)
	{
	case -1:
		perror("fork fail");
		exit(1);
	case 0:
		//Child execution
		write(fd,buf,3);
		write(fd,buf,1);
		write(fd,buf,2);
		if((lseek(fd,5,SEEK_SET)) == -1)
		{
			perror("lseekfail");
			exit(1);
		}
		
		// Fetch current flags
		flags=fcntl(fd,F_GETFD);
		if (flags == -1) 
		{
			perror("fcntl - F_GETFL");
			exit(1);
		}
		
		//modifying flag for fd
		flags |= O_APPEND;	/* Turn O_APPEND on */
		
		if (fcntl(fd, F_SETFL, flags) == -1) {
			perror("fcntl - F_SETFL");
			exit(1);
		}
		
		write(fd,buf,3);
		close(fd); // COW of fd for parent
		break;

	default:

		/* lets test if Parent can see file-Descriptor changes made by child */
		wait(NULL);

		printf("Child has exited\n");
		printf("File offset in parent: %lld\n",
		       (long long)lseek(fd, 0, SEEK_CUR));
		flags = fcntl(fd, F_GETFL);
		printf("O_APPEND flag in parent is: %s\n",
		       (flags & O_APPEND) ? "on" : "off");
		break;
	}
	return 0;
}
