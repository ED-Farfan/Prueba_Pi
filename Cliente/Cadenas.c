/*
* @brief: Funciones utilizadas para cadenas.
* @Author: Farfan Sanchez Erick David
* @Date: 12-Octubre-2021
*/
#include <stdio.h>
#include <stdlib.h>
#include "../defs.h"
int tamanio_cadena(char cad[]){
    if(cad != NULL){
        int i = 0;
        while(cad[i]!='\0'){
            i++;
        }
        return i;
    }else{
        return 0;
    }
}
int Contar_Caracteres_desde_hasta(char texto[],int ap,char limite){
    if(texto == NULL){
        return -1;
    }else{
        int tam = tamanio_cadena(texto);
        if(ap >= tam){
            return -2;
        }
        else
        {
            int i = ap;
            while (texto[i]!='\0' && texto[i]!= limite)
            {
                i++;
            }
            return i;
        }        
    }
}
int Copiar_Cadena_Desde_Hasta(char origen[], char destino[],int desde, int hasta){
    register int y = 0;
    for (register int i = desde; i < hasta ; i++)
    {
        destino[y] = origen[i];
        y++;
    }
    destino[y+1]='\0';
    return 1;    
}
char *extraer_datos_de_cadena(char texto[],int num_separador, char separador){
    
    int nnum_separador = 0;
    register int i = 0;
    int ap = 0, hasta=0;
    int tam = tamanio_cadena(texto);
    while (nnum_separador < num_separador && i < tam)
    {
        if(texto[i]==separador){
            nnum_separador ++;
        }
        i++;
    }
    if(i == tam){
        return NULL;
    }
    ap = i;
    hasta = Contar_Caracteres_desde_hasta(texto,ap,separador);
//    printf("\nDesde: %i [%c], hasta: %i[%c]\n",ap,texto[ap],hasta,texto[hasta]);
    char *nuevo=(char*)malloc(hasta-ap+1);
    nuevo[hasta-ap]='\0';
    Copiar_Cadena_Desde_Hasta(texto, nuevo,ap, hasta);
  //  printf("\nSe copeo: %s\n",nuevo);
    return nuevo;
}
int Coincide(char comparar[],char con[]){
    if( comparar != NULL && con != NULL){
        int tam_comparar = tamanio_cadena(comparar);
        int tam_con = tamanio_cadena(con);
        if (tam_comparar>tam_con)
        {
            return 0;
        }        
        for (register int i = 0; i < tam_comparar; i++)
        {
            if (comparar[i]!=con[i])
            {
                return 0;
            }            
        }
        return 1;
    }else{
        return -1;
    }
}
int Llenado_GPGGA(char cadena[],GPGGA *apt){
    char *dato =extraer_datos_de_cadena(cadena,1, ',');
    
    apt->hora=atof(dato);
    free(dato);
    
    dato =extraer_datos_de_cadena(cadena,2, ',');
    apt->latitud=atof(dato);
    free(dato);
    
    dato =extraer_datos_de_cadena(cadena,3, ',');
    apt->N_or_S = dato[0];   
    free(dato);
    
    dato =extraer_datos_de_cadena(cadena,4, ',');
    apt->longitud=atof(dato);
    free(dato);
    
    dato =extraer_datos_de_cadena(cadena,5, ',');
    apt->E_or_W=dato[0];
    free(dato);    
    return 1;
}
void ver_info(GPGGA x){
    printf("\n UTC de la posición: %f",x.hora);
    printf("\n Latitud: %f",x.latitud);
    printf("\n N o S: %c",x.N_or_S);
    printf("\n Longitud: %f",x.longitud);
    printf("\n E o W: %c\n",x.E_or_W);
}