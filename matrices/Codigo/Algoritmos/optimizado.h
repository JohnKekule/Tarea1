#ifndef OPTIMIZADO_H
#define OPTIMIZADO_H

#include <vector>

using namespace std;

typedef long long lld;  // Definir el tipo lld como long long int

// Función para trasponer una matriz
void trasponer(const vector<vector<lld>>& A, vector<vector<lld>>& At);

// Función para multiplicar dos matrices
void multiply_O(const vector<vector<lld>>& A, const vector<vector<lld>>& B, vector<vector<lld>>& C);

#endif // OPTIMIZADO_H
