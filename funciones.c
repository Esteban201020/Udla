#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funciones.h"

void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int intPositivo() {
    int num;
    int auxiliar;
    
    do {
        if (scanf("%d", &num) != 1) {
            auxiliar = 0; 
        } else {
            auxiliar = 1; 
        }

        if (auxiliar != 1 || num < 0) {
            printf("El dato ingresado es incorrecto\n");
            printf("Vuelva a ingresarlo\n");
            limpiarBuffer();
        }
        
    } while (auxiliar != 1 || num < 0);

    limpiarBuffer(); 
    return num;
}

void leerCadena(char *cadena, int n) {
    fgets(cadena, n, stdin);
    int len = strlen(cadena);
    if (len > 0 && cadena[len - 1] == '\n') {
        cadena[len - 1] = '\0';
    }
}

int buscarIndicePorID(Libro *libros, int *cont, int id) {
    for (int i = 0; i < *cont; i++) {
        if (libros[i].id == id) {
            return i;
        }
    }
    return -1;
}

int menu() {
    int opcion;
    printf("\n--- GESTION DE BIBLIOTECA ---\n");
    printf("1. Registrar libro\n");
    printf("2. Mostrar lista de libros\n");
    printf("3. Buscar libro \n");
    printf("4. Actualizar estado\n");
    printf("5. Eliminar libro\n");
    printf("6. Salir\n");
    printf("Seleccione una opcion: ");
    
    opcion = intPositivo(); 
    return opcion;
}

void registrarLibro(Libro *libros, int *cont) {
    if (*cont >= 10) {
        printf("Error: La biblioteca está llena (Maximo 10 libros).\n");
        return;
    }
    int espacioLibre = 10 - *cont;
    int cantidad = 0;

    printf("\n--- REGISTRO DE LIBROS ---\n");
    printf("Espacios disponibles: %d libros.\n", espacioLibre);

    do {
        printf("Cuantos libros desea ingresar ahora? -> ");
        cantidad = intPositivo();

        if (cantidad > espacioLibre) {
            printf("Error: Solo hay espacio para %d libros.\n", espacioLibre);
        } else if (cantidad == 0) {
            printf("Cantidad debe ser mayor a 0.\n");
        }
    } while (cantidad > espacioLibre || cantidad == 0);

    for (int k = 0; k < cantidad; k++) {
        printf("\n--- Ingresando libro %d de %d ---\n", k + 1, cantidad);

        Libro nuevoLibro;
        int idDuplicado = 0;

        do {
            idDuplicado = 0;
            printf("ID del libro -> ");
            nuevoLibro.id = intPositivo(); 

            if (buscarIndicePorID(libros, cont, nuevoLibro.id) != -1) {
                printf("Error: Ya existe un libro con el ID %d.\n", nuevoLibro.id);
                idDuplicado = 1;
            }
        } while (idDuplicado);

        printf("Titulo -> ");
        leerCadena(nuevoLibro.titulo, 100); 
        printf("Autor -> ");
        leerCadena(nuevoLibro.autor, 50); 
        printf("Anio de publicacion -> ");
        nuevoLibro.anio = intPositivo(); 
        strcpy(nuevoLibro.estado, "Disponible");
        libros[*cont] = nuevoLibro;
        (*cont)++; 
        
        printf("Libro guardado correctamente.\n");
    }
    
    printf("\n--- Registro finalizado. Total libros: %d ---\n", *cont);
}

void mostrarLibros(Libro *libros, int *cont) {
    if (*cont == 0) {
        printf("\nNo hay libros registrados para mostrar.\n");
        return;
    }

    printf("\nID\t\t\tTitulo\t\t\tAutor\t\t\tAnio\tEstado\n");
    printf("----------------------------------------------------------------------------------\n");

    for (int i = 0; i < *cont; i++) {
        printf("%d\t\t\t%s\t\t\t%s\t\t\t%d\t%s\n",
               libros[i].id,
               libros[i].titulo,
               libros[i].autor,
               libros[i].anio,
               libros[i].estado);
    }
    printf("----------------------------------------------------------------------------------\n");
}

void buscarLibro(Libro *libros, int *cont) {
    if (*cont == 0) {
        printf("\nError: No hay libros registrados. Ingrese uno primero.\n");
        return;
    }

    int opcion, idBusqueda;
    char tituloBusqueda[100];
    int encontrado = 0;

    printf("\nBuscar por: 1. ID, 2. Titulo\n");
    opcion = intPositivo(); 

    if (opcion == 1) {
        printf("Ingrese ID a buscar -> ");
        idBusqueda = intPositivo(); 
        
        for (int i = 0; i < *cont; i++) {
            if (libros[i].id == idBusqueda) {
                printf("\n--- LIBRO ENCONTRADO ---\n");
                printf("ID: %d\nTitulo: %s\nAutor: %s\nAnio: %d\nEstado: %s\n", 
                    libros[i].id, libros[i].titulo, libros[i].autor, libros[i].anio, libros[i].estado);
                encontrado = 1;
                break;
            }
        }
    } else if (opcion == 2) {
        printf("Ingrese Titulo a buscar -> ");
        leerCadena(tituloBusqueda, 100);

        for (int i = 0; i < *cont; i++) {
            if (strcmp(libros[i].titulo, tituloBusqueda) == 0) {
                printf("\n--- LIBRO ENCONTRADO ---\n");
                printf("ID: %d\nTitulo: %s\nAutor: %s\nAnio: %d\nEstado: %s\n", 
                    libros[i].id, libros[i].titulo, libros[i].autor, libros[i].anio, libros[i].estado);
                encontrado = 1;
            }
        }
    } else {
        printf("Opcion invalida.\n");
    }

    if (!encontrado && (opcion == 1 || opcion == 2)) printf("Libro no encontrado.\n");
}

void actualizarEstado(Libro *libros, int *cont) {
    if (*cont == 0) {
        printf("\nError: No hay libros registrados. Ingrese uno primero.\n");
        return;
    }

    printf("\n--- SELECCIONE UN LIBRO PARA ACTUALIZAR ---\n");
    mostrarLibros(libros, cont); 

    int id, indice;
    printf("\nIngrese ID del libro para cambiar su estado -> ");
    id = intPositivo(); 

    indice = buscarIndicePorID(libros, cont, id);

    if (indice != -1) {
        if (strcmp(libros[indice].estado, "Disponible") == 0) {
            strcpy(libros[indice].estado, "Prestado");
        } else {
            strcpy(libros[indice].estado, "Disponible");
        }
        printf("Estado actualizado a: %s\n", libros[indice].estado);
    } else {
        printf("Libro no encontrado.\n");
    }
}

void eliminarLibro(Libro *libros, int *cont) {
    if (*cont == 0) {
        printf("\nError: No hay libros registrados. Ingrese uno primero.\n");
        return;
    }
    printf("\n--- SELECCIONE UN LIBRO PARA ELIMINAR ---\n");
    mostrarLibros(libros, cont);

    int id, indice;
    printf("\nIngrese ID del libro a eliminar -> ");
    id = intPositivo(); 

    indice = buscarIndicePorID(libros, cont, id);

    if (indice != -1) {
        for (int j = indice; j < *cont - 1; j++) {
            libros[j] = libros[j + 1];
        }
        (*cont)--; 
        printf("Libro eliminado correctamente.\n");
    } else {
        printf("Libro no encontrado.\n");
    }
}