/*
 * author : albrile erik
 * version : 1.1
 *
 * una shell di comando
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>
 
#define PROMPT "$> "
 
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
*   return: array di stringhe dinamico WARN: ricordare di rilasciare la memoria allocata con questa funzione(v. free_array)
*
* char* prompt()
*   stampa il prompt della shell e attenda un input
*   return: stringa di input
*
* size_t len_str(char* str)
*   return: lunghezza di str
*
* free_array(char** din_array)
*   libera tutte le celle di un array allocate dinamicamente
*/
int cmpstr(char*s1, char*s2);
char* input_str();
char* strdup(char* str);
char** split(char* str, char comma);
char* prompt();
size_t len_str(char* str);
void free_array(char** din_array);

int main(){
 
  char* cmd;
  char** cmd_array;

 /* continuo a chiedere input
  * parole chiave vengono controllate dopo
  */
 while(1){
  
  cmd=prompt();

  if( !cmpstr(cmd, "exit") ) /*controllo che l'input non sia "exit"*/
      return EXIT_SUCCESS;

  cmd_array=split(cmd, ' ');
  
  if(!fork()){
   execvp(cmd_array[0], cmd_array);
   fprintf(stderr, "error: %s: command not found\n", cmd_array[0]);
   return EXIT_FAILURE;
  }
  
  wait(NULL);
  free(cmd);
  free_array(cmd_array); /*scorre tutto l'array e free() per ogni stringa che trova*/
  
 }

 return EXIT_SUCCESS;
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
 size_t i;
  
 for(i=0; i < 4095; i++){
  int c = getchar();

  if (c== '\n'){ 
    break;
  }

  buffer[i] = c;
 } 
 buffer[i]='\0'; /*sostituisce il carattere finale ('\n') con il carattere di fine riga ('\0')*/
 
 
 return (strdup(buffer)); 
}


/*duplica una stringa e la alloca dinamicamente 
 *
 * prende una stringa(array di caratteri a lunghezza fissa) qualsiasi e la copia dentro una stringa della lunghezza adeguata
 */
char* strdup(char* str){

 char *ret, *d;
 ret = (char*)malloc(sizeof(char) * (len_str(str)+1));
 
 for(d=ret; (*d=*str); d++,str++){} 
 
 return(ret);
}


/*splitta una stringa
 * char** puntatore a puntatori di caratteri : puntatore a stringhe
 */
char** split(char* str, char comma){

  char** ret; /*array restituito*/
  char** tmp; /*array temporaneo usato per la duplicazione*/
  char* split_buff[1024]; /*buffer per lo split*/
  char* first_char; /*primo char di ogni parola*/
  bool was_endstring; /*per sapere se era comma o \0*/
  size_t i=0;
  size_t j;


  while(*str){ /*tutta la stringa passata*/
    first_char = str; /*salvo il primo carattere della stringa*/

    if(*str == '\0') was_endstring = true;
    

    for(;!(*str==comma || *str=='\0'); str++){} /*finchè non trova un separatore o fine stringa*/
    *str='\0'; /*metto un fine stringa al posto del separatore*/

    split_buff[i] = strdup(first_char); /*duplico dal primo carattere alla comma (che è stata sostituita con \0)*/

    i++; /*mi sposto alla successiva cella dell'array*/
    if(!was_endstring) str++; /*se prima era un separatore(quindi non era l'ultima parola) sposto avanti il puntatore*/
  }

  split_buff[i]=NULL; /*aggiungo una cella NULL alla fine dell'array*/

  /*duplico l'array allocandolo dinamicamente*/
  ret = (char**) malloc(sizeof(char*) * (i+1));
  tmp=ret;
  for(j=0; (*tmp=split_buff[j]); j++)
    tmp++;

  return ret;
}

/* prompt
 */
char* prompt(){
 fputs(PROMPT, stdout);
 return(input_str());
}

/* libera tutte le celle allocate dinamicamente di un array
*/
void free_array(char** din_array){
  char** orig = din_array;
  for(; *din_array; din_array++)
    free(*din_array);
  free(orig);
}

/* restituisce lunghezza della stringa passata
*/
size_t len_str(char* str){
  size_t i;
  for(i=0; str[i]!='\0'; i++){}
  return i;
}
