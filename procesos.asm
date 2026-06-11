bits 64
global contarCaracterBuscado, detectarObjetoCelda, calcularPuntaje

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

calcularPuntaje:
;La tercera función obligatoria en NASM deberá calcular el puntaje del jugador.
;Esta función deberá recibir desde C los datos necesarios para calcular el puntaje, por ejemplo:
;Monedas recolectadas. 2000 puntos
;Pasos realizados. -50 puntos
;Niveles completados. 10000 puntos
;El puntaje puede definirse con una fórmula sencilla. Por ejemplo, se puede dar mayor valor
;a las monedas recolectadas y restar puntos por la cantidad de pasos realizados.
    mul rcx, 2000   ;Multipliamos el numero de monedas por 2000
    mul rdx, -50    ;Multiplicamos la penalización de los pasos por -50
    mul r8, 10000   ;Multiplicamos completar el nivel por 10000
    add rcx, rdx    ;(monedas * 2000) + (pasos * -50)
    add rcx, r8     ;(monedas * 2000) + (pasos * -50) + (niveles * 10000)
    div rcx, 10     ;(monedas * 2000) + (pasos * -50) + (niveles * 10000) / 10
    mov rax, rcx    ;Movemos el resultado a rax para retornar el puntaje
    ret


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


    