#!/bin/bash

# inicializar variables
Ninicio=1
Nfinal=4
fDAT=times.dat
fPNG=grafica.png


make all
./mult_normal_serie 1024 >> serie_1$fDAT
for((i=Ninicio; i <= Nfinal; i+=1)); do
    export OMP_NUM_THREADS=$i
     ./mult_normal_int 1024 >> int_1$fDAT
     ./mult_normal_med 1024 >> med_1$fDAT
     ./mult_normal_ext 1024 >> ext_1$fDAT

done

./mult_normal_serie 2048 >> serie_$fDAT
for((i=Ninicio; i <= Nfinal; i+=1)); do
    export OMP_NUM_THREADS=$i
     ./mult_normal_int 2048 >> int_2$fDAT
     ./mult_normal_med 2048 >> med_2$fDAT
     ./mult_normal_ext 2048 >> ext_2$fDAT

done

rm grafica.dat grafica.png acc_grafica.png

for ((N=512; N<=2560; N+=128)); do

    tiempo_serie=$(./mult_normal_serie $N)
    tiempo_ext=$(./mult_normal_ext $N)

    
     speedup=$(echo "scale=10; $tiempo_serie / $tiempo_ext" | bc)

    echo "$N $tiempo_serie $tiempo_ext $speedup" >> grafica.dat
done

echo "Generating plot..."
# llamar a gnuplot para generar el gráfico y pasarle directamente por la entrada
# estándar el script que está entre "<< END_GNUPLOT" y "END_GNUPLOT"
gnuplot << END_GNUPLOT
set title "Tiempo de ejecución serie y bucle-3"
set ylabel "Execution time (s)"
set xlabel "Matrix Size"
set key right bottom
set grid
set term png
set output "$fPNG"
plot "grafica.dat" using 1:2 with lines lw 2 title "serie", \
     "grafica.dat" using 1:3 with lines lw 2 title "bucle-3"
replot
quit
END_GNUPLOT



echo "Generating plot..."
# llamar a gnuplot para generar el gráfico y pasarle directamente por la entrada
# estándar el script que está entre "<< END_GNUPLOT" y "END_GNUPLOT"
gnuplot << END_GNUPLOT
set title "Tiempo de ejecución serie y bucle-3"
set ylabel "Execution time (s)"
set xlabel "Matrix Size"
set key right bottom
set grid
set term png
set output "acc_$fPNG"
plot "grafica.dat" using 1:4 with lines lw 2 title "aceleracion"
replot
quit
END_GNUPLOT
