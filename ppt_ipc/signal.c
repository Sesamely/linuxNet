/************************************************************************
 ****	> File Name:    	signal.c
 ****	> Author:       	yiwen liu
 ****	> Mail:         	newiyuil@163.com
 ****	> Created Time: 	2018年04月01日 星期日 20时30分51秒
************************************************************************/

#include <stdio.h>
#include <signal.h>
#include <error.h>

typedef void (*sighandler_t)(int);

static void SIGKIL_HANDLER(int signo) {
    if (signo == SIGKILL) {
        printf("get signal kill\n");
    } else {
        printf("get signal %d\n", signo);
    }
}

int main()
{
    sighandler_t ret;
    ret = signal(SIGSTOP, SIGKIL_HANDLER);
    if (ret == SIG_ERR) {
        fprintf(stderr, "mount SIGSTOP handler error\t");
        perror("cause");
        return -1;
    }

    raise(SIGKILL);

    return 0;
}

