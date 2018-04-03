/************************************************************************
 ****	> File Name:    	tcp_process.c
 ****	> Author:       	yiwen liu
 ****	> Mail:         	newiyuil@163.com
 ****	> Created Time: 	2018年04月03日 星期二 13时18分26秒
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#define BUF_SIZE 1024

void process_conn_server(int s) {
    ssize_t size = 0;
    char buf[BUF_SIZE];

    for (;;) {
        size = read(s, buf, BUF_SIZE);

        if (size < 0) {
            return;
        }

        sprintf(buf, "%ld bytes altogether\n", size);
        write(s, buf, strlen(buf) + 1);
    }
}

void process_conn_client(int s) {
    ssize_t size;
    char buf[BUF_SIZE];

    for (;;) {
        size = read(0, buf, BUF_SIZE);
        if (size > 0) {
            write(s, buf, size);
            size = read(s, buf, BUF_SIZE);
            write(1, buf, size);
        }
    }
}

void getline_from_stdin(char *buf, ssize_t max_size) {
    --max_size;
    int i = 0;
    char cur_char;
    for (; (cur_char=getchar())!=EOF && i<max_size; ++i) {
        if (cur_char == '\n') break;
        *buf++ = cur_char;
    }
    *buf = '\0';
}

void process_conn_client_forFile(int s) {
    ssize_t size;
    char buf[BUF_SIZE];

    getline_from_stdin(buf, BUF_SIZE);
    size = strlen(buf);
    if (size > 255) {
        fprintf(stderr, "too long filename\n");
        exit(EXIT_FAILURE);
    }

    size = write(s, buf, size+1);
    if (size == -1) {
        fprintf(stderr, "client send filename error\n");
        return;
    }

    int fd = open("client_recv/recv_file", O_CREAT | O_WRONLY | O_TRUNC, 00600);
    if (fd == -1) {
        fprintf(stderr, "client open file error!\n");
        return;
    }

    for (;;) {
        size = read(s, buf, BUF_SIZE);
        if (write(fd, buf, size) < 0) {
            fprintf(stderr, "client write file error!\n");
            return;
        }

        if (size != BUF_SIZE) {
            /*printf("client recv end\n");*/
            break;
        }
    }
}

void process_conn_server_forFile(int s) {
    char buf[BUF_SIZE];
    ssize_t size;

    if( (size = read(s, buf, BUF_SIZE)) == -1) {
        fprintf(stderr, "server read sock error\n");
        return;
    }

    int fd = open(buf, O_RDONLY);
    if (fd < 0) {
        fprintf(stderr, "server open file error\n");
        return;
    }

    for (;;) {
        size = read(fd, buf, BUF_SIZE);
        if (write(s, buf, size) < 0) {
            fprintf(stderr, "server write file error\n");
            close(fd);
            return;
        }
        /*printf("server read filename size is %ld\n", size);*/
        if (size != BUF_SIZE) {
            /*printf("server send all\n");*/
            break;
        }
    }
    /*printf("OK\n");*/
    close(fd);

}
