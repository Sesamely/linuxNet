/************************************************************************
 ****	> File Name:    	test.c
 ****	> Author:       	yiwen liu
 ****	> Mail:         	newiyuil@163.com
 ****	> Created Time: 	2018年05月15日 星期二 11时16分21秒
************************************************************************/

#include <stdio.h>

int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Hello ?!\n");
        return 0;
    }
    printf("Hello %s!\n", argv[1]);
    return 0;
}
