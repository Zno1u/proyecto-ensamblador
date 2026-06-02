#include <stdio.h>

int main() {
    int opcion;


    do {

        printf("NIVEL \n");
        printf("1. Facil\n");
        printf("2. Medio\n");
        printf("3. Dificil\n");
        printf("Elige una opcion (1-3): ");
        
        // Leemos la opción del usuario
        scanf("%d", &opcion);
    
        // Estructura switch para los niveles
        switch (opcion) {
            case 1:
                printf("\nModo Facil.\n");
                // Tu código para nivel fácil aquí
                break;
                
            case 2:
                printf("\nModo Medio.\n");
                // Tu código para nivel medio aquí
                break;
                
            case 3:
                printf("\nModo Dificil.\n");
                // Tu código para nivel difícil aquí
                break;
                
            default:
                printf("\nOpcion invalida.\n");
                break;
        }
    } while (opcion > 3 || opcion <= 0);

    return 0;
}