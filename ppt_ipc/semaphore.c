/************************************************************************
 ****	> File Name:    	semaphore.c
 ****	> Author:       	yiwen liu
 ****	> Mail:         	newiyuil@163.com
 ****	> Created Time: 	2018年03月30日 星期五 17时35分31秒
************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <sys/sem.h>
#include <sys/ipc.h>

typedef int sem_t;
union semun {
    int    val;
    struct semid_ds *buf;
    unsigned short *array;
};

sem_t CreateSem(key_t key, int value)
{
    union semun sem;
    sem_t semid;
    sem.val = value;

    /*printf("key value is: %d\n", key);*/
    semid = semget(key, 1, IPC_CREAT | 0666);
    if (semid == -1) {
        fprintf(stderr, "create semaphore error\t");
        perror("cause");
        return -1;
    }

    semctl(semid, 0, SETVAL, sem);

    return semid;
}

int Sem_P(sem_t semid) {
    struct sembuf sops = {0, +1, IPC_NOWAIT};

    return (semop(semid, &sops, 1));
}

int Sem_V(sem_t semid) {
    struct sembuf sops = {0, -1, IPC_NOWAIT};

    return (semop(semid, &sops, 1));
}

void SetvalueSem(sem_t semid, int value) {
    union semun sem;
    sem.val = value;

    semctl(semid, 0, SETVAL, sem);
}

int GetvalueSem(sem_t semid) {
    union semun sem;

    return (semctl(semid, 0, GETVAL, sem));
}

void DestroySem(sem_t semid) {
    union semun sem;
    sem.val = 0;

    semctl(semid, 0, IPC_RMID, sem);
}

int main_NO_USE()
{
    key_t key;
    int semid;
    int value = 0;

    key = ftok("/ipc/semaphore/", 'b');
    if (key < 0) {
        perror("Create key error\t cause");
        return -1;
    }

    semid = CreateSem(key, 100);

    for (int i=0; i<3; ++i) {
        Sem_P(semid);
        Sem_V(semid);
    }
    value = GetvalueSem(semid);
    printf("Semaphore value is: %d\n", value);

    DestroySem(semid);

    return 0;
}
