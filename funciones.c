#include <stdio.h>
#include "funciones.h"

int compararCadenasManual(const char *cad1, const char *cad2) {
    int i = 0;
    while (*(cad1 + i) != '\0' && *(cad2 + i) != '\0') {
        if (*(cad1 + i) != *(cad2 + i)) {
            return 0;
        }
        i++;
    }
    if (*(cad1 + i) == '\0' && *(cad2 + i) == '\0') {
        return 1;
    }
    return 0;
}

int buscarProducto(char nombres[][50], int total, const char *objetivo) {
    for (int i = 0; i < total; i++) {
        if (compararCadenasManual(*(nombres + i), objetivo) == 1) {
            return i;
        }
    }
    return -1;
}

void ingresarProducto(char nombres[][50], int *demandas, float *tiempos, float *recursos, int *total) {
    if (*total >= 5) {
        printf("\nCapacidad maxima alcanzada (5 productos).\n");
        return;
    }

    int idx = *total;
    printf("\nRegistro de producto %d\n", idx + 1);
    printf("Nombre del producto: ");
    scanf("%49s", *(nombres + idx));

    do {
        printf("Demanda solicitada (> 0): ");
        scanf("%d", (demandas + idx));
    } while (*(demandas + idx) <= 0);

    do {
        printf("Tiempo unitario de fabricacion (horas > 0): ");
        scanf("%f", (tiempos + idx));
    } while (*(tiempos + idx) <= 0.0f);

    do {
        printf("Recurso unitario necesario (> 0): ");
        scanf("%f", (recursos + idx));
    } while (*(recursos + idx) <= 0.0f);

    (*total)++;
    printf("Producto registrado con exito.\n");
}

void editarProducto(char nombres[][50], int *demandas, float *tiempos, float *recursos, int total) {
    if (total == 0) {
        printf("\nNo hay productos registrados.\n");
        return;
    }

    char buscado[50];
    printf("\nIngrese el nombre del producto a editar: ");
    scanf("%49s", buscado);

    int idx = buscarProducto(nombres, total, buscado);
    if (idx == -1) {
        printf("Producto no encontrado.\n");
        return;
    }

    printf("\nEditando: %s\n", *(nombres + idx));
    printf("Nuevo nombre: ");
    scanf("%49s", *(nombres + idx));

    do {
        printf("Nueva demanda (> 0): ");
        scanf("%d", (demandas + idx));
    } while (*(demandas + idx) <= 0);

    do {
        printf("Nuevo tiempo unitario (horas > 0): ");
        scanf("%f", (tiempos + idx));
    } while (*(tiempos + idx) <= 0.0f);

    do {
        printf("Nuevo recurso unitario (> 0): ");
        scanf("%f", (recursos + idx));
    } while (*(recursos + idx) <= 0.0f);

    printf("Producto actualizado correctamente.\n");
}

void eliminarProducto(char nombres[][50], int *demandas, float *tiempos, float *recursos, int *total) {
    if (*total == 0) {
        printf("\nNo hay productos registrados.\n");
        return;
    }

    char buscado[50];
    printf("\nIngrese el nombre del producto a eliminar: ");
    scanf("%49s", buscado);

    int idx = buscarProducto(nombres, *total, buscado);
    if (idx == -1) {
        printf("Producto no encontrado.\n");
        return;
    }

    for (int i = idx; i < (*total - 1); i++) {
        int c = 0;
        while (*(*(nombres + (i + 1)) + c) != '\0') {
            *(*(nombres + i) + c) = *(*(nombres + (i + 1)) + c);
            c++;
        }
        *(*(nombres + i) + c) = '\0';

        *(demandas + i) = *(demandas + (i + 1));
        *(tiempos + i) = *(tiempos + (i + 1));
        *(recursos + i) = *(recursos + (i + 1));
    }

    (*total)--;
    printf("Producto eliminado correctamente.\n");
}

void listarProductos(char nombres[][50], int *demandas, float *tiempos, float *recursos, int total) {
    if (total == 0) {
        printf("\nNo hay productos registrados.\n");
        return;
    }

    printf("\nLista de productos:\n");
    for (int i = 0; i < total; i++) {
        printf("%d. %s - Demanda: %d - Tiempo: %.2fh - Recursos: %.2f\n", 
               i + 1, *(nombres + i), *(demandas + i), *(tiempos + i), *(recursos + i));
    }
}

void calcularOptimizacion(int *demandas, float *tiempos, float *recursos, int total, 
                          float capTiempo, float capRecursos, float *tiempoTotal, float *recursosTotales, int *factible) {
    *tiempoTotal = 0.0f;
    *recursosTotales = 0.0f;

    for (int i = 0; i < total; i++) {
        *tiempoTotal += (*(demandas + i)) * (*(tiempos + i));
        *recursosTotales += (*(demandas + i)) * (*(recursos + i));
    }

    if (*tiempoTotal <= capTiempo && *recursosTotales <= capRecursos) {
        *factible = 1;
    } else {
        *factible = 0;
    }
}