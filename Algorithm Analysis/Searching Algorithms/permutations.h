/**
 * @file permutations.h
 * @brief Header file for functions related to permutations generation.
 *
 * This header file contains the declarations of functions for generating permutations.
 * It provides functions to generate a random number within a given range, generate a single permutation of size N,
 * and generate multiple permutations.
 *
 * @author Carlos Aguirre
 * @version 1.1
 * @date 16-09-2019
 */

#ifndef PERMUTATIONS_H
#define PERMUTATIONS_H

/* constants */

#ifndef ERR
  #define ERR -1
  #define OK (!(ERR))
#endif

/**
 * @brief Generates a random number within the specified range.
 *
 * This function generates a random number between the given lower and upper bounds (inclusive).
 *
 * @param inf The lower bound of the range.
 * @param sup The upper bound of the range.
 * @return The randomly generated number.
 */
int random_num(int inf, int sup);

/**
 * @brief Generates a single permutation of size N.
 *
 * This function generates a single permutation of size N.
 *
 * @param N The size of the permutation.
 * @return A dynamically allocated array representing the permutation.
 *         The caller is responsible for freeing the memory.
 */
int* generate_perm(int N);

/**
 * @brief Generates multiple permutations.
 *
 * This function generates a specified number of permutations, each of size N.
 *
 * @param n_perms The number of permutations to generate.
 * @param N The size of each permutation.
 * @return A dynamically allocated 2D array representing the permutations.
 *         The caller is responsible for freeing the memory.
 */
int** generate_permutations(int n_perms, int N);

#endif
