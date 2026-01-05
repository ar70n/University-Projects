#!/bin/bash


# Número de veces a ejecutar el programa

make all
# Bucle para ejecutar el programa varias veces
for i in {1..10} 
do
    ./greyScale ../images/SD.jpg ../images/HD.jpg ../images/FHD.jpg ../images/4k.jpg ../images/8k.jpg >> ../log/time_original
    ./greyScale_rowmayor ../images/SD.jpg ../images/HD.jpg ../images/FHD.jpg ../images/4k.jpg ../images/8k.jpg >> ../log/time_optimized
    ./greyScale_intrinsics ../images/SD.jpg ../images/HD.jpg ../images/FHD.jpg ../images/4k.jpg ../images/8k.jpg >> ../log/time_intrinsics
done

