// ----------- Arqo P4-----------------------
// pescalar_par1
// ¿Funciona correctamente?
//
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "arqo4.h"

#define N_OF_BLOCKS 10		 		// Número de bloques a medir
#define BLOCK_SIZE 1 				// Tamaño de los bloques
#define MAX_TRY_ITERATIONS 50000 	// Número máximo de iteraciones para encontrar el tamaño adecuado
#define DEFAULT_JUMP 100			// Cuánto aumentamos o disminuimos el tamaño del vector en cada iteración
#define START_SIZE 1000			 	// Tamaño inicial del vector

int test_treshold(int vector_size, int iterations, int big);
void analyze_threshold(int vector_size);
int test_block(int size, int iterations, tipo *A, tipo *B);

int main(int argc, char *argv[])
{
	int nproc;
	int size = START_SIZE;
	int small_size, big_size;
	int n_valid_blocks;
	float jump_multiplier;
	int i;

	nproc = omp_get_num_procs();
	omp_set_num_threads(nproc);

	for (i = 0; i < MAX_TRY_ITERATIONS; i++)
	{
		if(size < 1) size = 1;
		small_size = ceil(size * 0.8);
		big_size = ceil(size * 1.2);

		/*printf("Probando con tamaño %d\n", size);*/

		n_valid_blocks = test_treshold(small_size, N_OF_BLOCKS, 0);

		if (n_valid_blocks < N_OF_BLOCKS )
		{
			printf("[Tamaño: %d]\tValid blocks (small):\t[%d]\tDisminuir tamaño\t\u2193 \n", size, n_valid_blocks);
			jump_multiplier = 1 - (n_valid_blocks / (float) N_OF_BLOCKS);
			/*printf("Jump multiplier: %f\n", jump_multiplier);*/
			size -= DEFAULT_JUMP * jump_multiplier;
			continue;
		}

		n_valid_blocks = test_treshold(big_size, N_OF_BLOCKS, 1);

		if (n_valid_blocks < N_OF_BLOCKS )
		{
			printf("[Tamaño: %d]\tValid blocks (big):\t[%d]\tAumentar tamaño \t\u2191 \n", size, n_valid_blocks);
			jump_multiplier = 1 - (n_valid_blocks / (float) N_OF_BLOCKS);
			/*printf("Jump multiplier: %f\n", jump_multiplier);*/
			size += DEFAULT_JUMP * jump_multiplier;
			continue;
		}

		printf("Treshold válido: %d\n", size);
		analyze_threshold(size);
		return 0;
	}

	printf("MAX_ITERATIONS agotado: no se ha encontrado un treshold valido\n");

	return 0;
}

/*
vector_size: tamaño del vector
iterations: número de bloques que se van a validar
big: 	-si es 0, se espera que el monohilo sea más rápido
		-si es 1, se espera que el multihilo sea más rápido
devuelve el número de bloques que se comportan correctamente
*/
int test_treshold(int vector_size, int iterations, int big)
{
	tipo *A = NULL, *B = NULL;
	int n_valid_blocks = 0;
	int test;
	int i;

	A = generateVectorOne(vector_size);
	B = generateVectorOne(vector_size);

	if (!A || !B)
	{
		printf("Error when allocationg matrix\n");
		freeVector(A);
		freeVector(B);
		return -1;
	}

	for (i = 0; i < iterations; i++)
	{
		test = test_block(vector_size, BLOCK_SIZE, A, B);

		if ( (big == 1 && test == 1) || (big == 0 && test == 0) )
		{
			n_valid_blocks++;
		}
	}

	/* Free vectors*/
	freeVector(A);
	freeVector(B);

	return n_valid_blocks;
}

/*Ejecuta el producto escalar monohilo 'iterations' veces  mide el tiempo.
Hace lo mismo para la versión multihilo
Devuelve 0 si monohilo es más rápido, 1 si multihilo es más rápido
De esta forma, al múltiples iteraciones en la medición del tiempo,
logramos mitigar parcialmente las imprecisiones que se pueden cometer
al medir tiempos para tamaños muy pequeños de vector*/
int test_block(int size, int iterations, tipo *A, tipo *B)
{
	struct timeval fin, ini;
	double singlethread_time, multithread_time;
	int sum = 0;
	int i, k;

	/*MONOHILO*/
	gettimeofday(&ini, NULL);

	for (i = 0; i < iterations; i++)
	{
		for (k = 0; k < size; k++)
		{
			sum = sum + A[k] * B[k];
		}
	}

	gettimeofday(&fin, NULL);
	singlethread_time = ((fin.tv_sec * 1000000 + fin.tv_usec) - (ini.tv_sec * 1000000 + ini.tv_usec)) * 1.0 / 1000000.0;

	/*MULTIHILO*/
	gettimeofday(&ini, NULL);

	for (i = 0; i < iterations; i++)
	{
		#pragma omp parallel for reduction(+ : sum)	
		for (k = 0; k < size; k++)
		{
			sum = sum + A[k] * B[k];
		}
	}

	gettimeofday(&fin, NULL);
	multithread_time = ((fin.tv_sec * 1000000 + fin.tv_usec) - (ini.tv_sec * 1000000 + ini.tv_usec)) * 1.0 / 1000000.0;

	//printf("Singlethread time: %f, multithread time: %f\n", singlethread_time, multithread_time);

	if (singlethread_time < multithread_time)	return 0;
	else 										return 1;
}

/*
Guarda en un fichero los datos relativos a un treshold y sus proximidades
*/
void analyze_threshold(int vector_size)
{
	FILE *file = fopen("threshold.dat", "w");
	int size, small_size, big_size;
	float valid_blocks_small, valid_blocks_big;

	if (!file)
	{
		printf("Error opening file\n");
		return;
	}

	for (float factor = 0.1; factor <= 2.0; factor += 0.1)
	{
		size = ceil(vector_size * factor);
		small_size = ceil(size * 0.8);
		big_size = ceil(size * 1.2);

		valid_blocks_small = (float) test_treshold(small_size, N_OF_BLOCKS, 0) / N_OF_BLOCKS;
		valid_blocks_big = (float) test_treshold(big_size, N_OF_BLOCKS, 1) / N_OF_BLOCKS;

		fprintf(file, "%d %f %f\n", size, valid_blocks_small, valid_blocks_big);
	}

	fclose(file);
}