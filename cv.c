
#include <stdio.h> //debug

#include <stdlib.h> //malloc
#include <string.h> // strlen
#include <fcntl.h> // O_CREAT,O_WRONLY
#include <unistd.h> // read() write()

#include "headers/Auxiliares.h"

#pragma GCC diagnostic ignored "-Wunused-result"

int main(int argc, char *argv[]){
  char *msg;

  int fd = open("ServerCall",O_WRONLY);

  if(argc==3){//quando recebemos argumetnos da criaCasosTeste.c ou argumentos da consola
    msg = malloc(100 * sizeof(char *));//alloca espaço para poder criar o que vai enviar para o sv
    strcat(msg,argv[1]);
    strcat(msg," ");
    strcat(msg,argv[2]);
    write(fd,msg,strlen(msg)+1);//escreve para o serverCall

    int fPtrCliente = open("ClientCall",O_RDONLY);
    read(fPtrCliente,msg,100);//le a resposta do ciente call
    write(1,msg,strlen(msg)+1);//escreve a resposta na consola

    free(msg);//liberta a memoria allocoada
  }else if(argc==2){//igual ao anterior apenas recebe um argumento para verificar o stock
    msg = malloc(100 * sizeof(char *));
    strcat(msg,argv[1]);
    write(fd,msg,strlen(msg)+1);

    int fPtrCliente = open("ClientCall",O_RDONLY);
    read(fPtrCliente,msg,100);
    write(1,msg,strlen(msg)+1);

    free(msg);
  }else{//executa este se for feita manualmente sem argumentos
    while(1){//loop infinito para tar sempre a receber input
      msg = malloc(100 * sizeof(char *));
      read(0,msg,100);
      write(fd, msg, strlen(msg)+1);

      int fPtrCliente = open("ClientCall",O_RDONLY);
      read(fPtrCliente,msg,100);
      write(1,msg,strlen(msg)+1);

      close(fPtrCliente);
      free(msg);
    }
  }//fecha o ficheiro
  close(fd);
}
