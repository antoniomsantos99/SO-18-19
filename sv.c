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
    int newfd = gotoLines(fPtrArt,codigo);
    char ch,tempLine[20];
    int bit,len,preco,k=0; 
    

    if(newfd!=-1){
        while(read(newfd, &ch, 1)!=0 && ch != '\n') tempLine[k++] = ch;
        tempLine[k] = '\0';
        sscanf(tempLine,"%d %d %d",&bit, &len, &preco);
        printf("%d\n",preco);
    }

    close(fPtrArt);
    close(fPtrStock);

return 0;
}

int atualizaStock(int codigo, int stocks){
    int fdStock = open("Stocks.txt", O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
    int fdVendas = open("Vendas.txt", O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
    int fdArt  = open("Artigos.txt", O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
    char ch,tempLine[20],newLine[20];
    int bit,len,preco,k=0; 

    if(gotoLines(fdArt,codigo)!=-1){
        while(read(fdArt, &ch, 1)!=0 && ch != '\n') tempLine[k++] = ch;
        tempLine[k] = '\0';
        sscanf(tempLine,"%d %d %d",&bit, &len, &preco);
        sprintf(newLine,"%d %d %d\n", codigo, stocks, (stocks*preco));
        lseek(fdVendas,-1, SEEK_END);
        (void)(write(fdVendas,newLine,strlen(newLine))+1);
    }



    return 0;
}

int caller(char cmd[]){
    int arg1,arg2;
    if(0<contaPal(cmd) && contaPal(cmd) < 3){
        sscanf(cmd,"%d %d",&arg1,&arg2);
        if(contaPal(cmd) == 1)checkArt(arg1);
        else atualizaStock(arg1,arg2);
    }
    else write(1,"Comando Invalido!",18);

}

int main(){
    char msg[80];
    /* Criação de pipes */
    mkfifo("ServerCall",0666);
    mkfifo("ClientCall",0666);
    int fd1;
    while(1){
        fd1 = open("ServerCall",O_RDONLY);
        //sleep(3);
        read(fd1, msg, sizeof(msg)); 
        caller(msg);
        close(fd1); 
        
    }
    
    
}