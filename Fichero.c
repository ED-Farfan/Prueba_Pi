/*
* @brief: Funcion que busca un cadena en un txt y apartir de ella nos regresa toda la informacion encntrada hasta un salto de linea.
* @Author: Farfan Sanchez Erick David
* @Date: 12-Octubre-2021
*/
#include <syslog.h>
#include <stdio.h>
#include <stdlib.h>
#include "Cadenas.h"
#include "defs.h"
char*Leer_Fichero(char ruta[],char buscar[]){
    FILE *f = fopen(ruta,"r");
    if (f==NULL)
    {
        syslog(LOG_INFO,"\nError al abrir:%s\n",ruta);
        return NULL;
    }
    else{
        char *texto = (char*)malloc(BUFFER);
        texto[BUFFER-1]= '\0';
        int salir = 0;
        while (feof(f)!=1 && salir != 1) 
        {
            fgets (texto, BUFFER-1, f);  
            //syslog(LOG_INFO,"\nLeyendo: %s\n",texto);
            salir = Coincide(buscar,texto);
        }    
        fclose(f);
        if(salir){
            //syslog(LOG_INFO,"\nRetorno: %s\n",texto);
            return texto;
        }else{
            return NULL;
        }
        
    }
}