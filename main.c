// Función principal, menú inicial y control general del juego.
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "juego.h"

int main () {
    //1. INICIALIZACION DEL JUEGO
    int total_celdas = FILAS * COLUMNAS;
    char buscar_moneda = 2;

    // Calculamos el total de monedas del nivel usando NASM
    int monedas_totales = contar_caracteres_del_mapa((char *)mapa_nivel1, total_celdas, buscar_moneda);

    // TODO: Inicializar contadores globales del jugador (pasos = 0, monedas_recolectadas = 0, tiene_llave = 0)

    //2. BUCLE PRINCIPAL DEL JUEGO (Game Loop)
    char tecla = ' ';
    int pasos = 0;
    while(tecla != 'q' && tecla != 'Q'){

        //Llamamos a la funcion de C que calcula e imprime la ventana visible
        imprimir_mapa();

        printf("\nMonedas en este nivel: %d\n", monedas_totales);
        printf("Pasos realizados: %d\n", pasos);
        printf("Posicion del jugador: (%d, %d)\n", jugador_x, jugador_y);
        printf("Controles: W (Arriba), A (Izquierda), S (Abajo), D (Derecha) | Q (Salir)\n", jugador_x, jugador_y);

        //Capturamos la entrada del teclado de forma sincrona
        tecla = _getch();

        //Guardamos las coordenadas a donde el jugador desea ir
        int proximo_x = jugador_x;
        int proximo_y = jugador_y;
        int intento_movimiento = 0;

        //Evaluamos la tecla presionada
        switch(tecla){
            case 'w': case 'W':
            proximo_x = jugador_x - 1;
            intento_movimiento = 1;
            break;

            case 's': case 'S':
            proximo_x = jugador_x + 1;
            intento_movimiento = 1;
            break;

            case 'a': case 'A':
            proximo_y = jugador_y - 1;
            intento_movimiento = 1;
            break;

            case 'd': case 'D':
            proximo_y = jugador_y + 1;
            intento_movimiento = 1;
            break;
        }

        if(intento_movimiento){
            // TODO: Aquí llamaremos formalmente a validar_movimiento en NASM 
            // De momento, dejamos un validador temporal en C para probar la cámara:

            if(proximo_x >= 0 && proximo_x < FILAS && proximo_y >= 0 && proximo_y < COLUMNAS){
                // 1. Borramos al jugador de su posición vieja en la matriz gigante (se vuelve espacio libre)
                mapa_nivel1[jugador_x][jugador_y] = 0;
                
                // 2. Actualizamos las coordenadas globales a la nueva ubicación
                jugador_x = proximo_x;
                jugador_y = proximo_y;
                
                // 3. Colocamos el valor del jugador (1) en la nueva celda de la matriz
                mapa_nivel1[jugador_x][jugador_y] = 1;
                
                // 4. Incrementamos el contador de pasos de la sesión [cite: 157, 194]
                pasos++;
            }
        }

        // TODO: Validar el movimiento llamando a la función obligatoria de NASM: 
        // int movimiento_valido = validar_movimiento((char *)mapa_nivel1, COLUMNAS, proximo_x, proximo_y);

        // TODO: Si el movimiento es válido (regresa 1), actualizar la posición real:
        // Anterior posición en la matriz se vuelve camino libre (0). Nueva posición se vuelve jugador (1).
        // jugador_x = proximo_x; jugador_y = proximo_y;

        // TODO: REVISIÓN DE EVENTOS EN LA NUEVA CELDA USANDO LA FUNCIÓN 'detectar_objeto' de NASM:
        // - Si detecta moneda (2): Incrementar monedas_recolectadas del jugador.
        // - Si detecta llave (3): Cambiar bandera 'tiene_llave' a 1.
        // - Si detecta puerta (5): Validar si 'tiene_llave == 1' para dejar pasar, si no, bloquear.
        // - Si detecta salida (6): Terminar nivel actual, mostrar resumen y cargar Nivel 2.
    }
    // 3. PANTALLA FINAL / RESUMEN
    // TODO: Calcular puntaje final usando la rutina obligatoria en NASM 'calcular_puntaje' 
    // TODO: Mostrar estadísticas totales del juego

    printf("\nGracias por jugar BitQuest\n");
    return 0;
}
