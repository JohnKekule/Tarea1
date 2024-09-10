#include "tradicional_.h"

// Link al propietario del codigo: https://www.geeksforgeeks.org/strassens-matrix-multiplication/
// Este código fue modificado para trabajar en módulos




// Implementación de la multiplicación de matrices tradicional
// A y B son las matrices de entrada, y C es la matriz que almacenará el resultado de la multiplicación.
void multiply(const vector<vector<lld>>& A, const vector<vector<lld>>& B, vector<vector<lld>>& C) {
    int n = A.size();      // Número de filas de A
    int m = B[0].size();   // Número de columnas de B
    int p = B.size();      // Número de filas de B (que debe ser igual al número de columnas de A)

    // Inicializamos la matriz resultante C en 0
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            C[i][j] = 0;  // Iniciamos la posición C[i][j] en 0
            // Calculamos el producto escalar entre la fila i de A y la columna j de B
            for (int k = 0; k < p; k++) {
                C[i][j] += A[i][k] * B[k][j];  // Acumulamos la suma de productos en C[i][j]
            }
        }
    }
}





