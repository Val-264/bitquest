// Función principal, menú inicial y control general del juego.
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "juego.h"
/*
@ TODO quit no debe cerrar el programa es solo para salir del juego, devuelve al menu
@ TODO No se está mostrando el resumen final, arreglar
@ TODO el puntaje no se está mostrando, areglar función de mostrar puntaje
@ TODO areglar calculo depuntaje
@ TODO "el mensaje de Nivel iniciado X celdas libres en el mapa" se uestra en  la pantalla anterior al inico del juego, ponerlo en donde está el juego
@ TODO Hacer menú de inico
@ TODo Revisar la forma en que se pasa el mapa como argumento (posicion inicial)
@ TODO Rev .asm -> material de clase
*/

void mostrar_titulo()
{
    char titulo_bienvenida[20][26] = {
        {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '#', '#', '#', '#', '.', '.', '#', '#', '#', '.', '.', '#', '#', '#', '#', '#', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '#', '.', '.', '.', '#', '.', '.', '#', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '#', '#', '#', '#', '.', '.', '.', '#', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '#', '.', '.', '.', '#', '.', '.', '#', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '#', '#', '#', '#', '.', '.', '#', '#', '#', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '#', '#', '#', '.', '.', '#', '.', '.', '#', '.', '#', '#', '#', '#', '.', '.', '#', '#', '#', '.', '#', '#', '#', '#', '#'},
        {'#', '.', '.', '.', '#', '.', '#', '.', '.', '#', '.', '#', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '#', '.', '.'},
        {'#', '.', '.', '.', '#', '.', '#', '.', '.', '#', '.', '#', '#', '#', '.', '.', '.', '#', '#', '#', '.', '.', '.', '#', '.', '.'},
        {'#', '.', '.', '#', '#', '.', '#', '.', '.', '#', '.', '#', '.', '.', '.', '.', '.', '.', '.', '.', '#', '.', '.', '#', '.', '.'},
        {'.', '#', '#', '.', '#', '.', '.', '#', '#', '.', '.', '#', '#', '#', '#', '.', '.', '#', '#', '#', '.', '.', '.', '#', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'}

    };
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 26; j++)
        {

            // Miramos el valor numerico de la matriz y pintamos su caracter equivalente
            switch (titulo_bienvenida[i][j])
            {
            case '#':
                // Muros: Azul
                printf("\x1b[94m%c%c", 178, 177);
                break;
            case '.':
                // Camino libre: Espacio vacío doble
                printf("  ");
                break;
            }
        }
        
        // Al terminar la fila, reiniciamos el color por seguridad y saltamos de línea
        printf("\x1b[0m\n");
    }

    printf("\t\x1b[33mExplorador de matrices con C y NASM\n\n");
    printf("\x1b[0m\n");
    system("pause");
}

void mostrar_menu_inicio() {
    mostrar_titulo();
}

void controlar_juego()
{
    // INICIALIZACION DEL JUEGO
    int total_celdas = FILAS * COLUMNAS;
    char buscar_moneda = 'M';

    // ── Acumuladores globales del juego ──
    int monedas_globales_rec = 0; // monedas totales en todos los niveles
    int monedas_globales_tot = 0; // monedas disponibles en todos los niveles
    int pasos_globales = 0;
    int niveles_completados = 0;

    // Iteracion de los 3 niveles
    for (int nivel = 1; nivel <= 3; nivel++)
    {
        // Preparar el nivel: posicionar jugador en 'P' del nuevo mapa
        cambiar_nivel(nivel);

        // Obtener puntero al mapa activo (usa nivel_actual que seteó cambiar_nivel)
        char (*mapa_activo)[COLUMNAS] = mapas[nivel_actual];

        // Contar monedas del nivel usando NASM
        int monedas_totales_nivel = contar_caracteres_del_mapa((char *)mapa_activo, total_celdas, buscar_moneda);

        // Mostrar celdas libres al iniciar nivel
        int celdas_libres = contar_celdas_libres((char *)mapa_activo, total_celdas);
        printf("Nivel %d iniciado. Celdas libres en el mapa: %d\n", nivel, celdas_libres);
        _getch();

        // ── Estado del nivel actual ──
        int monedas_rec_nivel = 0;
        int tiene_llave = 0;
        int pasos_nivel = 0;
        int nivel_terminado = 0;

        char tecla = ' ';

        // ── Game loop de este nivel ──
        while (tecla != 'q' && tecla != 'Q' && !nivel_terminado)
        {

            imprimir_mapa();

            printf("Nivel: %d | Monedas: %d/%d | Llave: %s | Pasos: %d\n", nivel, monedas_rec_nivel, monedas_totales_nivel, tiene_llave ? "Si" : "No", pasos_nivel);
            printf("Posicion: (%d, %d)\n", jugador_x, jugador_y);
            printf("Controles: W/A/S/D Mover | Q Salir\n");

            tecla = _getch();

            int proximo_x = jugador_x;
            int proximo_y = jugador_y;
            int intento_movimiento = 0;

            switch (tecla)
            {
            case 'w':
            case 'W':
                proximo_x--;
                intento_movimiento = 1;
                break;

            case 's':
            case 'S':
                proximo_x++;
                intento_movimiento = 1;
                break;

            case 'a':
            case 'A':
                proximo_y--;
                intento_movimiento = 1;
                break;

            case 'd':
            case 'D':
                proximo_y++;
                intento_movimiento = 1;
                break;
            }

            if (intento_movimiento)
            {
                int movimiento_valido = 0;

                // Verificar límites antes de llamar a NASM
                if (proximo_x >= 0 && proximo_x < FILAS &&
                    proximo_y >= 0 && proximo_y < COLUMNAS)
                {

                    char destino = mapa_activo[proximo_x][proximo_y];

                    if (destino != '#')
                    {
                        // Validar con NASM
                        movimiento_valido = validar_movimiento((char *)mapa_activo, COLUMNAS, proximo_x, proximo_y);

                        // Bloquear puerta si no tiene llave
                        // Usamos NASM para detectar el objeto 'D'
                        if (movimiento_valido && detectar_objeto((char *)mapa_activo, COLUMNAS, proximo_x, proximo_y, 'D') && !tiene_llave)
                        {
                            movimiento_valido = 0;
                        }
                    }
                }

                if (movimiento_valido)
                {
                    char destino = mapa_activo[proximo_x][proximo_y];

                    // Recolectar moneda
                    if (destino == 'M')
                    {
                        monedas_rec_nivel++;
                        mapa_activo[proximo_x][proximo_y] = '.';
                    }

                    // Recoger llave
                    if (destino == 'K')
                    {
                        tiene_llave = 1;
                        mapa_activo[proximo_x][proximo_y] = '.';
                    }

                    // Abrir puerta con llave
                    if (destino == 'D' && tiene_llave)
                    {
                        mapa_activo[proximo_x][proximo_y] = '.';
                    }

                    // Mover jugador en el mapa
                    mapa_activo[jugador_x][jugador_y] = '.';
                    jugador_x = proximo_x;
                    jugador_y = proximo_y;
                    mapa_activo[jugador_x][jugador_y] = 'P';
                    pasos_nivel++;

                    // Verificar si llegó a la salida
                    if (destino == 'E')
                    {
                        niveles_completados++;
                        pasos_globales += pasos_nivel;
                        monedas_globales_rec += monedas_rec_nivel;
                        monedas_globales_tot += monedas_totales_nivel;

                        // Calcular puntaje parcial con NASM
                        int puntaje_parcial = calcular_puntaje(monedas_globales_rec, pasos_globales, niveles_completados);

                        // Mostrar resumen del nivel terminado
                        mostrar_resumen_nivel(nivel, monedas_rec_nivel, monedas_totales_nivel, pasos_nivel, puntaje_parcial);
                        nivel_terminado = 1;
                    }
                }
            }
        } // fin game loop del nivel

        // Si el jugador salió con Q, terminamos todo
        if (tecla == 'q' || tecla == 'Q')
            break;

    } // fin loop de todos los niveles

    // ── Resumen final ──
    int puntaje_final = calcular_puntaje(monedas_globales_rec, pasos_globales, niveles_completados);

    mostrar_resumen_final(monedas_globales_rec, monedas_globales_tot, pasos_globales, niveles_completados, puntaje_final);
}

int main()
{
    mostrar_menu_inicio();
    controlar_juego();

    return 0;
}
