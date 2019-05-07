#include <stdio.h>
#include "headers/Auxiliares.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int agregador(){
  int Arrsize = countLines("Artigos.txt");
  int fdVendas = open("Vendas.txt", O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
  int fdVendasAux = open("Vendas.txt", O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
  int arr[Arrsize],bitI=0,k=0;
  char tempLine[100],ch;
  int cod, quant,total,caux,qaux,taux;

  time_t t = time(NULL);
  struct tm tm = *localtime(&t);

  sprintf(tempLine,"%d-%d-%d|%d:%d:%d.txt\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
  int fdAg  = open(tempLine, O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);

  while (read(fdVendas,&ch,1)!=0){
    tempLine[k++] = ch;
    bitI++;
    if(ch=='\n'){
      tempLine[k]='/0';
      sscanf(tempLine, "%d %d %d", &cod, &quant, &total);
      k=0;
      if(addVer(arr,cod)==1){
        lseek(fdVendasAux,bitI,SEEK_SET);


        while (read(fdVendasAux,&ch,1)!=0){
          tempLine[k++] = ch;
          if(ch=='\n'){
            tempLine[k]='/0';
            sscanf(tempLine, "%d %d %d", &caux, &qaux, &taux);
            if(cod == caux){
              quant += qaux;
              total += taux;
            }
            k=0;
          }
        }

        sprintf(tempLine,"%d %d %d\n",cod,quant,total);
        write(fdAg,tempLine,strlen(tempLine));
      }
    }
  }
  return 0;

}
