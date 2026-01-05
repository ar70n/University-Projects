#!/bin/bash


# Número de veces a ejecutar el programa
tope=1000000

# Bucle para ejecutar el programa varias veces
for ((i=100000; i<=tope; i+=100000))
do
    gcc -march=native -DNUMBER_OF_TRIALS=$i -O3 simple2_intrinsics.c -o simple2_intrinsics
    ./simple2_intrinsics >> ./log/time_intrinsic
done

echo -e "\n" >> ./log/time_intrinsic
