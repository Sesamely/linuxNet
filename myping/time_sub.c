/************************************************************************
 ****	> File Name:    	time_sub.c
 ****	> Author:       	yiwen liu
 ****	> Mail:         	newiyuil@163.com
 ****	> Created Time: 	2018年04月24日 星期二 17时17分52秒
************************************************************************/

#include "./myping.h"

struct timeval
icmp_tvsub(struct timeval end,
            struct timeval start)
{
    struct timeval tv;

    tv.tv_sec = end.tv_sec - start.tv_sec;
    tv.tv_usec = end.tv_usec - start.tv_usec;

    if (tv.tv_usec < 0) {
        tv.tv_sec--;
        tv.tv_usec += 1000000;
    }
    
    return tv;
}
