bits 64
default rel
global contarCaracterBuscado, detectarObjetoCelda, validarMovimiento, contarCeldasLibres

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


contarCeldasLibres:
    ;1 rcx direccion del jugador sin aun moverse (segmento)
    ;2 rdx numero total de celdas, retorno
    ; r8d A-DONDE-A-MOVERSE

    ;1. Moverse hasta que encuentre un #
    ; * Saber a donde me voy a mover para ver si resto o sumo hasta encontrar #
    ; * Si es derecha, es sumar +i
    ; *Si es izquierda, es restar -i
    ; * Si es arriba, es restar -j
    ; * Si es abajo, es sumar -i
    
    ;Como me muevo?? base + (i · columnas + j) · tamaño
    ;columnas estaticas: 60
    cmp r8d,1; Izquierda
    jmp .loopIzquierda
    cmp r8d,2; Derecha
    jmp .loopDerecha
    cmp r8d,2; Arriba
    jmp .loopArriba
    cmp r8d,2; Abajo
    jmp .loopAbajo

    .loopIzquierda:
         mov eax, [rcx] ;PUNTERO RCX de la matriz, valor actual de la matriz

        

    .loopDerecha:
         mov eax, [rcx] ;PUNTERO RCX de la matriz, valor actual de la matriz
          add rcx, 1 ;se avanza de 1 en 1 por que la matriz es de caracteres, aqui se mueve por columna
        
    .loopArriba:
         mov eax, [rcx] ;PUNTERO RCX de la matriz, valor actual de la matriz

    .loopAbajo:
         mov eax, [rcx] ;PUNTERO RCX de la matriz, valor actual de la matriz
    
    



