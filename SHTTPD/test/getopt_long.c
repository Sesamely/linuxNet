/************************************************************************
 ****	> File Name:    	getopt_long.c
 ****	> Author:       	yiwen liu
 ****	> Mail:         	newiyuil@163.com
 ****	> Created Time: 	2018年05月14日 星期一 14时11分51秒
************************************************************************/

#include <stdio.h>
#include <getopt.h>

struct option long_args[] = {
    {"CGIRoot",     required_argument, NULL, 'c'},
    {"ConfigFile",  required_argument, NULL, 'f'}
};

int
main(int argc, char **argv)
{
    int result ;
    while ((result = getopt_long(argc, argv, "c:f:", long_args, NULL)) != -1) {
        printf("%c\t args is %s\n", result, optarg);
    }

    return 0;
}
