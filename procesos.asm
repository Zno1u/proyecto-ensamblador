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


contarCaracteres:
    