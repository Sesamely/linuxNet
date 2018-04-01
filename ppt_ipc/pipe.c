/************************************************************************
****	> File Name:    	pipe.c
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	2018年03月30日 星期五 00时30分42秒
************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

void pipe1()
{
    int result,
        fd[2], 
        nbytes;
    
    pid_t pid;
    int *write_fd = &fd[1],
        *read_fd  = &fd[0];

    if ( (result = pipe(fd)) < 0 ) {
        fprintf(stderr, "Create pipe error!\n");
        return ;
    }

    pid = fork();
    if (pid == -1) {
        fprintf(stderr, "fort error!\n");
    } else if (pid == 0) {
        char string[80] = "Hello world!";
        /*read(0, string, 80); // no real know*/

        printf ("I am child, write %ld bytes data\n", write(*write_fd, string, 0));
        printf ("I am child, write %ld bytes data", write(*write_fd, string, 1));
        /*
         *if ( write(*write_fd, string, strlen(string)+1) < 0) {
         *    fprintf(stderr, "I am child pid is %d, write error!\n", getpid());
         *    exit(-1);
         *}
         */
        exit(0);
    } else {
        char readbuf[80] = {};
        if ( (nbytes = read(*read_fd, readbuf, sizeof(readbuf))) < 0 ) {
            fprintf(stderr, "I am father pid is %d, read error!\n", getpid());
        } else {
            printf("I am father, get %d bytes data from child\n content is\t %s\n",
                   nbytes, readbuf);
        }
    }
}

#define K 1024
#define WRITELEN (256 * K)

void pipe2()
{
    int result, fd[2], nbytes,
        *write_fd = &fd[1],
        *read_fd  = &fd[0];

    pid_t pid;

    if ( (result = pipe(fd)) < 0 ) {
        fprintf(stderr, "Create pipe error!\n");
        return;
    }
    pid = fork();
    if (pid == -1) {
        fprintf(stderr, "fort error!\n");
    } else if (pid == 0) {

        int write_size = WRITELEN;
        char string[WRITELEN] = "你好，管道";

        while ( write_size >= 0 ) 
        {
            result = write(*write_fd, string, write_size);

            if (result > 0) {
                write_size -= result;
                printf("写入%d数据，剩余%d数据\n", result, write_size);
                if (write_size == 0) {
                    break;
                }
            } else {
                sleep(10);
            }
        }

        printf("I am child, pid is %d, bye~\n", getpid());
        exit(0);

    } else {
        sleep(10);

        char readbuf[10 * K] = {};

        while (0) {
            nbytes = read(*read_fd, readbuf, 10 * K);

            if (nbytes < 0) {
                printf("no data writed in\n");
                break;
            }

            printf("recive %d data\t content is \"%s\"\n", nbytes, readbuf);

        }

        close(fd[0]);
        close(fd[1]);
    }
}


int main()
{
    pipe2();

    return 0;
}
