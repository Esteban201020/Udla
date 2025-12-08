#include <stdio.h>
#include "funciones.h"

int main (int argc, char *argv[]) {
    
    Libro biblioteca[10]; 
    int totalLibros = 0;
    
    int opcion = 0;

    do {
        opcion = menu();

        switch (opcion) {
            case 1: 
                registrarLibro(biblioteca, &totalLibros); 
                break;
            case 2:
                mostrarLibros(biblioteca, &totalLibros); 
                break;
            case 3: 
                buscarLibro(biblioteca, &totalLibros); 
                break;
            case 4: 
                actualizarEstado(biblioteca, &totalLibros); 
                break;
            case 5: 
                eliminarLibro(biblioteca, &totalLibros); 
                break;
            case 6: 
                printf("Saliendo del programa...\n"); 
                break;
            default: 
                printf("Opcion no valida.\n");
        }
    } while (opcion != 6);

    return 0;
}