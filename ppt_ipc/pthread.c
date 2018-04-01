/************************************************************************
 ****	> File Name:    	pthread.c
 ****	> Author:       	yiwen liu
 ****	> Mail:         	newiyuil@163.com
 ****	> Created Time: 	2018年04月01日 星期日 20时51分58秒
************************************************************************/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

static int run = 1;
static int retvalue ;

void *start_routine(void *arg)
{
    int *running = (int *)arg;
    printf("子线程初始化完毕，传入参数为：%d\n", *running);
    while (*running) {
        printf("子线程正在运行\n");
        usleep(1);
    }
    printf("子线程退出\n");

    retvalue = 8;
    pthread_exit( (void *)&retvalue );
}

int main()
{
    pthread_t pt;
    int ret = -1;
    int times = 10;

    int i =0;
    int *ret_join = NULL;

    ret = pthread_create(&pt, NULL, (void *)start_routine, &run);

    if (ret != 0) {
        printf("线程建立失败\n");
        return -1;
    }
    usleep(1);
    for (; i<times; ++i) {
        printf("主线程打印\n");
        usleep(1);
    }

    run = 0;

    pthread_join(pt, (void *)&ret_join);
    printf("线程返回值是:%d\n", *ret_join);

    return 0;
}
