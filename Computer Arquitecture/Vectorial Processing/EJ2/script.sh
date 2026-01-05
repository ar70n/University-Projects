#!/bin/bash


# Número de veces a ejecutar el programa
tope=1000000

# Bucle para ejecutar el programa varias veces
for ((i=100000; i<=tope; i+=100000))
do
    gcc -march=native -O3 -fno-tree-vectorize -DNUMBER_OF_TRIALS=$i simple2.c -o simple2
    ./simple2 >> ./log/time_simple
done

echo -e "\n" >> ./log/time_simple
