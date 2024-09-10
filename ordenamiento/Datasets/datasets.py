import numpy as np

#Generar datos ordenados de manera descendente (tamaño 10^5)
def generar_datos_descendentes(tamaño):
    datos = np.arange(tamaño)[::-1]
    datos_txt = " ".join(map(str, datos))
    with open("datos_descendentes.txt", "w") as archivo:
        archivo.write(datos_txt)

# Generación de datos parcialmente ordenados (tamaño 10^5)
def generar_datos_parcialmente_ordenados(tamaño):
    datos = np.random.randint(0, 100000, tamaño)
    datos.sort()
    indices_desordenados = np.random.choice(tamaño, tamaño // 4, replace=False)
    np.random.shuffle(datos[indices_desordenados])
    datos_txt = " ".join(map(str, datos))
    with open("datos_ordenados.txt", "w") as archivo:
        archivo.write(datos_txt)

# Generación de datos semi ordenados (tamaño 10^5)
def generar_datos_semi_ordenados(tamaño):
    datos = np.concatenate([np.arange(tamaño // 2), np.random.randint(0, 100000, tamaño // 2)])
    np.random.shuffle(datos)
    datos_txt = " ".join(map(str, datos))
    with open("datos_semi_ordenados.txt", "w") as archivo:
        archivo.write(datos_txt)

# Generación de datos aleatorios (tamaño 10^5)
def generar_datos_aleatorios(tamaño):
    datos = np.random.randint(0, 100000, tamaño)
    datos_txt = " ".join(map(str, datos))
    with open("datos_aleatorios.txt", "w") as archivo:
        archivo.write(datos_txt)



# Tamaño mínimo de los datasets: 10^5
tamaño_minimo = 10**5

# Generar y guardar los datasets en archivos .txt
generar_datos_parcialmente_ordenados(tamaño_minimo)
generar_datos_semi_ordenados(tamaño_minimo)
generar_datos_aleatorios(tamaño_minimo)
generar_datos_descendentes(tamaño_minimo)


print("Datasets generados y guardados en archivos .txt.")
