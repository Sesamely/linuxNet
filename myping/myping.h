/************************************************************************
 ****	> File Name:    	myping.h
 ****	> Author:       	yiwen liu
 ****	> Mail:         	newiyuil@163.com
 ****	> Created Time: 	2018年04月24日 星期二 16时31分56秒
************************************************************************/

#ifndef _MYPING_H
#define _MYPING_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <signal.h>
#include <sys/time.h>
#include <string.h>
#include <pthread.h>
#include <netdb.h>
#include <netinet/ip_icmp.h>
#include <error.h>
#include <arpa/inet.h>
#include <errno.h>

//macro
#define ICMP_ECHO 8


//struct icmp
/*
 *struct icmp {
 *    u_int8_t      icmp_type;
 *    u_int8_t      icmp_code;
 *    u_int16_t     icmp_cksum;
 *    union {
 *        struct ih_idseq {
 *            u_int16_t     icd_id;
 *            u_int16_t     icd_seq;
 *        };
 *    } icmp_hun;
 *#define icmp_id     icmp_hun.ih_idseq.icd_id
 *#define icpm_seq    icmp_hun.ih_idseq.icd_seq
 *    
 *    union {
 *        u_int8_t    id_data[1];  [> 数据 <]
 *    } icpm_dun;
 *#define icmp_data   icmp_dun.id_data
 *
 *};
 */

//type
typedef struct pingm_packet {
    struct timeval tv_begin;
    struct timeval tv_end;
    short seq;
    int flag;
}pingm_packet;

//declaration
unsigned short  icmp_cksum(const unsigned char *, size_t len);
void            icmp_pack(struct icmp *, int, struct timeval *, int);
int             icmp_unpack(char *, int);
struct timeval  icmp_tvsub(struct timeval, struct timeval);
void            *icmp_send(void *);
void            *icmp_recv(void *);
pingm_packet    *icmp_findpacket(int);


#define K 0x400
#define BUFFERSIZE 72
#ifndef NOEXTERN
#define EXTERN 
#else
#define EXTERN extern
#endif
EXTERN pingm_packet pingpacket[128];
EXTERN unsigned char send_buf[BUFFERSIZE];
EXTERN unsigned char recv_buf[2 * K];
EXTERN struct sockaddr_in dest;
EXTERN int rawsock;
EXTERN pid_t pid;
EXTERN int alive;
EXTERN short packet_send;
EXTERN short packet_recv;
EXTERN char dest_str[80];
EXTERN struct timeval tv_begin, tv_end, tv_interval;

#endif
