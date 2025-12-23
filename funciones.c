#include <stdio.h>
#include <string.h>
#include "funciones.h"

void leerCadena(char *cadena, int n){
    fflush(stdin);
    fgets(cadena, n, stdin);
    int len = strlen(cadena) - 1;
    if(cadena[len] == '\n') cadena[len] = '\0';
}

int leerEnteroConRango(int inicio, int fin){
    int num;
    int val;
    do{
        val = scanf("%d", &num);
        if (val!=1 || num < inicio || num > fin){
            printf("Valor incorrecto. Intente de nuevo (%d-%d): ", inicio, fin);
            fflush(stdin);
        }
    }while(val!=1 || num < inicio || num > fin);
    return num;
}

float leerFlotanteConRango(float inicio, float fin){
    float num;
    int val;
    do{
        val = scanf("%f", &num);
        if (val!=1 || num < inicio || num > fin){
            printf("Valor incorrecto. Intente de nuevo: ");
            fflush(stdin);
        }
    }while(val!=1 || num < inicio || num > fin);
    return num;
}

int menu(){
    int opc;
    printf("\n=== CONCESIONARIA RUEDAS DE ORO ===\n");
    printf("1. Crear cliente\n");
    printf("2. Listar clientes\n");
    printf("3. Registrar Vehiculo\n");
    printf("4. Listar Vehiculos\n");
    printf("5. Buscar Vehiculos\n");
    printf("6. Crear Factura\n");
    printf("7. Listar Facturas\n");
    printf("8. Salir\n");
    printf(">> ");
    opc = leerEnteroConRango(1, 8);
    return opc;
}


void guardarCliente(Cliente *cliente){
    FILE *f;
    f = fopen("clientes.dat", "ab+");
    if (f==NULL) { printf("Error al abrir archivo\n"); return; }
    fwrite(cliente, sizeof(Cliente), 1, f);
    fclose(f);
}

int obtenerClientes(Cliente *clientes){
    FILE *f;
    f = fopen("clientes.dat", "rb");
    if (f==NULL) return 0;
    int count = fread(clientes, sizeof(Cliente), 50, f);
    fclose(f);
    return count;
}

void crearCliente(){
    Cliente cliente;
    printf("Ingrese Nombre: ");
    leerCadena(cliente.nombre, 30);
    printf("Ingrese Cedula: ");
    cliente.cedula = leerEnteroConRango(1, 999999999);
    printf("Ingrese Direccion: ");
    leerCadena(cliente.direccion, 50);
    printf("Ingrese Edad: ");
    cliente.edad = leerEnteroConRango(18, 100);
    
    guardarCliente(&cliente);
    printf("Cliente guardado con exito.\n");
}

void listarClientes(Cliente *clientes){
    int c = obtenerClientes(clientes);
    printf("#\tCedula\t\tNombre\t\tEdad\n");
    for (int i = 0; i < c; i++) {
        printf("%d\t%d\t\t%s\t\t%d\n", i+1, clientes[i].cedula, clientes[i].nombre, clientes[i].edad);
    }
}

void guardarVehiculo(Vehiculo *vehiculo){
    FILE *f;
    f = fopen("vehiculos.dat", "ab+");
    if (f==NULL) { printf("Error archivo vehiculos\n"); return; }
    fwrite(vehiculo, sizeof(Vehiculo), 1, f);
    fclose(f);
}

int obtenerVehiculos(Vehiculo *vehiculos){
    FILE *f;
    f = fopen("vehiculos.dat", "rb");
    if (f==NULL) return 0;
    int count = fread(vehiculos, sizeof(Vehiculo), 50, f);
    fclose(f);
    return count;
}

void crearVehiculo(){
    Vehiculo v;
    printf("Ingrese ID Vehiculo (1-999): ");
    v.id = leerEnteroConRango(1, 999);
    printf("Marca: ");
    leerCadena(v.marca, 20);
    printf("Modelo: ");
    leerCadena(v.modelo, 20);
    printf("Tipo (Camioneta/Sedan/SUV): ");
    leerCadena(v.tipo, 20);
    printf("Anio: ");
    v.anio = leerEnteroConRango(1980, 2025);
    printf("Precio: ");
    v.precio = leerFlotanteConRango(500, 100000);
    v.disponible = 1; 

    guardarVehiculo(&v);
    printf("Vehiculo registrado.\n");
}

void listarVehiculos(Vehiculo *vehiculos){
    int c = obtenerVehiculos(vehiculos);
    printf("#\tMarca\tModelo\tTipo\tPrecio\tEstado\n");
    for (int i = 0; i < c; i++) {
        printf("%d\t%s\t%s\t%s\t%.2f\t%s\n", 
               vehiculos[i].id, vehiculos[i].marca, vehiculos[i].modelo, vehiculos[i].tipo, 
               vehiculos[i].precio, (vehiculos[i].disponible ? "Disponible" : "Vendido"));
    }
}


void editarVehiculoEstado(int id, int nuevoEstado){
    Vehiculo v;
    FILE *f = fopen("vehiculos.dat", "rb+");
    if (f == NULL) return;

    while(fread(&v, sizeof(Vehiculo), 1, f)){
        if(v.id == id){
            v.disponible = nuevoEstado;
            fseek(f, -((long)sizeof(Vehiculo)), SEEK_CUR); 
            fwrite(&v, sizeof(Vehiculo), 1, f); 
            break;
        }
    }
    fclose(f);
}


void buscarVehiculosPreferencia(){
    Vehiculo vehiculos[50];
    int c = obtenerVehiculos(vehiculos);
    char marca[20];
    float presupuesto;

    printf("\n--- BUSQUEDA ESPECIAL ---\n");
    printf("Ingrese Marca preferida: ");
    leerCadena(marca, 20);
    printf("Ingrese Presupuesto maximo: ");
    presupuesto = leerFlotanteConRango(1, 200000);

    printf("\nResultados:\n");
    int encontrados = 0;
    for(int i=0; i<c; i++){
        if(vehiculos[i].disponible == 1 && 
           strcmp(vehiculos[i].marca, marca) == 0 && 
           vehiculos[i].precio <= presupuesto){
            
            printf("ID:%d | %s %s | $%.2f\n", vehiculos[i].id, vehiculos[i].marca, vehiculos[i].modelo, vehiculos[i].precio);
            encontrados++;
        }
    }
    if(encontrados == 0) printf("No se encontraron vehiculos.\n");
}



void guardarFactura(Factura *factura){
    FILE *f;
    f = fopen("facturas.dat", "ab+");
    if (f==NULL) { printf("Error archivo facturas\n"); return; }
    fwrite(factura, sizeof(Factura), 1, f);
    fclose(f);
}

int obtenerFacturas(Factura *facturas){
    FILE *f;
    f = fopen("facturas.dat", "rb");
    if (f==NULL) return 0;
    int count = fread(facturas, sizeof(Factura), 50, f);
    fclose(f);
    return count;
}

void crearFactura(){
    Factura factura;
    Cliente clientes[50];
    Vehiculo vehiculos[50];
    

    int cClientes = obtenerClientes(clientes);
    if (cClientes == 0) { printf("No hay clientes registrados.\n"); return; }

    printf("Seleccione un cliente:\n");
    for (int i = 0; i < cClientes; i++){
        printf("%d. %s (CI: %d)\n", i+1, clientes[i].nombre, clientes[i].cedula);
    }
    int opcCliente = leerEnteroConRango(1, cClientes);
    factura.cliente = clientes[opcCliente-1];

 
    int cVehiculos = obtenerVehiculos(vehiculos);
    printf("Seleccione el vehiculo a comprar:\n");
    
   
    int mapaIndices[50];
    int disponibles = 0;
    
    for (int i = 0; i < cVehiculos; i++){
        if(vehiculos[i].disponible == 1){
            printf("%d. %s %s - $%.2f\n", disponibles+1, vehiculos[i].marca, vehiculos[i].modelo, vehiculos[i].precio);
            mapaIndices[disponibles] = i;
            disponibles++; 
        }
    }

    if(disponibles == 0) { printf("No hay vehiculos disponibles.\n"); return; }

    int opcVehiculo = leerEnteroConRango(1, disponibles);
    int indiceReal = mapaIndices[opcVehiculo-1];
    Vehiculo vSeleccionado = vehiculos[indiceReal];

    
    printf("Ingrese Fecha (dd/mm/aaaa): ");
    leerCadena(factura.fecha, 15);
    
    factura.numProd = 1; 
    
    
    strcpy(factura.item[0].detalle, vSeleccionado.marca);
    strcat(factura.item[0].detalle, " ");
    strcat(factura.item[0].detalle, vSeleccionado.modelo);
    
    factura.item[0].precio = vSeleccionado.precio;
    factura.item[0].cantidad = 1;
    factura.total = vSeleccionado.precio;

   
    guardarFactura(&factura);
    editarVehiculoEstado(vSeleccionado.id, 0); 

    printf("Factura generada y vehiculo vendido exitosamente.\n");
}

void listarFacturas(Factura *facturas){
    int c = obtenerFacturas(facturas);
    for (int i = 0; i < c; i++)
    {
        printf("\n--- FACTURA ---\n");
        printf("Fecha: %s\n", facturas[i].fecha);
        printf("Cliente: %s (CI: %d)\n", facturas[i].cliente.nombre, facturas[i].cliente.cedula);
        printf("Detalle:\n");
        for(int j=0; j<facturas[i].numProd; j++){
            printf(" - %s | $%.2f\n", facturas[i].item[j].detalle, facturas[i].item[j].precio);
        }
        printf("TOTAL: $%.2f\n", facturas[i].total);
    }
}