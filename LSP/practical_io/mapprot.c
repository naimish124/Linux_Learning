/*
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * ******************************************************************************
 * This program is part of the source code provided with
 * "Linux Systems Programming Essentials" Course offered by TECHVEDA(c) 2020 - 2022
 * Course page : https://www.techveda.org/linuxsysprg
 * Trainer:  Raghu Bharadwaj
 * ******************************************************************************
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int fd, i;
	unsigned char *filedata = NULL, *temp;

	fd = open("test.file", O_RDWR);

	filedata = (char *)mmap((void *)0, 4096, PROT_READ, MAP_SHARED, fd, 0);
	if (filedata == NULL) {
		perror("Maping Failed");
		exit(1);
	}
	temp = filedata;

	for (i = 0; i < 100; i++, filedata++)
		printf("%c", *filedata);

	printf("pid %d\n", getpid());

	getchar();

	mprotect(temp, 100, PROT_WRITE);

	getchar();	

	filedata -= 100;
	for (i = 0; i < 100; i++, filedata++)
		*filedata = (char)(i + 65);

	if (msync(temp, 4096, MS_SYNC) != 0)
		perror("msync : ");

	i = munmap(temp, 4096);
	if (i != 0)
		printf(" failed to unmap\n");
	return 0;
}
