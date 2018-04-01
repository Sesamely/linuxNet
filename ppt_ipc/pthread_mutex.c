/************************************************************************
 ****	> File Name:    	pthread_mutex.c
 ****	> Author:       	yiwen liu
 ****	> Mail:         	newiyuil@163.com
 ****	> Created Time: 	2018年04月01日 星期日 21时54分12秒
************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>
#include <sched.h>

int running = 1;
int buffer_has_item = 0;
pthread_mutex_t mutex;

void *producter_f(void *args) {
    while (running) {
        pthread_mutex_lock(&mutex);
        ++buffer_has_item;
        printf("生产，总数量：%d\n", buffer_has_item);
        pthread_mutex_unlock(&mutex);
    }
}

void *consumer_f(void *args) {
    while (running) {
        pthread_mutex_lock(&mutex);
        --buffer_has_item;
        printf("消费，总数量：%d\n", buffer_has_item);
        pthread_mutex_unlock(&mutex);
    }
}

int main()
{
    pthread_t consumer_t;
    pthread_t producter_t;

    pthread_mutex_init (&mutex, NULL);

    pthread_create(&producter_t, NULL, (void *)producter_f, NULL);
    pthread_create(&consumer_t, NULL, (void *)consumer_f, NULL);

    usleep(300); 
    running = 0; 
    pthread_join(producter_t, NULL);
    pthread_join(consumer_t, NULL);
    pthread_mutex_destroy(&mutex);

    return 0;
}

