#include <stdio.h>
#include <string.h>
#include <sys/stat.h> //fifo (pipe)
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h> // atoi e atof

#include "headers/Auxiliares.h"

#pragma GCC diagnostic ignored "-Wunused-result"

//PRONTO E A FUNCIONAR BEM, NÃO MECHER
int checkArt(int codigo){
  int fPtrArt  = open("ficheirosTexto/Artigos.txt", O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
  int fPtrStock  = open("ficheirosTexto/Stocks.txt", O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
  int newfd = gotoLines(fPtrArt,codigo);
  int newfd1 = gotoLines(fPtrStock,codigo);
  char ch,tempLine[BUFFER_SIZE];
  int bit,len,preco,k=0;

  int fPtrCliente = open("ClientCall",O_WRONLY);

  if(newfd!=-1 && newfd1!=-1 && codigo < countLines("ficheirosTexto/Artigos.txt")-1){
    /*Saca o preço*/
    while(read(newfd , &ch, 1)!=0 && ch != '\n') tempLine[k++] = ch; //TODO
    tempLine[k] = '\0';
    sscanf(tempLine,"%d %d %d",&bit, &len, &preco);
    /*Saca o Stock*/
    k=0;
    while(read(newfd1 , &ch, 1)!=0 && ch != '\n') tempLine[k++] = ch; //TODO
    tempLine[k] = '\0';
    if(strlen(tempLine)==0) {
      write(fPtrCliente,"Artigo sem stock.\n",strlen("Artigo sem stock.\n")+1);
    }else{
      char newLine[100];
      sprintf(newLine,"Stock: %s  Preço: %d\n",tempLine,preco);
      write(fPtrCliente,newLine,strlen(newLine)+1);
    }//printf("%d %s\n",preco,tempLine);
  }else write(fPtrCliente,"Erro: Artigo não existe.\n",strlen("Erro: Artigo não existe.\n")+1);

  close(fPtrArt);
  close(fPtrStock);
  close(fPtrCliente);

  return 0;
}

int atualizaStock(int codigo, int stocksN){
  int fdStock = open("ficheirosTexto/Stocks.txt", O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
  int fdVendas = open("ficheirosTexto/Vendas.txt", O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
  int fdArt  = open("ficheirosTexto/Artigos.txt", O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
  char ch,tempLine[BUFFER_SIZE],newLine[BUFFER_SIZE],newLineV[BUFFER_SIZE];
  int bit,len,preco,k=0,counter=1,stocktotal;
  char stocks[100];

  sprintf(stocks,"%d",stocksN);

  int fPtrCliente = open("ClientCall",O_WRONLY);

  if(codigo <= countLines("ficheirosTexto/Artigos.txt")){
    /*Escreve a venda*/
    if(gotoLines(fdArt,codigo)!=-1 && atoi(stocks)<0){
      while(read(fdArt, &ch, 1)!=0 && ch != '\n') tempLine[k++] = ch;
      tempLine[k] = '\0';
      sscanf(tempLine,"%d %d %d",&bit, &len, &preco);
      sprintf(newLineV,"%d %d %d\n", codigo, -atoi(stocks), -(atoi(stocks)*preco));
    }

    /*Atualiza o stock*/
    /*Se o código for maior que o nrº de linhas do ficheiro dá append das linhas necessárias e acrescenta o stock*/
    if(countLines("ficheirosTexto/Stocks.txt")<codigo){
      while(read(fdStock, &ch, 1)!=0 && counter != codigo) if(ch == '\n') counter++;
      while(counter < codigo){
        write(fdStock,"\n",1);
        counter++;
      }
      if(stocksN>0){
      write(fdStock,stocks,strlen(stocks));
      write(fdStock,"\n",1);
      write(fPtrCliente,"Stock criado com sucesso.\n",strlen("Stock criado com sucesso.\n")+1);
      }
      else { 
      write(fPtrCliente,"Stock não pode ser negativo!\n",strlen("Stock não pode ser negativo!\n")+1);
      close(fdStock);
      close(fdArt);
      close(fdVendas);
      close(fPtrCliente);
      return -1;
      }

    } else{
      int fdTemp  = open("ficheirosTexto/replace.tmp", O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
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
      if(stocktotal<0){ 
      write(fPtrCliente,"Stock não pode ser negativo!\n",strlen("Stock não pode ser negativo!\n")+1);
      close(fdStock);
      close(fdArt);
      close(fdVendas);
      close(fdTemp);
      close(fPtrCliente);
      return -1;
      }
      
      else{
      sprintf(newLine,"%d\n",stocktotal);
      write(fdTemp,newLine,strlen(newLine));

      if(atoi(stocks)<0 && stocktotal>0){
      lseek(fdVendas,-1, SEEK_END);
      write(fdVendas,newLineV,strlen(newLineV));
      }


      lseek(fdStock,-1,SEEK_CUR);
      while(read(fdStock, &ch, 1)!=0) write(fdTemp, &ch, 1);

      remove("ficheirosTexto/Stocks.txt");
      rename("ficheirosTexto/replace.tmp", "ficheirosTexto/Stocks.txt");
      if(stocksN>0) write(fPtrCliente,"Stock adicionado com sucesso.\n",strlen("Stock adicionado com sucesso.\n")+1);
      else write(fPtrCliente,"Venda feita com sucesso.\n",strlen("Venda feita com sucesso.\n")+1);
    }
    close(fdTemp);
  }
  }else write(fPtrCliente,"Erro: Artigo não existe.\n",strlen("Erro: Artigo não existe.\n")+1);

  close(fdStock);
  close(fdArt);
  close(fdVendas);

  close(fPtrCliente);
  return 0;
}
//MUDEI DE INT PARA VOID PQ TAVA A DAR ERRO
void caller(char cmd[]){
  int arg1;
  int arg2;

  sscanf(cmd,"%d %d",&arg1,&arg2);
  if(contaPal(cmd) == 1) checkArt(arg1);
  if(contaPal(cmd) == 2) atualizaStock(arg1,arg2);
}

int main(){
  /* Criação de pipes */
  mkfifo("ServerCall",0666);
  mkfifo("ClientCall",0666);
  int fd1;
  while(1){

    fd1 = open("ServerCall",O_RDONLY);
    char *msg = malloc(100*sizeof(char *));
    read(fd1, msg, sizeof(msg));
    caller(msg);

    free(msg);
    close(fd1);
  }


}
