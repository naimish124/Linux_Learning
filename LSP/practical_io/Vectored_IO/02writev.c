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
	int fd,wbytes,rbytes,fdread;
	struct iovec iovec_instance[4];
	char write_buff1[100]={0};
	char write_buff2[100];
	char write_buff3[100];
	char write_buff4[100];
	
	fdread= open("./test_vector_IO_in",O_RDONLY);
	fd= open("./test_vector_IO_out",O_WRONLY|O_CREAT,0644);
	if(fd<0 | fdread<0)
	{
		perror("open fail\n");
		exit(1);
	}
	
	//sETUP IOVEC structure Instance array
	setup_iovec_instance(iovec_instance  ,write_buff1,sizeof(write_buff1)); 
	setup_iovec_instance(iovec_instance+1,write_buff2,sizeof(write_buff2)); 
	setup_iovec_instance(iovec_instance+2,write_buff3,sizeof(write_buff3)); 
	setup_iovec_instance(iovec_instance+3,write_buff4,sizeof(write_buff4)); 
	
	//read from file descriptor to iovecc instance
	rbytes=readv(fdread,iovec_instance,4);
	//write from iovecc instance to output fd
	wbytes=writev(fd,iovec_instance,sizeof(iovec_instance)/sizeof( struct iovec));
	
	printf("\n Total number of bytes read from file : %d \n", wbytes);
	printf("\n Total number of bytes read from file : %d \n", rbytes);
	printf("\n---------buf 1-----------\n%s", write_buff1);
	printf("\n---------buf 2-----------\n%s", write_buff2);
	printf("\n---------buf 3------------\n%s", write_buff3);
	printf("\n---------buf 4------------\n%s\n", write_buff4);

	close(fd);

	return 0;
}
