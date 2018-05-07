/************************************************************************
 ****	> File Name:    	icmp_recv.c
 ****	> Author:       	yiwen liu
 ****	> Mail:         	newiyuil@163.com
 ****	> Created Time: 	2018年04月24日 星期二 23时08分14秒
************************************************************************/

#include "./myping.h"

void *
icmp_recv(void *argv)
{
    struct timeval tv;
    tv.tv_usec = 0;
    tv.tv_sec = 1;

    fd_set readfd;

    while (alive) {
        int ret = 0;
        FD_ZERO(&readfd);
        FD_SET(rawsock, &readfd);
        ret = select(rawsock+1, &readfd, NULL, NULL, &tv);
        switch (ret) {
            case -1:
            break;
            case 0:
            break;
            default: {
                /*
                 *int fromlen = 0;
                 *struct sockaddr from;
                 */

                int size = recv(rawsock, recv_buf, sizeof(recv_buf), 0);
                if (errno == EINTR) {
                    perror("recvfrom error");
                    continue;
                }
                ret = icmp_unpack((char *)recv_buf, size);
                if (ret == -1) {
                    continue;
                }
            }
            break;
        }
    }
    return NULL;
}
