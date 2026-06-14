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

        while(getchar() != '\n'); // Limpiar el buffer

        // Validar que la opcion sea correcta antes de entrar al ciclo de niveles
        if (opcion >= 1 && opcion <= 4) {
            int nivelActual = opcion;

            // Bucle que permite la progresión de niveles
            while (nivelActual <= 4) {
                
                // Asignar el nombre del archivo según el nivel actual
                if (nivelActual == 1) {
                    strcpy(nombreArchivo, "nivelTutorial.txt");
                } else if (nivelActual == 2) {
                    strcpy(nombreArchivo, "nivelFacil.txt");
                } else if (nivelActual == 3) {
                    strcpy(nombreArchivo, "nivelMedio.txt");
                } else if (nivelActual == 4) {
                    strcpy(nombreArchivo, "nivelDificil.txt");
                }
                g_nivel = nivelActual;

                struct Personaje p;
                
                // Se carga el mapa desde un txt y se inicializa el personaje
                if (cargarMapaDesdeTXT(nombreArchivo, &p)) {
                    g_monedas = 0; 
                    g_monedasRecogidas = 0; // Reiniciar monedas al entrar al nivel
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

                    // Mostrar el resumen de victoria
                    imprimirPantallaVictoria(); 

                    // Logica para avanzar al siguiente nivel o regresar al menu
                    if (nivelActual < 4) {
                        char resp;
                        printf("     Quieres avanzar al siguiente nivel? (S/N): ");
                        scanf(" %c", &resp);
                        while(getchar() != '\n'); // Limpiar buffer de nuevo
                        
                        if (toupper(resp) == 'S') {
                            nivelActual++;
                        } else {
                            break;
                        }
                    } else {
                        // Si está en el nivel 4 (Dificil)
                        printf("     Has completado el nivel mas dificil!\n");
                        printf("     Presiona cualquier tecla para regresar al menu principal...\n");
                        getch();
                        break; 
                    }
                } else {
                    // Si hubo un error cargando el TXT, salir del bucle de progresion
                    printf("     Presiona cualquier tecla para regresar al menu...\n");
                    getch();
                    break;
                }
            } // Fin del while de progresion de niveles
        } 

    } while (opcion != 0);

    return 0;
}