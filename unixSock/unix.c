/************************************************************************
 ****	> File Name:    	unix.c
 ****	> Author:       	yiwen liu
 ****	> Mail:         	newiyuil@163.com
 ****	> Created Time: 	2018年04月04日 星期三 16时06分29秒
************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <signal.h>
#include <errno.h>
#include <sys/un.h>

static void display_err(const char *on_what) {
    perror(on_what);
    exit(EXIT_FAILURE);
}

int main()
{
    int error;
    int sock_UNIX;
    struct sockaddr_un addr_UNIX;
    int len_UNIX;
    const char path[] = "./demon/path";

    sock_UNIX = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sock_UNIX == -1) {
        display_err("socket()");
    }

    unlink(path);

    memset(&addr_UNIX, 0, sizeof(addr_UNIX));
    addr_UNIX.sun_family = AF_LOCAL;
    strcpy(addr_UNIX.sun_path, path);
    len_UNIX = sizeof(struct sockaddr_un);

    error = bind(sock_UNIX, (struct sockaddr*)&addr_UNIX, len_UNIX);
    if (error == -1) {
        display_err("bind()");
    }

    close(sock_UNIX);
    unlink(path);
    return 0;
}


