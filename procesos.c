/*
* @brief: Es un proceso que se encarga de atender a un cliente.
* @Author: Farfan Sanchez Erick David
* @Date: 12-Octubre-2021
*/
#include <syslog.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include "defs.h"
extern GPGGA dato;
void atiendeCliente(int cliente_sockfd)
{
    char leer_mensaje[TAM_BUFFER];
    int mi_pid = getpid();
    /*	Inicia la transferencia de datos entre cliente y servidor
 */
    //syslog(LOG_INFO,"Se aceptó un cliente y lo estoy atendiendo proceso %d\n", mi_pid);
    syslog(LOG_INFO,"Se aceptó un cliente y lo estoy atendiendo proceso %d\n", mi_pid);
    if (read(cliente_sockfd, leer_mensaje, TAM_BUFFER) < 0)
    {
        perror("Ocurrio algun problema al recibir datos del cliente");
        syslog(LOG_INFO,"Ocurrio algun problema al recibir datos del cliente");
        exit(EXIT_FAILURE);
    }
    //syslog(LOG_INFO,"El cliente nos envio el siguiente mensaje: \n %s \n", leer_mensaje);
    syslog(LOG_INFO,"El cliente nos envio el siguiente mensaje: \n %s \n", leer_mensaje);

    if (write(cliente_sockfd, &mi_pid, sizeof(int)) < 0)
    {
        perror("Ocurrio un problema en el envio de un mensaje al cliente");
        syslog(LOG_INFO,"Ocurrio un problema en el envio de un mensaje al cliente");
        exit(EXIT_FAILURE);
    }
    if (read(cliente_sockfd, leer_mensaje, TAM_BUFFER) < 0)
    {
        perror("Ocurrio algun problema al recibir datos del cliente");
        syslog(LOG_INFO,"Ocurrio algun problema al recibir datos del cliente");
        exit(EXIT_FAILURE);
    }
    //syslog(LOG_INFO,"El cliente nos envio el siguiente mensaje: \n %s \n", leer_mensaje);
    syslog(LOG_INFO,"El cliente nos envio el siguiente mensaje: \n %s \n", leer_mensaje);
    //syslog(LOG_INFO,"Enviamos datos GPS \n %s \n", leer_mensaje);
    syslog(LOG_INFO,"Enviamos datos GPS \n %s \n", leer_mensaje);
    if (write(cliente_sockfd, &dato, sizeof(GPGGA)) < 0)
    {
        perror("Ocurrio un problema en el envio de GPGGA al cliente");
        syslog(LOG_INFO,"Ocurrio un problema en el envio de GPGGA al cliente");
        exit(EXIT_FAILURE);
    }
    close(cliente_sockfd);    
    exit(0);
}