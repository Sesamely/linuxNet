/************************************************************************
 ****	> File Name:    	client_framework.c
 ****	> Author:       	yiwen liu
 ****	> Mail:         	newiyuil@163.com
 ****	> Created Time: 	2018年04月04日 星期三 10时06分08秒
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <strings.h>
#include <sys/socket.h>
#include <signal.h>
#include <netinet/in.h>
#include <arpa/inet.h>

extern void sig_process(int signum);
extern void sig_pipe(int signum);
static int s;
void sig_process_client(int signum) {
    printf("Catch a exit signal, value %d\n", signum);
    close(s);
    exit(0);
}

#define PORT 8888
int main(int argc, char **argv) 
{
    if (argc != 2) {
        fprintf(stderr, "Usage: elf IP\n");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr;

    signal(SIGINT, sig_process);
    signal(SIGPIPE, sig_pipe);

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
        fprintf(stderr, "socket error\n");
        exit(EXIT_FAILURE);
    }

    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    server_addr.sin_port = htons(PORT);

    inet_pton(AF_INET, argv[1], &server_addr.sin_addr);

    connect(s, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));

    /*process_conn_client(s);*/
    process_conn_client_msg(s);
    
    close(s);

    return 0;
}
