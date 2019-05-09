#include <stdio.h> // sprintf()
#include <sys/wait.h> // for wait()
#include <unistd.h> // for fork()
#include <time.h> // time(NULL)
#include <stdlib.h> // rand()

#include "headers/Auxiliares.h" // countLines

#define NR_EXECS 50
#define MAX_STOCKS 100

int main(){
  int maxLinha = countLines("ficheirosTexto/Artigos.txt");
  pid_t pid;
  //cria os forks
  for(int i = 0; i < NR_EXECS; i++){
    pid = fork();
    if(pid == 0){
      srand(time(NULL) ^ (getpid()<<16));
      int linha = 1+rand()%maxLinha;

      srand(time(NULL) ^ (getpid()<<16));
      int stock = rand()%MAX_STOCKS-20;


      //transforma os numeros numa string
      char sLinha[100];
      sprintf(sLinha,"%d",linha);
      char sStock[100];
      sprintf(sStock,"%d",stock);

      //executa a cv.c com os argumentos randomizados
      char *args[] = {"./cv",sLinha,sStock,NULL};
      execvp (args[0],args);
      _exit(0);
    }else{
      wait(NULL);
      sleep(0.1);
    }
  }
}
