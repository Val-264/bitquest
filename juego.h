// Prototipos de funciones y constantes generales

#ifndef JUEGO_H
#define JUEGO_H

#include "mapas.h"

// ==============================================================
//                       FUNCIONES NASM 
// ==============================================================

/*
*@brief Cuenta cuántas veces aparece un determinado caracter en el mapa 
*@param Direccion inicial del mapa
*@param Número total de celdas
*@param El carácter que se desea contar
*@return Cantidad de veces que aparece determinado caracter
*/
int contar_caracteres_del_mapa(char *matriz, int tot_celdas, char caracter); 

/*
*@brief Validar si una posición del mapa puede ser ocupada por el jugador
*@param Direccuón inicial del mapa 
*@param Número de columnas del mapa 
*@param La nueva fila propuesta por el jugador (coordenada del jugador en x)
*@param La nueva columna propuesta por el jugador (coordenada del jugador en y)
*@return Movimiento válido = 1, movimiento bloqueado =
*/
int validar_movimiento(char *matriz,int tot_columnas, int x_siguiente, int y_siguiente);

/*
*@brief Calcular puntaje 
*@param Monedas recolectadas 
*@param Pasos realizados 
*@param Niveles completados 
*@return Puntaje del jugador
*/
int calcular_puntaje(int monedas_recolectadas, int tot_pasos, int niveles_ok);

/*
*@brief Detectar si en una posición específica del
        mapa existe un determinado objeto
*@param Dirección inicial de mapa 
*@param Número de columnas del mapa
*@param Fila que se desea revisar (coordenada en x)
*@param Columna que se desea revisar (coordenada en y)
*@param Caracter del objeto a revisar 
*@return Objeto encontrado = 1, no encontrado = 0
*/
int detectar_objeto(char *matriz, int columnas, int revisar_x, int revisar_y, char carac_revisar);

/*
*@brief Contar celdas libres
*@param Dirección inicial del mapa 
*@param Número total de celdas 
*@return Total de celdas libres
*/
int contar_celdas_libres(char *matriz, int tot_celdas);

extern char (*mapas[3])[COLUMNAS];

//Variables de posicion del jugador y funcion de renderizado
extern int jugador_x;
extern int jugador_y;
void imprimir_mapa();

// Nivel activo: 0 = nivel1, 1 = nivel2, 2 = nivel3
// Se usa en imprimir_mapa() para saber qué mapa dibujar
extern int nivel_actual;

// Cambia el estado interno al nivel indicado (1, 2 o 3)
// Reposiciona al jugador en la celda 'P' del nuevo mapa
void cambiar_nivel(int nivel);

// Imprime el resumen al terminar un nivel
void mostrar_resumen_nivel(int nivel, int monedas_rec, int monedas_tot, int pasos, int puntaje_parcial);

// Imprime el resumen final al terminar los 3 niveles
void mostrar_resumen_final(int monedas_rec_total, int monedas_tot_total,int pasos_totales, int niveles_completados, int puntaje_final);

#endif 