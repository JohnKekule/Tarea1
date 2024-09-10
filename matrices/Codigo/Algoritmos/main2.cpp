#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include "strassen_.h"
#include "tradicional_.h"
#include "optimizado.h"

using namespace std;
using namespace std::chrono;

typedef long long lld;  

// Función para leer una matriz desde un archivo
vector<vector<lld>> leerMatrizDesdeArchivo(const string &nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "No se pudo abrir el archivo " << nombreArchivo << endl;
        exit(1);
    }

    int filas, columnas;
    archivo >> filas >> columnas;

    if (filas <= 0 || columnas <= 0) {
        cerr << "Dimensiones de la matriz inválidas en el archivo." << endl;
        exit(1);
    }

    cout << "Leyendo una matriz de dimensiones " << filas << "x" << columnas << endl;

    vector<vector<lld>> matriz(filas, vector<lld>(columnas));
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            if (!(archivo >> matriz[i][j])) {
                cerr << "Error al leer el elemento (" << i << ", " << j << ") de la matriz." << endl;
                exit(1);
            }
        }
    }
    archivo.close();
    return matriz;
}

// Función para verificar si una matriz es cuadrada
bool esCuadrada(const vector<vector<lld>>& matriz) {
    int filas = matriz.size();
    if (filas == 0) return false; 
    int columnas = matriz[0].size();
    return filas == columnas;
}

// Medir el tiempo de ejecución de Strassen
long long medirTiempoStrassen(const vector<vector<lld>>& A, int &tamano) {
    // Verificar si la matriz es cuadrada
    if (!esCuadrada(A)) {
        cerr << "Error: La matriz A no es cuadrada." << endl;
        exit(1);
    }

    // Multiplicar la matriz consigo misma
    auto inicio = high_resolution_clock::now();

    tamano = A.size(); // Obtener el tamaño de la matriz
    vector<vector<lld>> C = strassen(A, A, tamano);  // Multiplicar la matriz consigo misma

    auto fin = high_resolution_clock::now();
    return duration_cast<milliseconds>(fin - inicio).count();
}

long long medirTiempoTradicional(const vector<vector<lld>>& A, int &tamano) {
    // Verificar si la matriz es cuadrada
    if (!esCuadrada(A)) {
        cerr << "Error: La matriz A no es cuadrada." << endl;
        exit(1);
    }

    // Multiplicar la matriz consigo misma
    auto inicio = high_resolution_clock::now();

    tamano = A.size(); // Obtener el tamaño de la matriz
    vector<vector<lld>> C(A.size(), vector<lld>(A.size()));
    multiply(A, A, C);

    auto fin = high_resolution_clock::now();
    return duration_cast<milliseconds>(fin - inicio).count();
}

long long medirTiempoOptimizado(const vector<vector<lld>>& A, int &tamano) {
    // Verificar si la matriz es cuadrada
    if (!esCuadrada(A)) {
        cerr << "Error: La matriz A no es cuadrada." << endl;
        exit(1);
    }

    // Multiplicar la matriz consigo misma
    auto inicio = high_resolution_clock::now();

    tamano = A.size(); // Obtener el tamaño de la matriz
    vector<vector<lld>> C(A.size(), vector<lld>(A.size()));
    multiply_O(A, A, C);

    auto fin = high_resolution_clock::now();
    return duration_cast<milliseconds>(fin - inicio).count();
}

int main() {
    // Nombre del archivo CSV
    string archivoCSV = "Tiempos_matrices.csv";

    // Abrir el archivo CSV en modo append
    ofstream archivo(archivoCSV, ios::app);
    if (!archivo) {
        cerr << "No se pudo abrir el archivo CSV para escribir." << endl;
        return 1;
    }

    // Si el archivo está vacío, escribir los encabezados
    if (archivo.tellp() == 0) {
        archivo << "Metodo,Tamano_matriz,Tiempo(ms)\n";
    }

    // Definir los archivos de matrices y sus tamaños
    vector<string> nombresArchivos = {
        "matriz_cuadrada_100x100.txt",
        "matriz_cuadrada_200x200.txt",
        "matriz_cuadrada_300x300.txt",
        "matriz_cuadrada_400x400.txt",
        "matriz_cuadrada_500x500.txt",
        "matriz_cuadrada_600x600.txt",
        "matriz_cuadrada_700x700.txt",
        "matriz_cuadrada_800x800.txt"
    };

    for (const string& nombreArchivo : nombresArchivos) {
        vector<vector<lld>> matriz = leerMatrizDesdeArchivo(nombreArchivo);

        // Verificar si la matriz es cuadrada
        if (!esCuadrada(matriz)) {
            cout << "Error: La matriz leída no es cuadrada." << endl;
            return 1;
        }

        int tamano;
        // Medir el tiempo de Strassen multiplicando la matriz por sí misma
        long long tiempoEjecucion = medirTiempoStrassen(matriz, tamano);
        long long tiempoEjecucionTradicional = medirTiempoTradicional(matriz, tamano);
        long long tiempoEjecucionOptimizado = medirTiempoOptimizado(matriz, tamano);

        // Escribir los resultados en el archivo CSV
        archivo << "Strassen," << tamano << "," << tiempoEjecucion << "\n";
        archivo << "Tradicional," << tamano << "," << tiempoEjecucionTradicional << "\n";
        archivo << "Optimizado," << tamano << "," << tiempoEjecucionOptimizado << "\n";
    }

    archivo.close();

    cout << "Tiempos de ejecución guardados en " << archivoCSV << endl;
    return 0;
}
