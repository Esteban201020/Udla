#include <stdio.h>
#include <string.h>
#include "funciones.h"

void registrarLibro(struct Libro libros[], int *contador) {
    if (*contador >= MAX_LIBROS) {
        printf("\nNo se pueden registrar mas libros (limite 10).\n");
        return;
    }

    struct Libro nuevo;

    printf("\nIngrese ID del libro: ");
    scanf("%d", &nuevo.id);
    getchar();

    for (int i = 0; i < *contador; i++) {
        if (libros[i].id == nuevo.id) {
            printf("Error: El ID ya existe.\n");
            return;
        }
    }

    printf("Ingrese titulo: ");
    fgets(nuevo.titulo, sizeof(nuevo.titulo), stdin);
    nuevo.titulo[strcspn(nuevo.titulo, "\n")] = 0;

    printf("Ingrese autor: ");
    fgets(nuevo.autor, sizeof(nuevo.autor), stdin);
    nuevo.autor[strcspn(nuevo.autor, "\n")] = 0;

    printf("Ingrese ano de publicacion: ");
    scanf("%d", &nuevo.anio);
    getchar();

    strcpy(nuevo.estado, "Disponible");

    libros[*contador] = nuevo;
    (*contador)++;

    printf("\nLibro registrado exitosamente.\n");
}

void mostrarLibros(struct Libro libros[], int contador) {
    if (contador == 0) {
        printf("\nNo hay libros registrados.\n");
        return;
    }

    printf("\n%-5s %-30s %-20s %-10s %-12s\n",
           "ID", "TITULO", "AUTOR", "AÑO", "ESTADO");
    printf("-------------------------------------------------------------------------------\n");

    for (int i = 0; i < contador; i++) {
        printf("%-5d %-30s %-20s %-10d %-12s\n",
               libros[i].id, libros[i].titulo,
               libros[i].autor, libros[i].anio, libros[i].estado);
    }
}

void buscarLibro(struct Libro libros[], int contador) {
    if (contador == 0) {
        printf("\nNo hay libros para buscar.\n");
        return;
    }

    int opcion, id;
    char titulo[100];

    printf("\nBuscar por:\n1. ID\n2. Titulo\nOpcion: ");
    scanf("%d", &opcion);
    getchar();

    if (opcion == 1) {
        printf("Ingrese ID: ");
        scanf("%d", &id);

        for (int i = 0; i < contador; i++) {
            if (libros[i].id == id) {
                printf("\nLibro encontrado:\n");
                printf("ID: %d\nTitulo: %s\nAutor: %s\nAño: %d\nEstado: %s\n",
                       libros[i].id, libros[i].titulo,
                       libros[i].autor, libros[i].anio,
                       libros[i].estado);
                return;
            }
        }
        printf("No se encontro un libro con ese ID.\n");

    } else if (opcion == 2) {
        printf("Ingrese titulo: ");
        fgets(titulo, sizeof(titulo), stdin);
        titulo[strcspn(titulo, "\n")] = 0;

        for (int i = 0; i < contador; i++) {
            if (strcasecmp(libros[i].titulo, titulo) == 0) {
                printf("\nLibro encontrado:\n");
                printf("ID: %d\nTitulo: %s\nAutor: %s\nAño: %d\nEstado: %s\n",
                       libros[i].id, libros[i].titulo,
                       libros[i].autor, libros[i].anio,
                       libros[i].estado);
                return;
            }
        }
        printf("No se encontro un libro con ese titulo.\n");

    } else {
        printf("Opcion no valida.\n");
    }
}

void actualizarEstado(struct Libro libros[], int contador) {
    if (contador == 0) {
        printf("\nNo hay libros registrados.\n");
        return;
    }

    int id;
    printf("\nIngrese ID del libro a actualizar: ");
    scanf("%d", &id);

    for (int i = 0; i < contador; i++) {
        if (libros[i].id == id) {
            if (strcmp(libros[i].estado, "Disponible") == 0)
                strcpy(libros[i].estado, "Prestado");
            else
                strcpy(libros[i].estado, "Disponible");

            printf("Estado actualizado correctamente.\n");
            return;
        }
    }

    printf("No se encontro un libro con ese ID.\n");
}

void eliminarLibro(struct Libro libros[], int *contador) {
    if (*contador == 0) {
        printf("\nNo hay libros para eliminar.\n");
        return;
    }

    int id;
    printf("\nIngrese ID del libro a eliminar: ");
    scanf("%d", &id);

    for (int i = 0; i < *contador; i++) {
        if (libros[i].id == id) {
            for (int j = i; j < *contador - 1; j++) {
                libros[j] = libros[j + 1];
            }
            (*contador)--;
            printf("Libro eliminado correctamente.\n");
            return;
        }
    }

    printf("No se encontro un libro con ese ID.\n");
}
