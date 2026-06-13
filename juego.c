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
int contarCaracterBuscado(char mat[60][60], int columnas, int filas, char objetivo);
int validarMovimiento(char mat[60][60], int columnasTotales,int filas, int columnas); 
void imprimirMapa(char mapa[60][60], struct Personaje *p);
extern int calcularPuntaje(int monedas, int pasos, int nivel);

int main(){
    struct Personaje p = {2,2};
    int cnt = contarCaracterBuscado(lvlDif, 60, 60, 'M');
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
    bool movimiento = false; 
    // cambiar movimiento en true al hacer un movimiento valido para q cuando haya uno invalido no
    // se redibuje el mapa de nuevo
    
    static int filaMapa = 20;
    static int columnaMapa = 20;

    switch (letra)
    {
    // validar movimientos dependiendo del caso
    // A - columnaPersonaje-1 (moverse izq)
    // S - filaPersonaje+1 (moverse abajo)
    // D - columnaPersonaje+1 (moverse derecha)
    // W - filaPersonaje-1 (moverse arriba)
    // dsps de validar que sea valido, hacer el movimiento en el mapa correspondiente,
    // actualizar valores y cambiar flag.
    case 'A':
        if (p->columnaPersonaje > 1  && columnaMapa >= 0){
            if (validarMovimiento(lvlDifPlayer, 60, p->filaPersonaje, p->columnaPersonaje-1) == 1){
                intercambiar(p->filaPersonaje, p->columnaPersonaje, p->filaPersonaje, p->columnaPersonaje-1, lvlDifPlayer);
                p->columnaPersonaje--;
                movimiento = true;
            } 
        }
        break;
    case 'S':
        if (p->filaPersonaje < 58  && filaMapa <= 60){
            if (validarMovimiento(lvlDifPlayer, 60, p->filaPersonaje+1, p->columnaPersonaje) == 1){
                intercambiar(p->filaPersonaje, p->columnaPersonaje, p->filaPersonaje+1, p->columnaPersonaje, lvlDifPlayer);
                p->filaPersonaje++;
                movimiento = true;
            } 
        }
        break;
    case 'D':
        if (p->columnaPersonaje < 58 && columnaMapa <= 60){
            if (validarMovimiento(lvlDifPlayer, 60, p->filaPersonaje, p->columnaPersonaje+1) == 1){
                intercambiar(p->filaPersonaje, p->columnaPersonaje, p->filaPersonaje, p->columnaPersonaje+1, lvlDifPlayer);
                p->columnaPersonaje++;
                movimiento = true;
            } 
        }
        break;
    case 'W':
        if (p->filaPersonaje > 1  && filaMapa >= 0){
            if (validarMovimiento(lvlDifPlayer, 60, p->filaPersonaje-1, p->columnaPersonaje) == 1){
                intercambiar(p->filaPersonaje, p->columnaPersonaje, p->filaPersonaje-1, p->columnaPersonaje, lvlDifPlayer);
                p->filaPersonaje--;
                movimiento = true;
            } 
        }
        break;
    }

    if (movimiento){
        system("cls"); // limpiarr pantalla sol osi hay movimientos nuevos
        imprimirMapa(lvlDifPlayer, p);
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

void imprimirMapa(char mapa[60][60], struct Personaje *p){
    // dibujar de 20 en 20 [20,40,60]
    //dependiendo en donde se encuentre el jugador, cambia las filas a dibujar
    int filaMapa = (p->filaPersonaje < 20 ? 20 : (p->filaPersonaje < 40 ? 40 : 60));
    int columnaMapa = (p->columnaPersonaje < 20 ? 20 : (p->columnaPersonaje < 40 ? 40 : 60));

    // test para dibujar de 10 en 10 [20,30,40,50,60]
    // int filaMapa = (p->filaPersonaje < 20 ? 20 : (p->filaPersonaje < 30 ? 30 : (p->filaPersonaje < 40 ? 40 : (p->filaPersonaje < 50 ? 50 : 60))));
    // int columnaMapa = (p->columnaPersonaje < 20 ? 20 : (p->columnaPersonaje < 30 ? 30 : (p->columnaPersonaje < 40 ? 40 : (p->columnaPersonaje < 50 ? 50 : 60))));


    for (int i = filaMapa - 20; i < filaMapa; i++){
        for (int j = columnaMapa - 20; j < columnaMapa; j++){
            printf( "%c", lvlDifPlayer[i][j] );
            // evitar que se duplique el personaje, puertas, llaves, monedas en consola
            if ( lvlDifPlayer[i][j] == 'P' || lvlDifPlayer[i][j] == 'D' || lvlDifPlayer[i][j] == 'K' || lvlDifPlayer[i][j] == 'M' ) printf(".");
            else printf( "%c", lvlDifPlayer[i][j] );
        }
        printf("\n");
    }
}