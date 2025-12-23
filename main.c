#include <stdio.h>
#include "funciones.h"

int main(int argc, char *argv[]) {

    int opc2;

    do {
        int opc = menu();
        
        Cliente clientes[50];
        Vehiculo vehiculos[50];
        Factura facturas[50];

        switch (opc)
        {
        case 1:
            crearCliente();
            break;
        case 2:
            listarClientes(clientes);
            break;
        case 3:
            crearVehiculo();
            break;
        case 4:
            listarVehiculos(vehiculos);
            break;
        case 5:
            buscarVehiculosPreferencia(); 
            break;
        case 6:
            crearFactura();
            break;
        case 7:
            listarFacturas(facturas);
            break;
        case 8:
            printf("Saliendo...\n");
            return 0;
        default:
            printf("Opcion invalida.\n");
            break;
        }

        printf("\nDesea seleccionar otra opcion 1.Si/2.No: ");
        opc2 = leerEnteroConRango(1, 2);

    } while(opc2 == 1);

    return 0;
}