#include <stdio.h>
#include "mapas.h"
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <conio.h>

void imprimirMapa(int, char);

int main(){
    int nivel = 1;
    bool ganado = false;
    do {
        char letra = ' ';
        letra = getch();
        if (letra >= 'a' && letra <= 'z'){
            letra = letra-32;
        }
        if (letra == 'A' || letra == 'S' || letra == 'D' || letra == 'W'){
            imprimirMapa(nivel, letra);
        }
    } while (ganado==false);
    
}

void imprimirMapa(int nivel, char letra){
    static int i = 20;
    static int j = 20;
    switch (letra)
    {
    case 'A':
        if (i>20) i -= 1;
        break;
    case 'S':
        if (j<60) j += 1;
        break;
    case 'D':
        if (i<60) i += 1;
        break;
    case 'W':
        if (j>20) j -= 1;
        break;
    default:
        break;
    }
    // char[60][60] nivelFacil = "" 
    switch (nivel) {
    case 1:
        system("cls");
        for (int k = j-20; k<j; k++){
            for (int l = i-20; l<i; l++){
                printf( "%c", nivelFacil[k][l] );
                if ( nivelFacil[k][l] == 'P' || nivelFacil[k][l] == 'D' || nivelFacil[k][l] == 'K' || nivelFacil[k][l] == 'M' ) printf(".");
                else printf( "%c", nivelFacil[k][l] );
            }
            printf("\n");
        }
        break;
        
    case 2:
        break;
        
    case 3:
        break;
        
    }

    return;
}