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
; FUNCION 2: Validar movimiento
; RCX = char* matriz, RDX = columnas (60), R8D = proximo_x, R9D = proximo_y 
; Debe calcular el índice en el arreglo plano: (proximo_x * columnas) + proximo_y
; Retornar 1 si es caminable '.', retornar 0 si es pared '#' o está bloqueado
; =========================================================================
validar_movimiento:
    xor eax, eax
    
    cmp r8d, 0
    jl .no_valido
    cmp r8d, 59
    jg .no_valido
    cmp r9d, 0
    jl .no_valido
    cmp r9d, 59
    jg .no_valido
    
    mov r10d, edx          ; guardar columnas antes de que edx se corrompa
    mov eax, r8d
    imul eax, r10d
    add eax, r9d
    
    movzx eax, byte [rcx + rax]
    
    cmp al, '#'
    je .no_valido
    
    mov eax, 1
    ret
    
.no_valido:
    xor eax, eax
    ret
; =========================================================================
; FUNCION 3: Calcular puntaje 
; RCX = monedas, RDX = pasos, R8 = niveles_completados 
; Aplicar fórmula matemática en ensamblador y regresar el entero en EAX
; =========================================================================
calcular_puntaje:
    ; monedas * 150
    mov eax, ecx
    imul eax, 150

    ; niveles * 1000
    mov ecx, eax
    mov eax, r8d
    imul eax, 1000

    ; sumar puntos por niveles y restar penalización por pasos
    add eax, ecx
    mov ecx, edx
    imul ecx, 5
    sub eax, ecx

    ; asegurarse de no devolver valor negativo
    cmp eax, 0
    jge .fin_calc
    xor eax, eax

.fin_calc:
    ret

; =========================================================================
; FUNCION 4: Detectar objeto en una celda 
; RCX = char* matriz, RDX = columnas, R8D = x, R9D = y, [rsp+40] = caracter a buscar
; Retornar 1 si el objeto coincide con la celda, 0 si no
; =========================================================================
detectar_objeto:
    xor eax, eax
    
    cmp r8d, 0
    jl .fin_det
    cmp r8d, 59
    jg .fin_det
    cmp r9d, 0
    jl .fin_det
    cmp r9d, 59
    jg .fin_det
    
    mov r10d, edx          ; guardar columnas antes de que edx se corrompa
    mov eax, r8d
    imul eax, r10d
    add eax, r9d
    
    movzx eax, byte [rcx + rax]
    
    mov dl, byte [rsp + 40]   ; leer el 5to parámetro (aquí edx ya no importa)
    
    cmp al, dl
    jne .no_coincide
    mov eax, 1
    ret
    
.no_coincide:
    xor eax, eax
    ret
    
.fin_det:
    xor eax, eax
    ret

; =========================================================================
; FUNCION 5: Contar celdas libres 
; RCX = char* matriz, RDX = total_celdas (3600) 
; Recorrer la matriz y contar cuántas celdas tienen el valor 0
; =========================================================================
contar_celdas_libres:
    ; Inicializamos el contador de celdas libres en 0
    xor eax, eax

    ; Si el total de celdas es 0 o negativo, no hay nada que contar
    test rdx, rdx
    jle .fin_libres

.libre_bucle:
     ; Retrocedemos un índice en el arreglo lineal
    dec rdx

    ; Leemos el carácter de la celda actual
    mov al, [rcx + rdx]

    ; Si la celda es '.' significa camino libre
    cmp al, '.'
    jne .no_incremento
    inc eax

.no_incremento:
    ; Repetimos hasta que hayamos recorrido todas las celdas
    cmp rdx, 0
    jg .libre_bucle

.fin_libres:
    ret