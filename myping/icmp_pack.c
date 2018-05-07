/************************************************************************
****	> File Name:    	icmp_pack.c
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	2018年04月24日 星期二 16时53分09秒
************************************************************************/

#include "./myping.h"

extern pid_t pid;

void 
icmp_pack(struct icmp *icmph, int seq,
          struct timeval *tv, int length)
{
    unsigned char i = 0;
    icmph->icmp_type = ICMP_ECHO;
    icmph->icmp_code = 0;
    icmph->icmp_cksum = 0;
    icmph->icmp_seq = seq;
    icmph->icmp_id = pid & 0xFFFF;

    for (i=0; i<length; ++i)
        icmph->icmp_dun.id_data[i] = i;

    icmph->icmp_cksum = icmp_cksum((unsigned char *)icmph, length);
}
