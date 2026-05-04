#include "stats.h"

/*
 * Función auxiliar: suma
 * ----------------------------------
 * Calcula la suma de los elementos de un arreglo.
 *
 * IMPORTANTE:
 * Se declara como 'static' para que tenga
 * visibilidad SOLO dentro de este archivo (.c).
 *
 * Esto es un ejemplo de encapsulamiento:
 * - Evita que otras partes del programa llamen
 *   directamente a esta función interna.
 * - Previene conflictos de nombres con funciones
 *   similares en otros archivos.
 * - Refuerza la idea de "caja negra": desde fuera
 *   solo se usan promedio() y varianza().
 */
static double suma(double arr[], int n) {
    double total = 0.0;
    int i;

    for (i = 0; i < n; i++) {
        total += arr[i];
    }

    return total;
}

/*
 * Función: promedio
 * ----------------------------------
 * Calcula el promedio de un arreglo.
 */
double promedio(double arr[], int n) {
    if (n <= 0) {
        return 0.0;
    }

    return suma(arr, n) / n;
}

/*
 * Función: varianza
 * ----------------------------------
 * Calcula la varianza de un arreglo.
 * Usa la función promedio().
 */
double varianza(double arr[], int n) {
    if (n <= 0) {
        return 0.0;
    }

    double prom = promedio(arr, n);
    double acumulado = 0.0;
    int i;

    for (i = 0; i < n; i++) {
        double diferencia = arr[i] - prom;
        acumulado += diferencia * diferencia;
    }

    return acumulado / n;
}