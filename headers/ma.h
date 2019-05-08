#ifndef MA
#define MA

#define BUFFER_PATH 100
#define BUFFER_SIZE 1000

/*Retorna o numero de linhas no ficheiro*/
//int getLines(char path[BUFFER_PATH]);

/* Não usado mas poderá dar jeito no futuro */
//int gotoLines(int fd,int line);

int addString(char input[BUFFER_SIZE],int preco);

int mudaNome(int codigo, char input[BUFFER_SIZE]);

int mudaPreco(int codigo, int preco);

#endif
