#include <stdio.h>

int compararCadenasManual(const char *cad1, const char *cad2);
int buscarProducto(char nombres[][50], int total, const char *objetivo);

void ingresarProducto(char nombres[][50], int *demandas, float *tiempos, float *recursos, int *total);
void editarProducto(char nombres[][50], int *demandas, float *tiempos, float *recursos, int total);
void eliminarProducto(char nombres[][50], int *demandas, float *tiempos, float *recursos, int *total);
void listarProductos(char nombres[][50], int *demandas, float *tiempos, float *recursos, int total);
void calcularOptimizacion(int *demandas, float *tiempos, float *recursos, int total, float capTiempo, float capRecursos, float *tiempoTotal, float *recursosTotales, int *factible);