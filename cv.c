#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "Auxiliares.h"

#pragma GCC diagnostic ignored "-Wunused-result"

int main(int argc, char *argv[]){
  printf("Tenho %d argumentos!\n",argc); // debug
  char *msg;

  int fd;
  fd = open("ServerCall",O_WRONLY);

  if(argc==3){//quando recebemos argumetnos da criaCasosTeste.c
    char *recebido = malloc(100*sizeof(char *));
    strcat(recebido,argv[1]);
    strcat(recebido," ");
    strcat(recebido,argv[2]);
    printf("string: %s\ntamanho: %ld\n",recebido,strlen(recebido)); // debug
    write(fd,recebido,strlen(recebido));
  }else{//executa este se for feita manualmente sem argumentos
    while(1){
      msg = malloc(100 * sizeof(char *));
      read(0,msg,100);
      write(fd, msg, strlen(msg)+1);
      free(msg);
    }
  }
  close(fd);
}
