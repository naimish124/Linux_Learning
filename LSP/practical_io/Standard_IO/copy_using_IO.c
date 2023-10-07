#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
//#include<sys/stat.h>

#include<unistd.h>
#define buf_size 1024

int main(int argc, char *argv[])
{
int ifd,ofd,openflag;
ssize_t numread;
char buff[buf_size];
mode_t fileperm;

	ifd=open(argv[1],O_RDONLY);
	if(ifd == -1)
	{
		fprintf(stderr, "error opening source file");
	}

openflag=O_CREAT|O_WRONLY|O_TRUNC;
fileperm=S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH;

	ofd=open(argv[2],openflag,fileperm);
	if (ofd == -1) {
		fprintf(stderr, "error opening source file");
		exit(1);
	}


while((numread=read(ifd,buff,buf_size))>0)
{ 
	printf("%ld \n",numread);
	if(write(ofd,buff,numread) != numread){
			perror("write ");
			exit(1);
		}
}
close(ifd);
close(ofd);
}
