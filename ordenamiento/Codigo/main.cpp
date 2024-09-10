#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <chrono>
#include <algorithm>  
#include "merge_sort.h"
#include "quick_sort.h"
#include "selection_sort.h"
#include "utility.h" 

using namespace std;
using namespace std::chrono;

// Función para leer el archivo y almacenar los datos en un vector
vector<int> leerArchivo(const string &nombreArchivo) {
    vector<int> datos;
    ifstream archivo(nombreArchivo);
    string linea;
    int numero;

    if (!archivo) {
        cerr << "No se pudo abrir el archivo " << nombreArchivo << endl;
        exit(1);
    }

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        while (ss >> numero) {
            datos.push_back(numero);
        }
    }
    archivo.close();
    return datos;
}

// Función para escribir los resultados en un archivo CSV
void guardarEnCSV(int tamano, const string& algoritmo, long long tiempo, const string& nombreArchivoCSV) {
    ofstream archivoCSV(nombreArchivoCSV, ios::app);  // Usar 'append' para no sobrescribir
    archivoCSV << tamano << "," << algoritmo << "," << tiempo << endl;
    archivoCSV.close();
}

// Función para medir el tiempo de ejecución de cualquier algoritmo de ordenamiento
template <typename Func>
long long medirTiempoEjecucion(int tamano, const vector<int>& datosOriginal, Func algoritmo, const string& algoritmoNombre, const string& nombreCSV) {
    vector<int> datos(datosOriginal.begin(), datosOriginal.begin() + tamano);

    auto inicio = high_resolution_clock::now();
    algoritmo(datos.data(), 0, tamano - 1);  // Aquí ejecutamos el algoritmo
    auto fin = high_resolution_clock::now();

    auto duracion = duration_cast<milliseconds>(fin - inicio).count();

    // Guardar el tamaño, algoritmo y tiempo en el CSV
    guardarEnCSV(tamano, algoritmoNombre, duracion, nombreCSV);

    return duracion;
}

// Programa principal
int main() {
    string nombreArchivo, nombreCSV;
    cout << "Introduce el nombre del archivo del dataset: ";
    cin >> nombreArchivo;
    cout << "Introduce el nombre del archivo CSV para guardar los resultados: ";
    cin >> nombreCSV;

    vector<int> datos = leerArchivo(nombreArchivo);

    const int numPruebas = 10;
    const int tamanoMaximo = 100000;  // Tamaño máximo de los datos (10^5)
    int incremento = 10000;  // Incremento de elementos en cada prueba

    // Asegurarse de que haya suficientes datos en el archivo
    if (tamanoMaximo > datos.size()) {
        cout << "No hay suficientes datos en el archivo." << endl;
        return 1;
    }

    // Eliminar el archivo CSV si ya existe para empezar desde cero
    ofstream(nombreCSV).close();

    // Realizar las pruebas
    cout << "Realizando 100 pruebas, aumentando el tamaño de los datos progresivamente..." << endl;

    for (int i = 1; i <= numPruebas; i++) {
        int tamanoActual = i * incremento;  // Tamaño de los datos a ordenar en esta prueba

        // std::sort
        medirTiempoEjecucion(tamanoActual, datos, [tamanoActual](int* arr, int, int) { sort(arr, arr + tamanoActual); }, "std::sort", nombreCSV);

        // mergeSort
        medirTiempoEjecucion(tamanoActual, datos, mergeSort, "mergeSort", nombreCSV);

        // quickSort
        medirTiempoEjecucion(tamanoActual, datos, quickSort, "quickSort", nombreCSV);

        // selectionSort
        medirTiempoEjecucion(tamanoActual, datos, [tamanoActual](int* arr, int, int) { selectionSort(arr, tamanoActual); }, "selectionSort", nombreCSV);

        // Mostrar el progreso de la prueba actual
        cout << "Prueba " << i << " con " << tamanoActual << " elementos completada." << endl;
    }

    return 0;
}
