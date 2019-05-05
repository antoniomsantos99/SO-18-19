#ifndef AUX
#define AUX

#define BUFFER_PATH 20
#define BUFFER_SIZE 1000

/*Retorna o numero de linhas no ficheiro*/
int countLines(char path[BUFFER_PATH]);

/* Não usado mas poderá dar jeito no futuro */
int gotoLines(int fd,int line);

/*Conta o nrº de palavras numa string*/
int contaPal (char s[]);

/* Verifica se uma string é um número */
int myisnumber(char c[100]);


#endif
