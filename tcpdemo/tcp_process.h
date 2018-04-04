/************************************************************************
 ****	> File Name:    	tcp_process.h
 ****	> Author:       	yiwen liu
 ****	> Mail:         	newiyuil@163.com
 ****	> Created Time: 	2018年04月03日 星期二 13时17分47秒
************************************************************************/

#ifndef _TCP_PROCESS_H
#define _TCP_PROCESS_H

void process_conn_server(int s);
void process_conn_client(int s);
void process_conn_server_forFile(int s);
void process_conn_client_forFile(int s);

#endif
