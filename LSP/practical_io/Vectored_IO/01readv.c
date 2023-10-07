#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/uio.h>

void setup_iovec_instance(struct iovec *iovec, char* buff,int size)
{
	iovec->iov_base= buff;
	iovec->iov_len=size;
}


int main()
{
	int fd,rbytes;
	struct iovec iovec_instance[4];
	char read_buff1[512];
	char read_buff2[512];
	char read_buff3[512];
	char read_buff4[512];
	
	fd= open("./test_vector_IO_in",O_RDONLY);
	if(fd<0)
	{
		perror("open fail\n");
		exit(1);
	}
	
	//sETUP IOVEC structure Instance array
	setup_iovec_instance(iovec_instance  ,read_buff1,sizeof(read_buff1)); 
	setup_iovec_instance(iovec_instance+1,read_buff2,sizeof(read_buff2)); 
	setup_iovec_instance(iovec_instance+2,read_buff3,sizeof(read_buff3)); 
	setup_iovec_instance(iovec_instance+3,read_buff4,sizeof(read_buff4)); 
	
	//read from iovecc instance
	rbytes=readv(fd,iovec_instance,4);
	
	printf("\n Total number of bytes read from file : %d \n", rbytes);
	
	printf("\n---------buf 1-----------\n%s", read_buff1);
	printf("  ---------buf 2-----------\n%s", read_buff2);
	printf("   --------buf 3------------\n%s", read_buff3);
	printf("   --------buf 4------------\n%s\n", read_buff4);

	close(fd);

	return 0;
}
