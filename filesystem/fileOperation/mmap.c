/************************************************************************
****	> File Name:    	mmap.c
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	2018年03月29日 星期四 23时18分19秒
************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/mman.h>

#define FILELENGTH 80

int main() {
    int fd;
    char buf[] = "quick brown fox jumps over the lazy dog";
    char *ptr = NULL;
    char filename[] = "temp_testformmap";

    if ( (fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 00600)) == -1 ) {
        fprintf(stderr, "Open %s error\n", filename);
        exit(-1);
    }

    lseek(fd, FILELENGTH-1, SEEK_SET);

    write(fd, "a", 1);

    if ( *(ptr = (char *)mmap(NULL, FILELENGTH, PROT_READ | PROT_WRITE, MAP_SHARED, fd ,0))
        == -1 ) {
            fprintf(stderr, "Mmap %s error!\n", filename);
            exit(-1);
        }

    memcpy(ptr+0x10, buf, strlen(buf));

    munmap(ptr, FILELENGTH);
    close(fd);

    return 0;
}
