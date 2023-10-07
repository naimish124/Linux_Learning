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
	int fd;
	void* filep,*new_addr;
	
	printf("%d PID\n",getpid());
	
	fd=open("./mmap_test",O_CREAT|O_RDWR,S_IRWXU);
	if(fd<0)
	{
		perror("open\n");
		exit(1);
	}
	printf("empty inode assign to fd\n");
	
	posix_fallocate(fd,0,8192*2);
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
	printf("Memopory mapping done to phy m/r at %p \n",filep);
	getchar();
	
	close(fd);
	printf("Fd closed \n");
	getchar();
	
	memset(filep,'n',8192);
	printf("writing of 'n' in all reserved block\n");
	getchar();
	
	
	//In case of m/r mapping expanding address will change as per define flag/attribute
	new_addr=mremap(filep,8192,4*4096,MREMAP_MAYMOVE);
	
	//new_addr=mremap(filep,8192,4*4096,MREMAP_FIXED);
	// while doing memory rempaing if we are keeping FIXED flag than may be it leads to failure of remap becaus eof not available expandable m/r at filep place	
	
	if(new_addr == 0xffffffffffffffff)
	{
		perror("memory remap fail\n");
		exit(1);
	}
	else
	{
		printf("16k mapping done at %p New address is differ than old address\n",new_addr);
		getchar();
	}
	
	memset(new_addr,'o',8192*2);
	printf("writing of 'o' in all (old+ new) reserved block \n");
	getchar();
	
	munmap(new_addr,8192*2);	
	printf("m/r unmapping done");
	getchar();
	
	return 0;
}
