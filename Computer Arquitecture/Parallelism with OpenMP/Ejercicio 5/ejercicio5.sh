#!/bin/bash

imagenes=("images/SD.jpg" "images/HD.jpg" "images/FHD.jpg" "images/4k.jpg" "images/8k.jpg")

make all > make.log 2>&1

rm -f tiempos.dat speedup.dat 

# Tiempo = tiempo que tarde
# FPS = 1 / tiempo
# Speedup = tiempo_serie_median / Tiempo
for resolucion in "${imagenes[@]}"; do
    # Ejecutar los programas y guardar sus resultados
    t_edgeDetector_GAUSSIAN=$(./edgeDetector_GAUSSIAN $resolucion)
    t_edgeDetector_MEDIAN=$(./edgeDetector_MEDIAN $resolucion) # Referencia para el speedup
    
    t_edgeDetector_serie_GAUSSIAN=$(./edgeDetector_serie_GAUSSIAN $resolucion)
    t_edgeDetector_serie_MEDIAN=$(./edgeDetector_serie_MEDIAN $resolucion)
    
    t_edgeDetector_GAUSSIAN_O3=$(./edgeDetector_GAUSSIAN_O3 $resolucion)
    t_edgeDetector_MEDIAN_O3=$(./edgeDetector_MEDIAN_O3 $resolucion)
    
    t_edgeDetector_serie_GAUSSIAN_O3=$(./edgeDetector_serie_GAUSSIAN_O3 $resolucion)
    t_edgeDetector_serie_MEDIAN_O3=$(./edgeDetector_serie_MEDIAN_O3 $resolucion)

    # Calcular los datos a partir de las ejecuciones
    # FPS
    t_edgeDetector_GAUSSIAN_FPS=$(echo "scale=10; 1 / $t_edgeDetector_GAUSSIAN" | bc)
    t_edgeDetector_MEDIAN_FPS=$(echo "scale=10; 1 / $t_edgeDetector_MEDIAN" | bc) 

    t_edgeDetector_serie_GAUSSIAN_FPS=$(echo "scale=10; 1 / $t_edgeDetector_serie_GAUSSIAN" | bc) 
    t_edgeDetector_serie_MEDIAN_FPS=$(echo "scale=10; 1 / $t_edgeDetector_serie_MEDIAN" | bc) 

    t_edgeDetector_GAUSSIAN_O3_FPS=$(echo "scale=10; 1 / $t_edgeDetector_GAUSSIAN_O3" | bc) 
    t_edgeDetector_MEDIAN_O3_FPS=$(echo "scale=10; 1 / $t_edgeDetector_MEDIAN_O3" | bc) 

    t_edgeDetector_serie_GAUSSIAN_O3_FPS=$(echo "scale=10; 1 / $t_edgeDetector_serie_GAUSSIAN_O3" | bc) 
    t_edgeDetector_serie_MEDIAN_O3_FPS=$(echo "scale=10; 1 / $t_edgeDetector_serie_MEDIAN_O3" | bc)

    # Speedup
    speedup_GAUSSIAN=$(echo "scale=10; $t_edgeDetector_serie_MEDIAN / $t_edgeDetector_GAUSSIAN" | bc)
    speedup_MEDIAN=$(echo "scale=10; $t_edgeDetector_serie_MEDIAN / $t_edgeDetector_MEDIAN" | bc)

    speedup_serie_GAUSSIAN=$(echo "scale=10; $t_edgeDetector_serie_MEDIAN / $t_edgeDetector_serie_GAUSSIAN" | bc)
    speedup_serie_MEDIAN=1

    speedup_GAUSSIAN_O3=$(echo "scale=10; $t_edgeDetector_serie_MEDIAN / $t_edgeDetector_GAUSSIAN_O3" | bc)
    speedup_MEDIAN_O3=$(echo "scale=10; $t_edgeDetector_serie_MEDIAN / $t_edgeDetector_MEDIAN_O3" | bc)

    speedup_serie_GAUSSIAN_O3=$(echo "scale=10; $t_edgeDetector_serie_MEDIAN / $t_edgeDetector_serie_GAUSSIAN_O3" | bc)
    speedup_serie_MEDIAN_O3=$(echo "scale=10; $t_edgeDetector_serie_MEDIAN / $t_edgeDetector_serie_MEDIAN_O3" | bc)

    # Imprimir los resultados
    echo "$resolucion $t_edgeDetector_GAUSSIAN $t_edgeDetector_MEDIAN $t_edgeDetector_serie_GAUSSIAN $t_edgeDetector_serie_MEDIAN $t_edgeDetector_GAUSSIAN_O3 $t_edgeDetector_MEDIAN_O3 $t_edgeDetector_serie_GAUSSIAN_O3 $t_edgeDetector_serie_MEDIAN_O3 $t_edgeDetector_GAUSSIAN_FPS $t_edgeDetector_MEDIAN_FPS $t_edgeDetector_serie_GAUSSIAN_FPS $t_edgeDetector_serie_MEDIAN_FPS $t_edgeDetector_GAUSSIAN_O3_FPS $t_edgeDetector_MEDIAN_O3_FPS $t_edgeDetector_serie_GAUSSIAN_O3_FPS $t_edgeDetector_serie_MEDIAN_O3_FPS" >> tiempos.dat
    echo "$resolucion $speedup_GAUSSIAN $speedup_MEDIAN $speedup_serie_GAUSSIAN $speedup_serie_MEDIAN $speedup_GAUSSIAN_O3 $speedup_MEDIAN_O3 $speedup_serie_GAUSSIAN_O3 $speedup_serie_MEDIAN_O3" >> speedup.dat
     
done