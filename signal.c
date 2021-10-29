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
	//syslog(LOG_INFO,"\nSeñal recibida: %d \n", sig);
	syslog(LOG_INFO,"\nSeñal recibida: %d \n", sig);
	if( sig == SIGCHLD )	{        
		pid = wait(&estado);
		//syslog(LOG_INFO,"Proceso con pid: %d terminado y retorno: %d\n", pid, estado>>8);
		syslog(LOG_INFO,"Proceso con pid: %d terminado y retorno: %d\n", pid, estado>>8);
	}
    
    else if( sig == SIGINT )
	{
   		//syslog(LOG_INFO,"\nConcluimos la ejecución de la aplicacion Servidor \n");
		syslog(LOG_INFO,"\nConcluimos la ejecución de la aplicacion Servidor \n");
		//join hilo   
		syslog(LOG_INFO,"\nEsperamos a hilo \n");
		frenar = 1;     		
        pthread_join(hilo, NULL);        
		closelog( );
   		close (sockfd);        
		exit(0);
	}
}