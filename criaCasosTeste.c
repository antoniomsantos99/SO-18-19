#include <stdio.h>
#include <sys/wait.h> // for wait()
#include <unistd.h> // for fork()
#include <time.h> // time(NULL)
#include <stdlib.h> // rand()
#include <math.h>

#define NR_FORKS 2
#define MAX_STOCKS 100
#define MAX_LINHA 10

int main(){

  //cria os forks
  for(int i = 0; i < NR_FORKS; i++){
    fork();
  }

  //faz o random para cada pid, linha e o stock
  srand(time(NULL) ^ (getpid()<<16));
  int linha = 1+rand()%MAX_LINHA;

  srand(time(NULL) ^ (getpid()<<16));
  int stock = 1+rand()%MAX_STOCKS;


  //transforma os numeros numa string
  char sLinha[100];
  sprintf(sLinha,"%d",linha);
  char sStock[100];
  sprintf(sStock,"%d",stock);

  //executa a cv.c com os argumentos randomizados
  char *args[] = {"./cv",sLinha,sStock,NULL};
  execvp (args[0],args);
}
