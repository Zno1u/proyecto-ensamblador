#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include "juego.h"

// Inicializacion de variables globales
char mapaActual[60][60];
int g_monedas = 0;
bool g_llaveObtenida = false;
int g_pasos = 0;
int g_puntaje = 0;
int g_nivel = 1;
bool g_ganado = false;

void intercambiar(int x1, int y1, int x2, int y2, char mat1[60][60]){
    char temp = mat1[x2][y2];
    mat1[x2][y2] = mat1[x1][y1];
    mat1[x1][y1] = temp;
}

void validarWASD(char letra, struct Personaje *p){
    bool movimiento = false; 
    static int filaMapa = 20;
    static int columnaMapa = 20;
    static int celdasLibres = 0;
    static char letraPulsada = ' ';

    if (letraPulsada == letra && celdasLibres > 0){
        switch (letra){
            case 'A':
                intercambiar(p->filaPersonaje, p->columnaPersonaje, p->filaPersonaje, p->columnaPersonaje-1, mapaActual);
                p->columnaPersonaje--;
                movimiento = true;
                celdasLibres--;
                break;
            case 'S':
                intercambiar(p->filaPersonaje, p->columnaPersonaje, p->filaPersonaje+1, p->columnaPersonaje, mapaActual);
                p->filaPersonaje++;
                movimiento = true;
                celdasLibres--;
                break;
            case 'D':
                intercambiar(p->filaPersonaje, p->columnaPersonaje, p->filaPersonaje, p->columnaPersonaje+1, mapaActual);
                p->columnaPersonaje++;
                movimiento = true;
                celdasLibres--;
                break;
            case 'W':
                intercambiar(p->filaPersonaje, p->columnaPersonaje, p->filaPersonaje-1, p->columnaPersonaje, mapaActual);
                p->filaPersonaje--;
                movimiento = true;
                celdasLibres--;
                break;
            }
    } else {
        switch (letra)
        {
            case 'A':
                if (p->columnaPersonaje > 1 && columnaMapa >= 0){
                    if (validarMovimiento(mapaActual, 60, p->filaPersonaje, p->columnaPersonaje-1) == 1){
                        intercambiar(p->filaPersonaje, p->columnaPersonaje, p->filaPersonaje, p->columnaPersonaje-1, mapaActual);
                        p->columnaPersonaje--;
                        movimiento = true;
                        celdasLibres = contarCeldasLibres(mapaActual, 60, 60, p->filaPersonaje, p->columnaPersonaje, 2);
                        letraPulsada = 'A';
                    } 
                }
                break;
            case 'S':
                if (p->filaPersonaje < 58 && filaMapa <= 60){
                    if (validarMovimiento(mapaActual, 60, p->filaPersonaje+1, p->columnaPersonaje) == 1){
                        intercambiar(p->filaPersonaje, p->columnaPersonaje, p->filaPersonaje+1, p->columnaPersonaje, mapaActual);
                        p->filaPersonaje++;
                        movimiento = true;
                        celdasLibres = contarCeldasLibres(mapaActual, 60, 60, p->filaPersonaje, p->columnaPersonaje, 3);
                        letraPulsada = 'S';
                    } 
                }
                break;
            case 'D':
                if (p->columnaPersonaje < 58 && columnaMapa <= 60){
                    if (validarMovimiento(mapaActual, 60, p->filaPersonaje, p->columnaPersonaje+1) == 1){
                        intercambiar(p->filaPersonaje, p->columnaPersonaje, p->filaPersonaje, p->columnaPersonaje+1, mapaActual);
                        p->columnaPersonaje++;
                        movimiento = true;
                        celdasLibres = contarCeldasLibres(mapaActual, 60, 60, p->filaPersonaje, p->columnaPersonaje, 1);
                        letraPulsada = 'D';
                    } 
                }
                break;
            case 'W':
                if (p->filaPersonaje > 1 && filaMapa >= 0){
                    if (validarMovimiento(mapaActual, 60, p->filaPersonaje-1, p->columnaPersonaje) == 1){
                        intercambiar(p->filaPersonaje, p->columnaPersonaje, p->filaPersonaje-1, p->columnaPersonaje, mapaActual);
                        p->filaPersonaje--;
                        movimiento = true;
                        celdasLibres = contarCeldasLibres(mapaActual, 60, 60, p->filaPersonaje, p->columnaPersonaje, 4);
                        letraPulsada = 'W';
                    } 
                }
                break;
        }
    }

    if (movimiento){
        g_pasos++;
        system("cls"); 
        mostrarInterfaz();
        imprimirMapa(mapaActual, p);
    }
}

void imprimirMapa(char mapa[60][60], struct Personaje *p){
    int filaMapa = (p->filaPersonaje < 20 ? 20 : (p->filaPersonaje < 40 ? 40 : 60));
    int columnaMapa = (p->columnaPersonaje < 20 ? 20 : (p->columnaPersonaje < 40 ? 40 : 60));

    for (int i = filaMapa - 20; i < filaMapa; i++){
        for (int j = columnaMapa - 20; j < columnaMapa; j++){
            switch  (mapaActual[i][j]){
                case '#': 
                    printf( "%s%s%s", colorPared, simboloPared, colorDefault ); 
                    break;
                case '.': 
                    printf( "%s%s%s", colorFondo, simboloFondo, colorDefault );  
                    break;
                default: 
                    switch (mapaActual[i][j]){
                        case 'P': printf( "%s%s%s", colorPersonaje, simboloPersonaje, colorDefault ); break;
                        case 'M': printf( "%s%s%s", colorMoneda, simboloMoneda, colorDefault ); break;
                        case 'K': printf( "%s%s%s", colorLlave, simboloLlave, colorDefault ); break;
                        case 'D': printf( "%s%s%s", colorPuerta, simboloPuerta, colorDefault ); break;
                        default:  printf( "%c", mapaActual[i][j] ); break;
                    }
                break;
            }

            if ( mapaActual[i][j] == 'P' || mapaActual[i][j] == 'D' || mapaActual[i][j] == 'K' || mapaActual[i][j] == 'M' ) 
                printf( "%s%s%s", colorFondo, simboloFondo, colorDefault );
            else {
                switch  (mapaActual[i][j]){
                    case '#': printf( "%s%s%s", colorPared, simboloPared, colorDefault ); break;
                    case '.': printf( "%s%s%s", colorFondo, simboloFondo, colorDefault ); break;
                    default: printf( "%c", mapaActual[i][j] ); break;
                }
            }
        }
        printf("\n");
    }
}

void imprimirPantallaInicio(){
    system("cls");
    printf("\x1b[38;5;45m"); 
    printf("\n\n\n");
    printf("     ==========================================\n");
    printf("     ||                                      ||\n");
    printf("     ||        B I E N V E N I D O   A       ||\n");
    printf("     ||            B I T Q U E S T           ||\n");
    printf("     ||                                      ||\n");
    printf("     ==========================================\n");
    printf("\x1b[0m\n");
    printf("          Presiona cualquier tecla para iniciar...\n");
    getch();
}

void imprimirPantallaVictoria(){
    system("cls");
    printf("\x1b[38;5;46m"); 
    printf("\n\n\n");
    printf("     ===============================================\n");
    printf("     ||                                            ||\n");
    printf("     ||       ! N I V E L   S U P E R A D O !      ||\n");
    printf("     ||                                            ||\n");
    printf("     ===============================================\n");
    printf("\x1b[0m\n");
    printf("   --- RESUMEN DEL NIVEL %d ---\n", g_nivel);
    printf("   > Monedas recolectadas : %d\n", g_monedas);
    printf("   > Pasos dados          : %d\n", g_pasos);
    printf("   > Puntaje Final        : %d\n\n", g_puntaje);
    printf("     Presiona cualquier tecla para continuar...\n");
    getch();
}

void mostrarInterfaz(){
    g_puntaje = calcularPuntaje(g_monedas, g_pasos, g_nivel);
    if (g_puntaje < 0) g_puntaje = 0;

    printf("\x1b[38;5;226m"); 
    printf("=======================================================================\n");
    printf(" NIVEL: %d | MONEDAS: %d | LLAVE: %s | PASOS: %d | PUNTAJE: %d \n", 
           g_nivel, g_monedas, (g_llaveObtenida ? "OBTENIDA" : "FALTANTE"), g_pasos, g_puntaje);
    printf("=======================================================================\n");
    printf("\x1b[0m"); 
}

bool cargarMapaDesdeTXT(char nombreArchivo[], struct Personaje *p){
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo: %s\n", nombreArchivo);
        return false;
    }

    char linea[65];
    int fila = 0;

    while (fgets(linea, sizeof(linea), archivo) && fila < 60) {
        for (int col = 0; col < 60 && linea[col] != '\n' && linea[col] != '\0'; col++) {
            mapaActual[fila][col] = linea[col];
            if (linea[col] == 'P') {
                p->filaPersonaje = fila;
                p->columnaPersonaje = col;
            }
        }
        fila++;
    }

    fclose(archivo);
    return true;
}