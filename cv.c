#include <stdlib.h> //malloc
#include <string.h> // strlen
#include <fcntl.h> // O_CREAT,O_WRONLY
#include <unistd.h> // read() write()

#include "headers/Auxiliares.h"

#pragma GCC diagnostic ignored "-Wunused-result"

int main(int argc, char *argv[]){
  char *msg;

  int fd;
  fd = open("ServerCall",O_WRONLY);

  if(argc==3){//quando recebemos argumetnos da criaCasosTeste.c
    char *recebido = malloc(100*sizeof(char *));
    strcat(recebido,argv[1]);
    strcat(recebido," ");
    strcat(recebido,argv[2]);
    strcat(recebido,"?");
    write(fd,recebido,strlen(recebido)+1);
    free(recebido);
  }else if(argc==2){
    char *recebido = malloc(100*sizeof(char *));
    strcat(recebido,argv[1]);
    strcat(recebido,"?");
    write(fd,recebido,strlen(recebido)+1);
    free(recebido);
  }else{//executa este se for feita manualmente sem argumentos
    while(1){
      msg = malloc(100 * sizeof(char *));
      read(0,msg,100);
      strcat(msg,"?");
      write(fd, msg, strlen(msg)+1);
      free(msg);
    }
  }
  close(fd);
}
