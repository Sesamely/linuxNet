/************************************************************************
 ****	> File Name:    	support_cgi.c
 ****	> Author:       	yiwen liu
 ****	> Mail:         	newiyuil@163.com
 ****	> Created Time: 	2018年05月14日 星期一 23时16分46秒
************************************************************************/

#include "./shttpd.h"
#define CGISTR "/cgi-bin/"
#define ARGNUM 16
#define READIN 0
#define WRITEOUT 1

int cigHandler(struct worker_ctl *wctl)
{
    struct conn_request *req = &wctl->conn.con_req;
    struct conn_response *res = &wctl->conn.con_res;
    char *command = strstr(req->uri, CGISTR) + strlen(CGISTR);

    char *arg[ARGNUM];
    int num = 0;
    char *rpath = wctl->conn.con_req.rpath;
    struct stat *fs = &wctl->conn.con_res.fsate;
    int retval = -1;

    char *pos = command;
    for (; *pos!='?' && *pos!='\0'; pos++);
    *pos = '\0';
    sprintf(rpath, "%s%s",conf_para.CGIRoot, command);

    pos++;
    for (; *pos!='\0' && num < ARGNUM; ) {
        arg[num] = pos;
        for (; *pos != '+' && *pos != '\0'; pos++);

        if (*pos == '+') {
            *pos = '\0';
            pos++;
            num++;
        }
    }
    arg[num] = NULL;

    if (stat(rpath, fs) < 0) {
        res->status = 403;
        retval = -1;
        goto EXIT_cigHandler;
    } else if ((fs->st_mode & S_IFDIR) == S_IFDIR) {
        /*目录*/
    } else if ((fs->st_mode & S_IXUSR) != S_IXUSR) {
        res->status = 403;
        retval = -1;
        goto EXIT_cigHandler;
    }

    int pipe_in[2];
    int pipe_out[2];
    if (pipe(pipe_in) < 0) {
        res->status = 500;
        retval = -1;
        goto EXIT_cigHandler;
    }
    if (pipe(pipe_out) < 0) {
        res->status = 500;
        retval = -1;
        goto EXIT_cigHandler;
    }

    int pid = 0;
    if ((pid = fork()) < 0) {
        res->status = 500;
        retval = -1;
        goto EXIT_cigHandler;
    } else if (pid > 0) {
        close(pipe_out[WRITEOUT]);
        close(pipe_in[READIN]);
        int size = 0;
        int end = 0;
        while (size == 0 && !end) {
            size = read(pipe_out[READIN], res->res.ptr,
                        sizeof(wctl->conn.dres));
            if (size > 0) {
                send(wctl->conn.cs, res->res.ptr, strlen(res->res.ptr));
            }
            else {
                end = 1;
            }
        }
        wait();
        close(pipe_out[READIN]);
        close(pipe_in[WRITEOUT]);
        retval = 0;
    } else {
        char cmdarg[2048];
        char onearg[2048];
        char *pos = NULL;
        int i = 0;
        memset(onearg, 0, 2048);
        for (i=0; i<num; ++i) {
            sprintf(cmdarg, "%s %s", onearg, arg[i]);
        }
    }

EXIT_cigHandler:
    return retval;
}
