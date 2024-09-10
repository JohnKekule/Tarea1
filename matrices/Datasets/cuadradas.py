import numpy as np

def generar_matriz_cuadrada_y_guardar(orden, nombre_archivo):
    # Genera una matriz cuadrada de tamaño (orden x orden) con números aleatorios entre 0 y 9
    matriz = np.random.randint(0, 10, size=(orden, orden))
    # Guarda la matriz en un archivo .txt
    with open(nombre_archivo, 'w') as archivo:
        archivo.write(f"{orden} {orden}\n")  # Escribe las dimensiones en la primera línea
        np.savetxt(archivo, matriz, fmt='%d', delimiter=' ')  # Guarda la matriz

# Tamaños de matrices que son potencias de 2
ordenes = [100, 200, 300, 400, 500, 600, 700, 800]

# Generar y guardar las matrices cuadradas
for orden in ordenes:
    nombre_archivo = f"matriz_cuadrada_{orden}x{orden}.txt"
    generar_matriz_cuadrada_y_guardar(orden, nombre_archivo)
    print(f"Matriz cuadrada {orden}x{orden} guardada en {nombre_archivo}")

