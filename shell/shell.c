/*
 * author : albrile erik
 * version : 0.1
 *
 * una shell di comando
 */
 
 #include <stdio.h>
 #include <unistd.h>
#include <stdbool.h>
 
 #define PROMPT "shellpro $ "
 
/*PROTOTIPI FUNZIONI
*
* int cmpstr(char*s1, char*s2)
*   compara due stringhe
*   return: -1 se s1>s2 ; +1 se s1<s2 ; 0 se uguali
*
* char* input_str()
*   prende in input una stringa fino a che viene premuto invio
*   return: char* da 4096 caratteri
*
* char* strdup(char* str)
*   duplica una stringa, allocandola dinamicamente 
*   return: char*  WARN: ricordare di rilasciare la memoria allocata con questa funzione (free() )
*
* char** split(char* str, char comma)
*   splitta una stringa secondo ogni "comma"
*   return: array di stringhe dinamico WARN ricordare di rilasciare la memoria allocata con questa funzione(v. free_array)
*
* char* prompt()
*   stampa il prompt della shell e attenda un input
*   return: stringa di input
*
* int len_str(char* str)
*   return: lunghezza di str
*
* free_array(char** din_array)
*   rilascia tutte le celle di un array allocate dinamicamente
*/
int cmpstr(char*s1, char*s2);
char* input_str();
char* strdup(char* str);
char** split(char* str, char comma);
char* prompt();
int len_str(char* str);
void free_array(char** din_array);

int main(){
 
 char* cmd;
  

 /*comparo stringa presa in input e "exit"*/
 while( cmpstr(cmd=prompt(), "exit" ) ){
  
  char** cmd_array=split(cmd, ' ');
  
  if(!fork()){
   execvp(cmd_array[0], cmd_array);
   printf("command not found");
   return(-1);
  }
  
  wait();
  free(cmd);
  free_array(cmd_array); //scorre tutto l'array e free() per ogni stringa che trova
  cmd=prompt();
 
 }

 return 0;
}
 
 
/*compara due stringhe
 * -1 se la prima è maggiore
 * +1 se la prima è minore
 * 0 se sono uguali
 */
int cmpstr(char*s1, char*s2){
 if(*s1>*s2) return(-1);
 if(*s1<*s2) return(+1);
 if(*s1) return(cmpstr(++s1,++s2));
 return(0);
}
 
 
/*prende in input una stringa
 * buffer da 4096 caratteri, poi lo alloca dinamicamente e lo restituisce
 */ 
char* input_str(){

 char buffer[4096];
 int i;
  
 for(i=0; (buffer[i] = getchar()) != '\n'; i++){} //salva i caratteri premuti uno dopo l'altro
 buffer[i]='\0'; //sostituisce il carattere finale ('\n') con il carattere di fine riga ('\0')
 
 
 return (strdup(buffer)); 
}


/*duplica una stringa e la alloca dinamicamente 
 *
 * prende una stringa(array di caratteri a lunghezza fissa) qualsiasi e la copia dentro una stringa della lunghezza adeguata
 */
char* strdup(char* str){

 char *ret, *d;
 ret = (char*)malloc(sizeof(char) * (len_str(str)+1));
 
 for(d=ret; *d=*str; d++,str++){} 
 
 return(ret);
}


/*splitta una stringa
 * char** puntatore a puntatori di caratteri : puntatore a stringhe
 */
char** split(char* str, char comma){

  char** ret; /*array restituito*/

   /*usato per contare le parole*/
  char* c = str; /*punta al carattere che controllo per cercare i separatori*/
  int numero_parole = 0;
  bool comma_prec=true;

  /*usato per splittare*/
  char* str_tmp[512];/*continene la stringa temporanea man mano che la copio*/
  int i;

  /*conto quante parole ci sono nella stringa*/
  while(*c){

      if(*c == comma) {
        comma_prec = true; /*se trova un separatore lo segnala*/
      }
      else{ /* *c!=comma && *c!=\0 */
          numero_parole++; /*carattere dopo separatore significa nuova parola*/
          comma_prec = false;
      }

      c++;
  }

  **ret = (char**) malloc( sizeof(char*) * (numero_parole+1) ); /*alloco lo spazio per l'array*/

  /*splitto la stringa*/
  c=str; /*riparto dall'inizio*/

  while(*c){

    while(*c == comma) c++; /*salta i separatori*/

    for(i=0; (str_tmp[i]=*c) != comma && *c; i++,c++){} /*copio in str_tmp tutti i caratteri di *c fino al separatore*/
    str_tmp[++i] = '\0'; /*aggiungo il carattere di fine stringa a fine parola*/

    *ret = (char*) malloc(sizeof(char*) + (i+1)); /*alloco lo spazio per la singola parola (i è la lunghezza della parola)*/
    *ret = strdup(str_tmp); /*copio la parola in ret dopo allocata dinamicamente*/
    ret++; /*passo alla stringa dopo*/
  }

  /*aggiunge una stringa contentente solo '\0' come cella di fine vettore*/
  *ret = (char*) malloc(sizeof(char*));
  *ret = '\0';

  return **ret;
}

/* prompt base
 */
char* prompt(){
 printf(PROMPT);
 return(input_str);
}

/* rilascia tutte le celle allocate dinamicamente di un array
*/
void free_array(char** din_array){
  while( len_str(*din_array) ) /*l'ultima cella di un array dinamico contiene solo uncarattere '\0'*/
    free(*din_array);
}

/* restituisce lunghezza della stringa passata
*/
int len_str(char* str){
  int i;
  for(i=0; str[i]!='\0'; i++){}
  return i;
}