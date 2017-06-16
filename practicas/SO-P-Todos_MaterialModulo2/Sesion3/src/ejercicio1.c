#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<errno.h>
#include<unistd.h>
#include<stdlib.h>

int main(int argc, char *argv[]){
  if(argc != 2){
    printf("Número incorrecto de argumentos"); 
    printf("USO: ./ejercicio1 <numero> " ) ;
    return(EXIT_FAILURE) ;
  }
  else{
    pid_t pid ;

    if( ( pid=fork() ) < 0 ){
      perror("\nError en el fork") ;
      exit(EXIT_FAILURE) ;
    }
    else if(pid == 0) { //HIJO
      if(atoi(argv[1]) % 2 == 0)
	printf("El número es par\n");
      else printf ("El número es impar\n") ;
      return(EXIT_SUCCESS) ; 

    } else{  // PADRE
      if(atoi(argv[1]) % 4 == 0)
	printf("El número es divisible por 4\n") ;
     
      else
	printf("El número no es divisible por 4\n") ;
      return(EXIT_SUCCESS) ;
    }
  }
}
      
