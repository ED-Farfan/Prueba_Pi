#ifndef UART_H //Si no esta definida la constante CADENAS_H compilalo
    #define UART_H //define la constante CADENAS_H compilalo
    #include <termios.h>
    void guardaDatos(unsigned char datos[]);
    int config_serial(char *dispositivo_serial, speed_t baudios);
    int Lectura_UART();
#endif // Cerramos el if