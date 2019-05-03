#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_PATH 20
#define BUFFER_SIZE 1000

/*Retorna o numero de linhas no ficheiro*/
int getLines(char path[BUFFER_PATH]) {
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

int addString(char input[BUFFER_SIZE],int preco){

    int fPtr, fPtrArt;
    char path[BUFFER_PATH] = "Strings.txt";
    char buffer[BUFFER_SIZE];

    /*Abre os ficheiros necessarios*/
    fPtr  = open(path, O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
    fPtrArt  = open("Artigos.txt", O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);

    /*Arranja o primeiro byte do artigo e o seu tamanho*/
    int pos = lseek(fPtr, -1, SEEK_END) + 1;
    int size = strlen(input);

    /*Escreve os dados necessários nos ficheiros */
    (void) (write(fPtr, input, strlen(input))+1);
    sprintf(buffer, "%d %d %d\n", pos, size, preco);
    (void) (write(fPtrArt, buffer, strlen(buffer))+1);

    /*Encontra o codigo para dar ao artigo (linha do artigos.txt)*/
    lseek(fPtrArt, 0, SEEK_SET);
    int lines = getLines("Artigos.txt");
    sprintf(buffer, "Artigo criado com sucesso! Codigo = %d\n",lines);
    (void) (write(1, buffer, strlen(buffer))+1);

    /*Fecha os ficheiros*/
    close(fPtr);
    close(fPtrArt);

    return 0;
}

int mudaNome(int codigo, char input[BUFFER_SIZE]){
    int fPtr, fPtrArt,fptrTemp,i=1,k=0;
    char path[BUFFER_PATH] = "Strings.txt",c;
    char tempLine[20],newLine[20];
    int temPos,tempsize,preco;

    if(codigo > getLines("Artigos.txt")){
        (void) (write(1,"Codigo invalido!\n",18)+1);
        return -1;
    }

    /*Abre os ficheiros necessarios*/
    fPtr  = open(path, O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
    fPtrArt  = open("Artigos.txt", O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
    fptrTemp = open("temp.txt", O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);

    /*Arranja o primeiro byte do artigo e o seu tamanho*/
    int pos = lseek(fPtr, -1, SEEK_END) + 1;
    int size = strlen(input);
    (void) (write(fPtr, input, strlen(input))+1);

    /*Copia tudo o que está anterior á linha desejada para outro ficheiro e a linha desejada para uma variavel */
    while(read(fPtrArt, &c, 1)!=0 && codigo >=i){
        if(i!=codigo) (void) (write(fptrTemp, &c, 1)+1);
        else tempLine[k++] = c;
        if(c == '\n') i++;
    }
    tempLine[k-1] = '\0';

    /* Substitui os dados necessarios para a mudança de nome */
    sscanf(tempLine, "%d %d %d", &temPos, &tempsize, &preco);
    sprintf(newLine, "%d %d %d\n", pos, size, preco);
    (void) (write(fptrTemp, newLine, strlen(newLine))+1);

    /*Retrocede um byte e copia o resto do ficheiro antigo para o novo ficheiro */
    lseek(fPtrArt,-1,SEEK_CUR);
    while(read(fPtrArt, &c, 1)!=0) (void) (write(fptrTemp, &c, 1)+1);

    /*Limpa tudo*/
    close(fPtr);
    close(fptrTemp);
    close(fPtrArt);
    remove("Artigos.txt");
    rename("temp.txt", "Artigos.txt");

    (void) (write(1, "Nome mudado com Sucesso\n", 25)+1);
    return 0;

}

int mudaPreco(int codigo, int preco){
    int fPtrArt,fptrTemp,i=1,k=0;
    char c;
    char tempLine[20],newLine[20];
    int pos,size,tempreco;


    if(codigo > getLines("Artigos.txt")){
        (void) (write(1,"Codigo invalido!\n",18)+1);
        return -1;
    }

    /*Abre os ficheiros necessarios*/
    fPtrArt  = open("Artigos.txt", O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
    fptrTemp = open("temp.txt", O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);

    /*Copia tudo o que está anterior á linha desejada para outro ficheiro e a linha desejada para uma variavel */
    while(read(fPtrArt, &c, 1)!=0 && codigo >=i){
        if(i!=codigo) (void) (write(fptrTemp, &c, 1)+1);
        else tempLine[k++] = c;
        if(c == '\n') i++;
    }
    tempLine[k-1] = '\0';

    /* Substitui os dados necessarios para a mudança de nome */
    sscanf(tempLine, "%d %d %d", &pos, &size, &tempreco);
    sprintf(newLine, "%d %d %d\n", pos, size, preco);
    (void) (write(fptrTemp, newLine, strlen(newLine))+1);

    /*Retrocede um byte e copia o resto do ficheiro antigo para o novo ficheiro */
    lseek(fPtrArt,-1,SEEK_CUR);
    while(read(fPtrArt, &c, 1)!=0) (void) (write(fptrTemp, &c, 1)+1);

    /*Limpa tudo*/
    close(fptrTemp);
    close(fPtrArt);
    remove("Artigos.txt");
    rename("temp.txt", "Artigos.txt");

    (void) (write(1, "Preco mudado com Sucesso\n", 26)+1);
    return 0;

}
