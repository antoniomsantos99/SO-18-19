#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1000



int addString(char input[BUFFER_SIZE]){
    FILE * fPtr;
    char path[100] = "Strings.txt";
    char buffer[BUFFER_SIZE];

    fPtr  = fopen(path, "a");

    fputs(input, fPtr);

    fclose(fPtr);

    return 0;
}


int atualizaLinhaArtigo(int line)
{
    //Pointers
    FILE * fPtr;
    FILE * fTemp;
    char path[100] = "teste.txt";
    
    char buffer[BUFFER_SIZE];
    char input[BUFFER_SIZE];
    int  count;

    //Remove o \n do stdin
    fflush(stdin);

    write(1, "Input aqui\n", 10);
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
    return 0;
}