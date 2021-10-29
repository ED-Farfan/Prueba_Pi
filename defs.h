#ifndef DEFS_H //Si no esta definida la constante DEFS_H compilalo
    #define DEFS_H //define la constante DEFS_H compilalo
    #define BUFFER 100 //Lectura del archivo
    #define TAM_BUFFER 		100 //Envio y lectura de datos por socket
    #define EVER 1              //Siempre 1   
    #define PUERTO 5000 //Definimos puerto
    typedef struct GPGGA
    {
        float hora;
        float latitud;
        char N_or_S;
        float longitud;
        char E_or_W;
    } GPGGA;
#endif // Cerramos el if
