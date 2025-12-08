#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"



void leerCadena(char *cadena, int n){
    fflush(stdin);
    fgets(cadena, n, stdin);
    int len = strlen(cadena) - 1;
    if(len >= 0 && cadena[len] == '\n')
        cadena[len] = '\0';

    while(strlen(cadena) == 0){
        printf("Entrada vacia. Intente nuevamente: ");
        fflush(stdin);
        fgets(cadena, n, stdin);
        len = strlen(cadena) - 1;
        cadena[len] = '\0';
    }
}

int intPositivo(){
    int num;
    int valido;

    do {
        fflush(stdin);
        valido = scanf("%d", &num);
        if(valido != 1 || num < 0){
            printf("Valor invalido. Ingrese un numero positivo: ");
        }
    } while(valido != 1 || num < 0);

    return num;
}

int validarAnio(){
    int anio;
    printf("Ingrese ano de publicacion: ");
    anio = intPositivo();

    while(anio < 1000 || anio > 2050){
        printf("Ano invalido (1000 - 2050). Intente nuevamente: ");
        anio = intPositivo();
    }
    return anio;
}

void validarEstado(char *estado){
    do {
        printf("Ingrese estado (Disponible / Prestado): ");
        leerCadena(estado, 15);

        if(strcmp(estado, "Disponible") != 0 && strcmp(estado, "Prestado") != 0){
            printf("Estado invalido. Debe ser 'Disponible' o 'Prestado'.\n");
        }
    } while(strcmp(estado, "Disponible") != 0 && strcmp(estado, "Prestado") != 0);
}


void registrarLibro(Libro **libros, int *contador){
    Libro nuevo;

    printf("Ingrese ID del libro: ");
    nuevo.id = intPositivo();

    
    for(int i = 0; i < *contador; i++){
        if((*libros)[i].id == nuevo.id){
            printf("ERROR: El ID ya existe. Registro cancelado.\n");
            return;
        }
    }

    printf("Ingrese titulo: ");
    leerCadena(nuevo.titulo, 100);

    printf("Ingrese autor: ");
    leerCadena(nuevo.autor, 50);

    nuevo.anio = validarAnio();

    validarEstado(nuevo.estado);

    
    *libros = (Libro*) realloc(*libros, (*contador + 1) * sizeof(Libro));

    if(*libros == NULL){
        printf("Error al asignar memoria.\n");
        exit(1);
    }

    (*libros)[*contador] = nuevo;
    (*contador)++;

    printf("Libro registrado correctamente.\n");
}

void mostrarLibros(Libro *libros, int contador){
    if(contador == 0){
        printf("No hay libros registrados.\n");
        return;
    }

    printf("\n%-5s %-25s %-20s %-8s %-12s\n",
        "ID", "Titulo", "Autor", "Ano", "Estado");
    printf("-----------------------------------------------------------------\n");

    for(int i = 0; i < contador; i++){
        printf("%-5d %-25s %-20s %-8d %-12s\n",
            libros[i].id, libros[i].titulo, libros[i].autor,
            libros[i].anio, libros[i].estado);
    }
}

void buscarLibro(Libro *libros, int contador){
    if(contador == 0){
        printf("No hay libros registrados.\n");
        return;
    }

    int opcion;
    printf("Buscar por: 1) ID  2) Titulo  ");
    opcion = intPositivo();

    if(opcion == 1){
        int id;
        printf("Ingrese ID: ");
        id = intPositivo();

        for(int i = 0; i < contador; i++){
            if(libros[i].id == id){
                printf("\nLibro encontrado:\n");
                printf("Titulo: %s\nAutor: %s\nAno: %d\nEstado: %s\n",
                       libros[i].titulo, libros[i].autor,
                       libros[i].anio, libros[i].estado);
                return;
            }
        }

        printf("No se encontro libro con ese ID.\n");

    } else if(opcion == 2){
        char titulo[100];
        printf("Ingrese titulo: ");
        leerCadena(titulo, 100);

        for(int i = 0; i < contador; i++){
            if(strcmp(libros[i].titulo, titulo) == 0){
                printf("\nLibro encontrado:\n");
                printf("ID: %d\nAutor: %s\nAño: %d\nEstado: %s\n",
                       libros[i].id, libros[i].autor,
                       libros[i].anio, libros[i].estado);
                return;
            }
        }

        printf("No se encontro libro con ese titulo.\n");

    } else {
        printf("Opcion invalida.\n");
    }
}

void actualizarEstado(Libro *libros, int contador){
    if(contador == 0){
        printf("No hay libros registrados.\n");
        return;
    }

    int id;
    printf("Ingrese ID del libro a actualizar: ");
    id = intPositivo();

    for(int i = 0; i < contador; i++){
        if(libros[i].id == id){
            if(strcmp(libros[i].estado, "Disponible") == 0)
                strcpy(libros[i].estado, "Prestado");
            else
                strcpy(libros[i].estado, "Disponible");

            printf("Estado actualizado correctamente.\n");
            return;
        }
    }

    printf("No se encontro ese ID.\n");
}

void eliminarLibro(Libro **libros, int *contador){
    if(*contador == 0){
        printf("No hay libros registrados.\n");
        return;
    }

    int id;
    printf("Ingrese ID del libro a eliminar: ");
    id = intPositivo();

    for(int i = 0; i < *contador; i++){
        if((*libros)[i].id == id){

            for(int j = i; j < *contador - 1; j++){
                (*libros)[j] = (*libros)[j + 1];
            }

            (*contador)--;

            *libros = realloc(*libros, (*contador) * sizeof(Libro));

            printf("Libro eliminado correctamente.\n");
            return;
        }
    }

    printf("No existe un libro con ese ID.\n");
}
