# Ejemplo script, para P3 arq 2024-2025

#!/bin/bash

# inicializar variables
Ninicio=256
Npaso=256
Nfinal=2048
fDAT=mult.dat
fPNG=mult_time.png
fPNG_lec=mult_cache_read.png
fPNG_esc=mult_cache_write.png

iteraciones=1

# borrar el fichero DAT y el fichero PNG
rm -f $fDAT $fPNG $fPNG_lec $fPNG_esc

#Compilar los programas
make all

# generar el fichero DAT vacío
touch $fDAT


echo "Running normal and transposed multiplication..."
# bucle para N desde P hasta Q 
for ((N = Ninicio ; N <= Nfinal ; N += Npaso)); do	

    #Apartado 2)
    valgrind --tool=cachegrind --cachegrind-out-file=cachegrind.normal ./mult_normal $N  1>/dev/null 2>/dev/null
    valgrind --tool=cachegrind --cachegrind-out-file=cachegrind.transp ./mult_transp $N  1>/dev/null 2>/dev/null


    d1mr_normal=$(cg_annotate cachegrind.normal | sed -n "18p" | cut -d ' ' -f 9 | tr -d ',') 
    d1mw_normal=$(cg_annotate cachegrind.normal | sed -n "18p" | cut -d ' ' -f 15 | tr -d ',')

    d1mr_transp=$(cg_annotate cachegrind.transp | sed -n "18p" | cut -d ' ' -f 9 | tr -d ',') 
    d1mw_transp=$(cg_annotate cachegrind.transp | sed -n "18p" | cut -d ' ' -f 15 | tr -d ',') 
        

	normalTime=0
	transpTime=0

	for ((i=0;i<iteraciones;i+=1)); do
		echo "N: $N / $Nfinal..."
	
		# ejecutar los programas normal y transp consecutivamente con tamaño de matriz N
		# para cada uno, filtrar la línea que contiene el tiempo y seleccionar la
		# tercera columna (el valor del tiempo). Dejar los valores en variables
		# para poder imprimirlos en la misma línea del fichero de datos
		normalTimeAux=$(./mult_normal $N | grep 'time' | awk '{print $3}')
		transpTimeAux=$(./mult_transp $N | grep 'time' | awk '{print $3}')

		normalTime=$(echo "$normalTimeAux+$normalTime" | bc)
		transpTime=$(echo "$transpTimeAux+$transpTime" | bc)
	done
    
	normalTimeAvg=$(echo "$normalTime/$iteraciones" | bc -l)
	transpTimeAvg=$(echo "$transpTime/$iteraciones" | bc -l)
	

	echo normal Average N [$N] Iters [$iteraciones] Acc [$normalTime] Avg [$normalTimeAvg]
	echo transp Average N [$N] Iters [$iteraciones] Acc [$transpTime] Avg [$transpTimeAvg]
	echo -----------------------------------------------------------------------------

    echo "$N $normalTimeAvg $d1mr_normal $d1mw_normal $transpTimeAvg $d1mr_transp $d1mw_transp" >> $fDAT  


done


#Borramos los cache grind
rm cachegrind.*


echo "Generating times plot..."
# llamar a gnuplot para generar el gráfico y pasarle directamente por la entrada
# estándar el script que está entre "<< END_GNUPLOT" y "END_GNUPLOT"
gnuplot << END_GNUPLOT
set title "Comparación de tiempo de multiplicación entre normal y transposed"
set ylabel "Execution time (s)"
set xlabel "Matrix Size"
set key right bottom
set grid
set term png
set output "$fPNG"
plot "$fDAT" using 1:2 with lines lw 2 title "normal", \
     "$fDAT" using 1:5 with lines lw 2 title "transp"
replot
quit
END_GNUPLOT



echo "Generating read fails plot..."
# llamar a gnuplot para generar el gráfico y pasarle directamente por la entrada
# estándar el script que está entre "<< END_GNUPLOT" y "END_GNUPLOT"
gnuplot << END_GNUPLOT
set title "Comparacion de fallos de lectura por tamaño de caché" 
set ylabel "Fallos"
set xlabel "Tamaño Matriz"
set key box inside top left
set grid
set term png
set output "$fPNG_lec"
plot "$fDAT" using 1:3 with lines lw 2 title "normal", \
     "$fDAT" using 1:6 with lines lw 2 title "transp"
replot
quit
END_GNUPLOT


echo "Generating write fails plot..."
# llamar a gnuplot para generar el gráfico y pasarle directamente por la entrada
# estándar el script que está entre "<< END_GNUPLOT" y "END_GNUPLOT"
gnuplot << END_GNUPLOT
set title "Comparacion de fallos de escritura por tamaño de caché" 
set ylabel "Fallos"
set xlabel "Tamaño Matriz"
set key box inside top left
set grid
set term png
set output "$fPNG_esc"
plot "$fDAT" using 1:4 with lines lw 2 title "normal", \
     "$fDAT" using 1:7 with lines lw 2 title "transp"
replot
quit
END_GNUPLOT

    