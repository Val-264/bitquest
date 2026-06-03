// Función principal, menú inicial y control general del juego.
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "juego.h"

int main () {
    //1. INICIALIZACION DEL JUEGO
    int total_celdas = FILAS * COLUMNAS;
    char buscar_moneda = 'M';

    // Calculamos el total de monedas del nivel usando NASM
    int monedas_totales = contar_caracteres_del_mapa((char *)mapa_nivel1, total_celdas, buscar_moneda);

    //Estado del juego 
    int monedas_recolectadas = 0;
    int tiene_llave = 0;
    int niveles_completados = 0;

    //2. BUCLE PRINCIPAL DEL JUEGO (Game Loop)
    char tecla = ' ';
    int pasos = 0;
    while(tecla != 'q' && tecla != 'Q'){

        //Llamamos a la funcion de C que calcula e imprime la ventana visible
        imprimir_mapa();

        printf("\nMonedas en este nivel: %d\n", monedas_totales);
        printf("Pasos realizados: %d\n", pasos);
        printf("Posicion del jugador: (%d, %d)\n", jugador_x, jugador_y);
        printf("Controles: W (Arriba), A (Izquierda), S (Abajo), D (Derecha) | Q (Salir)\n");

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
            int movimiento_valido = 0;

            // Verificar límites de la matriz
            if(proximo_x >= 0 && proximo_x < FILAS && proximo_y >= 0 && proximo_y < COLUMNAS){
                char destino = mapa_nivel1[proximo_x][proximo_y];

                // Si es pared, el movimiento no es válido inmediatamente
                if(destino != '#'){
                    printf("DEBUG destino='%c' en (%d,%d)\n", destino, proximo_x, proximo_y);
                    movimiento_valido = validar_movimiento((char *)mapa_nivel1, COLUMNAS, proximo_x, proximo_y);

                    // Si es puerta y no tenemos llave, bloquear el paso
                    if(movimiento_valido
                       && detectar_objeto((char *)mapa_nivel1, COLUMNAS, proximo_x, proximo_y, 'D')
                       && !tiene_llave){
                        movimiento_valido = 0;
                    }
                }
            }

            if(movimiento_valido){
                char destino = mapa_nivel1[proximo_x][proximo_y];

                if(destino == 'M'){
                    monedas_recolectadas++;
                    monedas_totales = contar_caracteres_del_mapa((char *)mapa_nivel1, total_celdas, buscar_moneda);
                }

                if(destino == 'K'){
                    tiene_llave = 1;
                }

                if(destino == 'D' && tiene_llave){
                    mapa_nivel1[proximo_x][proximo_y] = '.';
                }

                mapa_nivel1[jugador_x][jugador_y] = '.';
                jugador_x = proximo_x;
                jugador_y = proximo_y;
                mapa_nivel1[jugador_x][jugador_y] = 'P';
                pasos++;

                if(destino == 'E'){
                    niveles_completados++;
                    int puntaje_parcial = calcular_puntaje(monedas_recolectadas, pasos, niveles_completados);
                    printf("\nNivel completado! Puntaje parcial: %d\n", puntaje_parcial);
                    break;
                }
            }
        }
    }
    
    int puntaje_final = calcular_puntaje(monedas_recolectadas, pasos, niveles_completados);
    printf("\nPuntaje final: %d\n", puntaje_final);
    printf("\nGracias por jugar BitQuest\n");
    return 0;
}
