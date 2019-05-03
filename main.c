#include "ma.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

int main(){
    // argumentos para serem utilizados no sscanf
    char input[100];
    char arg1;
    char *arg2 = malloc(100*sizeof(char *));
    int arg3;
    // loop infinito para tar sempre a pedir novo input (quando ouver input errado dá quits)
    while(1){
      read(0, input, 100);
      if (contaPal(input)>2){
      sscanf(input, "%c %s %d", &arg1, arg2, &arg3);
      if(arg1=='i'){
        addString(arg2,arg3);
      } //comando i para introduzir novo produto
      else if(arg1=='n'){
        sscanf(input, "%c %d %s", &arg1, &arg3, arg2);
        mudaNome(arg3,arg2);
      } // comando p muda o preco, primeiro local, depois preco novo
      else if(arg1=='p'){
        int arg4;
        sscanf(input, "%c %d %d", &arg1, &arg3, &arg4);
        mudaPreco(arg3,arg4);
      } // qaualquer outro comando dá quit
      else return;
    }
    else printf("Vai pa puta que te pariu tu e os formatos errados\n");
    }
    return 0;
}
