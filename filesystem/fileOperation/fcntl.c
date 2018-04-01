/************************************************************************
****	> File Name:    	fcntl.c
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	2018年03月29日 星期四 23时40分31秒
************************************************************************/

#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>

int main()
{
    int flags, accmode;

    if ( (flags = fcntl(0, F_GETFL, 0)) < 0) {
        fprintf(stderr, "Fcntl stdin error!\n");
        return -1;
    }

    accmode = flags & O_ACCMODE;
    if (accmode == O_RDONLY) {
        printf("STDIN RD ONLY\n");
    } else if (accmode == O_WRONLY) {
        printf("STDIN WR ONLY\n");
    } else if (accmode == O_RDWR) {
        printf("STDIN RD WR\n");
    } else {
        printf("UNKNOW MODE!\n");
    }

    if ( flags & O_APPEND ) {
        printf("STDIN APPEND\n");
    }
    if ( flags & O_NONBLOCK ) {
        printf("STDIN NONBLOCK\n");
    }

    return 0;
}
