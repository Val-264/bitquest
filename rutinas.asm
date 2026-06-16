; Funciones implementadas en NASM.
bits 64

global contar_caracteres_del_mapa
global validar_movimiento
global calcular_puntaje
global detectar_objeto
global contar_celdas_libres

section .text

; =========================================================================
; FUNCION 1: contar_caracteres_del_mapa
; =========================================================================
; Propósito: Recorre toda la matriz en memoria y cuenta cuántas veces
;            aparece un carácter específico (por ejemplo 'M' para monedas).
;
;   RCX = char* matriz       -> dirección base del arreglo plano en memoria
;   RDX = int tot_celdas     -> total de celdas (FILAS * COLUMNAS = 3600)
;   R8B = char caracter      -> el carácter que queremos contar
;   Retorna en EAX           -> cantidad de coincidencias encontradas
; =========================================================================
contar_caracteres_del_mapa:
    xor eax, eax                
    test rdx, rdx             ; Revisar si tot_celdas <= 0
    jle .fin                  ; Si tot_celdas <= 0, salir

.bucle:
    dec rdx                   ; Reducir el índice (recorrer de 3599 a 0)
    mov r9b, [rcx + rdx]      ; Leer el byte en la posición actual del arreglo
                              ; rcx = dirección base, rdx = índice actual
                              ; r9b = temporal para no pisar eax
    cmp r9b, r8b              ; ¿El carácter leído es igual al que buscamos?
    jne .no_es_igual          ; Si no coincide, saltar sin sumar
    inc eax                   ; Si coincide, sumar 1 al contador

.no_es_igual:
    cmp rdx, 0                ; Revisar que ya se hayan recorrido todas las celdas
    jg .bucle                

.fin:
    ret                       


; =========================================================================
; FUNCION 2: validar_movimiento
; =========================================================================
; Propósito: Verifica si la celda a la que el jugador quiere moverse
;            es una celda válida (no es pared '#').
;            Calcula el índice plano con: (fila * columnas) + columna
;            y lee el carácter en esa posición del mapa.
;
;   RCX  = char* matriz      -> dirección base del mapa
;   RDX  = int tot_columnas  -> número de columnas (60)
;   R8D  = int x_siguiente   -> fila a la que el jugador quiere ir
;   R9D  = int y_siguiente   -> columna a la que el jugador quiere ir
;   Retorna en EAX: 1 = movimiento válido, 0 = bloqueado
; =========================================================================
validar_movimiento:
    xor eax, eax              ; EAX = 0 (asumimos bloqueado por defecto)

    ; Verificamos que las coordenadas estén dentro de los límites del mapa
    cmp r8d, 0
    jl .no_valido             ; Si fila < 0, inválido
    cmp r8d, 59
    jg .no_valido             ; Si fila > 59, inválido
    cmp r9d, 0
    jl .no_valido             ; Si columna < 0, inválido
    cmp r9d, 59
    jg .no_valido             ; Si columna > 59, inválido

    ; Calculamos el índice plano: (fila * columnas) + columna
    ; Guardamos columnas en r10d antes de que edx se use en la multiplicación
    mov r10d, edx             ; r10d = columnas (60)
    mov eax, r8d              ; eax = fila
    imul eax, r10d            ; eax = fila * columnas
    add eax, r9d              ; eax = (fila * columnas) + columna

    ; Leemos el carácter en esa posición del mapa
    movzx eax, byte [rcx + rax]  ; eax = carácter en mapa[x][y]
                                  ; movzx extiende a 32 bits sin signo

    ; Verificamos si es pared
    cmp al, '#'
    je .no_valido             ; Si es '#', el movimiento está bloqueado

    mov eax, 1                ; Si no es pared, el movimiento es válido
    ret

.no_valido:
    xor eax, eax              ; Retornar 0 = bloqueado
    ret


; =========================================================================
; FUNCION 3: calcular_puntaje
; =========================================================================
; Propósito: Calcula el puntaje del jugador aplicando la siguiente fórmula:
;
;   puntaje = (monedas * 500) + (niveles * 2000) - pasos
;
;   - Cada moneda recolectada vale 150 puntos (recompensa la exploración)
;   - Cada nivel completado vale 1000 puntos (recompensa el progreso)
;   - Cada paso resta 1 punto (penaliza caminos largos o perderse)
;   - El resultado mínimo es 0 (nunca devuelve negativo)
;
;   RCX = int monedas_recolectadas
;   RDX = int tot_pasos
;   R8  = int niveles_ok
;   Retorna en EAX: puntaje calculado
; =========================================================================
calcular_puntaje:
    ; Paso 1: monedas * 500
    mov eax, ecx              ; eax = monedas
    imul eax, 500             ; eax = monedas * 500

    ; Paso 2: niveles * 2000
    mov ecx, eax              ; guardamos monedas*500 en ecx temporalmente
    mov eax, r8d              ; eax = niveles completados
    imul eax, 2000            ; eax = niveles * 2000

    ; Paso 3: sumamos ambas recompensas positivas
    add eax, ecx              ; eax = (monedas*500) + (niveles*2000)

    ; Paso 4: restamos la penalización por pasos (-1 punto por cada paso)
    sub eax, edx              ; eax = total - pasos

    ; Paso 5: nos aseguramos de no devolver negativo
    cmp eax, 0
    jge .fin_calc             ; Si eax >= 0, está bien
    xor eax, eax              ; Si es negativo, lo forzamos a 0

.fin_calc:
    ret                       ; Devolvemos el puntaje en EAX


; =========================================================================
; FUNCION 4: detectar_objeto
; =========================================================================
; Propósito: Revisa si en una celda específica del mapa existe
;            un carácter determinado (moneda, llave, puerta, salida).
;            Funciona igual que validar_movimiento pero en lugar de
;            verificar si es pared, compara con el carácter recibido.
;
;   RCX       = char* matriz      -> dirección base del mapa
;   RDX       = int columnas      -> número de columnas (60)
;   R8D       = int revisar_x     -> fila a revisar
;   R9D       = int revisar_y     -> columna a revisar
;   [rsp+40]  = char carac_revisar -> quinto parámetro, va en la pila
;   Retorna en EAX: 1 = objeto encontrado, 0 = no encontrado
; =========================================================================
detectar_objeto:
    xor eax, eax              

    ; Verificar límites igual que en validar_movimiento
    cmp r8d, 0
    jl .fin_det
    cmp r8d, 59
    jg .fin_det
    cmp r9d, 0
    jl .fin_det
    cmp r9d, 59
    jg .fin_det

    ; Calcular índice plano: (fila * columnas) + columna
    mov r10d, edx             ; r10d = columnas
    mov eax, r8d              ; eax = fila
    imul eax, r10d            ; eax = fila * columnas
    add eax, r9d              ; eax = índice final

    ; Leer el carácter en esa posición
    movzx eax, byte [rcx + rax]

    ; Leer el quinto parámetro desde la pila
    mov dl, byte [rsp + 40]   ; dl = carácter que se quiere detectar

    ; Comparar el carácter del mapa con el que se busca
    cmp al, dl
    jne .no_coincide          ; Si no coinciden, retornar 0
    mov eax, 1                ; Si coinciden, retornar 1
    ret

.no_coincide:
    xor eax, eax
    ret

.fin_det:
    xor eax, eax
    ret


; =========================================================================
; FUNCION 5: contar_celdas_libres
; =========================================================================
; Propósito: Recorre toda la matriz y cuenta cuántas celdas son
;            camino libre ('.'), es decir, celdas transitables vacías.
;            Sirve para mostrar información del nivel al iniciarlo.
;
;   RCX = char* matriz       -> dirección base del mapa
;   RDX = int tot_celdas     -> total de celdas (3600)
;   Retorna en EAX           -> cantidad de celdas libres
;
; =========================================================================
contar_celdas_libres:
    xor eax, eax             
    test rdx, rdx
    jle .fin_libres           ; Si tot_celdas <= 0, salir

.libre_bucle:
    dec rdx                   ; Reducir índice (recorrer de 3599 a 0)
    mov r9b, [rcx + rdx]      ; Leer carácter en posición actual
    cmp r9b, '.'              ; ¿Es celda libre?
    jne .no_incremento        ; Si no es '.', no se cuenta
    inc eax                   ; Si es '.', se suma 1 al contador

.no_incremento:
    cmp rdx, 0                ; ¿Terminar de recorrer todo?
    jg .libre_bucle           ; Si rdx > 0, seguir

.fin_libres:
    ret                       ; Devolver el total en EAX