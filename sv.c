#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h> // atoi e atof
#include "headers/Auxiliares.h"

#pragma GCC diagnostic ignored "-Wunused-result"

//talvez tenha erro todo
int checkArt(int codigo){

    int fPtrArt  = open("Artigos.txt", O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
    int fPtrStock  = open("Stocks.txt", O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
    int newfd = gotoLines(fPtrArt,codigo);
    int newfd1 = gotoLines(fPtrStock,codigo);
    char ch,tempLine[20],buffer[BUFFER_SIZE];
    int bit,len,preco,k=0;


    if(newfd!=-1 && newfd1!=-1){
        /*Saca o preço*/
        while(read(newfd , &ch, 1)!=0 && ch != '\n') tempLine[k++] = ch; //TODO
        tempLine[k] = '\0';
        sscanf(tempLine,"%d %d %d",&bit, &len, &preco);
        /*Saca o Stock*/
        k=0;
        while(read(newfd1 , &ch, 1)!=0 && ch != '\n') tempLine[k++] = ch; //TODO
        tempLine[k] = '\0';
        if(strlen(tempLine)==0) printf("Stock não inserido\n");
        else printf("%d %s\n",preco,tempLine);


    }else printf("Oof\n");

    close(fPtrArt);
    close(fPtrStock);
    if (newfd==-1) return 1; else return 0;
}

int atualizaStock(int codigo, char stocks[]){
    int fdStock = open("Stocks.txt", O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
    int fdVendas = open("Vendas.txt", O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
    int fdArt  = open("Artigos.txt", O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
    char ch,tempLine[20],newLine[20];
    int bit,len,preco,k=0,counter=1,stocktotal;

if(codigo <= countLines("Artigos.txt")){
/*Escreve a venda*/
    if(gotoLines(fdArt,codigo)!=-1){
        while(read(fdArt, &ch, 1)!=0 && ch != '\n') tempLine[k++] = ch;
        tempLine[k] = '\0';
        sscanf(tempLine,"%d %d %d",&bit, &len, &preco);
        sprintf(newLine,"%d %d %d\n", codigo, atoi(stocks), (atoi(stocks)*preco));
        lseek(fdVendas,-1, SEEK_END);
        (void)(write(fdVendas,newLine,strlen(newLine))+1);
    }

/*Atualiza o stock*/
/*Se o código for maior que o nrº de linhas do ficheiro dá append das linhas necessárias e acrescenta o stock*/
if(countLines("Stocks.txt")<codigo){
    while(read(fdStock, &ch, 1)!=0 && counter != codigo) if(ch == '\n') counter++;
    while(counter < codigo){
        write(fdStock,"\n",1);
        counter++;
        }

write(fdStock,stocks,strlen(stocks));
} else{
        int fdTemp  = open("replace.tmp", O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
        int i = 1;
        k=0;
        while(read(fdStock, &ch, 1)!=0 && codigo >=i){
        if(i!=codigo) (void) (write(fdTemp, &ch, 1)+1);
        else tempLine[k++] = ch;
        if(ch == '\n') i++;
    }
    tempLine[k]='\0';

    if(strlen(tempLine)==1) stocktotal = atoi(stocks);
    else stocktotal = atoi(stocks)+atoi(tempLine);

    sprintf(newLine,"%d\n",stocktotal);
    write(fdTemp,newLine,strlen(newLine));


    lseek(fdStock,-1,SEEK_CUR);
    while(read(fdStock, &ch, 1)!=0) (void) (write(fdTemp, &ch, 1)+1);

    close(fdTemp);
    remove("Stocks.txt");
    rename("replace.tmp", "Stocks.txt");
}
}
else printf("Codigo Invalido!\n");

    //write(fdStock,stocks,strlen(stocks));
    close(fdStock);
    close(fdArt);
    close(fdVendas);
    return 0;
}
//MUDEI DE INT PARA VOID PQ TAVA A DAR ERRO
void caller(char cmd[]){
    printf("%d\n",contaPal(cmd));
    int arg1;
    char arg2[100];
    if(0<contaPal(cmd) && contaPal(cmd) < 3){
        sscanf(cmd,"%d %s",&arg1,arg2);
        if(contaPal(cmd) == 1)checkArt(arg1);
        else atualizaStock(arg1,arg2);
    }
    else write(1,"Comando Invalido!",18);

}

int main(){
    char *msg = malloc(100*sizeof(char *));
    /* Criação de pipes */
    mkfifo("ServerCall",0666);
    mkfifo("ClientCall",0666);
    int fd1;
    fd1 = open("ServerCall",O_RDONLY);
    while(1){
      int num = 0;
        //fd1 = open("ServerCall",O_RDONLY);
        read(fd1, msg, sizeof(msg));
        printf("%s",msg);
        char *token;
        token = strtok(msg,"?");
        while(token!=NULL){
          printf("%s\n",token);
          token=strtok(NULL,"?");
          caller(msg);
        }

        scanf("%d",&num);
    }
    close(fd1);


}
