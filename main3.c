#include <stdio.h>

int main() {
    int ID, Stock = 0, opcion, cantidad = 0, Agregar = 0, registrado = 0;
    char nombre[30];
    float precio = 0, ganancias = 0, descuento = 0, PrecioFinal = 0, Total = 0, Mdes = 0;

    do {
        printf("\n\t=== Tienda ===\n");  
        printf("\t1. Registrar producto\n");
        printf("\t2. Venta\n");
        printf("\t3. Reabastecer\n");
        printf("\t4. Informacion\n");
        printf("\t5. Ganancias\n");
        printf("\t6. Salir\n");
        printf("\tIngrese una opcion: ");   
        fflush(stdout); 
        scanf("%d", &opcion);          

        switch (opcion) {
            case 1: 
                printf("\n\tIngresar ID: ");
                fflush(stdout);
                scanf("%d", &ID);

                printf("\tNombre del producto: ");
                fflush(stdout);
                scanf(" %[^\n]", nombre); 

                do {
                    printf("\tStock inicial: ");
                    fflush(stdout);
                    scanf("%d", &Stock);
                    if (Stock <= 0) {
                        printf("\tIngrese un valor mayor a 0.\n");
                    }
                } while (Stock <= 0);

                do {
                    printf("\tValor unitario: ");
                    fflush(stdout);
                    scanf("%f", &precio);
                    if (precio <= 0) {
                        printf("\tDebe ingresar un valor positivo.\n");
                    }
                } while (precio <= 0);

                printf("\t Producto registrado con exito.\n");
                registrado = 1;
                break;

            case 2: 
                if (!registrado) {
                    printf("\tPrimero debe registrar un producto.\n");
                    break;
                }
                if (Stock == 0) {
                    printf("\tNo hay stock disponible.\n");
                } else {
                    do {
                        printf("\tIngrese cantidad a vender: ");
                        fflush(stdout);
                        scanf("%d", &cantidad);
                        if (cantidad <= 0) {
                            printf("\tCantidad inválida.\n");
                        } else if (cantidad > Stock) {
                            printf("\tStock insuficiente.\n");
                        }
                    } while (cantidad <= 0 || cantidad > Stock);

                    do {
                        printf("\tAplicar descuento (0-100): ");
                        fflush(stdout);
                        scanf("%f", &descuento);
                        if (descuento < 0 || descuento > 100) {
                            printf("\tDescuento inválido.\n");
                        }
                    } while (descuento < 0 || descuento > 100);

                    Mdes = precio * descuento / 100;     
                    PrecioFinal = precio - Mdes;
                    Total = PrecioFinal * cantidad;
                    Stock -= cantidad;
                    ganancias += Total;

                    printf("\tDescuento aplicado: %.2f%%\n", descuento);
                    printf("\tPrecio final por unidad: $%.2f\n", PrecioFinal);
                    printf("\tTotal de la venta: $%.2f\n", Total);
                    printf("\tStock restante: %d\n", Stock);
                }
                break;

            case 3: 
                if (!registrado) {
                    printf("\tPrimero debe registrar un producto.\n");
                    break;
                }
                do {
                    printf("\n\tAgregar mas producto: ");
                    fflush(stdout);
                    scanf("%d", &Agregar);
                    if (Agregar <= 0) {
                        printf("\tNúmero inválido.\n");
                    }
                } while (Agregar <= 0);
                Stock += Agregar;
                printf("\tStock actualizado: %d\n", Stock);
                break;

            case 4: 
                if (!registrado) {
                    printf("\tPrimero debe registrar un producto.\n");
                    break;
                }
                printf("\n\t=== Informacion del producto ===\n");
                printf("\tID: %d\n", ID);
                printf("\tNombre: %s\n", nombre);
                printf("\tStock: %d\n", Stock);
                printf("\tPrecio unitario: $%.2f\n", precio);
                break;

            case 5:  
                if (!registrado) {
                    printf("\tPrimero debe registrar un producto.\n");
                    break;
                }
                printf("\n\tGanancias totales: $%.2f\n", ganancias);
                break;

            case 6: 
                printf("\tSaliendo...\n");
                break;

            default:
                printf("\tOpcion invalida.\n");
        }
    } while (opcion != 6);

    return 0;
}
