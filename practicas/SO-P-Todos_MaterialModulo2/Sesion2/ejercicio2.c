#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<unistd.h>
#include<dirent.h>

int main(int argc, char *argv[])
{

  if(argc != 3){
    printf("\n[NÚMERO DE PAŔAMETROS INCORRECTO] USO: <dir pathname> <n octal> ") ;
    exit(EXIT_FAILURE) ; 
  }
  else{

    int base = 8 ; 
    char *endptr, *str ;

    str = argv[2] ;
    
   unsigned int permisos = strtol(str,  &endptr, base) ;

    if(endptr == str){
      fprintf(stderr, "No se ha introducido ningun dígito\n") ;
      exit(EXIT_FAILURE) ;
}

 DIR * directorio ;
 char *pathname;
 char *fpathname ; 
 struct stat atributos ;
 struct dirent * file   ;
 char salida[300] ; 

 
 pathname = argv[1] ;
 directorio = opendir(pathname) ;


 while((file = readdir(directorio)) != NULL){
   sprintf(fpathname, "%s/%s", pathname, file->d_name) ;

   if(stat(fpathname, &atributos) < 0 ){
     printf("\nError intentando acceder a los atributos del archivo.") ;
     fprintf(stderr, "\nError en stat") ;
     exit(EXIT_FAILURE) ;
   }
  
   if(S_ISREG(atributos.st_mode)){
     
     sprintf(salida, "%s: ", file->d_name) ;

     if(chmod(fpathname, permisos) < 0 ) {
       sprintf(salida, "%s errno:%d %o\n", salida, errno, permisos) ; 
	 }
     else sprintf(salida, "%s %o %o\n", salida, atributos.st_mode, permisos) ; 

     printf("%s", salida) ;
   }
 }
  
 

    exit(EXIT_SUCCESS) ;

  }
}
