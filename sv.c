#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include "Auxiliares.h"

int checkArt(int codigo){
    int fPtrArt  = open("Artigos.txt", O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
    int fPtrStock  = open("Stocks.txt", O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
    char ch,tempLine[20];
    int bit,len,preco,k=0; 
    
    gotoLines(fPtrArt,codigo-1);
    while(read(fPtrArt, &ch, 1)!=0 && ch != '\n') tempLine[k++] = ch;
    tempLine[k] = '\0';
    sscanf(tempLine,"%d %d %d",&bit, &len, &preco);
    printf("%d\n",preco);

    


return 0;
}

int atualizaStock(int codigo, int stocks){
    int fdStock = open("Stocks.txt", O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);

    return 0;
}

int main(){
    char msg[80];
    /* Criação de pipes */
    mkfifo("ServerCall",0666);
    mkfifo("ClientCall",0666);
    checkArt(3);
    int fd1;
    while(1){
        fd1 = open("ServerCall",O_RDONLY);
        //sleep(3);
        read(fd1, msg, sizeof(msg)); 
        write(1,msg,strlen(msg)+1);
        close(fd1); 
        
    }
    
    
}