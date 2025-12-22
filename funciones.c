#include <stdio.h>
#include <string.h>
#include "funciones.h"

// ================= VEHICULOS =================

void registrarVehiculo() {
    FILE* f = fopen("vehiculos.dat", "ab");
    Vehiculo v;

    if (!f) return;

    printf("ID: ");
    scanf("%d", &v.id);
    printf("Marca: ");
    scanf("%s", v.marca);
    printf("Modelo: ");
    scanf("%s", v.modelo);
    printf("Tipo (camioneta, sedan, SUV): ");
    scanf("%s", v.tipo);
    printf("Anio: ");
    scanf("%d", &v.anio);
    printf("Precio: ");
    scanf("%f", &v.precio);

    v.disponible = 1;

    fwrite(&v, sizeof(Vehiculo), 1, f);
    fclose(f);

    printf("Vehiculo registrado.\n");
}

void listarVehiculos() {
    FILE* f = fopen("vehiculos.dat", "rb");
    Vehiculo v;

    if (!f) return;

    printf("\n--- VEHICULOS ---\n");
    while (fread(&v, sizeof(Vehiculo), 1, f)) {
        if (v.disponible)
            printf("ID:%d | %s %s | $%.2f\n", v.id, v.marca, v.modelo, v.precio);
    }

    fclose(f);
}

void buscarVehiculosPreferencia() {
    FILE* f = fopen("vehiculos.dat", "rb");
    Vehiculo v;
    char marca[20];
    float presupuesto;

    if (!f) return;

    printf("Marca deseada: ");
    scanf("%s", marca);
    printf("Presupuesto maximo: ");
    scanf("%f", &presupuesto);

    while (fread(&v, sizeof(Vehiculo), 1, f)) {
        if (v.disponible && strcmp(v.marca, marca) == 0 && v.precio <= presupuesto) {
            printf("ID:%d | %s %s | $%.2f\n", v.id, v.modelo, v.tipo, v.precio);
        }
    }

    fclose(f);
}

void actualizarVehiculo(Vehiculo veh) {
    FILE* f = fopen("vehiculos.dat", "rb+");
    Vehiculo v;

    if (!f) return;

    while (fread(&v, sizeof(Vehiculo), 1, f)) {
        if (v.id == veh.id) {
            fseek(f, -(long)sizeof(Vehiculo), SEEK_CUR);
            fwrite(&veh, sizeof(Vehiculo), 1, f);
            break;
        }
    }

    fclose(f);
}

// ================= CLIENTES =================

void registrarCliente() {
    FILE* f = fopen("clientes.dat", "ab");
    Cliente c;

    if (!f) return;

    printf("ID: ");
    scanf("%d", &c.id);
    printf("Nombre: ");
    scanf("%s", c.nombre);
    printf("Edad: ");
    scanf("%d", &c.edad);

    fwrite(&c, sizeof(Cliente), 1, f);
    fclose(f);

    printf("Cliente registrado.\n");
}

void listarClientes() {
    FILE* f = fopen("clientes.dat", "rb");
    Cliente c;

    if (!f) {
        printf("No hay clientes registrados.\n");
        return;
    }

    printf("\n--- CLIENTES ---\n");
    while (fread(&c, sizeof(Cliente), 1, f)) {
        printf("ID:%d | Nombre:%s | Edad:%d\n", c.id, c.nombre, c.edad);
    }

    fclose(f);
}

// ================= VENTAS =================

void registrarVenta() {
    FILE* f = fopen("ventas.dat", "ab");
    Venta v;
    Vehiculo veh;
    FILE* fv = fopen("vehiculos.dat", "rb");

    if (!f || !fv) return;

    printf("ID Venta: ");
    scanf("%d", &v.idVenta);
    printf("ID Cliente: ");
    scanf("%d", &v.idCliente);
    printf("ID Vehiculo: ");
    scanf("%d", &v.idVehiculo);

    while (fread(&veh, sizeof(Vehiculo), 1, fv)) {
        if (veh.id == v.idVehiculo && veh.disponible) {
            v.precioVenta = veh.precio;
            veh.disponible = 0;
            actualizarVehiculo(veh);
            break;
        }
    }

    fwrite(&v, sizeof(Venta), 1, f);
    fclose(f);
    fclose(fv);

    crearFactura(v);
    printf("Venta y factura registradas.\n");
}

// ================= FACTURAS =================

void crearFactura(Venta v) {
    FILE* f = fopen("facturas.dat", "ab");
    Factura fac;

    if (!f) return;

    fac.idFactura = v.idVenta;
    fac.idVenta = v.idVenta;
    fac.idCliente = v.idCliente;
    fac.idVehiculo = v.idVehiculo;
    fac.total = v.precioVenta;

    printf("Fecha (dd/mm/aaaa): ");
    scanf("%s", fac.fecha);

    fwrite(&fac, sizeof(Factura), 1, f);
    fclose(f);
}

void listarFacturas() {
    FILE* f = fopen("facturas.dat", "rb");
    Factura fac;

    if (!f) {
        printf("No hay facturas.\n");
        return;
    }

    printf("\n--- FACTURAS ---\n");
    while (fread(&fac, sizeof(Factura), 1, f)) {
        printf("Factura:%d | Cliente:%d | Vehiculo:%d | Total:$%.2f | Fecha:%s\n",
               fac.idFactura, fac.idCliente, fac.idVehiculo, fac.total, fac.fecha);
    }

    fclose(f);
}
