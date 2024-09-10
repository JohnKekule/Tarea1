#include <vector>
#include "optimizado.h"

// Función para trasponer matrices
// A es la matriz de entrada y At será la matriz traspuesta de A.
// Esta función intercambia las filas por columnas, es decir, At[j][i] = A[i][j].
void trasponer(const vector<vector<lld>>& A, vector<vector<lld>>& At) {
    int m = A.size();      // Número de filas de A
    int n = A[0].size();   // Número de columnas de A
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            At[j][i] = A[i][j]; // Intercambiamos filas por columnas
        }
    }
}

// Función de multiplicación de matrices tradicional optimizada
// A es la primera matriz, B es la segunda matriz y C es la matriz resultante.
// Se optimiza trasponiendo la matriz B para mejorar la localización espacial en el acceso a la memoria.
void multiply_O(const vector<vector<lld>>& A, const vector<vector<lld>>& B, vector<vector<lld>>& C) {
    // Crear una matriz transpuesta de B para mejorar la eficiencia en la multiplicación
    vector<vector<lld>> B_transpuesta(B[0].size(), vector<lld>(B.size()));
    trasponer(B, B_transpuesta);  // Llamamos a la función que transpone la matriz B

    int m = A.size();            // Número de filas de A
    int n = B_transpuesta[0].size();  // Número de columnas de B transpuesta (originalmente las filas de B)
    int p = B_transpuesta.size();     // Número de filas de B transpuesta (originalmente las columnas de B)

    // Inicializamos la matriz resultante C en 0
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;  // Inicializamos cada entrada de C a 0
            // Multiplicamos las matrices usando B transpuesta para mejorar el acceso a memoria
            for (int k = 0; k < p; k++) {
                C[i][j] += A[i][k] * B_transpuesta[j][k];  // Producto escalar entre fila de A y columna de B transpuesta
            }
        }
    }
}
