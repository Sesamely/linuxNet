/************************************************************************
 ****	> File Name:    	tcp_server.c
 ****	> Author:       	yiwen liu
 ****	> Mail:         	newiyuil@163.com
 ****	> Created Time: 	2018年04月03日 星期二 13时02分34秒
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>

#include "tcp_process.h"

#define PORT 8888
#define BACKLOG 2

int main()
{
    int ss, sc;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;

    int err;
    pid_t pid;

    ss = socket(AF_INET, SOCK_STREAM, 0);
    if (ss < 0) {
        fprintf(stderr, "socket error\n");
        return -1;
    }
    
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORT);

    err = bind(ss, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (err < 0) {
        fprintf(stderr, "bind error!\n");
        return -1;
    }

    err = listen(ss, BACKLOG);
    if (err < 0) {
        fprintf(stderr, "listen error!\n");
        return -1;
    }

    signal(SIGCHLD, SIG_IGN);
    for (;;) {
        socklen_t addrlen = sizeof(struct sockaddr);

        sc = accept(ss, (struct sockaddr *)&client_addr, &addrlen);
        if (sc < 0) {
            continue;
        }

        pid = fork();
        if (pid == -1) {
            close(sc);
            continue;
        }
        if (pid == 0) {
            close(ss);

    #ifndef __FOR_FILE
            process_conn_server(sc);
    #else
            process_conn_server_forFile(sc);
    #endif

            close(sc);
            exit(0);
        } else {
            close(sc);
        }
    }
}
