#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/sendfile.h>
#include<unistd.h>
#define buf_size 1024

int main(int argc, char *argv[])
{
	int ifd,ofd,openflag;
	ssize_t numread;
	char buff[buf_size];
	mode_t fileperm;
	struct stat f;

	printf("%d PID\n",getpid());
	ifd=open(argv[1],O_RDONLY);
	if(ifd == -1)
	{
		fprintf(stderr, "error opening source file");
	}
	printf("Input fd setup\n");
	getchar();

	openflag=O_CREAT|O_WRONLY|O_TRUNC;
	fileperm=S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH;

	ofd=open(argv[2],openflag,fileperm);
	if (ofd == -1) 
	{
		fprintf(stderr, "error opening source file");
		exit(1);
	}
	printf("Output fd setup\n");
	getchar();

	fstat(ifd,&f);
	printf("get file state of input fd and store in stat structure\n");
	getchar();
	
	sendfile(ofd,ifd,0,f.st_size);
	printf("transfer data between file descriptors\n");
	getchar();
	
	fsync(ofd);
	
	close(ifd);
	close(ofd);
	return 0;
}
