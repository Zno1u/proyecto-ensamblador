#include <stdio.h>
#include "mapas.h"
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

// para los colores verlos aqui https://talyian.github.io/ansicolors/
#define colorDefault "\x1b[0m"
#define colorPared "\x1b[38;5;45m"
#define colorFondo "\x1b[38;5;153m"
#define colorMoneda "\x1b[38;5;220m" //48 color fondo, 38 color letra
#define colorPersonaje "\x1b[48;5;225m\x1b[38;5;218m"
#define colorPuerta "\x1b[48;2;64;36;0m\x1b[38;5;11m"
#define colorLlave "\x1b[48;5;158m\x1b[38;5;2m"


//simbolos de la tabla ascii https://elcodigoascii.com.ar/codigos-ascii-extendidos/simbolo-copyright-derecho-autor-codigo-ascii-184.html
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

void validarWASD(char, struct Personaje*);
void intercambiar(int x1, int y1, int x2, int y2, char mat[60][60]);
int contarCaracterBuscado(char mat[60][60], int columnas, int filas, char objetivo);
int validarMovimiento(char mat[60][60], int columnasTotales,int filas, int columnas); 
void imprimirMapa(char mapa[60][60], struct Personaje *p);

int contarCeldasLibres(char mat[60][60], int columnasTotales, int filasTotales, int filaPersonaje, int columnaPersonaje, int direccion);

extern int calcularPuntaje(int monedas, int pasos, int nivel);

int main(){

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // 2. Activar las secuencias ANSI (Para que tus macros de colores funcionen en Windows)
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    printf("\x1b[?25l"); // quitar cursor de la pantalla  (sale como un bloque blanco y se ve feo)

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
    
    static int celdasLibres = 0;
    static char letraPulsada = ' ';

    if (letraPulsada == letra && celdasLibres>0){
        switch (letra){
            case 'A':
                intercambiar(p->filaPersonaje, p->columnaPersonaje, p->filaPersonaje, p->columnaPersonaje-1, lvlDifPlayer);
                p->columnaPersonaje--;
                movimiento = true;
                celdasLibres--;
                printf("cambio desde celdasLibres %d\n", celdasLibres);
                break;

            case 'S':
                intercambiar(p->filaPersonaje, p->columnaPersonaje, p->filaPersonaje+1, p->columnaPersonaje, lvlDifPlayer);
                p->filaPersonaje++;
                movimiento = true;
                celdasLibres--;
                printf("cambio desde celdasLibres %d\n", celdasLibres);
                break;

            case 'D':
                intercambiar(p->filaPersonaje, p->columnaPersonaje, p->filaPersonaje, p->columnaPersonaje+1, lvlDifPlayer);
                p->columnaPersonaje++;
                movimiento = true;
                celdasLibres--;
                printf("cambio desde celdasLibres %d\n", celdasLibres);
                break;

            case 'W':
                intercambiar(p->filaPersonaje, p->columnaPersonaje, p->filaPersonaje-1, p->columnaPersonaje, lvlDifPlayer);
                p->filaPersonaje--;
                movimiento = true;
                celdasLibres--;
                printf("cambio desde celdasLibres %d\n", celdasLibres);
                break;
            }
    } else {
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
                        //validar movimiento, si es valido, hacer el intercambio
                        intercambiar(p->filaPersonaje, p->columnaPersonaje, p->filaPersonaje, p->columnaPersonaje-1, lvlDifPlayer);
                        
                        //actualizar valores del personaje
                        p->columnaPersonaje--;
                        
                        //flag para ver si se realizo un movimiento
                        movimiento = true;
    
                        celdasLibres = contarCeldasLibres(lvlDifPlayer, 60, 60, p->filaPersonaje, p->columnaPersonaje, 2);
                        letraPulsada = 'A';
    
                    } 
                }
                break;
            case 'S':
                if (p->filaPersonaje < 58  && filaMapa <= 60){
                    if (validarMovimiento(lvlDifPlayer, 60, p->filaPersonaje+1, p->columnaPersonaje) == 1){
                        intercambiar(p->filaPersonaje, p->columnaPersonaje, p->filaPersonaje+1, p->columnaPersonaje, lvlDifPlayer);
                        p->filaPersonaje++;
                        movimiento = true;
    
                        celdasLibres = contarCeldasLibres(lvlDifPlayer, 60, 60, p->filaPersonaje, p->columnaPersonaje, 3);
                        letraPulsada = 'S';
                    } 
                }
                break;
            case 'D':
                if (p->columnaPersonaje < 58 && columnaMapa <= 60){
                    if (validarMovimiento(lvlDifPlayer, 60, p->filaPersonaje, p->columnaPersonaje+1) == 1){
                        intercambiar(p->filaPersonaje, p->columnaPersonaje, p->filaPersonaje, p->columnaPersonaje+1, lvlDifPlayer);
                        p->columnaPersonaje++;
                        movimiento = true;
    
                        celdasLibres = contarCeldasLibres(lvlDifPlayer, 60, 60, p->filaPersonaje, p->columnaPersonaje, 1);
                        letraPulsada = 'D';
                    } 
                }
                break;
            case 'W':
                if (p->filaPersonaje > 1  && filaMapa >= 0){
                    if (validarMovimiento(lvlDifPlayer, 60, p->filaPersonaje-1, p->columnaPersonaje) == 1){
                        intercambiar(p->filaPersonaje, p->columnaPersonaje, p->filaPersonaje-1, p->columnaPersonaje, lvlDifPlayer);
                        p->filaPersonaje--;
                        movimiento = true;
                        
                        celdasLibres = contarCeldasLibres(lvlDifPlayer, 60, 60, p->filaPersonaje, p->columnaPersonaje, 4);
                        letraPulsada = 'W';
                    } 
                }
                break;
        }
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

    // dibujar de 10 en 10 [20,30,40,50,60]
    // int filaMapa = (p->filaPersonaje < 20 ? 20 : (p->filaPersonaje < 30 ? 30 : (p->filaPersonaje < 40 ? 40 : (p->filaPersonaje < 50 ? 50 : 60))));
    // int columnaMapa = (p->columnaPersonaje < 20 ? 20 : (p->columnaPersonaje < 30 ? 30 : (p->columnaPersonaje < 40 ? 40 : (p->columnaPersonaje < 50 ? 50 : 60))));


    for (int i = filaMapa - 20; i < filaMapa; i++){
        for (int j = columnaMapa - 20; j < columnaMapa; j++){
            switch  (lvlDifPlayer[i][j]){
                case '#': // si es pared (o #)
                    printf( "%s%s%s", colorPared, simboloPared, colorDefault ); // imprimir color, simbolo, y regresar al color default 
                    break;
                
                case '.': // si es fondo (o .)
                    printf( "%s%s%s", colorFondo, simboloFondo, colorDefault );  // imprimir color, simbolo, y regresar al color default
                    break;
                
                default: // otra cosa

                    switch (lvlDifPlayer[i][j]){
                        case 'P':
                            printf( "%s%s%s", colorPersonaje, simboloPersonaje, colorDefault ); 
                            break;
    
                        case 'M': 
                            printf( "%s%s%s", colorMoneda, simboloMoneda, colorDefault );
                            break;
    
                        case 'K': 
                            printf( "%s%s%s", colorLlave, simboloLlave, colorDefault );
                            break;
    
                        case 'D': 
                            printf( "%s%s%s", colorPuerta, simboloPuerta, colorDefault );
                            break;
        
                        default:
                            printf( "%c", lvlDifPlayer[i][j] );
                            break;
                    }
                break;
            }

            if ( lvlDifPlayer[i][j] == 'P' || lvlDifPlayer[i][j] == 'D' || lvlDifPlayer[i][j] == 'K' || lvlDifPlayer[i][j] == 'M' ) 
                printf( "%s%s%s", colorFondo, simboloFondo, colorDefault );
            else {
                switch  (lvlDifPlayer[i][j]){
                    case '#': // si es pared (o #)
                        printf( "%s%s%s", colorPared, simboloPared, colorDefault ); // imprimir color, simbolo, y regresar al color default 
                        break;
                    
                    case '.': // si es fondo (o .)
                        printf( "%s%s%s", colorFondo, simboloFondo, colorDefault );  // imprimir color, simbolo, y regresar al color default
                        break;
                    
                    default: // otra cosa
                        printf( "%c", lvlDifPlayer[i][j] );
                        break;
                }
            }
        }
        printf("\n");
    }
}
