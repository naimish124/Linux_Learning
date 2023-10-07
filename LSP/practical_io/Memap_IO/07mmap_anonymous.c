#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/mman.h>
#include<string.h>

int main()
{
	int i;
	void* filep,*temp;
	
	printf("%d PID\n",getpid());
	
	filep=mmap(0,4096,PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,-1,0);
	if(filep == MAP_FAILED)
	{
		perror("mapping fail\n");
		exit(1);
	}
	printf("Anonymous Memopory mapping done to phy m/r \n");
	getchar();
	
	memset(filep,'n',4096);
	temp=filep;
	printf("writing of 'n' in all reserved block\n");
	for(i=0;i<4096;i++,filep++)
		printf("%c",*(char *)filep);
	printf("\nscreen print of 'n' in all reserved block\n");
	getchar();
	
	if((munmap(temp,4096))!=0)
	{
		perror("failed to unmap\n");
		exit(1);
	}	
	printf("Anonymous m/r unmapping done");
	getchar();
	
	return 0;
}
