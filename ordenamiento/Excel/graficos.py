import pandas as pd
import matplotlib.pyplot as plt

def leer_datos_csv(nombre_archivo):
    df = pd.read_csv(nombre_archivo, header=None, names=['Tamaño', 'Algoritmo', 'Tiempo'])
    return df

def graficar_datos(datos):
    for algoritmo in datos['Algoritmo'].unique():
        datos_filtrados = datos[datos['Algoritmo'] == algoritmo]
        

        plt.plot(datos_filtrados['Tamaño'], datos_filtrados['Tiempo'], label=algoritmo, marker='o')
    


    plt.xlabel('Tamaño del arreglo')
    plt.ylabel('Tiempo (ms)')
    plt.title('Datos Parcialmente Desordenados')
    plt.legend()
    plt.grid(True)
    plt.show()


datos_ordenado_A = leer_datos_csv(r'C:\Users\oscar\OneDrive - Universidad Técnica Federico Santa María\Escritorio\Universidad\Algoloco\Tarea1\ordenamiento\Excel\Desordenados.csv')


graficar_datos(datos_ordenado_A)
