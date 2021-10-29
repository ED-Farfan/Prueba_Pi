/*
* @brief: Hilo que lee a UART (GPS)y lo almacena en un archivo para despues buscar dentro del el archivo para obtener los datos de geolocalizacion
* @Author: Farfan Sanchez Erick David
* @Date: 24-Octubre-2021
*/
#include <syslog.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <signal.h>
#include "defs.h"
#include "Fichero.h"
#include "Cadenas.h"
#include "signal.h"
#include "UART.h"
pthread_t hilo;
extern int frenar;

void *funHilo(void *arg)
{
    //syslog(LOG_INFO,"[TH_1:%ld]: Hola soy un hilo \n", pthread_self());
    syslog(LOG_INFO, "Hola soy un hilo \n");

    GPGGA *dato = (GPGGA *)arg;
    for (; EVER;)
    {
        if (frenar != 1)
        {
            if (dato != NULL)
            {
                ////syslog(LOG_INFO,"[Hilo] Inicio a leer archivo  \n", pthread_self());
                syslog(LOG_INFO, "[Hilo] Inicio a leer UART  \n");
                Lectura_UART();
                syslog(LOG_INFO, "[Hilo] Termine de leer UART  \n");
                syslog(LOG_INFO, "[Hilo] Inicio a leer archivo  \n");
                char *texto = Leer_Fichero("Datos/nmea.txt", "$GPGGA");
                Llenado_GPGGA(texto, dato);
                free(texto);
                syslog(LOG_INFO, "[Hilo] Termine de leer archivo  \n");
                //syslog(LOG_INFO,"[Hilo] Termine de leer archivo  \n");
                sleep(1);
            }
            else
            {
                //syslog(LOG_INFO,"[TH_1:%ld]: Termine hilo Con ERROR\n", pthread_self());
                syslog(LOG_INFO, "[Hilo] Termine hilo Con ERROR\n");
                pthread_exit(NULL);
            }
        }
        else
        {
            //syslog(LOG_INFO,"[Hilo] Termine  \n");
            syslog(LOG_INFO, "[Hilo] Termine Ejecucion\n");
            pthread_exit(dato);
        }
    }
}
void Hilo(GPGGA *dato)
{
    syslog(LOG_INFO, "\nCreo Hilo ...\n");
    pthread_create(&hilo, NULL, funHilo, (void *)dato);    
}
