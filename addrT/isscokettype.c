/************************************************************************
 ****	> File Name:    	isscokettype.c
 ****	> Author:       	yiwen liu
 ****	> Mail:         	newiyuil@163.com
 ****	> Created Time: 	2018年04月04日 星期三 09时51分39秒
************************************************************************/

#include <stdio.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <arpa/inet.h>

int issockettype(int fd) {
    struct stat st;

    int err = fstat(fd, &st);
    if (err < 0) {
        return -1;
    }

    if ((st.st_mode & S_IFMT) == S_IFSOCK) {
        return 1;
    }
    return 0;
}

int main()
{
    int ret  = issockettype(0);
    printf("value %d\n", ret);

    int s = socket(AF_INET, SOCK_STREAM, 0);
    printf("value %d\n", issockettype(s));

    return 0;
}
