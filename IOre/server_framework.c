/************************************************************************
 ****	> File Name:    	server_framework.c
 ****	> Author:       	yiwen liu
 ****	> Mail:         	newiyuil@163.com
 ****	> Created Time: 	2018年04月04日 星期三 10时19分13秒
************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <signal.h>

extern void sig_process(int signum);
#define PORT 8888
#define BACKLOG 2

int main()
{
    int ss, sc;
    struct sockaddr_in server_addr,
                        client_addr;
    int err;
    pid_t pid;

    signal(SIGINT, sig_process);
    signal(SIGPIPE, sig_process);
    signal(SIGCHLD, SIG_IGN);

    ss = socket(AF_INET, SOCK_STREAM, 0);
    if(ss < 0) {
        fprintf(stderr, "server socket error\n");
        exit(EXIT_FAILURE);
    }

    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    err = bind(ss, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (err < 0) {
        fprintf(stderr, "bind error\n");
        exit(EXIT_FAILURE);
    }

    err = listen(ss, BACKLOG);
    if (err < 0) {
        fprintf(stderr, "listen error\n");
        exit(EXIT_FAILURE);
    }

    for (;;) {
        socklen_t addrlen = sizeof(struct sockaddr);

        sc = accept(ss, (struct sockaddr*)&client_addr, &addrlen);
        if (sc < 0) {
            continue;
        }

        pid = fork();
        if (pid == -1) {
            fprintf(stderr, "fork error\n");
            close(sc);
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            close (ss);
            /*process_conn_server(sc);*/
            process_conn_server_msg(sc);
            close(sc);
            exit(EXIT_FAILURE);
        } else {
            close(sc);
        }
    }
}
