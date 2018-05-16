/************************************************************************
 ****	> File Name:    	work_schedule_run.c
 ****	> Author:       	yiwen liu
 ****	> Mail:         	newiyuil@163.com
 ****	> Created Time: 	2018年05月14日 星期一 21时01分55秒
************************************************************************/

#include "./shttpd.h"

int Worker_ScheduleRun(int ss)
{
    DBGPRINT("==>Worker_ScheduleRun\n");
    struct sockaddr_in client;
    socklen_t len = sizeof(client);
    Worker_Init();

    int i = 0;

    for (; SCHEDULESTATUS==STATUS_RUNNING; ) {
        struct timeval tv;
        fd_set rfds;
        int retval = -1;
        FD_ZERO(&rfds);
        FD_SET(ss, &rfds);

        tv.tv_sec = 0;
        tv.tv_usec = 500000;
        
        retval = select(ss + 1, &rfds, NULL, NULL, &tv);
        switch (retval)
        {
            case -1:
            case  0:
                continue;
            default:
                if(FD_ISSET(ss, &rfds)) {
                    int sc = accept(ss, (struct sockaddr*)&client, &len);
                    i = WORKER_ISSTATUS(WORKER_IDEL);
                    if (i == -1) {
                        i = WORKER_ISSTATUS(WORKER_DETACHED);
                        if (i != -1) Worker_Add(i);
                        else close(sc);
                    }
                    if (i != -1) {
                        wctls[i].conn.cs = sc;
                        pthread_mutex_unlock(&wctls[i].opts.mutex);
                    }
                }
        }
    }

    DBGPRINT("<==Worker_ScheduleRun\n");
    return 0;
}

int Worker_ScheduleStop()
{
    DBGPRINT("==>Worker_ScheduleStop\n");
    SCHEDULESTATUS = STATUS_STOP;
    int  i = 0;
    Worker_Destroy();
    int allfired = 0;
    for (; !allfired; ) {
        allfired = 1;
        for (i = 0; i < conf_para.MaxClient; ++i) {
            int flags = wctls[i].opts.flags;
            if (flags == WORKER_DETACHED || flags == WORKER_IDEL)
                allfired = 0;
        }
    }

    pthread_mutex_destroy(&thread_init);
    for (i = 0; i<conf_para.MaxClient; ++i) 
        pthread_mutex_destroy(&wctls[i].opts.mutex);
    free(wctls);

    DBGPRINT("<==Worker_ScheduleStop");
    return 0;
}

void Worker_Init()
{
    DBGPRINT("==>Worker_Init");
    int i = 0;

    wctls = (struct worker_ctl*)malloc(
        sizeof(struct worker_ctl) * conf_para.MaxClient);

    memset(wcls, 0, sizeof(*wclts) * conf_para.MaxClient);

    for (i=0; i<conf_para.MaxClient, ++i) {
        wctls[i].opts.work = &wctls[i];
        wctls[i].conn.work = &wctls[i];

        wctls[i].opts.flags = WORKER_DETACHED;
        
        pthread_mutex_init(&wclts[i].opts.mutex, NULL);
        pthread_mutex_lock(&wctls[i].opts.mutex);

        wctls[i].conn.con_req.conn = &wctls[i].conn;
        wctls[i].conn.con_res.conn = &wctls[i].conn;
        wctls[i].conn.cs = -1;

        wctls[i].conn.con_req.req.ptr = wctls[i].conn.dreq;
        wctls[i].conn.con_req.head = wctls[i],conn.dreq;
        wctls[i].conn.con_req.uri = wctls[i].conn.dreq;

        wctls[i].conn.con_res.fd = -1;
        wctls[i].conn.con_res.res.ptr = wctls[i].conn.dres;
    }

    for (i=0; i<conf_para.InitClient; ++i)
        Worker_Add(i);
    DBGPRINT("<==Worker_Init");
}


