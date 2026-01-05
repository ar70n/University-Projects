#!/bin/bash

# inicializar variables
Ninicio=256
Npaso=256
Nfinal=1024
fDAT=mult.dat
fPNG=mult_time.png
fPNG_lec=mult_cache_read.png
fPNG_esc=mult_cache_write.png

cache_inf=(1024 2048 4096 8192) # En Bytes
cache_sup=$((8*(2**20))) #8MB

assoc=(1 4 8)
line_size=(32 64) #64B

iteraciones=1

# borrar el fichero DAT y el fichero PNG
rm -f $fDAT $fPNG $fPNG_lec $fPNG_esc mult.*

#Compilar los programas
make all


echo "Running normal and transposed multiplication..."
# bucle para N desde P hasta Q 
for ((N = Ninicio ; N <= Nfinal ; N += Npaso)); do	

    #Apartado 2)
 	for cache_size in ${cache_inf[@]}; do
 		for line_s in ${line_size[@]}; do
 			for assoc_s in ${assoc[@]}; do 
 				valgrind --tool=cachegrind --I1=$cache_size,1,$line_s --D1=$cache_size,$assoc_s,$line_s --LL=$cache_sup,$assoc_s,$line_s --cachegrind-out-file=cachegrind.normal ./mult_normal $N  1>/dev/null 2>/dev/null
 				valgrind --tool=cachegrind --I1=$cache_size,1,$line_s --D1=$cache_size,$assoc_s,$line_s --LL=$cache_sup,$assoc_s,$line_s --cachegrind-out-file=cachegrind.transp ./mult_transp $N  1>/dev/null 2>/dev/null


 				ir_normal=$(cg_annotate cachegrind.normal | sed -n "18p" | cut -d ' ' -f 1 | tr -d ',')
 				i1mr_normal=$(cg_annotate cachegrind.normal | sed -n "18p" | cut -d ' ' -f 3 | tr -d ',')
 				ilmr_normal=$(cg_annotate cachegrind.normal | sed -n "18p" | cut -d ' ' -f 5 | tr -d ',')
 				dr_normal=$(cg_annotate cachegrind.normal | sed -n "18p" | cut -d ' ' -f 7 | tr -d ',')
 				d1mr_normal=$(cg_annotate cachegrind.normal | sed -n "18p" | cut -d ' ' -f 9 | tr -d ',')
 				dlmr_normal=$(cg_annotate cachegrind.normal | sed -n "18p" | cut -d ' ' -f 11 | tr -d ',')
 				dw_normal=$(cg_annotate cachegrind.normal | sed -n "18p" | cut -d ' ' -f 13 | tr -d ',') 
 				d1mw_normal=$(cg_annotate cachegrind.normal | sed -n "18p" | cut -d ' ' -f 15 | tr -d ',')
 				dlmw_normal=$(cg_annotate cachegrind.normal | sed -n "18p" | cut -d ' ' -f 17 | tr -d ',')

 				ir_transp=$(cg_annotate cachegrind.transp | sed -n "18p" | cut -d ' ' -f 1 | tr -d ',')
 				i1mr_transp=$(cg_annotate cachegrind.transp | sed -n "18p" | cut -d ' ' -f 3 | tr -d ',')
 				ilmr_transp=$(cg_annotate cachegrind.transp | sed -n "18p" | cut -d ' ' -f 5 | tr -d ',')
 				dr_transp=$(cg_annotate cachegrind.transp | sed -n "18p" | cut -d ' ' -f 7 | tr -d ',')
 				d1mr_transp=$(cg_annotate cachegrind.transp | sed -n "18p" | cut -d ' ' -f 9 | tr -d ',')
				dlmr_transp=$(cg_annotate cachegrind.transp | sed -n "18p" | cut -d ' ' -f 11 | tr -d ',')
				dw_transp=$(cg_annotate cachegrind.transp | sed -n "18p" | cut -d ' ' -f 13 | tr -d ',') 
				d1mw_transp=$(cg_annotate cachegrind.transp | sed -n "18p" | cut -d ' ' -f 15 | tr -d ',')
				dlmw_transp=$(cg_annotate cachegrind.transp | sed -n "18p" | cut -d ' ' -f 17 | tr -d ',')					


				echo "$N  $ir_normal $i1mr_normal $ilmr_normal $dr_normal $d1mr_normal $dlmr_normal $dw_normal $d1mw_normal $dlmw_normal $ir_transp $i1mr_transp $ilmr_transp $dr_transp $d1mr_transp $dlmr_transp $dw_transp $d1mw_transp $dlmw_transp" >> mult.$cache_size.$line_s.$assoc_s.dat  
			done
		done
	done 

done


#Borramos los cache grind
rm cachegrind.*



echo "Generating instruction read plot..."
gnuplot << END_GNUPLOT
set title "Comparación de lecturas de instrucciones entre normal y transposed"
set ylabel "Lecturas de instrucciones"
set xlabel "Tamaño Matriz"
set key right bottom
set grid
set term png
set output "ir_$fPNG"
plot "$fDAT" using 1:2 with lines lw 2 title "normal", \
	"$fDAT" using 1:11 with lines lw 2 title "transp"
replot
quit
END_GNUPLOT


echo "Generating instruction L1 cache miss plot..."
for cache_size in ${cache_inf[@]}; do
	for line_s in ${line_size[@]}; do
		for assoc_s in ${assoc[@]}; do
			echo "Generating L1 data cache miss plot for cache size $cache_size, line size $line_s, associativity $assoc_s..."
			gnuplot << END_GNUPLOT
set title "Comparación de fallos de memoria de datos de la cache L1 entre normal y transposed (Cache: ${cache_size}B, Line: ${line_s}B, Assoc: ${assoc_s})"
set ylabel "Fallos de memoria de datos de la cache L1"
set xlabel "Tamaño Matriz"
set key right bottom
set grid
set term png size 1200,800
set output "d1mr_${cache_size}_${line_s}_${assoc_s}_$fPNG"
plot "mult.${cache_size}.${line_s}.${assoc_s}.dat" using 1:6 with lines lw 2 title "normal", \
	"mult.${cache_size}.${line_s}.${assoc_s}.dat" using 1:15 with lines lw 2 title "transp"
replot
quit
END_GNUPLOT
		done
	done
done