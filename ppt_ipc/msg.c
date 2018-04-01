/************************************************************************
 ****	> File Name:    	msg.c
 ****	> Author:       	yiwen liu
 ****	> Mail:         	newiyuil@163.com
 ****	> Created Time: 	2018年03月30日 星期五 15时24分55秒
************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>

void msg_show_attr(int msg_id, struct msqid_ds msg_info)
{
    int ret;
    sleep(1);

    ret = msgctl(msg_id, IPC_STAT, &msg_info);
    if (ret == -1) {
        fprintf(stderr, "get msg info error!\n");
        perror("cause");
        return;
    }

    printf("\n/*******************************************************");
    printf("msgid_ds info disp follow:\n");
    printf("cur queue byte count is: %ld\n", msg_info.msg_qbytes);
    printf("queue msg count is: %lu\n", msg_info.msg_qnum);
    printf("queue max byte count is: %lu\n", msg_info.msg_qbytes);
    printf("last send pid is: %d\n", msg_info.msg_lspid);
    printf("last receive pid is: %d\n", msg_info.msg_lrpid);
    printf("last get msg time is: %s\n", ctime(&(msg_info.msg_rtime)));
    printf("last receive msg time is: %s\n", ctime(&(msg_info.msg_rtime)));
    printf("msg UID is: %d\n", msg_info.msg_perm.uid);
    printf("msg GID is: %d\n", msg_info.msg_perm.gid);
    printf("*******************************************************/\n");

}

int main()
{
    int ret;
    int msg_flags, msg_id;

    key_t key;

    struct msgmbuf {
        long mtype;
        char mtext[10];
    };

    struct msqid_ds msg_info;
    struct msgmbuf msg_mbuf;

    int msg_sflags, msg_rflags;
    char msgpath[] = "./";

    key = ftok(msgpath, 'a');
    if (key == -1) {
        fprintf(stderr, "create key error!\n");
        return -1;
    }

    msg_flags = IPC_CREAT ;
    msg_id = msgget(key, msg_flags | 00666);
    if (msg_id == -1) {
        fprintf(stderr, "create msg_id error!\t");
        fprintf(stderr, "errno is: %s\n", strerror(errno));
        /*perror("error");*/
        return -1;
    }

    msg_show_attr(msg_id, msg_info);

    msg_sflags = IPC_NOWAIT;
    msg_mbuf.mtype = 10;
    memcpy(msg_mbuf.mtext, "test data", strlen("test data")+1);
    /*printf("mtype is: %d\n", msg_mbuf.mtype);*/
    ret = msgsnd(msg_id, &msg_mbuf, sizeof("test data"), msg_sflags);
    if (ret == -1) {
        fprintf(stderr, "msgsnd error!\n");
        return -1;
    }
    msg_show_attr(msg_id, msg_info);

    msg_rflags = IPC_NOWAIT | MSG_NOERROR;
    /*msg_rflags = MSG_NOERROR;*/
    ret = msgrcv(msg_id, &msg_mbuf, 10, 10, msg_rflags);
    if (ret == -1) {
        fprintf(stderr, "msgrcv error!\n");
        return -1;
    } else {
        printf("receive bytes count is: %d\n", ret);
    }
    msg_show_attr(msg_id, msg_info);

    msg_info.msg_perm.uid = 8;
    msg_info.msg_perm.gid = 8;
    msg_info.msg_qbytes = 12345;
    ret = msgctl(msg_id, IPC_SET, &msg_info);
    if (ret == -1) {
        fprintf(stderr, "msgctl error!\n");
        return -1;
    }
    msg_show_attr(msg_id, msg_info);

    ret = msgctl(msg_id, IPC_RMID, NULL);
    if (ret == -1) {
        fprintf(stderr, "delete msg_id error!\n");
        return -1;
    }

    return 0;
}
