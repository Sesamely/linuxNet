/************************************************************************
 ****	> File Name:    	udp_server.c
 ****	> Author:       	yiwen liu
 ****	> Mail:         	newiyuil@163.com
 ****	> Created Time: 	2018年04月04日 星期三 13时59分24秒
************************************************************************/

#include <sys/types.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT_SERV 8888

void udpserv_echo(int s, struct sockaddr *clie);
int main()
{
    int s;
    struct sockaddr_in addr_serv, addr_clie;

    s = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&addr_serv, 0, sizeof(addr_serv));
    addr_serv.sin_addr.s_addr = htonl(INADDR_ANY);
    addr_serv.sin_family = AF_INET;
    addr_serv.sin_port = htons(PORT_SERV);

    bind(s, (struct sockaddr*)&addr_serv, sizeof(addr_serv));

    udpserv_echo(s, (struct sockaddr*)&addr_clie);
    
    return 0;
}

#define BUFF_LEN 256
void udpserv_echo(int s, struct sockaddr *clie) {
    int n;
    char buff[BUFF_LEN];
    socklen_t len;

    for (;;) {
        len = sizeof(*clie);
        n = recvfrom(s , buff, BUFF_LEN, 0, clie, &len);
        sendto(s, buff, n, 0, clie, len);
    }
}
