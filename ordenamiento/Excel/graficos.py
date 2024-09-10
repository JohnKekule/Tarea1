import pandas as pd
import matplotlib.pyplot as plt

def leer_datos_csv(nombre_archivo):
    # Leer el archivo CSV sin encabezado y asignar los nombres de las columnas
    df = pd.read_csv(nombre_archivo, header=None, names=['Tamaño', 'Algoritmo', 'Tiempo'])
    return df

def graficar_datos(datos):
    # Graficar los datos agrupados por algoritmo usando líneas con puntos
    for algoritmo in datos['Algoritmo'].unique():
        datos_filtrados = datos[datos['Algoritmo'] == algoritmo]
        
        # Graficar la línea conectando los puntos
        plt.plot(datos_filtrados['Tamaño'], datos_filtrados['Tiempo'], label=algoritmo, marker='o')
    
    # Configurar el rango del eje y entre 0 y 1 ms


    plt.xlabel('Tamaño del arreglo')
    plt.ylabel('Tiempo (ms)')
    plt.title('Datos Parcialmente Desordenados')
    plt.legend()
    plt.grid(True)
    plt.show()

# Leer los datos
datos_ordenado_A = leer_datos_csv(r'C:\Users\oscar\OneDrive - Universidad Técnica Federico Santa María\Escritorio\Universidad\Algoloco\Tarea1\ordenamiento\Excel\Desordenados.csv')

# Graficar los datos
graficar_datos(datos_ordenado_A)
