#include <stdio.h>
#include "funciones.h"

int main() {
    int opcion;

    do {
        printf("\n=== CONCESIONARIA RUEDAS DE ORO ===\n");
        printf("1. Registrar vehiculo\n");
        printf("2. Listar vehiculos\n");
        printf("3. Buscar vehiculos por preferencia\n");
        printf("4. Registrar cliente\n");
        printf("5. Listar clientes\n");
        printf("6. Registrar venta (crea factura)\n");
        printf("7. Listar facturas\n");
        printf("8. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
        case 1: registrarVehiculo(); break;
        case 2: listarVehiculos(); break;
        case 3: buscarVehiculosPreferencia(); break;
        case 4: registrarCliente(); break;
        case 5: listarClientes(); break;
        case 6: registrarVenta(); break;
        case 7: listarFacturas(); break;
        case 8: printf("Saliendo...\n"); break;
        default: printf("Opcion invalida.\n");
        }

    } while (opcion != 8);

    return 0;
}
