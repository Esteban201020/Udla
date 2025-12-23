typedef struct{
    char nombre[30];
    int cedula;
    char direccion[50];
    int edad; 
} Cliente;

typedef struct{
    int id;
    char marca[20];
    char modelo[20];
    char tipo[20]; 
    int anio;
    float precio;
    int disponible; 
} Vehiculo;

typedef struct{
    char detalle[50]; 
    float precio;
    int cantidad;
} Item;

typedef struct{
    Cliente cliente;
    int numProd;
    Item item[5]; 
    float total;
    char fecha[15];
} Factura;


void leerCadena(char *cadena, int n);
int leerEnteroConRango(int inicio, int fin);
float leerFlotanteConRango(float inicio, float fin);
int menu();


void crearCliente();
void listarClientes(Cliente *clientes);
void guardarCliente(Cliente *cliente);
int obtenerClientes(Cliente *clientes);


void crearVehiculo();
void guardarVehiculo(Vehiculo *vehiculo);
int obtenerVehiculos(Vehiculo *vehiculos);
void listarVehiculos(Vehiculo *vehiculos);
void editarVehiculoEstado(int id, int nuevoEstado);
void buscarVehiculosPreferencia(); 


void crearFactura(); 
void guardarFactura(Factura *factura);
int obtenerFacturas(Factura *facturas);
void listarFacturas(Factura *facturas);