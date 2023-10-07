#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <malloc.h>

int main()
{
	int fd, ret;
	ssize_t numRead;
	size_t size, alignment = 512;
	off_t offset;
	void *buf; // applicastion buffer

	size = getpagesize();
/*
   O_DIRECT: 
   configure user buffer (passed as agrument to read()) to be considered as 
   file cache, this buffer is passed to storage driver for direct transfer.

*/
	fd = open("./direct_read_in", O_RDONLY | O_DIRECT);
	if (fd == -1) {
		perror("open");
		exit(1);
	}
 /* 
      set up sector aligned buffer, only such allocations are suitable for
      file cache.
 */
	ret = posix_memalign(&buf, alignment, size * 8); //buffer set up as per disk partion block size so storage controller can do operation
	if (ret < 0) {
		perror("memalign");
		exit(1);
	}

/* initiate read() on the buffer for direct transfer */
	numRead = read(fd, buf, size);
	if (numRead == -1) {
		perror("read");
		exit(1);
	}
	printf("Read %ld bytes\n", (long)numRead);

}
