; Funciones implementadas en NASM.
bits 64

;Exportacion de las 5 funciones obligatorias para que C las reconozca
global contar_caracteres_del_mapa
global validar_movimiento
global calcular_puntaje
global detectar_objeto
global contar_celdas_libres

section .text

; =========================================================================
; FUNCION 1: Contar caracteres del mapa 
; =========================================================================
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

; =========================================================================
; TODO: FUNCION 2: Validar movimiento [cite: 140]
; RCX = char* matriz, RDX = columnas (60), R8D = proximo_x, R9D = proximo_y 
; Debe calcular el índice en el arreglo plano: (proximo_x * columnas) + proximo_y
; Retornar 1 si es caminable (0), retornar 0 si es pared (4) o está bloqueado
; =========================================================================
validar_movimiento:
    ; Integrar código aquí
    mov eax, 1 ; Retorno temporal para que permita avanzar las pruebas
    ret

; =========================================================================
; TODO: FUNCION 3: Calcular puntaje 
; RCX = monedas, RDX = pasos, R8 = niveles_completados 
; Aplicar fórmula matemática en ensamblador y regresar el entero en EAX
; =========================================================================
calcular_puntaje:
    ; Integrar código aquí
    xor eax, eax
    ret

; =========================================================================
; TODO: FUNCION 4: Detectar objeto en una celda 
; RCX = char* matriz, RDX = columnas, R8D = x, R9D = y, [rsp+40] = caracter a buscar
; Retornar 1 si el objeto coincide con la celda, 0 si no
; =========================================================================
detectar_objeto:
    ; Integrar código aquí
    xor eax, eax
    ret

; =========================================================================
; TODO: FUNCION 5: Contar celdas libres 
; RCX = char* matriz, RDX = total_celdas (3600) 
; Recorrer la matriz y contar cuántas celdas tienen el valor 0
; =========================================================================
contar_celdas_libres:
    ; Integrar código aquí
    xor eax, eax
    ret