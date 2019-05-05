#include "ma.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>

int contaPal (char s[]) {
    int i,count=0;
    char last='\0';
    for (i=0;s[i]!='\0';i++)
    {
    	if (s[i]!=' ' && (last ==' ' || last =='\0'))
    	{
    		count ++;
    	}
    	last =s[i];
    }
    return count;
}

int isnumber(char c[100])
{
  int i;
  for(i=0;c[i];i++){
    if (isdigit(c[i]) == 0) return 0;
  }
  return 1;
}

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
      if(arg1=='i' && isnumber(arg3)){
        addString(arg2,atoi(arg3));
      } //comando i para introduzir novo produto
      else if(arg1=='n' && isnumber(arg2)){
        sscanf(input, "%c %s %s", &arg1, arg2, arg3);
        mudaNome(atoi(arg2),arg3);
      } // comando p muda o preco, primeiro local, depois preco novo
      else if(arg1=='p'&& isnumber(arg2) && isnumber(arg3)){
        sscanf(input, "%c %s %s", &arg1, arg2, arg3);
        mudaPreco(atoi(arg2),atoi(arg3));
      }
      else printf("Formato errado!");
    }
    else printf("Vai pa puta que te pariu tu e os formatos errados\n");
    }
    return 0;
}
