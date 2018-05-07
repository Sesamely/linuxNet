/************************************************************************
 ****	> File Name:    	icmp_send.c
 ****	> Author:       	yiwen liu
 ****	> Mail:         	newiyuil@163.com
 ****	> Created Time: 	2018年04月24日 星期二 23时02分32秒
************************************************************************/

#include "./myping.h"

void *
icmp_send(void *argv)
{
    gettimeofday(&tv_begin, NULL);

    while (alive) {
        int size = 0;
        struct timeval tv;
        gettimeofday(&tv, NULL);

        pingm_packet *packet = icmp_findpacket(-1);
        if (packet) {
            packet->seq = packet_send;
            packet->flag = 1;
            gettimeofday(&packet->tv_begin, NULL);
        }

        icmp_pack((struct icmp *)send_buf, packet_send, &tv, 64);
        size = sendto(rawsock, send_buf, 64, 0,
                      (struct sockaddr *)&dest, sizeof(dest));

        if (size < 0) {
            perror("sendto error");
            continue;
        }
        packet_send++;
        sleep(1);
    }
    return NULL;
}

