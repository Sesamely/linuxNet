/************************************************************************
 ****	> File Name:    	tcp_client.c
 ****	> Author:       	yiwen liu
 ****	> Mail:         	newiyuil@163.com
 ****	> Created Time: 	2018年04月03日 星期二 13时25分59秒
************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "./tcp_process.h"
#define PORT 8888
int main(int argc, char **argv)
{
    if (argc != 2) {
        printf("Usage: elf IP\n");
        return 0;
    }

    int s;
    struct sockaddr_in server_addr;

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
        fprintf(stderr, "socket error\n");
        exit(-1);
    }
    
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORT);

    inet_pton(AF_INET, argv[1], &server_addr.sin_addr);
    
    connect(s, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
#ifndef __FOR_FILE
    process_conn_client(s);
#else
    process_conn_client_forFile(s);
#endif

    close(s);

    return 0;
}

