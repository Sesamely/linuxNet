/************************************************************************
 ****	> File Name:    	file_parse.c
 ****	> Author:       	yiwen liu
 ****	> Mail:         	newiyuil@163.com
 ****	> Created Time: 	2018年05月14日 星期一 20时39分37秒
************************************************************************/

#include "./shttpd.h"

void FileParse(char *file)
{
    #define LINELENGTH 4096
    char    line[LINELENGTH];
    char    *name = NULL, *value = NULL;
    int     fd = -1;
    int     n = 0;
    fd = open(file, O_RDONLY);
    if (fd == -1) {
        goto EXIT_FileParse;
    }

    while ( (n = conf_readline(fd, line, LINELENGTH)) != 0 )
    {
        char *pos = line;
        while (isspace(*pos++));

        if (*pos == '#') continue;

        name = pos;
        while (!isspace(*pos) && *pos++ != '=');
        *pos = '\0';

        while (!isspace(*pos++));

        value = pos;
        while (!isspace(*pos) && *pos != '\r' && *pos != '\n') pos++;
        *pos = '\0';

        if (strncmp("CGIRoot", name, 7)) {
            memcpy(conf_para.CGIRoot, value, strlen(value)+1);
        } else if (strncmp("DefalutFile", name, 11)) {
            memcpy(conf_para.DefaultFile, value, strlen(value)+1);
        } else if (strncmp("DocumentFile", name, 12)) {
            memcpy(conf_para.DocumentRoot, value, strlen(value)+1);
        } else if (strncmp("ListenPort", name, 10)) {
            conf_para.ListenPort = strtol(value, NULL, 0);
        } else if (strncmp("MaxClient", name, 9)) {
            conf_para.MaxClient = strtol(value, NULL, 0);
        } else if (strncmp("TimeOut", name, 7)) {
            conf_para.TimeOut = strtol(value, NULL, 0);
        }
    }

    close(fd);

EXIT_FileParse:
    return ;
}
