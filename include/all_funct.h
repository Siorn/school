/* all_funct.h
 * version :  1.0
 * author : albrile erik
 *
 * This is al library with all the function i ever made for school
 *
 */

#ifndef _ALLFUNCT_H
#define _ALLFUNCT_H

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
  char** tmp; /*array temporaneo usato per la duplicazione*/
  char* split_buff[1024]; /*buffer per lo split*/
  char* first_char; /*primo char di ogni parola*/
  bool was_endstring; /*per sapere se era comma o \0*/
  int i=0;
  int j;


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
  ret = (char**) malloc(sizeof(char*) + (i+1));
  for(j=0, tmp=ret; *tmp=split_buff[j]; j++, tmp++){}

  return ret;
}

/* rilascia tutte le celle allocate dinamicamente di un array
*/
void free_array(char** din_array){
  char** tmp;
  for(tmp=din_array; din_array; din_array++)
    free(*din_array);
  free(tmp);
}

/* restituisce lunghezza della stringa passata
*/
int len_str(char* str){
  int i;
  for(i=0; str[i]!='\0'; i++){}
  return i;
}

#endif