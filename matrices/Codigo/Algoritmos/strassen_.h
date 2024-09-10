#ifndef STRASSEN_H
#define STRASSEN_H

#include <vector>

using namespace std;

// Definición de tipos
typedef long long lld;
typedef vector<vector<lld>> Matrix;

// Funciones
Matrix inicializarMatriz(int size);
Matrix sumarMatrices(const Matrix &A, const Matrix &B, int n);
Matrix restarMatrices(const Matrix &A, const Matrix &B, int n);
Matrix multiplicacionTradicional(const Matrix &A, const Matrix &B, int n);
Matrix strassen(const Matrix &A, const Matrix &B, int n);

#endif // STRASSEN_H
