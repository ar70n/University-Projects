#!/bin/bash

executables=("pi_serie" "pi_par1" "pi_par2" "pi_par3" "pi_par4" "pi_par5" "pi_par6" "pi_par7")
output_file="tiempos_versiones.dat"
> $output_file

# Función para calcular el tiempo medio
calculate_average_time() {
    local executable=$1
    local total_time=0

    for i in {1..10}; do
        # Ejecutar el programa y extraer el tiempo
        time=$(./$executable | grep "Tiempo" | awk '{print $2}')
        total_time=$(echo "$total_time + $time" | bc)
    done

    # Calcular el tiempo medio
    average_time=$(echo "scale=6; $total_time / 10" | bc)
    echo $average_time
}

# Calcular el tiempo medio para pi_serie
average_time_serie=$(calculate_average_time "pi_serie")
echo "$average_time_serie 1.0" >> $output_file

# Calcular el tiempo medio y el speedup para el resto de ejecutables
for executable in "${executables[@]:1}"; do
    average_time=$(calculate_average_time $executable)
    speedup=$(echo "scale=6; $average_time_serie / $average_time" | bc)
    echo "$average_time $speedup" >> $output_file
done