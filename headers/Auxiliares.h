
#ifndef AUX
#define AUX

#define BUFFER_PATH 100
#define BUFFER_SIZE 1000

/*Retorna o numero de linhas no ficheiro*/
int countLines(char path[BUFFER_PATH]);

/* Não usado mas poderá dar jeito no futuro */
int gotoLines(int fd,int line);

/*Conta o nrº de palavras numa string*/
int contaPal (char s[]);

/* Verifica se uma string é um número */
int myisnumber(char c[100]);

void nextLine(int fd);

/*Adiciona a um array caso não exista, return 1 se colocou, 0 se não*/
int addVer (int a[],int nr);

int addString(char input[BUFFER_SIZE],int preco,char pathArt[BUFFER_PATH],char pathStr[BUFFER_PATH]);

int transpose(int linhaI,int linhaF,char pathI[],char pathF[]);

#endif
