/************************************************************************
 ****	> File Name:    	shttpd.h
 ****	> Author:       	yiwen liu
 ****	> Mail:         	newiyuil@163.com
 ****	> Created Time: 	2018年05月14日 星期一 19时46分14秒
************************************************************************/

#ifndef _SHTTPD_H
#define _SHTTPD_H

#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <time.h>

typedef struct vec {
    char        *ptr;  //C string
    int         len;    //C string len
    SHTTPD_METHOD_TYPE type; //type
}vec;

struct conf_opts {
    char    CGIRoot[128];
    char    DefaultFile[128];
    char    DocumentRoot[128];
    char    ConfigFile[128];
    int     ListenPort;
    int     MaxClient;
    int     TimeOut;
    int     InitClient;
};

struct worker_opts {
    pthread_t th;
    int flags;
    pthread_mutex_t mutex;
    struct worket_ctl *work;
};

struct headers {
    union variant   cl;
    union variant   ct;
}

struct conn_response {
    struct vec res;
    time_t birth_time;
    time_t expire_time;
    int status;
    int cl;
    int fd;
    struct stat fsate;
    struct worker_conn *conn;
};

struct conn_request {
    struct vec  req;
    char *head;
    char *uri;
    char rpath[URI_MAX];
    int method;

    unsigned long major;
    unsigned long minor;
    struct headers ch;
    struct worker_conn *conn;
    int err;
};

struct worker_conn {
#define K 1024
    char    dreq[16*K];
    char    dres[16*K];
    int     cs;
    int     to;
    struct conn_response con_res;
    struct conn_request con_req;
    struct worker_ctl *work;
};

struct worker_ctl {
    struct worker_opts opts;
    struct worker_conn conn;
};

#ifndef _DEFINE_CONF_PARA
    extern struct conf_opts conf_para;
#endif
#ifndef _DEFINE_METHOD
    extern struct vec _shttpd_methods;
#endif

void display_usage();
void display_conf();
int CmdParse(int, char **);
size_t conf_readline(int, char *, int);

#endif
