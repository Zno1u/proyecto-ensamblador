#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include "juego.h"

int main(){

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    printf("\x1b[?25l"); // Quitar cursor

    imprimirPantallaInicio();
    int opcion = 0;
    char tutorial = ' ';
    char nombreArchivo[50]; 
    
    do {
        system("cls");
        printf("==============================\n");
        printf("      MENU DE SELECCION       \n");
        printf("==============================\n");
        printf("1. Nivel Muy Facil\n");
        printf("2. Nivel Facil\n");
        printf("3. Nivel Medio\n");
        printf("4. Nivel Dificil\n");
        printf("0. Salir\n");
        printf("Elige una opcion: ");
        scanf("%d", &opcion);

        if (opcion == 0) break;

        while(getchar() != '\n'); 

        if (opcion == 1) {
            strcpy(nombreArchivo, "nivelTutorial.txt");
            g_nivel = 1;
        } else if (opcion == 2) {
            strcpy(nombreArchivo, "nivelFacil.txt");
            g_nivel = 2;
        } else if (opcion == 3) {
            strcpy(nombreArchivo, "nivelMedio.txt");
            g_nivel = 3;
        } else if (opcion == 4) {
            strcpy(nombreArchivo, "nivelDificil.txt");
            g_nivel = 4;
        } else {
            continue; 
        }

        struct Personaje p;
        // Se carga el mapa desde un txt y se inicializa el personaje
        if (cargarMapaDesdeTXT(nombreArchivo, &p)) {
            g_monedas = 0;
            g_llaveObtenida = false;
            g_pasos = 0;
            g_puntaje = 0;
            g_ganado = false;

            system("cls");
            mostrarInterfaz();
            imprimirMapa(mapaActual, &p);

            // Bucle principal del juego
            do {
                char letra = getch();
                if (letra >= 'a' && letra <= 'z'){
                    letra = letra - 32;
                }
                if (letra == 'A' || letra == 'S' || letra == 'D' || letra == 'W'){
                    validarWASD(letra, &p); 
                }
            } while (g_ganado == false);

            imprimirPantallaVictoria(); 
        }

    } while (opcion != 0);

    return 0;
}