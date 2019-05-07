#include <stdio.h>
#include "headers/Auxiliares.h"
#include <unistd.h>

int agregador(){
    int Arrsize = countLines("Artigos.txt");
    int fdVendas = open("Vendas.txt", O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
    int arr[Arrsize];
    char tempLine[100];

    




}


int main(){
    int i = 300;
    int array[10] = {30,110,2,-44,6};
    addVer(array,i);
    for(i = 0; i<10;i++){
        printf("%d\n",array[i]);
    }
    return 0;
}