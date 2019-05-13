
#include <stdio.h> // sprintf
#include <unistd.h> // systemcalls
#include <fcntl.h> // O_CREAT, O_RDWR
#include <time.h> // time
#include <string.h> // strings
#include <math.h>

#include "headers/Auxiliares.h"

#pragma GCC diagnostic ignored "-Wunused-result"

//função principal, excuta o agregador todo apartir desta função, recebe o path onde vai executar o agregador
int agregador(char path[],int tag){
  int Arrsize = countLines("ficheirosTexto/Artigos.txt");
  int fdVendas = open(path, O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
  int fdVendasAux = open(path , O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
  int arr[Arrsize],bitI=0,k=0;
  char tempLine[100],pathF[100],ch;
  long int quant,total;
  int cod, caux,qaux,taux,l=0;

  /*Esvazia o array por segurança*/
  memset(arr, 0, sizeof arr);

  /*Cria o ficheiro onde os dados agregados vão ficar*/
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  if(tag == -1) sprintf(pathF,"ficheirosTexto/%d-%d-%d|%d:%d:%d.txt\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
  else sprintf(pathF,"ficheirosTexto/gtempAg%d.txt",tag);
  int fdAg  = open(pathF, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);

  /*Começa a ler o ficheiro de vendas guardando o byte onde está*/
  while (read(fdVendas,&ch,1)!=0){
    tempLine[k++] = ch;
    bitI++;

    /* Caso encontre o fim de uma linha guarda as variaveis para comparar*/
    if(ch=='\n'){
      l++;
      tempLine[k]='\0';
      sscanf(tempLine, "%d %ld %ld", &cod, &quant, &total);
      k=0;
      if(addVer(arr,cod)==1){
        lseek(fdVendasAux,bitI,SEEK_SET);

        /*Lê o ficheiro e vai agregando os valores */
        while (read(fdVendasAux,&ch,1)!=0){
          tempLine[k++] = ch;
          if(ch=='\n'){
            tempLine[k]='\0';
            sscanf(tempLine, "%d %d %d", &caux, &qaux, &taux);
            if(cod == caux && l != countLines(path)){
              quant += qaux;
              total += taux;
            }
            k=0;
          }
        }
        /*Escreve os valores agregados no ficheiro */
        sprintf(tempLine,"%d %ld %ld\n",cod,quant,total);
        write(fdAg,tempLine,strlen(tempLine));
      }
    }
  }
  write(1,"Agregador executado com successo!\n",strlen("Agregador executado com successo!\n")+1);
  if(tag != -1){
    remove(path);
    rename(pathF,path);
  }
  close(fdVendas);
  close(fdVendasAux);
  return 0;

}


int multiag(int power){
  int i;int j = 0;
  pid_t pid;
  int files = pow(2,power);
  int linhaI = 1,linhasP = ceil((countLines("ficheirosTexto/Vendas.txt") / files));
  char name[100];

  //transpose(2,10,"ficheirosTexto/Vendas.txt","testainde.txt");
  for(i=0;i<files;i++){
    sprintf(name,"ficheirosTexto/gtemp%d.txt",i);
    if(i == files-1) transpose(linhaI,countLines("ficheirosTexto/Vendas.txt")+5,"ficheirosTexto/Vendas.txt",name);
    else transpose(linhaI,linhaI+linhasP,"ficheirosTexto/Vendas.txt",name);
    linhaI += linhasP;
  }
  /* o que eu fiz */
  for(i=1;i<files;i++){
    pid = fork();
    if(pid==0){
      break;
    }else{
      j+=1;
    }
  }
  sprintf(name,"ficheirosTexto/gtemp%d.txt",j);
  agregador(name,j);
  if(j!=0) _exit(0);
  for(i=0;i<files;i++){
  sprintf(name,"ficheirosTexto/gtemp%d.txt",i);
  transpose(1,countLines(name)+100,name,"ficheirosTexto/AgAll.txt");
  }
  agregador("ficheirosTexto/AgAll.txt",-1);
  
  return 0;
}


int main(){//executa o agregador para o ficheiro com as vendas
  agregador("ficheirosTexto/Vendas.txt",-1);
  //multiag(2);
  return 0;
}
