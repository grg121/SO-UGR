#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<errno.h>
#include<unistd.h>
#include<stdlib.h>
#include <string.h>
#include <sys/wait.h>



int main(int argc, char *argv[]){

  if(argc != 2){
    perror("\nError, uso: ./3 <número de procesos> ") ;
    exit(EXIT_FAILURE)  ;
  }

  int childpid = 0 ;
  int estado = 0 ; 

  for(int i = 1 ; i < atoi(argv[1]) ; i++){
      if((childpid = fork()) == -1){
	fprintf(stderr, "Could not create child %d: %s\n", i, strerror(errno)) ;
	exit(EXIT_FAILURE);
      }
        if(!childpid){
         printf("\tPID: %d  -- PPID: %d\n", getpid(), getppid()) ;
	 break ; 
	}

      if(childpid){
	 printf("\t\tPID: %d  -- PPID: %d\n", getpid(), getppid()) ;
         //break ;
      }
  }


  while(wait(&estado) != NULL){}

  return 1 ; 
    
}
