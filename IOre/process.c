/************************************************************************
 ****	> File Name:    	process.c
 ****	> Author:       	yiwen liu
 ****	> Mail:         	newiyuil@163.com
 ****	> Created Time: 	2018年04月04日 星期三 10时36分24秒
************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>

#define BUFSIZE 1024
void process_conn_server0(int s) {
    ssize_t size;
    char buf[BUFSIZE];

    for (;;) {
        size = recv(s, buf, BUFSIZE, 0);

        if (size < 0) {
            return;
        }
        sprintf(buf, "%ld bytes altogether\n", size);
        send(s, buf, strlen(buf) + 1, 0);
    }
}

void process_conn_client0(int s) {
    ssize_t size;
    char buf[BUFSIZE];

    for (;;) {
        size = read(0, buf, BUFSIZE);

        if (size > 0) {
            send(s, buf, size, 0);
            size = recv(s, buf, BUFSIZE, 0);
            write(1, buf, size);
        }
    }
}

void sig_process0(int signum) {
    printf("Catch a exit signal, value is %d\n", signum);
    _exit(0);
}

void sig_pipe0(int signum) {
    printf("Catch a SIGPIPE signal, value is %d\n", signum);
}

static struct iovec *vs = NULL, *vc = NULL;
void process_conn_server(int s) {
    char buf[30] = {};
    ssize_t size;

    struct iovec *v = (struct iovec*)malloc(3 * sizeof(struct iovec));
    if (!v) {
        fprintf(stderr, "malloc error\n");
        return;
    }

    vs = v;
    v[0].iov_base = buf;
    v[1].iov_base = buf + 10;
    v[2].iov_base = buf + 20;
    
    v[0].iov_len = v[1].iov_len = v[2].iov_len = 10;

    for (;;) {
        size = readv(s, v, 3);
        if (size < 0) {
            return;
        }

        sprintf((char *)v[0].iov_base, "%ld ", size);
        sprintf((char *)v[1].iov_base, "bytes alt");
        sprintf((char *)v[2].iov_base, "ogether\n");
        v[0].iov_len = strlen((char *)v[0].iov_base);
        v[1].iov_len = strlen((char *)v[1].iov_base);
        v[2].iov_len = strlen((char *)v[2].iov_base);
        writev(s, v, 3);
    }
}

void process_conn_client(int s) {
    char buf[30] = {};
    ssize_t size = 0;

    struct iovec *v = (struct iovec*)malloc(3 * sizeof(struct iovec));
    if (!v) {
        fprintf(stderr, "malloc error\n");
        return;
    }

    vc = v;

    v[0].iov_base = buf;
    v[1].iov_base = buf + 10;
    v[2].iov_base = buf + 20;
    v[0].iov_len = v[1].iov_len = v[2].iov_len = 10;

    int i = 0;
    for (;;) {
        size = read(0, v[0].iov_base, 10);
        if (size > 0) {
            v[0].iov_len = size;
            v[1].iov_len = v[2].iov_len = 0;
            writev(s, v, 1);
            v[0].iov_len = v[1].iov_len = v[2].iov_len = 10;
            size = readv(s, v, 3);

            for (i = 0; i < 3; ++i) {
                if (v[i].iov_len > 0) 
                write(1, v[i].iov_base, v[i].iov_len);
            }
        }
    }
}

void sig_process(int signum) {
    printf("Catch a exit signal, value is %d\n", signum);
    free(vc);
    free(vs);
    _exit(0);
}

void sig_pipe(int signum) {
    printf("Catch a SIGPIPE signal, value is %d\n", signum);
    free(vc);
    free(vs);
    _exit(0);
}

void process_conn_server_msg(int s) {
    char buf[30] = {};
    ssize_t size;
    struct msghdr msg;

    struct iovec *v = (struct iovec*)malloc(3 * sizeof(struct iovec));
    if (!v) {
        fprintf(stderr,"Not enough memory!\n");
        return ;
    }

    vs = v;
    msg.msg_name = NULL;
    msg.msg_namelen = 0;
    msg.msg_control = NULL;
    msg.msg_controllen = 0;
    msg.msg_iov = v;
    msg.msg_iovlen = 30;
    msg.msg_flags = 0;

    v[0].iov_base = buf;
    v[1].iov_base = buf + 10;
    v[2].iov_base = buf + 20;
    v[0].iov_len = v[1].iov_len = v[2].iov_len = 10;

    for (;;) {
        size = recvmsg(s, &msg, 0);
        if (size < 0) {
            perror("server end");
            return ;
        }

        snprintf((char *)v[0].iov_base, 10, "%ld ", size);
        snprintf((char *)v[1].iov_base, 10, "bytes alt");
        snprintf((char *)v[2].iov_base, 10, "ogether\n");

        v[0].iov_len = strlen((char *)v[0].iov_base);
        v[1].iov_len = strlen((char *)v[1].iov_base);
        v[2].iov_len = strlen((char *)v[2].iov_base);

        sendmsg(s, &msg, 0);
    }
}

void process_conn_client_msg(int s) {
    char buf[30] = {};
    ssize_t size;
    struct msghdr msg;

    struct iovec *v = (struct iovec*)malloc(3 * sizeof(struct iovec));
    if (!v) {
        fprintf(stderr, "malloc error\n");
        return ;
    }
    vc = v;

    msg.msg_name = NULL;
    msg.msg_namelen = 0;
    msg.msg_control = NULL;
    msg.msg_controllen = 0;
    msg.msg_iov = v;
    msg.msg_iovlen = 30;
    msg.msg_flags = 0;

    v[0].iov_base = buf;
    v[1].iov_base = buf + 10;
    v[2].iov_base = buf + 20;
    v[0].iov_len = v[1].iov_len = v[2].iov_len = 10;
    
    int i = 0;
    for (;;) {
        bzero(&buf, 30);
        size = read(0, v[0].iov_base, 10);
        if (size > 0) {
            v[0].iov_len = size;
            v[1].iov_len = v[2].iov_len = 0;
            sendmsg(s, &msg, 0);
            v[0].iov_len = v[1].iov_len = v[2].iov_len = 10;
            size = recvmsg(s, &msg, 0);
            for (i=0; i<3; ++i) {
                if (v[i].iov_len > 0) {
                    write(1, v[i].iov_base, v[i].iov_len);
                }
            }
        }
    }
}

