#ifndef FUNCIONES_H
#define FUNCIONES_H

#define MAX_LIBROS 10

struct Libro {
    int id;
    char titulo[100];
    char autor[50];
    int anio;
    char estado[15];
};


void registrarLibro(struct Libro libros[], int *contador);
void mostrarLibros(struct Libro libros[], int contador);
void buscarLibro(struct Libro libros[], int contador);
void actualizarEstado(struct Libro libros[], int contador);
void eliminarLibro(struct Libro libros[], int *contador);

#endif