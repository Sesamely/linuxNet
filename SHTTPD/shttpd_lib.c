/************************************************************************
 ****	> File Name:    	display_usage.c
 ****	> Author:       	yiwen liu
 ****	> Mail:         	newiyuil@163.com
 ****	> Created Time: 	2018年05月14日 星期一 20时10分17秒
************************************************************************/

#include "./shttpd.h"

void display_usage()
{
    printf("temp usage\n");
}

void display_conf()
{
    printf("conf_opt show below:");
    printf("\nCGIRoot:\t%s"
         "\nDefaultFile\t%s"
         "\nDocumentRoot\t%s"
         "\nConfigFile\t%s"
         "\nListenPort\t%d"
         "\nMaxClient\t%d"
         "\nTimeOut\t\t%d"
         "\nInitClient\t%d\n",
         conf_para.CGIRoot,
         conf_para.DefaultFile,
         conf_para.DocumentRoot,
         conf_para.ConfigFile,
         conf_para.ListenPort,
         conf_para.MaxClient,
         conf_para.TimeOut,
         conf_para.InitClient);
    int i;
    for(i=0; i<40; ++i)
        printf("-");
    printf("\n\n");
}
