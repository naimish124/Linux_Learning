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
	int fd,i;
	unsigned char* filep,*temp;
	
	printf("%d PID\n",getpid());
	
	fd=open("./protect_test.txt",O_RDWR);
	if(fd<0)
	{
		perror("open fail\n");
		exit(1);
	}
	printf("fd created\n");
	
	filep=(char*)mmap(0,8192,PROT_READ,MAP_SHARED,fd,0);
	if(filep == NULL)
	{
		perror("mapping fail\n");
		exit(1);
	}
	temp=filep;
	
	for(i=0;i<100;i++,filep++)
		printf("%c",*filep);
	printf("\nData printed on terminal from file\n");
	getchar();
	
	mprotect(temp,100,PROT_WRITE);
	printf(" acess chnage for 100 byte\n");
	getchar();
	
	filep -=100;
	
	for(i=0;i<100;i++,filep++)
		*filep=(char)(i+65);
	printf("writing data into file\n");
	
	
	filep -=100;
	for(i=0;i<100;i++,filep++)
		printf("%c",*filep);
	printf("\n Updated Data printed on terminal from file\n");
	getchar();
	
	if(msync(temp,4096,MS_SYNC)!=0)
		perror("msync :\n");
	
	if((munmap(temp,4096))!=0)
		printf("unmapping fail");
		
	return 0;
}
