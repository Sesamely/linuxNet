/************************************************************************
 ****	> File Name:    	inet_p.c
 ****	> Author:       	yiwen liu
 ****	> Mail:         	newiyuil@163.com
 ****	> Created Time: 	2018年04月04日 星期三 09时44分09秒
************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define ADDRLEN 16

int main()
{
    struct in_addr ip;
    char IPSTR[] = "192.168.1.1";
    char addr[ADDRLEN];
    const char *str = NULL;
    int err;

    err = inet_pton(AF_INET, IPSTR, &ip);
    if (err > 0) {
        printf("inet_pton:ip, %s value is: 0x%x\n",
               IPSTR, ip.s_addr);
    }

    ip.s_addr = htonl(192<<24|168<<16|1<<8|1);
    str = (const char *)inet_ntop(AF_INET, (void *)&ip, (char *)&addr[0], ADDRLEN);
    if (str) {
        printf("inet_ntop:ip, 0x%x is %s\n", ip.s_addr, str);
    }

    return 0;
}
