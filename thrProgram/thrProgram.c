/*
 *author: albrile erik
 *version: 1.0
 *
 *genera un thread e al suo interno esegue un programma esterno
 */

//unistd.h : standard unix
#include <unistd.h>
    /*execvp(programma, null) : sostituisce il codice del thread con quello di un altro eseguibile (abilitando l'accesso a $PATH)
     *                          return int : -1 se c'è un errore
     */
//stdio.h : standard input/output
#include <stdio.h>

int main(int argc, char* args[]){

    printf("opening xterm in a different thread... \n");
    
    //creo un thread e nel figlio eseguo il programma
    if(fork()){
        execvp("xterm", NULL);
    }else{
        printf("parent %d", getpid());
        wait();
    }
    return 0;
}