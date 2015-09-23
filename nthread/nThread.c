/*
 * author: albrile erik
 * version: 1.0
 *
 * Stampa pid del padre
 * Crea N (input) thread, stampa il loro pid e quello del padre
 * Il numero di thread viene richiesto all'inizio o passato come argomento
 */

//unistd.h : libreria standard unix
#include <unistd.h>
    /* fork() : crea un thread figlio; return int : 0 se è un figlio, pid se è il padre
     * wait() : il padre attende la morte del primo figlio creato
     * getpid() : return int : pid di questo processo
     * getppid() : return int : pid del processo genitore
     */
//stdio.h : libreria standard input/output
#include <stdio.h>


int main(int argc, char* argv[]){
    
    int i=0;
    //numero di thread da creare
    int n = 0;
    //pid del processo, verrà inizializzato da fork()
    int pid = 0;
    
    //controllo argomenti
    if(argc == 2) //se c'è un argomento
        n = atoi(argv[1]); //n = argomento
    else if(argc > 2){ //se ci sono troppi argomenti
        printf("uso scorretto, non verranno generati thread\n");
        printf("uso : nthread [number of threads]\n\n"); 
    }else{ //se non ci sono argomenti
        printf("numero di thread da creare:\n"); //richiedo input numero dei thread da creare
        scanf("%d", &n);
    }
    
    
    //stampo pid del padre
    printf("pid padre: %d\n", getpid());
    
    while(i<n && !pid){ //per n volte e solo nel padre
        pid = fork(); //crea un figlio
            wait(); //aspetta i figli
        i++;
    }
    
    if(pid){//figli
        printf("\tpid figlio: %d\t padre: %d\n", getpid(), getppid());
    }
    
    return 0;
}