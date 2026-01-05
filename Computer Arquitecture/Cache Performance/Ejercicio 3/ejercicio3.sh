#!/bin/bash

Ninicio=1000
Npaso=500
Nfinal=$((Ninicio + 3500))
fPNG_lec=cache_lectura.png
fPNG_esc=cache_escritura.png

cache_inf=(1024 2048 4096 8192) # En Bytes
cache_sup=$((8*(2**20))) #8MB
line_size=64 #64B

#Borramos los .dat y los .png
rm cache_* 

#Compilar los programas
make all

for ((N=Ninicio; N < Nfinal; N+=Npaso)); do
    for cache_size in ${cache_inf[@]}; do
        echo "Matrix size: $N -- Cache size: $cache_size"
        valgrind --tool=cachegrind --I1=$cache_size,1,$line_size --D1=$cache_size,1,$line_size --LL=$cache_sup,1,$line_size --cachegrind-out-file=cachegrind.slow ./slow $N  1>/dev/null 2>/dev/null
        valgrind --tool=cachegrind --I1=$cache_size,1,$line_size --D1=$cache_size,1,$line_size --LL=$cache_sup,1,$line_size --cachegrind-out-file=cachegrind.fast ./fast $N  1>/dev/null 2>/dev/null

        d1mr_slow=$(cg_annotate cachegrind.slow | sed -n "18p" | cut -d ' ' -f 9 | tr -d ',') 
        d1mw_slow=$(cg_annotate cachegrind.slow | sed -n "18p" | cut -d ' ' -f 15 | tr -d ',')

        d1mr_fast=$(cg_annotate cachegrind.fast | sed -n "18p" | cut -d ' ' -f 9 | tr -d ',') 
        d1mw_fast=$(cg_annotate cachegrind.fast | sed -n "18p" | cut -d ' ' -f 15 | tr -d ',') 
        
        #echo "$d1mr_slow"
        #echo "$d1mw_slow"
        #echo "$d1mr_fast"
        #echo "$d1mw_fast"

        echo "$N $d1mr_slow $d1mw_slow $d1mr_fast $d1mw_fast" >> cache_$cache_size.dat  


    done
done

#Borramos los cache grind
rm cachegrind.*


echo "Generating plot lectura..."
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
plot "cache_1024.dat" using 1:2 with lines lw 2 title "slow_{1024}", \
     "cache_1024.dat" using 1:4 with lines lw 2 title "fast_{1024}", \
     "cache_2048.dat" using 1:2 with lines lw 2 title "slow_{2048}", \
     "cache_2048.dat" using 1:4 with lines lw 2 title "fast_{2048}", \
     "cache_4096.dat" using 1:2 with lines lw 2 title "slow_{4096}", \
     "cache_4096.dat" using 1:4 with lines lw 2 title "fast_{4096}", \
     "cache_8192.dat" using 1:2 with lines lw 2 title "slow_{8192}", \
     "cache_8192.dat" using 1:4 with lines lw 2 title "fast_{8192}"
replot
quit
END_GNUPLOT


echo "Generating plot escritura..."
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
plot "cache_1024.dat" using 1:3 with lines lw 2 title "slow_{1024}", \
     "cache_1024.dat" using 1:5 with lines lw 2 title "fast_{1024}", \
     "cache_2048.dat" using 1:3 with lines lw 2 title "slow_{2048}", \
     "cache_2048.dat" using 1:5 with lines lw 2 title "fast_{2048}", \
     "cache_4096.dat" using 1:3 with lines lw 2 title "slow_{4096}", \
     "cache_4096.dat" using 1:5 with lines lw 2 title "fast_{4096}", \
     "cache_8192.dat" using 1:3 with lines lw 2 title "slow_{8192}", \
     "cache_8192.dat" using 1:5 with lines lw 2 title "fast_{8192}"
replot
quit
END_GNUPLOT

    