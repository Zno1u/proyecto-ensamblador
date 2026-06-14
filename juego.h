#ifndef JUEGO_H
#define JUEGO_H

#include <stdbool.h>

// Simbolos y Colores
#define colorDefault "\x1b[0m"
#define colorPared "\x1b[38;5;45m"
#define colorFondo "\x1b[38;5;153m"
#define colorMoneda "\x1b[38;5;220m"
#define colorPersonaje "\x1b[48;5;225m\x1b[38;5;218m"
#define colorPuerta "\x1b[48;2;64;36;0m\x1b[38;5;11m"
#define colorLlave "\x1b[48;5;158m\x1b[38;5;2m"

#define simboloPared "█"
#define simboloFondo "░"
#define simboloPersonaje "P"
#define simboloMoneda "©"
#define simboloPuerta "≡"
#define simboloLlave "┼"

struct Personaje {
    int filaPersonaje;
    int columnaPersonaje;
};

// Variables globales 
extern char mapaActual[60][60];
extern int g_monedas;
extern bool g_llaveObtenida;
extern int g_pasos;
extern int g_puntaje;
extern int g_nivel;
extern bool g_ganado;

// Prototipos de funciones en Ensamblador (NASM)
int contarCaracterBuscado(char mat[60][60], int columnas, int filas, char objetivo);
int detectarObjetoCelda(char mat[60][60], int columnas, int fila, int columna, char objetivo);
int validarMovimiento(char mat[60][60], int columnasTotales, int filas, int columnas); 
int contarCeldasLibres(char mat[60][60], int columnasTotales, int filasTotales, int filaPersonaje, int columnaPersonaje, int direccion);
int calcularPuntaje(int monedas, int pasos, int nivel);

// Prototipos de funciones en C
void validarWASD(char letra, struct Personaje *p);
void intercambiar(int x1, int y1, int x2, int y2, char mat[60][60]);
void imprimirMapa(char mapa[60][60], struct Personaje *p);
void imprimirPantallaInicio();
void imprimirPantallaVictoria();
void mostrarInterfaz();
bool cargarMapaDesdeTXT(char nombreArchivo[], struct Personaje *p);

#endif