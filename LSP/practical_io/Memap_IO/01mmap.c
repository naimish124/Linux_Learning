#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/mman.h>
#include<string.h>

int main()
{
	int fd;
	void* filep;
	
	printf("%d PID\n",getpid());
	
	fd=open("./mmap_test",O_CREAT|O_RDWR,S_IRWXU);
	if(fd<0)
	{
		perror("open\n");
		exit(1);
	}
	printf("empty inode assign to fd\n");
	
	posix_fallocate(fd,0,8192);
	printf("phy data block (I/O cache) reserve to avoid shortage\n");
	getchar();
	
	filep=mmap(0,8192,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	
	// filep=mmap(0,8192,PROT_READ,MAP_SHARED,fd,0);
	// filep=mmap(0,8192,PROT_NONE,MAP_SHARED,fd,0);
	// memset will fail because noone can access that pages
	
	if(filep == MAP_FAILED)
	{
		perror("mapping fail\n");
		exit(1);
	}
	printf("Memopory mapping done to phy m/r \n");
	getchar();
	
	close(fd);
	printf("Fd closed \n");
	getchar();
	
	memset(filep,'n',8192);
	printf("writing of 'n' in all reserved block\n");
	getchar();
	
	munmap(filep,8192);	
	printf("m/r unmapping done");
	getchar();
	
	return 0;
}
