/************************************************************************
 ****	> File Name:    	udp_client.c
 ****	> Author:       	yiwen liu
 ****	> Mail:         	newiyuil@163.com
 ****	> Created Time: 	2018年04月04日 星期三 14时08分05秒
************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>

#define PORT_SERV 8888

void udpclie_echo(int s, struct sockaddr *serv);
int main()
{
    int s;
    struct sockaddr_in addr_serv;

    s = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&addr_serv, 0, sizeof(addr_serv));
    addr_serv.sin_addr.s_addr = htonl(INADDR_ANY);
    addr_serv.sin_family = AF_INET;
    addr_serv.sin_port = htons(PORT_SERV);

    udpclie_echo(s, (struct sockaddr*)&addr_serv);

    close(s);
    return 0;
}

#define BUFF_LEN 256
void udpclie_echo(int s, struct sockaddr *serv) {
    char buff[BUFF_LEN] = "UPD TEST";

    struct sockaddr_in from;
    socklen_t len = sizeof(*serv);
    sendto(s, buff, BUFF_LEN, 0, serv, len);
    recvfrom(s, buff, BUFF_LEN, 0, (struct sockaddr*)&from, &len);

    printf("recved: %s\n", buff);
}
