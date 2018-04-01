/************************************************************************
****	> File Name:    	open.c
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	2018年03月29日 星期四 22时22分42秒
************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>

int main1()
{
    int fd;
    int mode;
    scanf("%d", &mode); //not security
    char filename[] = "testfile1";
    if ( (fd = open(filename, O_WRONLY | O_CREAT | O_EXCL, 10600)) < 0 )
    {
        printf("Exist %s\t", filename);
    } else {
        printf("Create %s\t", filename);
    }
    printf("file descriptor is %d\n", fd);

    close(fd);

    return 0;
}

int main()
{
    int fd, mode;
    char filename[] = "testfile1";

    scanf("%o", &mode); 
    /*printf("%d\n", mode);*/

    if (access(filename, F_OK) == 0) {
        /*printf("remove %s\n", filename);*/
        remove(filename);
    }
    if ( (fd = creat(filename, mode)) < 0) {
        printf ("Create %s error!\n", filename);
        /*read(fd, (void *)&mode, sizeof(mode));*/
    }
    close(fd);

    return 0;
}

int main_test()
{
    printf ("%x\n", S_IRWXU);
    printf ("%x\n", S_IRUSR);
    printf ("%x\n", S_IWUSR);
    printf ("%x\n", S_IRWXG);
    printf ("%x\n", S_IRGRP);
    printf ("%x\n", S_IWGRP);
    printf ("%x\n", S_IRWXO);
    printf ("%x\n", S_IROTH);
    printf ("%x\n", S_IWOTH);

    return 0;
}
