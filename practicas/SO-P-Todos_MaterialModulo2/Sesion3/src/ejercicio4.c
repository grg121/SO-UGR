#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<sys/types.h>
#include <sys/wait.h>



int main(){
int i, estado;
pid_t PID;


for(i=0; i<5; i++){
	if((PID = fork())<0){ 
	perror("Error en fork\n");
	exit(-1);
	}
	
	if(PID==0){  //Hijo
		printf("\tSoy el hijo PID = %i\n", getpid());
		return(getpid()); 
	}
}
// CÓDIGO QUE EJECUTARÁ SOLO EL PADRE
for(i=4; i>=0; i--){
PID = wait(&estado); 
printf("Padre: Ha finalizado mi hijo con PID = %i\n", PID);
printf("Padre: Solo me quedan %i hijos vivos\n", i);
}

return(1) ; 
}
