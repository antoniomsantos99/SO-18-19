#include "ma.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#include "Auxiliares.c"


int main(){
    // argumentos para serem utilizados no sscanf
    char input[100];
    char arg1,arg2[100],arg3[100];
    //char *arg2 = malloc(100*sizeof(char *));
    // loop infinito para tar sempre a pedir novo input (quando ouver input errado dá quits)
    while(1){
      read(0, input, 100);
      if (contaPal(input)>2){
      sscanf(input, "%c %s %s", &arg1, arg2, arg3);
      if(arg1=='i' && myisnumber(arg3)){
        addString(arg2,atoi(arg3));
      } //comando i para introduzir novo produto
      else if(arg1=='n' && myisnumber(arg2)){
        sscanf(input, "%c %s %s", &arg1, arg2, arg3);
        mudaNome(atoi(arg2),arg3);
      } // comando p muda o preco, primeiro local, depois preco novo
      else if(arg1=='p'&& myisnumber(arg2) && myisnumber(arg3)){
        sscanf(input, "%c %s %s", &arg1, arg2, arg3);
        mudaPreco(atoi(arg2),atoi(arg3));
      }
      else printf("Formato errado!\n");
    }
    else printf("Formato errado!\n");
    }
    return 0;
}
