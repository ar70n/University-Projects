#!/bin/bash

# Compilar el programa
make pescalar_threshold_automated

# Ejecutar el programa
./pescalar_threshold_automated

# Crear el script de gnuplot
cat <<EOF > plot_threshold.gnuplot
set title "Fiabilidad Threshold"
set xlabel "Tamaño"
set ylabel "Porcentaje de Intentos Válidos"
set key inside right top
set grid
set yrange [0:1.4]

plot "threshold.dat" using 1:2 with linespoints title "% Monohílo más Rápido (tamaño pequeño)", \
     "threshold.dat" using 1:3 with linespoints title "% Multihilo más Rápido (tamaño grande)"
EOF

# Ejecutar gnuplot con el script
gnuplot -persist plot_threshold.gnuplot
