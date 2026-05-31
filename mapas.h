// Declaración de los mapas de cada nivel.

#ifndef MAPAS_H
#define MAPAS_H

#include <stdio.h>
#define FILAS 60
#define COLUMNAS 60

/*
Matriz  ASCII   Representa
4       219     pared
0       32      camino libre
1       80      jugador
2       36      moneda
3       190     llave
5       186     puerta
6       176     salida
*/

// Cambiamos 'int' por 'char' para que coincida con juego.h y optimice NASM
// Agregamos 'extern'. Esto le dice a todos los archivos .c: 
// "El mapa existe, mide 60x60 y es tipo char, pero no lo crees aquí".
extern char mapa_nivel1[FILAS][COLUMNAS];
#endif