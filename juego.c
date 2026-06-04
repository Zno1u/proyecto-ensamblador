#include <stdio.h>
#include "mapas.h"
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <conio.h>

void validarWASD(char);
void intercambiar(int x1, int y1, int x2, int y2, char mat[][61]);
extern int contarCaracterBuscado(char **mat, int filas, char objetivo);

int main(){
    int cnt = contarCaracterBuscado(nivelFacil, 60, 'M');
    bool ganado = false;
    do {
        char letra = ' ';
        letra = getch();
        if (letra >= 'a' && letra <= 'z'){
            letra = letra-32;
        }
        if (letra == 'A' || letra == 'S' || letra == 'D' || letra == 'W'){
            validarWASD(letra);
        }
    } while (ganado==false);
    
}

void validarWASD(char letra){
    system("cls");

    static int filaPersonaje = 2;
    static int columnaPersonaje = 2;
    static int filaMapa = 20;
    static int columnaMapa = 20;

    switch (letra)
    {
    case 'A':
        if (columnaPersonaje > 1  && columnaMapa >= 0){
            intercambiar(filaPersonaje, columnaPersonaje, filaPersonaje, columnaPersonaje-1, lvlDifPlayer);
            columnaPersonaje--;
        }
        break;
    case 'S':
        if (filaPersonaje < 58  && filaMapa <= 60){
            intercambiar(filaPersonaje, columnaPersonaje, filaPersonaje+1, columnaPersonaje, lvlDifPlayer);
            filaPersonaje++;
        }
        break;
    case 'D':
        if (columnaPersonaje < 58 && columnaMapa <= 60){
            intercambiar(filaPersonaje, columnaPersonaje, filaPersonaje, columnaPersonaje+1, lvlDifPlayer);
            columnaPersonaje++;
        }
        break;
    case 'W':
        if (filaPersonaje > 1  && filaMapa >= 0){
            intercambiar(filaPersonaje, columnaPersonaje, filaPersonaje-1, columnaPersonaje, lvlDifPlayer);
            filaPersonaje--;
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

void intercambiar(int x1, int y1, int x2, int y2, char mat1[][61]){
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