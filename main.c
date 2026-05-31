// Función principal, menú inicial y control general del juego.
#include <stdio.h>
#include <stdlib.h>
#include "juego.h"

int main () {
    int total_celdas = FILAS * COLUMNAS;
    char buscar_moneda = 2;

    // Calculamos el total de monedas del nivel usando NASM
    int monedas_encontradas = contar_caracteres_del_mapa((char *)mapa_nivel1, total_celdas, buscar_moneda);

    //Llamamos a la funcion de C que calcula e imprime la ventana visible
    imprimir_mapa();

    printf("Monedas detectadas en el Nivel 1 por NASM: %d\n", monedas_encontradas);
    printf("Posicion del jugador: (%d, %d)\n", jugador_x, jugador_y);
    return 0;
}
