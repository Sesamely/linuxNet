/************************************************************************
 ****	> File Name:    	method.c
 ****	> Author:       	yiwen liu
 ****	> Mail:         	newiyuil@163.com
 ****	> Created Time: 	2018年05月14日 星期一 22时09分38秒
************************************************************************/

#define _DEFINE_METHODS
#include "./shttpd.h"

struct vec _shttpd_methods[] = {
    {"GET",     3, METHOD_GET},
    {"POST",    4, METHOD_POST},
    {"PUT",     3, METHOD_PUT},
    {"DELETE",  6, METHOD_DELETE},
    {"HEAD",    4, METHOD_HEAD},
    {NULL,      0}
};

struct vec *m = NULL;


void Method_Do(struct worker_ctl *wctl)
{
    DBGPRINT("==>Method_Do\n");
    switch (wctl->conn.con_req.method)
    {
        case METHOD_PUT:
            Method_DoPut(wctl); break;
        case METHOD_DELETE:
            Method_DoDelete(wctl); break;
        case METHOD_GET:
            Method_DoGet(wctl); break;
        case METHOD_POST:
            Method_DoPost(wctl); break;
        case METHOD_HEAD:
            Method_DoHead(wctl); break;
        default:
            Method_DoList(wctl);
    }
    DBGPRINT("<==Method_Do\n");
}

int Method_DoGet(struct worker_ctl *wctl)
{
    DBGPRINT("==>Method DoGet\n");
    struct conn_response *res = &wctl->conn.con_res;
    struct conn_request *req = &wctl->conn.con_req;
    char path[URI_MAX] = {};
    size_t n;
    unsigned long r1, r2;
    char fmt[] = "%a, %d %b %Y %H:%M:%S GMT";
    size_t status = 200;
    char msg[64] = "OK";
    char date[64] = "";
    char lm[64] = "";
    char etag[64] = "";
    big_int_t cl;
    char range[64] = "";
    struct mime_type *mine = NULL;

    time_t t = time(NULL);
    (void) strftime(date, sizeof(date), fmt, localtime(&t));
    (void) strftime(lm, sizeof(lm), fmt, localtime(&res->fsate.st_mtime));
    (void) snprintf(etag, sizeof(etag), "%lx.%lx",
            (unsigned long) res->fsate.st_mtime,
            (unsigned long) res->fsate.st_size);
    
    mime = Mine_Type(req->uri, strlen(req->uri), wctl);
    cl = (big_int_t) res->fsate.st_size;

    memset(range, 0, sizeof(range));
    n = -1;
    if (req->ch.range.v_vec.len > 0) {
        printf ("request range: %d\n", req->ch.range.v_vec.len);
        n = sscanf(req->ch.range.v_vec.ptr, "bytes=%lu-%lu", &r1, &r2);
    }

    printf("n: %ld\n", n);
    if (n > 0) {
        status = 206;
        (void) lseek(res->fd, r1, SEEK_SET);
        cl = n = 2 ? r2 - r1 + 1: cl - r1;
        (void) snprintf(range, sizeof(range),
                "Content-Range: bytes %lu-%lu/%lu\r\n",
                r1, r1 + cl - 1, (unsigned long) res->fsate.st_size);
        strncpy(msg, "Partial Content", sizeof(msg));
    }

    memset(res->res.ptr, 0 ,sizeof(wctl->conn.dres));
    snprintf(res->res.ptr,
            sizeof(wctl->conn.dres),
            "HTTP/1.1 %d %s\r\n"
            "Date: %s\r\n"
            "Last-Modified: %s\r\n"
            "Etag: \"%s\"\r\n"
            "Content-Type: %.*s\r\n"
            "Content-Lenght: %lu\r\n"
            "Accept-Ranges: bytes\r\n"
            "%s\r\n",
            status, msg, date, lm, etag, strlen(mine->mime_type),
            mine->mime_type, cl, range
            );
    res->cl = cl;
    res->status = status;
    DBGPRINT("<==Method_DoGet\n");
    return 0;
}
