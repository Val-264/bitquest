; Funciones implementadas en NASM.
bits 64

global contar_caracteres_del_mapa

section .text

;int contar_caracteres_del_mapa(char *matriz, int tot_celdas, char caracter);
;Parametros
;RCX = Direccion base de la metriz (char *matriz)
;RDX = Numero total de celdas (int tot_celdas = 3600)
;R8B = Caracter o numero a buscar (char caracter)

contar_caracteres_del_mapa:
    xor eax, eax    ;Limpiamos eax, donde se acumulan las coincidencias
    test rdx, rdx    ;Verificamos si el total de celdas es <=0
    jle .fin        ;Si lo es terminamos inmediatamente

.bucle:
    dec rdx         ;Decrementamos rdx para usarlo como indice inverso de 3599 a 0
    mov r9b, [rcx + rdx] ;Leemos el byte de la matriz en la posicion actual
    cmp r9b, r8b    ;Es igual al caracter que buscamos?
    jne .no_es_igual    ;Si no coincide saltamos al sig ciclo
    inc eax             ;Si coincide le sumamos 1 a eax

.no_es_igual:
    cmp rdx, 0      ;Ya terminamos de revisar toda la celda?
    jg .bucle       ;Si rdx > 0 repetimos para la sig celda

.fin:
    ret             ;El resultado de la funcion se devuelve en eax