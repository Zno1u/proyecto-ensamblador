#include <stdio.h>
#include "mapas.h"
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <conio.h>

struct Personaje {
    int filaPersonaje;
    int columnaPersonaje;
};

void validarWASD(char, struct Personaje*);
void intercambiar(int x1, int y1, int x2, int y2, char mat[60][60]);
int contarCaracterBuscado(char mat[60][60], int filas, char objetivo);
int validarMovimiento(char mat[60][60], int columnasTotales,int filas, int columnas); 

int main(){
    struct Personaje p = {2,2};
    // int cnt = contarCaracterBuscado(&lvlDif[0][0], 61, 60, 'M');
    bool ganado = false;
    do {
        char letra = ' ';
        letra = getch();
        if (letra >= 'a' && letra <= 'z'){
            letra = letra-32;
        }
        if (letra == 'A' || letra == 'S' || letra == 'D' || letra == 'W'){
            validarWASD(letra, &p);
        }
    } while (ganado==false);
    
}


void validarWASD(char letra, struct Personaje *p){
    system("cls");

    static int filaMapa = 20;
    static int columnaMapa = 20;

    switch (letra)
    {
    case 'A':
        if (p->columnaPersonaje > 1  && columnaMapa >= 0){
            if (validarMovimiento(lvlDifPlayer, 60, p->filaPersonaje, p->columnaPersonaje-1) == 1){
                intercambiar(p->filaPersonaje, p->columnaPersonaje, p->filaPersonaje, p->columnaPersonaje-1, lvlDifPlayer);
                p->columnaPersonaje--;
            } else {
                printf("Invalido debug");
            }
        }
        break;
    case 'S':
        if (p->filaPersonaje < 58  && filaMapa <= 60){
            if (validarMovimiento(lvlDifPlayer, 60, p->filaPersonaje+1, p->columnaPersonaje) == 1){
                intercambiar(p->filaPersonaje, p->columnaPersonaje, p->filaPersonaje+1, p->columnaPersonaje, lvlDifPlayer);
                p->filaPersonaje++;
            } else {
                printf("Invalido debug");
            }
        }
        break;
    case 'D':
        if (p->columnaPersonaje < 58 && columnaMapa <= 60){
            if (validarMovimiento(lvlDifPlayer, 60, p->filaPersonaje, p->columnaPersonaje+1) == 1){
                intercambiar(p->filaPersonaje, p->columnaPersonaje, p->filaPersonaje, p->columnaPersonaje+1, lvlDifPlayer);
                p->columnaPersonaje++;
            } else {
                printf("Invalido debug");
            }
        }
        break;
    case 'W':
        if (p->filaPersonaje > 1  && filaMapa >= 0){
            if (validarMovimiento(lvlDifPlayer, 60, p->filaPersonaje-1, p->columnaPersonaje) == 1){
                intercambiar(p->filaPersonaje, p->columnaPersonaje, p->filaPersonaje-1, p->columnaPersonaje, lvlDifPlayer);
                p->filaPersonaje--;
            } else {
                printf("Invalido debug");
            }
        }
        break;
    }

    for (int i = 0; i<60; i++){
        for (int j = 0; j<60; j++){
            printf( "%c", lvlDifPlayer[i][j] );
            printf( "%c", lvlDifPlayer[i][j] );
        }
        printf("\n");
    }
    return;
}

void intercambiar(int x1, int y1, int x2, int y2, char mat1[60][60]){
    char temp = mat1[x2][y2];
    mat1[x2][y2] = mat1[x1][y1];
    mat1[x1][y1] = temp;
}

// void imprimir20(int nivel, char mapa[][], int filaMapa, int columnaMapa){
//     switch (nivel) {
//     case 1:
//         system("cls");
//         for (int k = j-20; k<j; k++){
//             for (int l = i-20; l<i; l++){
//                 printf( "%c", mapa[k][l] );
//                 if ( mapa[k][l] == 'P' || mapa[k][l] == 'D' || mapa[k][l] == 'K' || mapa[k][l] == 'M' ) printf(".");
//                 else printf( "%c", mapa[k][l] );
//             }
//             printf("\n");
//         }
//         break;
        
//     case 2:
//         break;
        
//     case 3:
//         break;
        
//     }
// }