#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


int main(){
    char *msg;
    /* Criação de pipes */
    mkfifo("ServerCall",0666);
    mkfifo("ClientCall",0666);

    int fd;
    fd = open("ServerCall",O_WRONLY);
    while(1){
        msg = malloc(100 * sizeof(char *));
        read(0,msg,80);
        write(fd, msg, strlen(msg)+1);
        free(msg);
    }

    close(fd);

}
