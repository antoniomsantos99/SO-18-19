#include <fcntl.h> // O_RDONLY, OCREAT
#include <unistd.h> // read write
#include <ctype.h> // isdigit

#include "headers/Auxiliares.h"

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
  int counter=1;
  if(counter == line) return fd;
  char buffer;
  while(read(fd, &buffer, 1)!=0){
    if(buffer == '\n') counter++;
    if(counter == line) return fd;
  }
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
/*Vai para a linha seguinte*/
void nextLine(int fd){
  char c;
  while(read(fd,&c,1)!=0 && c != '\n');
}

/*Adiciona a um array caso não exista*/
int addVer (int a[],int nr){
  int i = 0;
  while(a[i]){
    if(a[i]==nr){
      return 0;
    }
    i++;
  }
  a[i]=nr;
  return 1;
}
