# Ejemplo script, para P3 arq 2024-2025

#!/bin/bash

# inicializar variables
Ninicio=2000
Npaso=2000
Nfinal=$((Ninicio + 18000))
fDAT=slow_fast_time.dat
fPNG=slow_fast_time.png
iteraciones=10

# borrar el fichero DAT y el fichero PNG
rm -f $fDAT fPNG

#Compilar los programas
make all

# generar el fichero DAT vacío
touch $fDAT

echo "Running slow and fast..."
# bucle para N desde P hasta Q 
#for N in $(seq $Ninicio $Npaso $Nfinal);
for ((N = Ninicio ; N <= Nfinal ; N += Npaso)); do
	
	slowTime=0
	fastTime=0
	for ((i=0;i<iteraciones;i+=1)); do
		echo "N: $N / $Nfinal..."
	
		# ejecutar los programas slow y fast consecutivamente con tamaño de matriz N
		# para cada uno, filtrar la línea que contiene el tiempo y seleccionar la
		# tercera columna (el valor del tiempo). Dejar los valores en variables
		# para poder imprimirlos en la misma línea del fichero de datos
		slowTimeAux=$(./slow $N | grep 'time' | awk '{print $3}')
		fastTimeAux=$(./fast $N | grep 'time' | awk '{print $3}')

		slowTime=$(echo "$slowTimeAux+$slowTime" | bc)
		fastTime=$(echo "$fastTimeAux+$fastTime" | bc)
	done
	slowTimeAvg=$(echo "$slowTime/$iteraciones" | bc -l)
	fastTimeAvg=$(echo "$fastTime/$iteraciones" | bc -l)
	
	echo "$N	$slowTimeAvg	$fastTimeAvg" >> $fDAT

	echo SLOW Average N [$N] Iters [$iteraciones] Acc [$slowTime] Avg [$slowTimeAvg]
	echo FAST Average N [$N] Iters [$iteraciones] Acc [$fastTime] Avg [$fastTimeAvg]
	echo -----------------------------------------------------------------------------

done

echo "Generating plot..."
# llamar a gnuplot para generar el gráfico y pasarle directamente por la entrada
# estándar el script que está entre "<< END_GNUPLOT" y "END_GNUPLOT"
gnuplot << END_GNUPLOT
set title "Slow-Fast Execution Time"
set ylabel "Execution time (s)"
set xlabel "Matrix Size"
set key right bottom
set grid
set term png
set output "$fPNG"
plot "$fDAT" using 1:2 with lines lw 2 title "slow", \
     "$fDAT" using 1:3 with lines lw 2 title "fast"
replot
quit
END_GNUPLOT
