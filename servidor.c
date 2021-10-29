/*
* @brief: Inicializa un servidor, posteriormente crea un hilo para leer las coordenadas despues cada vez que un cliente se conecte va a crear un proceso para que atienda al cliente.
* @Author: Farfan Sanchez Erick David
* @Date: 12-Octubre-2021
*/
#include "defs.h"
#include "hilo.h"
#include "procesos.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "signal.h"
#include <sys/types.h>
#include <signal.h>
#include <syslog.h>


#define COLA_CLIENTES 5 //Tamaño de la cola de espera para clientes
extern GPGGA dato;
int sockfd;
int p_pid;
int frenar = 0;
int iniServidor()
{
    struct sockaddr_in direccion_servidor; //Estructura de la familia AF_INET, que almacena direccion
    int sockfd;
    /*
 *  AF_INET - Protocolo de internet IPV4
 *  htons - El ordenamiento de bytes en la red es siempre big-endian, por lo que
 *  en arquitecturas little-endian se deben revertir los bytes
 *  INADDR_ANY - Se elige cualquier interfaz de entrada
 */
    // 0101 = 5 - Arquitectura little endian
    // 3210

    // 0101 = 10 - Arquitectura big endian
    // 0123
    memset(&direccion_servidor, 0, sizeof(direccion_servidor)); //se limpia la estructura con ceros
    direccion_servidor.sin_family = AF_INET;
    direccion_servidor.sin_port = htons(PUERTO);
    direccion_servidor.sin_addr.s_addr = INADDR_ANY;

    /*
 *  Creacion de las estructuras necesarias para el manejo de un socket
 *  SOCK_STREAM - Protocolo orientado a conexión
 */
    //printf("Creando Socket ....\n");
    printf( "Creando Socket ....\n");
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Ocurrio un problema en la creacion del socket");
        printf( "Ocurrio un problema en la creacion del socket");
        exit(EXIT_FAILURE);
    }
    /*
 *  bind - Se utiliza para unir un socket con una dirección de red determinada
 */
    //printf("Configurando socket ...\n");
    printf( "Configurando socket ...\n");
    if (bind(sockfd, (struct sockaddr *)&direccion_servidor, sizeof(direccion_servidor)) < 0)
    {
        perror("Ocurrio un problema al configurar el socket");
        printf( "Ocurrio un problema al configurar el socket");
        exit(EXIT_FAILURE);
    }
    /*
 *  listen - Marca al socket indicado por sockfd como un socket pasivo, esto es, como un socket
 *  que será usado para aceptar solicitudes de conexiones de entrada usando "accept"
 *  Habilita una cola asociada la socket para alojar peticiones de conector procedentes
 *  de los procesos clientes
 */
    //printf("Estableciendo la aceptacion de clientes...\n");
    printf( "Estableciendo la aceptacion de clientes...\n");
    if (listen(sockfd, COLA_CLIENTES) < 0)
    {
        perror("Ocurrio un problema al crear la cola de aceptar peticiones de los clientes");
        printf( "Ocurrio un problema al crear la cola de aceptar peticiones de los clientes");
        exit(EXIT_FAILURE);
    }
    return sockfd;
}
int Servidor()
{
    int cliente_sockfd;
    pid_t pid;
    p_pid = getpid();
    // Se abre un archivo log en modo de escritura.
    openlog( "Demonio_Servidor", LOG_NDELAY | LOG_PID, LOG_LOCAL0 );
    if( signal( SIGCHLD, ISRsw ) == SIG_ERR )
	{
		perror("Error en la señal SIGCHLD\n");
        printf( "Error en la señal SIGCHLD\n");
		exit(EXIT_FAILURE); 
	}
    if( signal( SIGINT, ISRsw ) == SIG_ERR )
	{
		perror("Error en la señal SIGINT\n");
        printf( "Error en la señal SIGINT\n");
		exit(EXIT_FAILURE); 
	}

    Hilo(&dato); //Creamos un hilo para leer el archivo txt

    //Creacion del servior
    sockfd = iniServidor();
   
    
    for (; EVER;)    
    {
        
        //printf("\nEn espera de peticiones de conexión ...\n");
        printf( "\nEn espera de peticiones de conexión ...\n");
        if ((cliente_sockfd = accept(sockfd, NULL, NULL)) < 0)
        {
            perror("Ocurrio algun problema al atender a un cliente");
            printf( "Ocurrio algun problema al atender a un cliente");
            exit(EXIT_FAILURE);
        }
        pid = fork();
        if (!pid) //El Proceso hijo atiende al cliente
        {
            atiendeCliente(cliente_sockfd);
        }
    }
    close (sockfd);
    sleep(30);
    return 0;
}