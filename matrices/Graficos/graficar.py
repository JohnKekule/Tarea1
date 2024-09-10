import pandas as pd
import matplotlib.pyplot as plt


archivo_csv = r'C:\Users\oscar\OneDrive - Universidad Técnica Federico Santa María\Escritorio\Universidad\Algoloco\Tarea1\matrices\Graficos\Tiempos_matrices.csv'
datos = pd.read_csv(archivo_csv)


metodos = datos['Metodo'].unique()
tamanos = datos['Tamano_matriz'].unique()


tiempos = {metodo: [] for metodo in metodos}


for metodo in metodos:
    datos_metodo = datos[datos['Metodo'] == metodo]
    tiempos[metodo] = datos_metodo.sort_values(by='Tamano_matriz')['Tiempo(ms)'].tolist()


plt.figure(figsize=(12, 8))


for metodo in metodos:
    tamanos_matrices = datos[datos['Metodo'] == metodo]['Tamano_matriz'].unique()
    plt.plot(tamanos_matrices, tiempos[metodo], marker='o', linestyle='-', label=metodo)

plt.xlabel('Tamaño de la matriz (n x n)')
plt.ylabel('Tiempo de ejecución (ms)')
plt.title('Tiempo de Ejecución vs Tamaño de la Matriz')
plt.legend()
plt.grid(True)
plt.show()
