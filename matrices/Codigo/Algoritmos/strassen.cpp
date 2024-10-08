#include "strassen_.h"

//Codigo obtenido de: https://www.geeksforgeeks.org/strassens-matrix-multiplication/
//Este codigo si bien fue extraido de Geeks for Geeks, fue modificado para poder trabajar en modulos
//y arreglar errores de compilacion (mayoritariamente modificado por chatGPT)

// Función que inicializa una matriz cuadrada de tamaño `size`, 
// rellenándola con ceros. Devuelve la matriz recién creada.
Matrix inicializarMatriz(int size) {
    return Matrix(size, vector<lld>(size, 0));
}

// Función que toma dos matrices cuadradas A y B de tamaño `n` 
// y devuelve una nueva matriz C que es la suma de A y B.
Matrix sumarMatrices(const Matrix &A, const Matrix &B, int n) {
    Matrix C = inicializarMatriz(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
    return C;
}

// Función que toma dos matrices cuadradas A y B de tamaño `n` 
// y devuelve una nueva matriz C que es la resta de A y B.
Matrix restarMatrices(const Matrix &A, const Matrix &B, int n) {
    Matrix C = inicializarMatriz(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
    return C;
}

// Implementa la multiplicación tradicional de matrices. 
// Toma dos matrices cuadradas A y B de tamaño `n` y devuelve la matriz C 
// que es el resultado de multiplicar A por B.
Matrix multiplicacionTradicional(const Matrix &A, const Matrix &B, int n) {
    Matrix C = inicializarMatriz(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
    return C;
}

// Implementa el algoritmo de Strassen para la multiplicación de matrices. 
// Divide las matrices de entrada A y B en submatrices más pequeñas y utiliza 
// un conjunto de multiplicaciones y sumas/restas para calcular el resultado 
// más eficientemente que la multiplicación tradicional.
// Si `n` es menor o igual a 16, usa la multiplicación tradicional.
Matrix strassen(const Matrix &A, const Matrix &B, int n) {
    if (n <= 16) {
        return multiplicacionTradicional(A, B, n);
    }

    int newSize = n / 2;
    
    // Aquí dividimos las matrices A y B en cuatro submatrices cada una.
    Matrix A11 = inicializarMatriz(newSize), A12 = inicializarMatriz(newSize);
    Matrix A21 = inicializarMatriz(newSize), A22 = inicializarMatriz(newSize);
    Matrix B11 = inicializarMatriz(newSize), B12 = inicializarMatriz(newSize);
    Matrix B21 = inicializarMatriz(newSize), B22 = inicializarMatriz(newSize);

    // Poblamos las submatrices.
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    // Realizamos las operaciones de suma y resta necesarias para calcular los productos M1 a M7.
    Matrix AResult = sumarMatrices(A11, A22, newSize);
    Matrix BResult = sumarMatrices(B11, B22, newSize);
    Matrix M1 = strassen(AResult, BResult, newSize);
    
    AResult = sumarMatrices(A21, A22, newSize);
    Matrix M2 = strassen(AResult, B11, newSize);
    
    BResult = restarMatrices(B12, B22, newSize);
    Matrix M3 = strassen(A11, BResult, newSize);
    
    BResult = restarMatrices(B21, B11, newSize);
    Matrix M4 = strassen(A22, BResult, newSize);
    
    AResult = sumarMatrices(A11, A12, newSize);
    Matrix M5 = strassen(AResult, B22, newSize);
    
    AResult = restarMatrices(A21, A11, newSize);
    BResult = sumarMatrices(B11, B12, newSize);
    Matrix M6 = strassen(AResult, BResult, newSize);
    
    AResult = restarMatrices(A12, A22, newSize);
    BResult = sumarMatrices(B21, B22, newSize);
    Matrix M7 = strassen(AResult, BResult, newSize);

    // Una vez que tenemos todos los productos intermedios, combinamos los resultados 
    // para obtener la matriz resultante C.
    Matrix C = inicializarMatriz(n);
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = M1[i][j] + M4[i][j] - M5[i][j] + M7[i][j];    // C11
            C[i][j + newSize] = M3[i][j] + M5[i][j];                 // C12
            C[i + newSize][j] = M2[i][j] + M4[i][j];                 // C21
            C[i + newSize][j + newSize] = M1[i][j] - M2[i][j] + M3[i][j] + M6[i][j]; // C22
        }
    }
    return C;
}
