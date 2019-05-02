#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 


int main(){
    char msg[80];
    /* Criação de pipes */
    //mkfifo("ServerCall",0666);
    //mkfifo("ClientCall",0666);

    int fd1;
    while(1){
        fd1 = open("ServerCall",O_RDONLY);
        //sleep(3);
        read(fd1, msg, sizeof(msg)); 
        write(1,msg,strlen(msg)+1);
        close(fd1); 
        
    }
    
    
}