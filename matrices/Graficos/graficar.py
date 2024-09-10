import pandas as pd
import matplotlib.pyplot as plt

# Leer el archivo CSV
archivo_csv = r'C:\Users\oscar\OneDrive - Universidad Técnica Federico Santa María\Escritorio\Universidad\Algoloco\Tarea1\matrices\Graficos\Tiempos_matrices.csv'
datos = pd.read_csv(archivo_csv)

# Separar los datos en función del método
metodos = datos['Metodo'].unique()
tamanos = datos['Tamano_matriz'].unique()

# Crear un diccionario para almacenar los tiempos
tiempos = {metodo: [] for metodo in metodos}

# Rellenar el diccionario con los tiempos
for metodo in metodos:
    datos_metodo = datos[datos['Metodo'] == metodo]
    tiempos[metodo] = datos_metodo.sort_values(by='Tamano_matriz')['Tiempo(ms)'].tolist()

# Graficar los datos
plt.figure(figsize=(12, 8))

# Graficar cada método
for metodo in metodos:
    tamanos_matrices = datos[datos['Metodo'] == metodo]['Tamano_matriz'].unique()
    plt.plot(tamanos_matrices, tiempos[metodo], marker='o', linestyle='-', label=metodo)

plt.xlabel('Tamaño de la matriz (n x n)')
plt.ylabel('Tiempo de ejecución (ms)')
plt.title('Tiempo de Ejecución vs Tamaño de la Matriz')
plt.legend()
plt.grid(True)
plt.show()
