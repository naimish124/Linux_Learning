#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
//#include<sys/stat.h>

#include<unistd.h>
#define buf_size 1024

int main(int argc, char *argv[])
{
	int ifd,ofd,openflag,rev;
	ssize_t numread;
	char buff[buf_size];
	mode_t fileperm;

	printf("%d PID",getpid());
	
	ifd=open(argv[1],O_RDONLY);
	if(ifd == -1)
	{
		fprintf(stderr, "error opening source file");
	}

/*	rev = posix_fadvise(ifd, 0 , 20, POSIX_FADV_NORMAL);	 	Ok with default read_ahead */
/*	rev = posix_fadvise(ifd, 0 , 20, POSIX_FADV_RANDOM);  		Disable read_ahead */
	rev = posix_fadvise(ifd, 0, 20, POSIX_FADV_SEQUENTIAL);	// Enable full read_ahead 	
	if(rev!=0)
		perror("Posix fadvice fail");
	printf("Read ahead before Read call\n");
	getchar();

	openflag=O_CREAT|O_WRONLY|O_TRUNC;
	fileperm=S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH;

	ofd=open(argv[2],openflag,fileperm);
	if (ofd == -1) 
	{
		fprintf(stderr, "error opening source file");
		exit(1);
	}

	while((numread=read(ifd,buff,buf_size))>0)
	{ 
		printf("%ld \n",numread);
		if(write(ofd,buff,numread) != numread)
		{
			perror("write ");
			exit(1);
		}
	}
	printf("\n The read and write msg \n");
	getchar();
	
	close(ifd);
	close(ofd);
	return 0;
}
