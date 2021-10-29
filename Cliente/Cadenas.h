#ifndef CADENAS_H //Si no esta definida la constante CADENAS_H compilalo
    #define CADENAS_H //define la constante CADENAS_H compilalo
    #include "../defs.h"
    int tamanio_cadena(char cad[]);
    int Contar_Caracteres_desde_hasta(char texto[],int ap,char limite);
    int Copiar_Cadena_Desde_Hasta(char origen[], char destino[],int desde, int hasta);
    char *extraer_datos_de_cadena(char texto[],int num_separador, char separador);
    int Coincide(char comparar[],char con[]);
    int Llenado_GPGGA(char cadena[],GPGGA *apt);
    void ver_info(GPGGA x);
#endif // Cerramos el if