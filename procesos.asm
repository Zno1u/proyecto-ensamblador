bits 64
default rel
global contarCaracterBuscado, detectarObjetoCelda, validarMovimiento, contarCeldasLibres, calcularPuntaje

section .text

;--------------------------------------------
; Funcion: contarCaracterBuscado
; Entradas:
;   rcx = Dirección base de la matriz (&lvlDif[0][0])
;   rdx = Número de filas (60)
;   r8  = Número de columnas (61)
;   r9  = Caracter a buscar ('M')
; Salida:
;   rax = total de concidencias encontradas
;---------------------------------------------

contarCaracteres:
    ;Calcular el total de elementos (3660)
    mov rax, rdx
    imul rax, r8

    ;Inicializamos el contador
    xor r10, r10
    xor r11, r11

    .ciclo_lectura:
        cmp r11, rax
        jge .fin_funcion

        mov r12b, byte [rcx + r11]

        cmp r12b, r9b
        jne .siguiente

        inc r10
    
    .siguiente:
        inc r11
        jmp .ciclo_lectura

    .fin_funcion:
        mov rax, r10
        ret


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


    

contarCaracteres:


validarMovimiento:
    ; rcx = puntero a la matriz
    ; edx = columnas
    ; r8d = fila (i)
    ; r9d = columna (j)
    ; eax = retorno

    ; base + (i * columnas + j)

    imul r8d, edx  ; i * columnas
    add r8d, r9d ; i * columnas + j 

    ; cambiar r8d de 32 a 64 bits
    movsxd rax, r8d

    ; hacer la suma base + (i * columnas + j)
    lea r11, [rcx + rax]

    ; el puntero de la direccion a la que se va a mover se
    ; guarda en r11, acceder con [] al valor

    ; comparar 1 byte para ver si es un '#'
    cmp byte [r11], '#'
    je .movimientoInvalido

    ; si no es, retornar un 1 para q si pueda avanzar
    mov eax, 1
    jmp .salida

    .movimientoInvalido:
    mov eax, 0 ; si si es, moverle un 0 para que no pueda avanzar
    
    .salida:
    ret

contarCeldasLibres:
    ; rcx = puntero inicial a la matriz
    ; edx = columnas
    ; r8d = filas
    ; r9d = fila (i)
    ;[rsp+40] fila (j)
    ;[rsp+48] a donde me voy a mover
    ; eax = numero total de celdas, retorno
    ; Dirección Real = Base + ((i * Total_Columnas) + j) * tamaño de la celda
    
    mov eax, r9d
    imul eax, edx ; eax = i * Total_Columnas
    add  eax, [rsp+40] ;eax = ((i * Total_Columnas) + j)
    movsxd r10, eax ;Cambiar eax a 64 bits para despues calular posicion acutal
    
    ;VALORES QUE SE USAN MAS ADELANTE
    lea r11, [rcx + r10] ;Poscicion Actual
    mov r12d, edx ;Columnas guardadas
    ;Verificar a donde se va a mover
    xor edx, edx ;limpiar
    mov edx, dword [rsp+48] ; 1 = Derecha, 2 = Izquierda, 3 = Abajo, 4 = Arriba
    xor ecx, ecx ;Contador limpio

    ;CASOS SEGUN EL PARAMETRO
    cmp edx, 1
    je .Derecha

    cmp edx, 2
    je .Izquierda

     cmp edx, 3
    je .Abajo

     cmp edx, 4
    je .Arriba

    jmp .DejarDeContar

    ;ETIQUETE DERECHA
    .Derecha:
        ;Limite hacia la derecha de la fila del pesonaje (columnas disonibles para avanzar)
        mov r13d, r12d ;r13 = columnas
        sub r13d, 1    ;r13 = columnas - 1
        sub r13d, [rsp+40] ;r13 = (columnas - 1) - j

        .ContarDerecha:
            cmp ecx, r13d ;Comprobar si llegamos a los pasos máximos (limite), ver que es r13d
            je .DejarDeContar

            cmp byte [r11 + 1], "#" ;Si hay pared en la siguiente, dejar de contar
            je .DejarDeContar

            add r11, 1
            inc ecx ;Incrementar 1
            jmp .ContarDerecha
    .Izquierda:
        ;Limite hacia la izquierdo de la fila del pesonaje (columnas disonibles para retroceder)
        mov r13d, [rsp+40] ;r13 = j
        .ContarIzquierda:
            ;ecx es nuestro contador
            cmp ecx, r13d ;Comprobar si llegamos a los pasos máximos (limite), ver que es r13d
            je .DejarDeContar

            cmp byte [r11 - 1], "#" ;Si hay pared atras, dejar de contar
            je .DejarDeContar
            sub r11, 1
            inc ecx ;Incrementar 1
            jmp .ContarIzquierda
    .Abajo:
        ;Limite hacia abajo de la columna del pesonaje (filas disonibles para avanzar)
        mov r13d, r8d ;r13 = filas
        sub r13d, 1   ;r13 = filas - 1
        sub r13d, r9d ;r13 = (filas - 1) - i
        movsxd rax, r12d ;numero de columnas que hay: Se convierte a 64 para calcular direccion
        
        .ContarAbajo:
            cmp ecx, r13d ;Comprobar si llegamos a los pasos máximos (limite), ver que es r13d
            je .DejarDeContar
            
            cmp byte [r11 + rax], "#" ;Si hay pared en la siguiente, dejar de contar
            je .DejarDeContar

            add r11, rax
            inc ecx ;Incrementar 1
            jmp .ContarAbajo
    .Arriba:    
        ;Limite hacia arriba de la columna del pesonaje (filas disponibles para retroceder)
        mov r13d, r9d ;r13 = i
        movsxd rax, r12d ;numero de columnas que hay: Se convierte a 64 para calcular direccion
        .ContarArriba:
            cmp ecx, r13d ;Comprobar si llegamos a los pasos máximos (limite), ver que es r13d
            je .DejarDeContar
            
            cmp byte [r11 - rax], "#" ;Si hay pared en la anterior, dejar de contar
            je .DejarDeContar

            sub r11, rax
            inc ecx ;Incrementar 1
            jmp .ContarArriba

    .DejarDeContar:
        mov eax, ecx
        ret
  