// Declaración de los mapas de cada nivel

#ifndef MAPAS_H
#define MAPAS_H

#include <stdio.h>
#define FILAS 60
#define COLUMNAS 60

// El mapa se declara extern aquí para que todos los .c vean la misma matriz.
// La definición real (inicialización) debe ir en un solo archivo .c, no en el header,
// porque de lo contrario cada .c tendría su propia copia separada del mapa.
extern char mapa_nivel1[FILAS][COLUMNAS];
#endif