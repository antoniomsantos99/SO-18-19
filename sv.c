#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 


int main(){
    char msg[80];
    /* Criação de pipes */
    mkfifo("ServerCall",0666);
    mkfifo("ClientCall",0666);

    int fd;
    while(1){
        fd = open("ServerCall",O_WRONLY);
        //read(0,msg,80);
        fgets(msg, 80, stdin); 

        write(fd, msg, strlen(msg)+1); 
        close(fd); 
        
    }
    
    
}