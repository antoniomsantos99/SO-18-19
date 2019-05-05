#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>

#define BUFFER_PATH 20
#define BUFFER_SIZE 1000

/*Retorna o numero de linhas no ficheiro*/
int countLines(char path[BUFFER_PATH]) {
    int counter=0;
    char buffer;
    int fd = open(path,O_RDONLY);
    while(read(fd, &buffer, 1)!=0)
        if(buffer == '\n') counter++;
    return counter;
}

/* Não usado mas poderá dar jeito no futuro */
int gotoLines(int fd,int line) {
    int counter=0;
    char buffer;
    while(read(fd, &buffer, 1)!=0)
        if(buffer == '\n'){
            counter++;
            if(counter == line) return fd;
        }
    (void) (write(1, "Linha não existente!\n", 30)+1);
    return -1;
}
/*Conta o nrº de palavras numa string*/
int contaPal (char s[]) {
    int i,count=0;
    char last='\0';
    for (i=0;s[i]!='\0';i++){
    	if (s[i]!=' ' && (last ==' ' || last =='\0')) count++;
    	last = s[i];
    }
    return count;
}
/* Verifica se uma string é um número */
int myisnumber(char c[]){
  int i;
  for(i=0;c[i];i++){
    if (isdigit(c[i]) == 0) return 0;
  }
  return 1;
}