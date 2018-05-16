/************************************************************************
 ****	> File Name:    	CmdParse.c
 ****	> Author:       	yiwen liu
 ****	> Mail:         	newiyuil@163.com
 ****	> Created Time: 	2018年05月14日 星期一 19时50分42秒
************************************************************************/
#define _DEFINE_CONF_PARA
#include "./shttpd.h"

struct conf_opts conf_para = {
    "/home/lyw/CODE/linuxNet/SHTTPD/www/cgi-bin",
    "index.html",
    "/home/lyw/CODE/linuxNet/SHTTPD/www/",
    "/home/lyw/CODE/linuxNet/SHTTPD/www/conf",
    8080,
    4,
    3,
    2
};

static char shortopts[] = "c:d:f:ho:l:m:t:";

static struct option longopts[] = {
    {"CGIRoot",     required_argument, NULL, 'c'},
    {"ConfigFile",  required_argument, NULL, 'f'},
    {"DefaultFile", required_argument, NULL, 'd'},
    {"DocumentRoot",required_argument, NULL, 'o'},
    {"ListenPort",  required_argument, NULL, 'l'},
    {"MaxClinet",   required_argument, NULL, 'm'},
    {"Help",        no_argument,       NULL, 'h'},
    {0, 0, 0, 0},
};

static char *l_opt_arg = NULL;

int CmdParse(int argc, char **argv)
{
    int c;
    int len;
    long value;

    while ( (c = getopt_long(argc, argv, shortopts, longopts, NULL)) != -1 )
    {
        switch (c) {
            case 'c':
                l_opt_arg= optarg;
                if (l_opt_arg && l_opt_arg[0]!=':') {
                    len = strlen(l_opt_arg);
                    memcpy(conf_para.CGIRoot, l_opt_arg, len+1);
                }
                break;
            case 'd':
                l_opt_arg= optarg;
                if (l_opt_arg && l_opt_arg[0]!=':') {
                    len = strlen(l_opt_arg);
                    memcpy(conf_para.DefaultFile, l_opt_arg, len+1);
                }
                break;
            case 'f':
                l_opt_arg= optarg;
                if (l_opt_arg && l_opt_arg[0]!=':') {
                    len = strlen(l_opt_arg);
                    memcpy(conf_para.ConfigFile, l_opt_arg, len+1);
                }
                break;
            case 'o':
                l_opt_arg= optarg;
                if (l_opt_arg && l_opt_arg[0]!=':') {
                    len = strlen(l_opt_arg);
                    memcpy(conf_para.DocumentRoot, l_opt_arg, len+1);
                }
                break;
            case 'l':
                l_opt_arg= optarg;
                if (l_opt_arg && l_opt_arg[0]!=':') {
                    len = strlen(l_opt_arg);
                    value = strtol(l_opt_arg, NULL, 10);
                    if (value != LONG_MAX && value != LONG_MIN)
                        conf_para.ListenPort = value;
                }
                break;
            case 'm':
                l_opt_arg= optarg;
                if (l_opt_arg && l_opt_arg[0]!=':') {
                    len = strlen(l_opt_arg);
                    value = strtol(l_opt_arg, NULL, 10);
                    if (value != LONG_MAX && value != LONG_MIN)
                        conf_para.MaxClient = value;
                }
                break;
            case 't':
                l_opt_arg= optarg;
                if (l_opt_arg && l_opt_arg[0]!=':') {
                    len = strlen(l_opt_arg);
                    value = strtol(l_opt_arg, NULL, 10);
                    if (value != LONG_MAX && value != LONG_MIN)
                        conf_para.TimeOut = value;
                }
                break;
            case '?':
                printf("Invalid para\n");
            case 'h':
                display_usage();
                break;
        }
    }

    return 0;
}

int main(int argc, char **argv)
{
    CmdParse(argc, argv);
    display_conf();
    return 0;
}
