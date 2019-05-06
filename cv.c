#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "Auxiliares.h"


#pragma GCC diagnostic ignored "-Wunused-result"

int main(){
    char *msg;

    int fd;
    fd = open("ServerCall",O_WRONLY);
    while(1){
        msg = malloc(100 * sizeof(char *));
        read(0,msg,100);
        write(fd, msg, strlen(msg)+1);
        free(msg);
    }

    close(fd);

}
