#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

int main(){
    Libro *libros = NULL;
    int contador = 0;
    int opcion;

    do{
        printf("\n===== MENU BIBLIOTECA =====\n");
        printf("1. Registrar libro\n");
        printf("2. Mostrar libros\n");
        printf("3. Buscar libro\n");
        printf("4. Actualizar estado\n");
        printf("5. Eliminar libro\n");
        printf("6. Salir\n");
        printf("Seleccione una opcion: ");

        opcion = intPositivo();

        switch(opcion){
            case 1: registrarLibro(&libros, &contador); break;
            case 2: mostrarLibros(libros, contador); break;
            case 3: buscarLibro(libros, contador); break;
            case 4: actualizarEstado(libros, contador); break;
            case 5: eliminarLibro(&libros, &contador); break;
            case 6: printf("Saliendo...\n"); break;
            default: printf("Opcion invalida.\n");
        }

    }while(opcion != 6);

    free(libros);
    return 0;
}
