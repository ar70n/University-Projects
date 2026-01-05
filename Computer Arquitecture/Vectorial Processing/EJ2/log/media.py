archivo = 'time_intrinsic'

try:
    with open(archivo, 'r') as f:
        valores = f.readlines()
        
        a = [[] for _ in range(10)]

        
        i = 0
        while(i < len(valores)):
                
            if i % 11    == 0:
                a[0].append(float(valores[i].strip()))
            elif i % 11 == 1:
                a[1].append(float(valores[i].strip()))
            elif i % 11 == 2:
                a[2].append(float(valores[i].strip()))
            elif i % 11 == 3:
                a[3].append(float(valores[i].strip()))
            elif i % 11 == 4:
                a[4].append(float(valores[i].strip()))
            elif i % 11 == 5:
                a[5].append(float(valores[i].strip()))
            elif i % 11 == 6:
                a[6].append(float(valores[i].strip()))
            elif i % 11 == 7:
                a[7].append(float(valores[i].strip()))
            elif i % 11 == 8:
                a[8].append(float(valores[i].strip()))
            elif i % 11 == 9:
                a[9].append(float(valores[i].strip()))
            i += 1  
        
        
    for i in range(10):
            print(sum(a[i]) / len(a[i]))            
except Exception as e:
    print(f"Error al leer el archivo: {archivo}")
    