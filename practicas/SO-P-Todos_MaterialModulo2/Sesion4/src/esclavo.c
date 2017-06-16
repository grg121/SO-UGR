
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<math.h> // compilar con -lm 


int primo(int n){
  int i;
  int limite = sqrt(n);
  int es_primo = 1;
  for (i = 2; i <= limite && es_primo; i++)
    if (n % i == 0)
      es_primo = 0;
  return es_primo;
};


int main(int argc, char * argv[]){

  int inicio,fin,i ;
  inicio = atoi(argv[1]) ;
  fin = atoi(argv[2]) ;

  for( i = inicio ; i <= fin ; i++){
    if( primo(i))
      write(STDOUT_FILENO, &i, sizeof(int)) ;
  }

  return 0 ;
}
