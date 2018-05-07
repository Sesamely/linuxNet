/************************************************************************
 ****	> File Name:    	icmp_unpack.c
 ****	> Author:       	yiwen liu
 ****	> Mail:         	newiyuil@163.com
 ****	> Created Time: 	2018年04月24日 星期二 17时05分42秒
************************************************************************/

#include "./myping.h"

int 
icmp_unpack(char *buf, int len)
{
    int iphdrlen;
    struct ip *ip = NULL;
    struct icmp *icmp = NULL;
    int rtt;

    ip = (struct ip *)buf;
    iphdrlen = ip->ip_hl * 4;
    icmp=(struct icmp *)(buf + iphdrlen);
    len -= iphdrlen;

    if (len < 8) {
        fprintf(stderr, "ICMP packet's length is less than 8\n");
        return -1;
    }

    if ( (icmp->icmp_type == ICMP_ECHOREPLY) && (icmp->icmp_id == pid) ) {
        struct timeval tv_internel, tv_recv, tv_send;

        pingm_packet *packet = icmp_findpacket(icmp->icmp_seq);
        if (packet == NULL)
            return -1;
        packet->flag = 0;
        tv_send = packet->tv_begin;

        gettimeofday(&tv_recv, NULL);
        tv_internel = icmp_tvsub(tv_recv, tv_send);
        rtt = tv_internel.tv_sec*1000 + tv_internel.tv_usec/1000;


        printf("%d byte from %s: icmp_seq=%u ttl=%d rtt=%d ms\n",
              len,
              inet_ntoa(ip->ip_src),
              icmp->icmp_seq,
              ip->ip_ttl,
              rtt);
        packet_recv++;
    } else {
        return -1;
    }

    return 0;
}
