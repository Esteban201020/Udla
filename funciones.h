#ifndef FUNCIONES_H
#define FUNCIONES_H

typedef struct {
    int id;
    char marca[20];
    char modelo[20];
    char tipo[20];
    int anio;
    float precio;
    int disponible;
} Vehiculo;

typedef struct {
    int id;
    char nombre[30];
    int edad;
} Cliente;

typedef struct {
    int idVenta;
    int idCliente;
    int idVehiculo;
    float precioVenta;
} Venta;

typedef struct {
    int idFactura;
    int idVenta;
    int idCliente;
    int idVehiculo;
    float total;
    char fecha[15];
} Factura;

// VEHICULOS
void registrarVehiculo();
void listarVehiculos();
void buscarVehiculosPreferencia();
void actualizarVehiculo(Vehiculo v);

// CLIENTES
void registrarCliente();
void listarClientes();

// VENTAS
void registrarVenta();

// FACTURAS
void crearFactura(Venta v);
void listarFacturas();

#endif
