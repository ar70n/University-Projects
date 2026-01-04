
/**
 *
 * Descripcion: Header file for time measurement functions 
 *
 * Fichero: times.h
 * Autor: Carlos Aguirre.
 * Version: 1.1
 * Fecha: 15-09-2019
 *
 */

#ifndef TIMES_H
#define TIMES_H

/* constants */

#ifndef ERR
  #define ERR -1
  #define OK (!(ERR))
#endif

#include "sorting.h"
#include "search.h"

/* type definitions */
typedef struct time_aa {
  int N;           /* size of each element */
  int n_elems;     /* number of elements to average */
  double time;   /* average clock time */
  double average_ob; /* average number of times that the OB is executed */
  int min_ob;      /* minimum of executions of the OB */
  int max_ob;      /* maximum of executions of the OB */
} TIME_AA, *PTIME_AA;


/**
 * Calculates the average sorting time for a given sorting method.
 *
 * @param method The sorting method to be evaluated.
 * @param n_perms The number of permutations to generate.
 * @param N The size of each element.
 * @param ptime Pointer to the TIME_AA structure to store the results.
 * @return Returns 0 if the sorting time was calculated successfully, -1 otherwise.
 */
short average_sorting_time(pfunc_sort method, int n_perms, int N, PTIME_AA ptime);

/**
 * Generates sorting times for a given sorting method and saves them to a file.
 *
 * @param method The sorting method to be evaluated.
 * @param file The file path to save the results.
 * @param num_min The minimum number of elements.
 * @param num_max The maximum number of elements.
 * @param incr The increment value for the number of elements.
 * @param n_perms The number of permutations to generate.
 * @return Returns 0 if the sorting times were generated and saved successfully, -1 otherwise.
 */
short generate_sorting_times(pfunc_sort method, char* file, int num_min, int num_max, int incr, int n_perms);

/**
 * Saves the time table to a file.
 *
 * @param file The file path to save the time table.
 * @param time Pointer to the TIME_AA structure containing the time table.
 * @param n_times The number of time measurements.
 * @return Returns 0 if the time table was saved successfully, -1 otherwise.
 */
short save_time_table(char* file, PTIME_AA time, int n_times);

/**
 * Generates search times for a given search method and saves them to a file.
 *
 * @param method The search method to be evaluated.
 * @param generator The key generator function.
 * @param order The order of the elements (ascending 'a' or descending 'd').
 * @param file The file path to save the results.
 * @param num_min The minimum number of elements.
 * @param num_max The maximum number of elements.
 * @param incr The increment value for the number of elements.
 * @param n_times The number of time measurements.
 * @return Returns 0 if the search times were generated and saved successfully, -1 otherwise.
 */
short generate_search_times(pfunc_search method, pfunc_key_generator generator, int order, char* file, int num_min, int num_max, int incr, int n_times);

/**
 * Calculates the average search time for a given search method.
 *
 * @param method The search method to be evaluated.
 * @param generator The key generator function.
 * @param order The order of the elements (ascending 'a' or descending 'd').
 * @param N The size of each element.
 * @param n_times The number of time measurements.
 * @param ptime Pointer to the TIME_AA structure to store the results.
 * @return Returns 0 if the search time was calculated successfully, -1 otherwise.
 */
short average_search_time(pfunc_search method, pfunc_key_generator generator, char order, int N, int n_times, PTIME_AA ptime);
#endif
