/**
 *
 * Descripcion: Implementation of function that generate permutations
 *
 * File: permutations.c
 * Autor: Carlos Aguirre
 * Version: 1.1
 * Fecha: 21-09-2019
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "permutations.h"

/***************************************************/
/* Function: random_num Date: 22-09-2023           */
/* Authors: Miguel Campo, Antonio Moroño    	   */
/*                                                 */
/* Rutine that generates a random number           */
/* between two given numbers                       */
/*                                                 */
/* Input:                                          */
/* int inf: lower limit                            */
/* int sup: upper limit                            */
/* Output:                                         */
/* int: random number                              */
/***************************************************/
int random_num(int inf, int sup)
{
	int n;
	double i = (double)sup - inf + 1;

	n = (int)((i)*rand() / (RAND_MAX + 1.0)) + inf;

	return n;
}

/***************************************************/
/* Function: generate_perm Date: 22-09-2023        */
/* Authors: Miguel Campo, Antonio Moroño           */
/*                                                 */
/* Rutine that generates a random permutation      */
/*                                                 */
/* Input:                                          */
/* int n: number of elements in the permutation    */
/* Output:                                         */
/* int *: pointer to integer array                 */
/* that contains the permitation                   */
/* or NULL in case of error                        */
/***************************************************/
int *generate_perm(int N)
{
	int i, *perm, aux, random;

	if (N < 1)
	{
		return NULL;
	}
	perm = (int *)malloc(sizeof(int) * N);

	if (perm == NULL)
	{
		return NULL;
	}

	for (i = 0; i < N; i++)
	{
		perm[i] = i + 1;
	}

	for (i = 0; i < N; i++)
	{
		aux = perm[i];
		random = random_num(i, N - 1);
		perm[i] = perm[random];
		perm[random] = aux;
	}

	return perm;
}

/***************************************************/
/* Function: generate_permutations Date: 29-09-2023*/
/* Authors: Miguel Campo, Antonio Moroño           */
/*                                                 */
/* Function that generates n_perms random          */
/* permutations with N elements                    */
/*                                                 */
/* Input:                                          */
/* int n_perms: Number of permutations             */
/* int N: Number of elements in each permutation   */
/* Output:                                         */
/* int**: Array of pointers to integer that point  */
/* to each of the permutations                     */
/* NULL en case of error                           */
/***************************************************/
int **generate_permutations(int n_perms, int N)
{
	int **array, i;

	if (N <= 0 || n_perms <= 0)
	{
		return NULL;
	}

	array = (int **)malloc(sizeof(int *) * n_perms);
	if (!array)
	{
		return NULL;
	}

	for (i = 0; i < n_perms; i++)
	{

		array[i] = generate_perm(N);

		if (array[i] == NULL)
		{
			for (i--; i >= 0; i--)
			{
				free(array[i]);
			}
			free(array);
		}
	}

	return array;
}
