/*
 * author : albrile erik
 * version : 0.1
 *
 * una shell di comando
 */
 
 #include <stdio.h>
 #include <unistd.h>
 #include <string.h>
 
 #define PROMPT "shellpro $ "
 
int cmpstr(char*s1, char*s2);
char* input_str();
char* strdup(char* str);
char** split(char* str);
char* prompt();
 
int main(){
 
 char* cmd;
  

 /*comparo stringa presa in input e "exit"*/
 while( cmpstr( cmd=prompt() , "exit" ) ){
  
  cmd_array=split(cmd);
  
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
 *
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
  
 for(i=0; (buffer[i] = getchar()) != '\n'; i++){}
 buffer[i]='\0';
 
 
 return (strdup(buffer)); 
}


/*duplica una stringa e la alloca dinamicamente 
 *
 * prende una stringa qualsiasi e la copia dentro una stringa della lunghezza adeguata
 */
char* strdup(char* str){

 char *ret, *d;
 ret = (char*)malloc(sizeof(char) * (len_str(str)+1));
 
 for(d=ret; *d=*s, d++,str++){}
 
 return(ret);
}


/*splitta una stringa
 * char** puntatore a puntatori di caratteri : puntatore a stringhe
 */
char** split(char*){

}

/*
 *
 */
char* prompt(){
 printf(PROMPT);
 return(input_str);
}