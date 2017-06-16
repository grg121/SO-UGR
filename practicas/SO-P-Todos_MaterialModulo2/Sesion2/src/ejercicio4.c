#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<unistd.h>
#include<dirent.h>
#include<ftw.h>

int reg = 0 ; int size = 0 ; 

void busqueda(const char * path, const struct stat * stat, int flags, struct FTW* ftw){


  char fpathname[400] ;
  struct stat atributos ;
  struct dirent * file ;
  DIR *c_dir ; 


  while((file=readdir(directorio)) != NULL){
    if(strcmp(file->d_name, "..") != 0 && strcmp(file->d_name, ".") != 0){
      sprintf(fpathname,"%s/%s", pathname, file->d_name) ; 
      if(stat(fpathname,&atributos) <0){
	printf("\nError accediendo a los atributos del archivo") ;
	fprintf(stderr, "\nError en stat") ;
	exit(EXIT_FAILURE) ;
      }
      if(S_ISDIR(atributos.st_mode)){ 
	if((c_dir = opendir(fpathname)) == NULL)
	  printf("\nError al abrir el directorio: %s\n", fpathname) ;
	else
	  busqueda(c_dir, fpathname, reg, size) ;
				      

      }else{
	printf("%s %lu \n", fpathname, atributos.st_ino) ;
	if(S_ISREG(atributos.st_mode)){
	  if(atributos.st_mode &(S_IXOTH | S_IXGRP) == (S_IXOTH | S_IXGRP)){
	    *reg = *reg + 1 ;
	    *size = *size + (int) atributos.st_size ;
	  }
	}
      }
    }
  }
    closedir(directorio) ;
  
}
      

int main(int argc, char *argv[]){

  char *pathname ;
  

  if(argc != 2){
    printf("\nNúmero de argumentos incorrecto. Uso: ./buscar <pathname> ") ;
    exit(EXIT_FAILURE) ;
  }else{
      pathname = argv[1] ; 

  printf("Los inodos son: \n\n") ;

  if(nftw(pathname, busqueda, 10, 0) != 0)
    perror("nftw") ;


  printf("Hay %d archivos regulares con permiso x para grupo y otros \n", reg) ;
  printf("El tamaño total ocupado por dichos archivos es %d bytes\n", size) ;

  exit(EXIT_SUCCESS) ;
  
  }
}

  
