/************************************************************************
 ****	> File Name:    	icmp_cksum.c
 ****	> Author:       	yiwen liu
 ****	> Mail:         	newiyuil@163.com
 ****	> Created Time: 	2018年04月24日 星期二 16时31分41秒
************************************************************************/

#include "./myping.h"

unsigned short
icmp_cksum(const unsigned char *data, size_t len)
{
    int sum = 0; /* a tricky */
    int odd = len & 0x01;

    while (len > 1) {
        sum += *(unsigned short *)data;
        data += 2;
        len -= 2;
    }

    if (odd) {
        sum += (unsigned short)((*data << 8) & 0xFF00);
    }

    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += sum >> 16;

    return ~sum;
}
