#include <stdio.h> // sprintf()
#include <sys/wait.h> // for wait()
#include <unistd.h> // for fork()
#include <time.h> // time(NULL)
#include <stdlib.h> // rand()

#include "headers/Auxiliares.h" // countLines

#define NR_EXECS 100
#define MAX_STOCKS 100
#define MIN_STOCKS -20

int main(int argc, char *argv[]){
  //contar as linhas do ficheiro para saber em quais pode adicioanr stock
  int maxLinha = countLines("ficheirosTexto/Artigos.txt");
  pid_t pid;
  if(argc==2){//caso recebe argumentos executa o numero de vezes no argumento
    int execs = atoi(argv[1]);
    for(int i = 0; i < execs; i++){
      pid = fork();
      if(pid == 0){
        //randomizar seed
        srand(time(NULL) ^ (getpid()<<16));
        int linha = 1+rand()%maxLinha;

        srand(time(NULL) ^ (getpid()<<16));
        int stock = (rand()%MAX_STOCKS)+MIN_STOCKS;


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
        //espera que o filho acabe para criar novo filho e executar o programa de novo
        wait(NULL);
        //espera um pouco para não dar overload ao pipe (0.02 segundos)
        usleep(20000);
      }
    }
  }else{//caso seja iniciado normalmente executa com o numero de execuções defenido acima
    for(int i = 0; i < NR_EXECS; i++){
      //cria os forks
      pid = fork();
      if(pid == 0){
        //randomizar seed
        srand(time(NULL) ^ (getpid()<<16));
        int linha = 1+rand()%maxLinha;

        srand(time(NULL) ^ (getpid()<<16));
        int stock = (rand()%MAX_STOCKS)+MIN_STOCKS;


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
        //espera que o filho acabe para criar novo filho e executar o programa de novo
        wait(NULL);
        //espera um pouco para não dar overload ao pipe (0.02 segundos)
        usleep(20000);
      }
    }
  }
}
