/*
* @brief: Se reciben la señal de terminacion de proceso y cuando queremos terminar al servidor.
* @Author: Farfan Sanchez Erick David
* @Date: 12-Octubre-2021
*/
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <syslog.h>
extern int sockfd;
extern pthread_t hilo;
extern int frenar;
void ISRsw( int sig )
{
	int estado;
	pid_t pid;
	//printf("\nSeñal recibida: %d \n", sig);
	printf("\nSeñal recibida: %d \n", sig);
	if( sig == SIGCHLD )	{        
		pid = wait(&estado);
		//printf("Proceso con pid: %d terminado y retorno: %d\n", pid, estado>>8);
		printf("Proceso con pid: %d terminado y retorno: %d\n", pid, estado>>8);
	}
    
    else if( sig == SIGINT )
	{
   		//printf("\nConcluimos la ejecución de la aplicacion Servidor \n");
		printf("\nConcluimos la ejecución de la aplicacion Servidor \n");
		//join hilo   
		printf("\nEsperamos a hilo \n");
		frenar = 1;     		
        pthread_join(hilo, NULL);        
		closelog( );
   		close (sockfd);        
		exit(0);
	}
}