/************************************************************************
 ****	> File Name:    	uri.c
 ****	> Author:       	yiwen liu
 ****	> Mail:         	newiyuil@163.com
 ****	> Created Time: 	2018年05月14日 星期一 21时45分28秒
************************************************************************/

#include "./shttpd.h"

int 
uri_decode(char *src, int src_len, char *dst, int dst_len)
{
    int i, j, a, b;
#define HEXTOI(x) (isdigit(x) ? x - '0' : x - 'W')
    for (i = j = 0; i<src_len && j<dst_len-1; i++,j++) {
        switch (src[i])
        {
            case '%':
                if (isxdigit( ((unsigned char *)src)[i+1] )
                   && isxdigit( ((unsigned char *)src)[i+2] )) 
                {
                    a = tolower( ((unsigned char *)src)[i+1] );
                    b = tolower( ((unsigned char *)src)[i+2] );
                    dst[j] = (HEXTOI(a) << 4) | HEXTOI(b);
                    i += 2;
                } else {
                    dst[j] = '%';
                } break;
            default :
                dst[j] = src[i];
                break;
        }
    }
    dst[j] = '\0';
    return j;
}

void remove_double_dots(char *s) {
    char *p = s;
    while (*s != '\0') {
        *p++ = *s++;
        if (s[-1] == '/' || s[-1] == '\\' ) {
            while (*s == '.' || *s == '/' || *s == '\\') s++;
        }
        *p = '\0';
    }
}

/*
 *#include <stdio.h>
 *int main(int argc, char **argv)
 *{
 *    printf("%s\n", argv[1]);
 *    remove_double_dots(argv[1]);
 *    printf("%s\n", argv[1]);
 *
 *    return 0;
 *}
 */
