/************************************************************************
 ****	> File Name:    	shm.c
 ****	> Author:       	yiwen liu
 ****	> Mail:         	newiyuil@163.com
 ****	> Created Time: 	2018年03月30日 星期五 18时48分57秒
************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include "./semaphore.c"

static char msg[] = "你好，共享内存";

int main()
{
    key_t key;
    int semid, shmid;
    char /* i,*/
        *shms, *shmc;

/*
 *    struct semid_ds buf;
 *
 *    int value;
 *    char buffer[80];
 */
    pid_t p;

    key = ftok("./", 'a');
    shmid = shmget(key, 1024, IPC_CREAT | 00604);

    semid = CreateSem(key, 0);

    p = fork();
    if (p == -1) {
        fprintf(stderr, "fork error!\n");
        return -1;
    } else if (p == 0) {

        shms = (char *)shmat(shmid, 0, 0);    
        memcpy(shms, msg, strlen(msg) + 1);

        Sem_P(semid);

        while (GetvalueSem(semid) != 0) {
            printf("@");
        }

        shmdt(shms);

        /*printf("%d\n", GetvalueSem(semid));*/
        Sem_P(semid);
        /*printf("%d\n", GetvalueSem(semid));*/

    } else {
        while (GetvalueSem(semid) == 0) {
            printf(".");
        }

        shmc = (char *)shmat(shmid, 0, 0);
        printf("共享内存的值为:%s\n", shmc);
        shmdt(shmc);
        Sem_V(semid);
        while (GetvalueSem(semid) == 0) {
            printf("!");
        }
        printf("end parent\n");
        DestroySem(semid);
    }

    return 0;
}

