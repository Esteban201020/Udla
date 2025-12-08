typedef struct {
    int id;
    char titulo[100];
    char autor[50];
    int anio;
    char estado[15];
} Libro;


void leerCadena(char *cadena, int n);
int intPositivo();
int validarAnio();
void validarEstado(char *estado);

void registrarLibro(Libro **libros, int *contador);
void mostrarLibros(Libro *libros, int contador);
void buscarLibro(Libro *libros, int contador);
void actualizarEstado(Libro *libros, int contador);
void eliminarLibro(Libro **libros, int *contador);
