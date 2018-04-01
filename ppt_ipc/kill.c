/************************************************************************
 ****	> File Name:    	kill.c
 ****	> Author:       	yiwen liu
 ****	> Mail:         	newiyuil@163.com
 ****	> Created Time: 	2018年04月01日 星期日 20时36分19秒
************************************************************************/

#include <stdio.h>
#include <signal.h>

int main()
{
    int i;
    scanf("%d", &i);
    kill (i, SIGKILL);

    return 0;
}
