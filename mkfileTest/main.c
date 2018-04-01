/************************************************************************
****	> File Name:    	main.c
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	2018年03月29日 星期四 11时00分46秒
************************************************************************/

#include <stdio.h>

#include "add.h"
#include "sub.h"

int main()
{
    int a=10, b=12;
    float x = 1.23,
        y = 9.876;

    printf("int a+b IS: %d\n", add_int(a, b));
    printf("int a-b IS: %d\n", sub_int(a, b));
    printf("int x+y IS: %f\n", add_float(x, y));
    printf("int x-y IS: %f\n", sub_float(x, y));

    return 0;
}
