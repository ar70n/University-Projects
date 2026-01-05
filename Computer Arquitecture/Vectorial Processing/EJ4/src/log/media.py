import sys

if len(sys.argv) < 2:
    print("Por favor, proporciona al menos un nombre de archivo como argumento.")
    sys.exit(1)

archivos = sys.argv[1:]
for archivo in archivos:
    try:
        with open(archivo, 'r') as f:
            valores = f.readlines()
            
            a = [[] for _ in range(5)]

            i = 0
            while i < len(valores):
                if i % 10 == 0:
                    a[0].append(float(valores[i].strip()))
                elif i % 10 == 1:
                    a[1].append(float(valores[i].strip()))
                elif i % 10 == 2:
                    a[2].append(float(valores[i].strip()))
                elif i % 10 == 3:
                    a[3].append(float(valores[i].strip()))
                elif i % 10 == 4:
                    a[4].append(float(valores[i].strip()))
                i += 1  
            
        # Calcular los promedios y agregarlos a un archivo
        with open(f'media_{archivo}.txt', 'a') as resultado_archivo:
            for i in range(5):
                promedio = (sum(a[i]) / len(a[i]))*(10**3)
                resultado_archivo.write(f"Promedio {i}: {promedio}\n")
                print(promedio)
    except Exception as e:
        print(f"Error al leer el archivo: {archivo}")