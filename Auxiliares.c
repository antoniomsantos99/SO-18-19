#include <stdio.h>
#include <stdlib.h>//atoi
#include <string.h>//strlen
#include <sys/wait.h> // for wait()
#include <unistd.h>//O_CREAT
#include <fcntl.h>//read write
#include <ctype.h>

#include "headers/Auxiliares.h"

#pragma GCC diagnostic ignored "-Wunused-result"

/*Retorna o numero de linhas no ficheiro*/
int countLines(char path[BUFFER_PATH]) {
  int counter=0;
  char buffer;
  int fd = open(path,O_RDONLY);
  while(read(fd, &buffer, 1)!=0)
  if(buffer == '\n') counter++;
  close(fd);
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

int addString(char input[BUFFER_SIZE],int preco,char pathArt[BUFFER_PATH],char pathStr[BUFFER_PATH]){

  int fPtr, fPtrArt;
  char buffer[BUFFER_SIZE];

  /*Abre os ficheiros necessarios*/
  fPtr  = open(pathStr, O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
  fPtrArt  = open(pathArt, O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);

  /*Arranja o primeiro byte do artigo e o seu tamanho*/
  int pos = lseek(fPtr, -1, SEEK_END) + 1;
  int size = strlen(input);

  /*Escreve os dados necessários nos ficheiros */
  write(fPtr, input, strlen(input));
  sprintf(buffer, "%d %d %d\n", pos, size, preco);
  write(fPtrArt, buffer, strlen(buffer));

  /*Encontra o codigo para dar ao artigo (linha do artigos.txt)*/
  lseek(fPtrArt, 0, SEEK_SET);
  int lines = countLines(pathArt);
  sprintf(buffer, "Artigo criado com sucesso! Codigo = %d\n",lines);
  write(1, buffer, strlen(buffer));

  /*Fecha os ficheiros*/
  close(fPtr);
  close(fPtrArt);

  return 0;
}

int transpose(int linhaI,int linhaF,char pathI[],char pathF[]){
  int fdI = open(pathI, O_RDONLY | O_APPEND, S_IRUSR | S_IWUSR);
  int fdF = open(pathF, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
  char ch;
  if(countLines(pathI) < linhaI){
    write(1,"Linha Invalida!\n",16);
    close(fdI);
    close(fdF);
    return -1;
  }

  gotoLines(fdI,linhaI);
  while(read(fdI,&ch,1)!=0 && linhaI < linhaF){
    if(ch == '\n') linhaI++;
    write(fdF,&ch,1);
  }
  close(fdI);
  close(fdF);
  return 0;
}
