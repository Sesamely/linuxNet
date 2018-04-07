/************************************************************************
 ****	> File Name:    	getsockopt.c
 ****	> Author:       	yiwen liu
 ****	> Mail:         	newiyuil@163.com
 ****	> Created Time: 	2018年04月07日 星期六 22时16分01秒
************************************************************************/

#include <netinet/tcp.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>

typedef union optval {
    int             val;
    struct linger   linger;
    struct timeval  tv;
    unsigned char   str[16];
}val;
static val optval;

typedef enum valtype {
    VALINT,
    VALLINGER,
    VALTIMEVAL,
    VALUCHAR,
    VALMAX
}valtype;

typedef struct sopts {
    int level;
    int optname;
    char *name;
    valtype valtype;
}sopts;

sopts sockopts[] = {
    {SOL_SOCKET,    SO_BROADCAST,   (char *)"SO_BROADCAST",      VALINT},
    {SOL_SOCKET,    SO_DEBUG,       (char *)"SO_DEBUF",          VALINT},
    {SOL_SOCKET,    SO_DONTROUTE,   (char *)"SO_DONTROUTE",      VALINT},
    {SOL_SOCKET,    SO_ERROR,       (char *)"SO_ERROR",          VALINT},
    {SOL_SOCKET,    SO_KEEPALIVE,   (char *)"SO_KEEPALIVE",      VALINT},
    {SOL_SOCKET,    SO_LINGER,      (char *)"SO_LINGER",         VALINT},
    {SOL_SOCKET,    SO_OOBINLINE,   (char *)"SO_OOBINLINE",      VALINT},
    {SOL_SOCKET,    SO_RCVBUF,      (char *)"SO_RCVBUF",         VALINT},
    {SOL_SOCKET,    SO_RCVLOWAT,    (char *)"SO_RCVLOWAT",       VALINT},
    {SOL_SOCKET,    SO_RCVTIMEO,    (char *)"SO_RCVTIMEO",       VALTIMEVAL},
    {SOL_SOCKET,    SO_SNDTIMEO,    (char *)"SO_SNDTIMEO",       VALTIMEVAL},
    {SOL_SOCKET,    SO_TYPE,        (char *)"SO_TYPE",           VALINT},
    {IPPROTO_IP,    IP_HDRINCL,     (char *)"IP_HDRINCL",        VALINT},
    {IPPROTO_IP,    IP_OPTIONS,     (char *)"IP_OPTIONS",        VALINT},
    {IPPROTO_IP,    IP_TOS,         (char *)"IP_TOS",            VALINT},
    {IPPROTO_IP,    IP_TTL,         (char *)"IP_TTL",            VALINT},
    {IPPROTO_IP,    IP_MULTICAST_TTL,    (char *)"IP_MULTICAST_TTL",       VALUCHAR},
    {IPPROTO_TCP,   IP_MULTICAST_LOOP,   (char *)"IP_MULTICAST_LOOP",      VALUCHAR},
    {IPPROTO_TCP,   TCP_KEEPCNT,         (char *)"TCP_KEEPCNT",            VALINT},
    {IPPROTO_TCP,   TCP_MAXSEG,          (char *)"TCP_MAXSEG",             VALINT},
    {IPPROTO_TCP,   TCP_NODELAY,         (char *)"TCP_NODELAY",            VALINT},
    {0,          0,         NULL,     VALMAX}
};

static void disp_outcome(sopts *sockopt, int len, int err)
{
    if (err == -1) {
        printf("optname %s NOT support\n", sockopt->name);
        return ;
    }

    switch ((int)sockopt->valtype) {
        case VALINT:
            printf("optname %s: defalut is %d\n", sockopt->name, optval.val); break;
        case VALLINGER:/*struct linger*/
            printf("optname %s: defalut is %d(ON/OFF), %d to linger\n",
                  sockopt->name,
                  optval.linger.l_onoff,
                  optval.linger.l_linger); break;
        case VALTIMEVAL:
            printf("optname %s: default is %.06f\n",
                  sockopt->name,
                  (((double)optval.tv.tv_sec*100000 + (double)optval.tv.tv_usec)) /
                    (double)1000000); break;
        case VALUCHAR:
        {
            int i = 0;
            printf("optname %s: default is ", sockopt->name);
            for (i=0; i<len; ++i) {
                printf("%02x ", optval.str[i]);
            }
            printf("\n");
        } break;
        default: break;
    }
}

int main()
{
    int err;
    socklen_t len = 0;
    int i = 0,
        s = socket(AF_INET, SOCK_STREAM, 0);

    while (sockopts[i].valtype != VALMAX) {
        len = sizeof(sopts);
        err = getsockopt(s, sockopts->level, sockopts->optname, &optval, &len);

        disp_outcome(&sockopts[i], len, err);
        ++i;
    }
    close(s);

    return 0;
}
