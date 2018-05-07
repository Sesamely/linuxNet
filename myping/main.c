/************************************************************************
 ****	> File Name:    	main.c
 ****	> Author:       	yiwen liu
 ****	> Mail:         	newiyuil@163.com
 ****	> Created Time: 	2018年04月24日 星期二 23时14分13秒
************************************************************************/

#define NOEXTERN

#include "./myping.h"

static void icmp_usage(const char *program) {
    printf("%s aaa.bbb.ccc.ddd", program);
}

static void icmp_sigint(int signo) {
    alive = 0;
    gettimeofday(&tv_end, NULL);
    tv_interval = icmp_tvsub(tv_end, tv_begin);

    return ;
}

pingm_packet *icmp_findpacket(int seq) {
    int i=0;
    pingm_packet *found = NULL;

    if (seq == -1) {
        for (i=0; i<128; ++i) {
            if (pingpacket[i].flag == 0) {
                found = &pingpacket[i];
                break;
            }
        }
    }
    else if (seq >= 0) {
        for (i=0; i<128; ++i) {
            found = &pingpacket[i];
            break;
        }
    }
    return found;
}

static void icmp_statistics(void) {
    long time = (tv_interval.tv_sec*1000) + (tv_interval.tv_usec/1000);
    printf("--- %s ping statistics ---\n", dest_str);
    printf("%d packets transmitted, %d received, %d%c packet loss, time %ld ns\n",
          packet_send, packet_recv, (packet_send-packet_recv)*100/packet_send, '%', time);
}

int 
main(int argc, char **argv) {
    struct hostent *host = NULL;
    struct protoent *protocol = NULL;
    char protoname[] = "icmp";
    unsigned long inaddr = 1;
    int size = 128 * K;

    if (argc < 2) {
        icmp_usage(argv[0]);
        exit(-1);
    }

    protocol = getprotobyname(protoname);
    if (protocol == NULL) {
        perror("getprotobyname error");
        exit(-1);
    }

    memcpy(dest_str, argv[1], strlen(argv[1]) + 1);
    memset(pingpacket, 0, sizeof(pingm_packet) * 128);

    rawsock = socket(AF_INET, SOCK_RAW, protocol->p_proto);
    if (rawsock == -1) {
        perror("socket error");
        exit(-1);
    }

    pid = getuid();
    
    setsockopt(rawsock, SOL_SOCKET, SO_RCVBUF, &size, sizeof(size));
    bzero(&dest, sizeof(dest));

    dest.sin_family = AF_INET;

    inaddr = inet_addr(argv[1]);
    if (inaddr == INADDR_NONE) {
        host = gethostbyname(argv[1]);
        if (host == NULL) {
            perror("gethostbyname");
            exit(-1);
        }
        memcpy((char *)&dest.sin_addr, host->h_addr, host->h_length);
    }
    else {
        memcpy((char *)&dest.sin_addr, &inaddr, sizeof(inaddr));
    }
    inaddr = dest.sin_addr.s_addr;

    printf("PING %s (%ld.%ld.%ld.%ld) 56(84) bytes of data.\n",
          dest_str,
          (inaddr&0x000000FF)>>0,
          (inaddr&0x0000FF00)>>8,
          (inaddr&0x00FF0000)>>16,
          (inaddr&0xFF000000)>>24);

    signal(SIGINT, icmp_sigint);

    alive = 1;
    pthread_t send_id, recv_id;
    int err = 0;
    err = pthread_create(&send_id, NULL, icmp_send, NULL);
    if (err < 0) {
        perror("pthread_create error");
        exit(-1);
    }

    err = pthread_create(&recv_id, NULL, icmp_recv, NULL);
    if (err < 0) {
        perror("pthread_create error");
        exit(-1);
    }

    pthread_join(send_id, NULL);
    pthread_join(recv_id, NULL);

    close(rawsock);
    icmp_statistics();

    exit(-1);
}
