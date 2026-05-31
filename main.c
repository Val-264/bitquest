// Función principal, menú inicial y control general del juego.
#include <stdio.h>
#include <stdlib.h>
#include "juego.h"

int main () {
    printf("=== BIENVENIDO A BITQUEST ===\n");

    int total_celdas = FILAS * COLUMNAS;

    char buscar_moneda = 2;

    int monedas_encontradas = contar_caracteres_del_mapa((char *)mapa_nivel1, total_celdas, buscar_moneda);

    printf("Monedas detectadas en el Nivel 1 por NASM: %d\n", monedas_encontradas);
    return 0;
}
