/************************************************************************
 ****	> File Name:    	select.c
 ****	> Author:       	yiwen liu
 ****	> Mail:         	newiyuil@163.com
 ****	> Created Time: 	2018年04月04日 星期三 12时33分06秒
************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>

int main()
{
    fd_set rd;
    struct timeval tv;
    int err;

    FD_ZERO(&rd);
    FD_SET(0, &rd);

    tv.tv_sec = 5;
    tv.tv_usec = 0;
    err = select(1, &rd, NULL, NULL, &tv);

    if (err == -1) {
        perror("select():");
    } else if (err) {
        printf("Data is available now\n");
    } else {
        printf("No data within five seconds.\n");
    }

    char c;
    while ( (c=getchar())!=EOF && c!='\n' );
    return 0;
}

