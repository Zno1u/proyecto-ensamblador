bits 64
default rel
global contarCaracterBuscado, detectarObjetoCelda, validarMovimiento

section .text

;--------------------------------------------
; Funcion: contarCaracterBuscado
; Entradas:
;   rdi = matriz(char **)
;   rsi = numero de filas
;   rdx = caracter a buscar
; Salida:
;   rax = total de concidencias encontradas
;---------------------------------------------

;contarCaracteres:
;---------------------------------------------
;Función: detectar objeto en una celda
;La cuarta función obligatoria en NASM deberá detectar si en una posición específica del
;mapa existe un determinado objeto.
;Esta función deberá recibir desde C:
;La dirección inicial del mapa.
;El número de columnas del mapa.
;La fila que se desea revisar.
;La columna que se desea revisar.
;El carácter del objeto que se desea buscar.
;ret

detectarObjetoCelda:
;1 rcx direccion inicial del mapa (segmento)
;2 rdx numero de columnas del mapa
;ulimos parametros, FILA-A-REVISAR r8d COLUMNA-A-REVISAR r9d
;PILA rsp+40, CARACTER-A-COMPARAR 
;PILA rsp + 48 RETORNAR UNO O CERO
    
    ;1. Encontrar el caracter que esta en [FILA][COLUMNA]
    ;base + (i · columnas + j) · tamaño
    mov eax, r8d            ; eax = i
    imul eax, edx           ; eax = i * columnas
    add eax, r9d            ; eax = i * columnas + j
    ;no se multiplica el tamanio ya que es matriz de bytes 
    movsxd rax, eax
    lea r10, [rcx + rax]
    ;1.1 Verificar matriz
    mov r11b, [r10] ;CaracterDelaMatriz
    mov r12b, [rsp+40] ;CaraterParaComparar
    ;2. COMPARAR, caracter con posicion
    cmp r11b,r12b
    je .igual
    mov word [rsp+48], 0
    jmp .salir
    .igual:
        mov word [rsp+48], 1
    .salir:
    ;3. RETORNAR
    ret


    

contarCaracteres:


validarMovimiento:
