typedef struct {
    int id;
    char titulo[100];
    char autor[50];
    int anio;
    char estado[15]; 
} Libro;


void limpiarBuffer();
int intPositivo();
void leerCadena(char *cadena, int n);
int buscarIndicePorID(Libro *libros, int *cont, int id);
int menu();


void registrarLibro(Libro *libros, int *cont);
void mostrarLibros(Libro *libros, int *cont);
void buscarLibro(Libro *libros, int *cont);
void actualizarEstado(Libro *libros, int *cont);
void eliminarLibro(Libro *libros, int *cont);