/************************************************************************
 ****	> File Name:    	addrT.c
 ****	> Author:       	yiwen liu
 ****	> Mail:         	newiyuil@163.com
 ****	> Created Time: 	2018年04月04日 星期三 00时31分18秒
************************************************************************/

#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
    struct in_addr ip, local, network;
    char addr1[] = "192.168.1.1";
    char addr2[] = "255.255.255.255";
    char addr3[] = "192.16.1";
    char *str1=NULL,
         *str2=NULL;

    int err = 0;

    err = inet_aton(addr1, &ip);
    if (err) {
        printf("inet_aton:string %s value is:0x%x\n", addr1, ip.s_addr);
    } else {
        printf("inet_aton:string %s error\n",addr1);
    }

    ip.s_addr = inet_addr(addr1);
    if (err != -1) {
        printf("inet_addr:string %s value is: 0x%x\n",addr1, ip.s_addr);
    } else {
        printf("inet_addr:string %s error\n",addr1);
    }

    ip.s_addr = inet_addr(addr2);
    if (err != -1) {
        printf("inet_addr:string %s value is: 0x%x\n",addr2, ip.s_addr);
    } else {
        printf("inet_addr:string %s error\n",addr2);
    }

    ip.s_addr = 192<<24 | 168<<16 | 1<<8 | 1;
    str1 = inet_ntoa(ip);
    ip.s_addr = 255<<24 | 255<<16 | 255<<8 | 255;
    str2 = inet_ntoa(ip);
    printf("inet_ntoa:0x%x string1 %s, pre is %s\n", ip.s_addr, str2, str1);

    ip.s_addr = inet_addr(addr3);
    if (err != -1) {
        printf("inet_addr:string %s value is:0x%x\n", addr3, ip.s_addr);
    } else {
        printf("inet_addr:string %s error\n", addr3);
    }

    inet_aton(addr1, &ip);
    local.s_addr = htonl(ip.s_addr);
    local.s_addr = inet_lnaof(ip);
    str1 = inet_ntoa(local);
    printf("inet_lnaof:string %s ip:0x%x \n", str1, local.s_addr);

    network.s_addr = inet_netof(ip);
    printf("inet_netof: value:0x%x \n", network.s_addr);

    return 0;
}
