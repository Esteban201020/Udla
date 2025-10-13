#include <stdio.h>
#include <string.h>

int main (int argc, char *argv[]) {

    int estudiantes = 5, asignaturas = 3;
    float notas[5][3];
    int opc;
    int datosIngresados = 0;
    char materias[3][20] = {"Matematicas", "Historia   ", "Programacion"};
    char entrada[20];
    int conversionOk;


    do
    {
        printf("\n==== MENU PRINCIPAL ====\n");
        printf("1. Ingresar notas\n");
        printf("2. Mostrar promedio por estudiante\n");
        printf("3. Mostrar promedio por asignatura\n");
        printf("4. Mostrar notas altas y bajas (estudiantes y asignaturas)\n");
        printf("5. Mostrar aprobados y reprobados por asignatura\n");
        printf("6. Salir\n");
        printf("Seleccione la opcion: ");
        scanf("%d", &opc);

        fgets(entrada, sizeof(entrada), stdin);
        conversionOk = sscanf(entrada, "%d", &opc);

          if (conversionOk != 1)
        {
            printf("\n Error: Debe ingresar un numero (1-6)\n");
            continue; 
        }
        switch (opc)
        {
        case 1:
            if (datosIngresados == 1)
            {
                printf("\n Ya se ingresaron las notas. No puede volver a ingresarlas.\n");
                break;
            }
            for (int i = 0; i < estudiantes; i++)
            {
                printf("\n--- Estudiante %d ---\n", i + 1);
                for (int j = 0; j < asignaturas; j++)
                {
                    do
                    {
                        printf("Nota de %s: ", materias[j]);
                        fgets(entrada, sizeof(entrada), stdin);
                            conversionOk = sscanf(entrada, "%f", &notas[i][j]);

                            if (conversionOk != 1)
                            {
                                printf("Error: Ingrese un numero valido.\n");
                                continue;
                            }
                        if (notas[i][j] < 0 || notas[i][j] > 10)
                           printf("La nota ingresada debe estar entre 0 y 10.\n");
                    } while (notas[i][j] < 0 || notas[i][j] > 10);
                }
            }
            datosIngresados = 1;
            printf("\n Notas ingresadas correctamente");
            break;
        
        case 2:
            if (datosIngresados == 0)
            {
                printf("\n Primero ingrese las notas (opcion 1).\n");
                break;
            }

            printf("\n==== PROMEDIO POR ESTUDIANTE ====\n");
            for (int i = 0; i < estudiantes; i++)
            {
                float suma = 0;
                for (int j = 0; j < asignaturas; j++)
                {
                    suma += notas[i][j];
                }
                float promedio = suma / asignaturas;
                printf("Estudiantes %d -> Promedio: %.2f\n", i + 1, promedio);
            }
            break;
        case 3: 
            if(datosIngresados == 0)
            {
               printf("\n Primero ingrese las notas (opcion 1).\n");
               break;
            }

            printf("\n==== PROMEDIO POR ASIGNATURA ====\n");
            for(int j = 0; j < asignaturas; j++)
            {
                float suma = 0;
                for (int i = 0; i < estudiantes; i++)
                {
                   suma += notas[i][j]; 
                }
                float promedio = suma / estudiantes;
                printf("%s -> Promedio: %.2f\n", materias[j], promedio);
            }
            break;
        case 4:
            if(datosIngresados == 0)
            {
               printf("\n Primero ingrese las notas (opcion 1).\n");
               break;
            }
             printf("\n===== NOTAS ALTAS Y BAJAS POR ESTUDIANTE =====\n");
            for (int i = 0; i < estudiantes; i++)
            {
                float mayor = notas[i][0];
                float menor = notas[i][0];
                for (int j = 1; j < asignaturas; j++)
                {
                    if (notas[i][j] > mayor)
                        mayor = notas[i][j];
                    if (notas[i][j] < menor)
                        menor = notas[i][j];
                }
                printf("Estudiante %d -> Alta: %.2f | Baja: %.2f\n", i + 1, mayor, menor);
            }

            printf("\n===== NOTAS ALTAS Y BAJAS POR ASIGNATURA =====\n");
            for (int j = 0; j < asignaturas; j++)
            {
                float mayor = notas[0][j];
                float menor = notas[0][j];
                for (int i = 1; i < estudiantes; i++)
                {
                    if (notas[i][j] > mayor)
                        mayor = notas[i][j];
                    if (notas[i][j] < menor)
                        menor = notas[i][j];
                }
                printf("%s -> Alta: %.2f | Baja: %.2f\n", materias[j], mayor, menor);
            }
            break;
        case 5:
            if (datosIngresados == 0)
            {
                printf("\n Primero ingrese las notas (opcion 1).\n");
                break;
            }

            printf("\n===== APROBADOS Y REPROBADOS POR ASIGNATURA =====\n");
            for (int j = 0; j < asignaturas; j++)
            {
                int aprobados = 0, reprobados = 0;
                for (int i = 0; i < estudiantes; i++)
                {
                    if (notas[i][j] >= 6)
                        aprobados++;
                    else
                        reprobados++;
                }
                printf("%s -> Aprobados: %d | Reprobados: %d\n",
                       materias[j], aprobados, reprobados);
            }
            break;
        case 6:
            printf("\n Saliendo...\n");
            break;
    
        default:
           printf("\n Opcion no valida. Intente de nuevo.\n");
            break;
        }
    } while (opc != 6);
    
    return 0;
}  