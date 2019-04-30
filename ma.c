#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_PATH 20
#define BUFFER_SIZE 1000



int addString(char input[BUFFER_SIZE]){
    int fPtr;
    char path[BUFFER_PATH] = "Strings.txt";
    char buffer[BUFFER_SIZE];

    
    
    fPtr  = open(path, O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);

    int pos = lseek(fPtr, -1, SEEK_END);
    int size = strlen(input);
    
    printf("%i\n",pos);
    
    write(fPtr, input, strlen(input));

    close(fPtr);

    return 0;
}


int atualizaLinhaArtigos(int line,int size, int pos)
{
    //Pointers
    FILE * fPtr;
    FILE * fTemp;
    char path[100] = "artigo.txt";
    
    char buffer[BUFFER_SIZE];
    char input[BUFFER_SIZE];
    int  count;

    //Remove o \n do stdin
    fflush(stdin);

    fgets(input, BUFFER_SIZE, stdin);

    //Parse do input
    



    //Abre os ficheiros necessarios
    fPtr  = fopen(path, "r");
    fTemp = fopen("replace.tmp", "w"); 

    
    if (fPtr == NULL || fTemp == NULL)
    {
        
        write(1, "Impossivel aceder ao ficheiro\n", 30);
        exit(EXIT_SUCCESS);
    }



    count = 0;
    while ((fgets(buffer, BUFFER_SIZE, fPtr)) != NULL)
    {
        count++;

        
        if (count == line)
            fputs(input, fTemp);
        else
            fputs(buffer, fTemp);
    }


 
    fclose(fPtr);
    fclose(fTemp);



    remove(path);

 
    rename("replace.tmp", path);

    write(1, "Sucesso\n", 10);

    return 0;
}

int main(){
    addString("Bola");
    addString("Caneta");
    addString("Foice");
    addString("Raquete");
    addString("Violoncelo");
    return 0;
}