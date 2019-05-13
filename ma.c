#include <stdio.h>
#include <stdlib.h>//atoi
#include <string.h>//strlen
#include <sys/wait.h> // for wait()
#include <unistd.h>//O_CREAT
#include <fcntl.h>//read write

#include "headers/Auxiliares.h"
#include "headers/ma.h"
#include "headers/ag.h"
#include "compactador.c"//agregador()

#pragma GCC diagnostic ignored "-Wunused-result"

//função para mudar o nome de um determinado produto
int mudaNome(int codigo, char input[BUFFER_SIZE]){
  int fPtr, fPtrArt,fptrTemp,i=1,k=0;
  char path[BUFFER_PATH] = "ficheirosTexto/Strings.txt",c;
  char tempLine[20],newLine[20];
  int temPos,tempsize,preco;

  if(codigo > countLines("ficheirosTexto/Artigos.txt")){
    write(1,"Codigo invalido!\n",strlen("Codigo invalido!\n")+1);
    return -1;
  }

  /*Abre os ficheiros necessarios*/
  fPtr  = open(path, O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
  fPtrArt  = open("ficheirosTexto/Artigos.txt", O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
  fptrTemp = open("ficheirosTexto/temp.txt", O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);

  /*Arranja o primeiro byte do artigo e o seu tamanho*/
  int pos = lseek(fPtr, -1, SEEK_END) + 1;
  int size = strlen(input);
  write(fPtr, input, strlen(input));

  /*Copia tudo o que está anterior á linha desejada para outro ficheiro e a linha desejada para uma variavel */
  while(read(fPtrArt, &c, 1)!=0 && codigo >=i){
    if(i!=codigo) write(fptrTemp, &c, 1);
    else tempLine[k++] = c;
    if(c == '\n') i++;
  }
  tempLine[k-1] = '\0';

  /* Substitui os dados necessarios para a mudança de nome */
  sscanf(tempLine, "%d %d %d", &temPos, &tempsize, &preco);
  sprintf(newLine, "%d %d %d\n", pos, size, preco);
  write(fptrTemp, newLine, strlen(newLine));

  /*Retrocede um byte e copia o resto do ficheiro antigo para o novo ficheiro */
  lseek(fPtrArt,-1,SEEK_CUR);
  while(read(fPtrArt, &c, 1)!=0) (void) write(fptrTemp, &c, 1);

  /*Limpa tudo*/
  close(fPtr);
  close(fptrTemp);
  close(fPtrArt);
  remove("ficheirosTexto/Artigos.txt");
  rename("ficheirosTexto/temp.txt", "ficheirosTexto/Artigos.txt");

  write(1, "Nome mudado com Sucesso\n", strlen("Nome mudado com Sucesso\n")+1);
  if(checkthespacito()<0.8){
    write(1,"Muito lixo detetado!! Compactando!\n",30);
    Compress();
  }
  return 0;
}
//funçao para mudar o nome de um determinado produto
int mudaPreco(int codigo, int preco){
  int fPtrArt,fptrTemp,i=1,k=0;
  char c;
  char tempLine[20],newLine[20];
  int pos,size,tempreco;


  if(codigo > countLines("ficheirosTexto/Artigos.txt")){
    write(1,"Codigo invalido!\n",strlen("Codigo invalido!\n")+1);
    return 1;
  }

  /*Abre os ficheiros necessarios*/
  fPtrArt  = open("ficheirosTexto/Artigos.txt", O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
  fptrTemp = open("ficheirosTexto/temp.txt", O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);

  /*Copia tudo o que está anterior á linha desejada para outro ficheiro e a linha desejada para uma variavel */
  while(read(fPtrArt, &c, 1)!=0 && codigo >=i){
    if(i!=codigo) write(fptrTemp, &c, 1);
    else tempLine[k++] = c;
    if(c == '\n') i++;
  }
  tempLine[k-1] = '\0';

  /* Substitui os dados necessarios para a mudança de nome */
  sscanf(tempLine, "%d %d %d", &pos, &size, &tempreco);
  sprintf(newLine, "%d %d %d\n", pos, size, preco);
  write(fptrTemp, newLine, strlen(newLine));

  /*Retrocede um byte e copia o resto do ficheiro antigo para o novo ficheiro */
  lseek(fPtrArt,-1,SEEK_CUR);
  while(read(fPtrArt, &c, 1)!=0) write(fptrTemp, &c, 1);

  /*Limpa tudo*/
  close(fptrTemp);
  close(fPtrArt);
  remove("ficheirosTexto/Artigos.txt");
  rename("ficheirosTexto/temp.txt", "ficheirosTexto/Artigos.txt");

  write(1, "Preco mudado com Sucesso\n", strlen("Preco mudado com Sucesso\n")+1);
  return 0;

}

int main(){
  // argumentos para serem utilizados no sscanf
  char input[100];
  char arg1,arg2[100],arg3[100];
  // loop infinito para tar sempre a pedir novo input (quando ouver input errado dá quits)
  while(1){
    read(0, input, 100);
    if(input[0] == 'a'){//se o input for a excuta o agregador (faz fork para ser possivel continuar a execução deste programa)
      pid_t pid = fork();
      if(pid==0){
        char *args[] = {"./ag",NULL};
        execvp (args[0],args);
        _exit(0);
      }else{
        wait(NULL);
      }

    }else if (contaPal(input)>2){
      sscanf(input, "%c %s %s", &arg1, arg2, arg3);
      if(arg1=='i' && myisnumber(arg3)){ //adiciona novo produto, primeiro nome, depois preço
        addString(arg2,atoi(arg3),"ficheirosTexto/Artigos.txt","ficheirosTexto/Strings.txt");
      }
      else if(arg1=='n' && myisnumber(arg2)){//altera o nome de um produto, primeiro codigo, depois o novo nome
        sscanf(input, "%c %s %s", &arg1, arg2, arg3);
        mudaNome(atoi(arg2),arg3);
      } // comando p muda o preco, primeiro local, depois preco novo
      else if(arg1=='p'&& myisnumber(arg2) && myisnumber(arg3)){
        sscanf(input, "%c %s %s", &arg1, arg2, arg3);
        mudaPreco(atoi(arg2),atoi(arg3));
      }//caso input seja diferente de i,n,p dá erro pois n reconhece o comando
      else write(1,"Formato errado!\n",strlen("Formato errado!\n")+1);
    }//caso input que recebe seja < que o numero de argumentos necessários
    else write(1,"Formato errado!\n",strlen("Formato errado!\n")+1);
  }
  return 0;
}
