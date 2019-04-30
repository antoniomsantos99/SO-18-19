#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_PATH 20
#define BUFFER_SIZE 1000



int addString(char input[BUFFER_SIZE],int preco){
    
    int fPtr, fPtrArt,count=0;
    char path[BUFFER_PATH] = "Strings.txt";
    char buffer[BUFFER_SIZE];

    /*Abre os ficheiros necessarios*/
    fPtr  = open(path, O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
    fPtrArt  = open("Artigos.txt", O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);

    /*Arranja o primeiro byte do artigo e o seu tamanho*/
    int pos = lseek(fPtr, -1, SEEK_END) + 1;
    int size = strlen(input);
    
    /*Escreve os dados necessários nos ficheiros */
    write(fPtr, input, strlen(input));
    sprintf(buffer, "%d %d %d\n", pos, size, preco); 
    write(fPtrArt, buffer, strlen(buffer));

/*WIP
    char c;
    for (c = getc(fPtrArt); c != EOF; c = getc(fPtrArt)) 
        if (c == '\n') // Increment count if this character is newline 
            count = count + 1;
    printf("Codigo = %d\n",count);

    //write(1, "Impossivel aceder ao ficheiro\n", 30);
*/

    close(fPtr);
    close(fPtrArt);

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

    sprintf(input, "%d %d", pos, size); 
    
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
    addString("Bola",10);
    addString("Caneta",10);
    addString("Foice",10);
    addString("Raquete",10);
    addString("Violoncelo",10);
    return 0;
}