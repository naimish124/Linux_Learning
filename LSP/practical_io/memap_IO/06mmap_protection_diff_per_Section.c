#define _GNU_SOURCE

#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/mman.h>
#include<string.h>
#include<sys/types.h>

int main()
{
	int fd,ret;
	void* filep,*new_addr;
	
	printf("%d PID\n",getpid());
	
	fd=open("./mmap_section_test",O_CREAT|O_RDWR,S_IRWXU);
	if(fd<0)
	{
		perror("open\n");
		exit(1);
	}
	printf("empty inode assign to fd\n");
	
	posix_fallocate(fd,0,8192*2);
	printf("phy data block (I/O cache) reserve to avoid shortage\n");
	getchar();
	
	filep=mmap(0,8192*2,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	
	// filep=mmap(0,8192,PROT_READ,MAP_SHARED,fd,0);
	// filep=mmap(0,8192,PROT_NONE,MAP_SHARED,fd,0);
	// memset will fail because noone can access that pages
	if(filep == MAP_FAILED)
	{
		perror("mapping fail\n");
		exit(1);
	}
	printf("Memopory mapping of 16k done to phy m/r at %p \n",filep);
	getchar();
	
	ret=mprotect(filep,4096,PROT_EXEC|PROT_WRITE|PROT_READ);
	if(ret<0)
	{
		perror("");
		exit(1);
	}
	printf(" acess chnage for first 4k byte\n");
	getchar();
	
	ret=mprotect(filep+4096,4096,PROT_READ|PROT_WRITE);
	if(ret<0)
	{
		perror("");
		exit(1);
	}
	printf(" acess chnage for first 4k byte\n");
	getchar();
		
	ret=mprotect(filep+8192,4096,PROT_READ);
	if(ret<0)
	{
		perror("");
		exit(1);
	}
	printf(" acess chnage for first 4k byte\n");
	getchar();
		
	ret=mprotect(filep+12288,4096,PROT_READ|PROT_WRITE);
	if(ret<0)
	{
		perror("");
		exit(1);
	}
	printf(" acess chnage for first 4k byte\n");
	getchar();
	
	memset(filep+4096,'m',10);
	memset(filep+12288,'n',40);
	printf(" data written on respective section as per permission \n");
	getchar();
	
	if((munmap(filep,4096*4))!=0)
		printf("unmapping fail");
		
	return 0;
}
