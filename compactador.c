#include <stdio.h>
#include <stdlib.h>//atoi
#include <string.h>//strlen
#include <sys/wait.h> // for wait()
#include <unistd.h>//O_CREAT
#include <fcntl.h>//read write
#include <math.h>
#include "headers/Auxiliares.h"

#pragma GCC diagnostic ignored "-Wunused-result"

double checkthespacito(){
    int fdart = open("ficheirosTexto/Artigos.txt", O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
    int fdstr = open("ficheirosTexto/Strings.txt", O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
    int bit,len,preco,bitsUsados=-1,k=0;
    int bitstotais = lseek(fdstr,-1,SEEK_END);
    double percent;
    char ch,tempLine[100];

    while(read(fdart , &ch, 1)!=0)
    if(ch != '\n') tempLine[k++] = ch;
    else {
        tempLine[k] = '\0';
        k=0;
        sscanf(tempLine,"%d %d %d",&bit, &len, &preco);
        bitsUsados += len;
    }

    percent = ((double) bitsUsados/(double) bitstotais);



return percent;

}

int Compress(){
    int fdart = open("ficheirosTexto/Artigos.txt", O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
    int fdstr = open("ficheirosTexto/Strings.txt", O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
    int k=0,bit,len,preco,i;
    char tempLine[100],ch;

    while(read(fdart , &ch, 1)!=0)
    if(ch != '\n') tempLine[k++] = ch;
    else {
        tempLine[k] = '\0';
        k=0;
        sscanf(tempLine,"%d %d %d",&bit, &len, &preco);
        lseek(fdstr,bit,SEEK_SET);
        for(i=0;i<len;i++){
            read(fdstr, &ch, 1);
            tempLine[k++] = ch;
        }
        tempLine[k] = '\0';
        k=0;
        printf("%s\n",tempLine);
        addString(tempLine,preco,"ficheirosTexto/NewArtigos.txt","ficheirosTexto/NewStrings.txt");
     }
     remove("ficheirosTexto/Artigos.txt");
     remove("ficheirosTexto/Strings.txt");
     rename("ficheirosTexto/NewArtigos.txt","ficheirosTexto/Artigos.txt");
     rename("ficheirosTexto/NewStrings.txt","ficheirosTexto/Strings.txt");

     return 0;
}
