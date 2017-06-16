#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>

int main(int argc, char *argv[]){

  if(argc != 3){
    perror("Argumentos no válidos. Uso: ./me <extremo inferior> <extremo superior>\n") ; exit(EXIT_FAILURE) ;
  }



  
  int fd1[2] ;
  int fd2[2] ; 
  pid_t PID;

  pipe(fd1) ;
  pipe(fd2) ;

  int inf = atoi(argv[1]) ;
  int sup = atoi(argv[2]) ;

      printf("\nNúmeros primos en el intervalo [%d,%d]: \n", inf, sup) ;

  int tam = sup - inf ; 

  tam /= 2 ;
  

  if ( ( PID= fork()) < 0){
    perror("fork");
    exit(EXIT_FAILURE) ;
  }

  
  int lect1, lect2, byt1, byt2 ;
  pid_t esclavo1, esclavo2 ;

  char parametros[2]  ; 


  esclavo1 = fork() ;

  if(esclavo1 == 0){ //esclavo1
    close(fd1[0]) ;
    dup2(fd1[1], STDOUT_FILENO) ;

    parametros[0] = inf ;
    parametros[1] = inf+tam ; 
    if(execl("esclavo","esclavo", parametros, NULL) < 0){
      perror("\nError en exec 1 ") ;
      exit(EXIT_FAILURE) ;
    }
    else{ // padre
      close(fd1[1]) ;

      while((byt1 = read(fd1[0],&lect1,sizeof(int))) > 0){
	printf("%d ", lect1) ;
      }
      close(fd1[0]) ;
      printf("\n") ;
    
      esclavo2 = fork() ;
      if(esclavo2==0){//esclavo2
	close(fd2[0]) ;
	dup2(fd2[1],STDOUT_FILENO) ;
	parametros[0] = inf+tam+1 ;
	parametros[1] = sup ;
	
	if(execl("esclavo","esclavo",parametros,NULL) < 0){
	  perror("\nError en el execl") ;
	  exit(EXIT_FAILURE) ;
	}
	else{//padre
	  close(fd2[1]) ;
	  while((byt2 = read(fd2[0],&lect2,sizeof(int))) > 0){
	    printf("%d", lect2) ;
	  }

	  close(fd2[0]) ;
	  printf("\n") ;
	}
	return 0 ;
      }
    }
  }
}
