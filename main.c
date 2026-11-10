#include <stdio.h>
#include "funciones.h"

int main() {
    char nombres[5][50];
    int demandas[5];
    float tiempos[5];
    float recursos[5];

    int totalProductos = 0;
    int opcion;

    float capacidadTiempo = 0.0f;
    float capacidadRecursos = 0.0f;

    printf("Optimizacion de Produccion\n");

    do {
        printf("Capacidad maxima de tiempo (horas > 0): ");
        scanf("%f", &capacidadTiempo);
    } while (capacidadTiempo <= 0.0f);

    do {
        printf("Capacidad maxima de recursos (> 0): ");
        scanf("%f", &capacidadRecursos);
    } while (capacidadRecursos <= 0.0f);

    do {
        printf("\nMenu Principal\n");
        printf("1. Ingresar producto\n");
        printf("2. Editar producto\n");
        printf("3. Eliminar producto\n");
        printf("4. Listar productos\n");
        printf("5. Evaluar produccion\n");
        printf("6. Salir\n");
        printf("Opcion: ");
        scanf("%d", &opcion);
        switch (opcion) {
            case 1:
                ingresarProducto(nombres, demandas, tiempos, recursos, &totalProductos);
                break;
            case 2:
                editarProducto(nombres, demandas, tiempos, recursos, totalProductos);
                break;
            case 3:
                eliminarProducto(nombres, demandas, tiempos, recursos, &totalProductos);
                break;
            case 4:
                listarProductos(nombres, demandas, tiempos, recursos, totalProductos);
                break;
            case 5:
                if (totalProductos == 0) {
                    printf("\nNo hay productos registrados para evaluar.\n");
                } else {
                    float tTotal = 0.0f, rTotal = 0.0f;
                    int esFactible = 0;

                    calcularOptimizacion(demandas, tiempos, recursos, totalProductos, 
                                         capacidadTiempo, capacidadRecursos, 
                                         &tTotal, &rTotal, &esFactible);

                    printf("\nResultados:\n");
                    printf("Tiempo requerido: %.2f horas (Disponible: %.2f)\n", tTotal, capacidadTiempo);
                    printf("Recursos requeridos: %.2f unidades (Disponible: %.2f)\n", rTotal, capacidadRecursos);
                    
                    if (esFactible) {
                        printf("Estado: La fabrica cumple con la demanda.\n");
                    } else {
                        printf("Estado: No se puede cumplir la demanda.\n");
                        if (tTotal > capacidadTiempo) {
                            printf("Faltan %.2f horas de tiempo.\n", tTotal - capacidadTiempo);
                        }
                        if (rTotal > capacidadRecursos) {
                            printf("Faltan %.2f unidades de recursos.\n", rTotal - capacidadRecursos);
                        }
                    }
                }
                break;
            case 6:
                printf("\nSaliendo del programa...\n");
                break;
            default:
                printf("\nOpcion invalida. Intente de nuevo.\n");
                break;
        }
    } while (opcion != 6);

    return 0;
}