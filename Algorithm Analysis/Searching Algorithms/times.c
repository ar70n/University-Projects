/**
 *
 * Descripcion: Implementation of time measurement functions
 *
 * Fichero: times.c
 * Autor: Carlos Aguirre Maeso
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */

#include "permutations.h"
#include "times.h"
#include "sorting.h"
#include "search.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

/***************************************************/
/* Function: average_sorting_time  Date: 6-10-2023 */
/* Authors: Miguel Campo, Antonio Moroño           */
/* It stores in ptime data about the functioning   */
/* of the metodo function                          */
/*                                                 */
/* Input:                                          */
/* metodo: sorting method                          */
/* n_perms: number of permutations                 */
/* N: size of the permutations                     */
/* ptime: where the info will be stored            */
/* Output:                                         */
/* -1 if there is an error, 0 if it is OK          */
/***************************************************/
short average_sorting_time(pfunc_sort metodo, int n_perms, int N, PTIME_AA ptime)
{
  clock_t ini, fin;
  int min = 0, max = 0, i, **perms, it = 0, itac = 0;
  double total_time = 0;

  if (!metodo || n_perms <= 0 || N <= 0 || !ptime)
  {
    return -1;
  }

  perms = generate_permutations(n_perms, N);

  if (!perms)
  {
    return -1;
  }

  for (i = 0; i < n_perms; i++)
  {
    if (!perms[i])
    {
      for (i = 0; i < n_perms; i++)
      {
        free(perms[i]);
      }
      free(perms);
      return -1;
    }
    ini = clock();
    itac = metodo(perms[i], 0, N - 1);
    it = it + itac;
    fin = clock();
    if (ini == -1 || fin == -1)
    {
      for (i = 0; i < n_perms; i++)
      {
        free(perms[i]);
      }
      free(perms);
      return -1;
    }
    if (itac > max)
    {
      max = itac;
    }
    if (itac < min || min == 0)
    {
      min = itac;
    }
    total_time = total_time + (double)(fin - ini) / CLOCKS_PER_SEC;
  }
  ptime->average_ob = (double)it / n_perms;
  ptime->max_ob = max;
  ptime->min_ob = min;
  ptime->N = N;
  ptime->n_elems = n_perms;
  ptime->time = (double)total_time / n_perms;

  for (i = 0; i < n_perms; i++)
  {
    free(perms[i]);
  }
  free(perms);
  return 0;
}

/***************************************************/
/* Function: generate_sorting_times Date:20-10-2023*/
/* Authors: Miguel Campo, Antonio Moroño           */
/* It creates data about the functioning of method */
/*                                                 */
/* Input:                                          */
/* method: sorting method                          */
/* file: name of the file to store the info        */
/* num_min: lowest size of permutations            */
/* num_max: highest size of permutations           */
/* incr: difference of size between iterations     */
/* n_perms: number of permutations                 */
/* Output:                                         */
/* -1 if error, 0 if not                           */
/***************************************************/
short generate_sorting_times(pfunc_sort method, char *file, int num_min, int num_max, int incr, int n_perms)
{
  int i, j = 0;
  PTIME_AA ptime;

  if (!method || !file || num_min < 0 || num_max < num_min || incr <= 0 || n_perms <= 0)
  {
    return -1;
  }

  ptime = malloc(sizeof(TIME_AA) * ((num_max - num_min) / incr + 1));
  if (!ptime)
  {
    return -1;
  }

  for (i = num_min; i <= num_max; i = i + incr)
  {
    printf("i = %d\n", i);
    if (average_sorting_time(method, n_perms, i, &ptime[j]) == -1)
    {
      free(ptime);
      return -1;
    }
    j++;
  }

  if (save_time_table(file, ptime, (num_max - num_min) / incr + 1) == -1)
  {
    free(ptime);
    return -1;
  }

  free(ptime);
  return 0;
}

/***************************************************/
/* Function: save_time_table   Date: 6-10-2023     */
/* Authors: Miguel Campo, Antonio Moroño           */
/* It saves data from ptime in a file              */
/*                                                 */
/* Input:                                          */
/* file: name of the file to store the info        */
/* ptime: where the info is taken from             */
/* n_times: number of rows in the file             */
/* Output:                                         */
/* -1 if error, 0 if not                           */
/***************************************************/
short save_time_table(char *file, PTIME_AA ptime, int n_times)
{

  int i, status = 0;

  FILE *entrada = NULL;

  if (file == NULL || n_times < 0 || !ptime)
  {
    return ERR;
  }

  entrada = fopen(file, "w");
  if (entrada == NULL)
  {
    return ERR;
  }

  for (i = 0; i < n_times; i++)
  {
    status = fprintf(entrada, "%d\t%f\t%d\t%d\t%f\n", ptime[i].N, ptime[i].average_ob, ptime[i].max_ob, ptime[i].min_ob, ptime[i].time);
    if (status < 0)
    {
      fclose(entrada);
      return ERR;
    }
  }

  fclose(entrada);

  return OK;
}

short generate_search_times(pfunc_search method, pfunc_key_generator generator, int order, char *file, int num_min, int num_max, int incr, int n_times)
{
  int i, j = 0;
  PTIME_AA ptime;

  if (!method || !file || num_min < 0 || num_max < num_min || incr <= 0)
  {
    return -1;
  }

  ptime = malloc(sizeof(TIME_AA) * ((num_max - num_min) / incr + 1));
  if (!ptime)
  {
    return -1;
  }

  for (i = num_min; i <= num_max; i = i + incr)
  {
    printf("i = %d\n", i);
    if (average_search_time(method, generator, order, i, n_times, &ptime[j]) == -1)
    {
      free(ptime);
      return -1;
    }
    j++;
  }

  if (save_time_table(file, ptime, (num_max - num_min) / incr + 1) == -1)
  {
    free(ptime);
    return -1;
  }

  free(ptime);
  return 0;
}

/***************************************************/
/* Function: average_sorting_time  Date: 6-10-2023 */
/* Authors: Miguel Campo, Antonio Moroño           */
/* It stores in ptime data about the functioning   */
/* of the metodo function                          */
/*                                                 */
/* Input:                                          */
/* metodo: sorting method                          */
/* n_times: number of permutations                 */
/* N: size of the permutations                     */
/* ptime: where the info will be stored            */
/* Output:                                         */
/* -1 if there is an error, 0 if it is OK          */
/***************************************************/
short average_search_time(pfunc_search metodo, pfunc_key_generator generator,
                          char order, int N, int n_times, PTIME_AA ptime)
{
  clock_t ini, fin;
  int min = 0, max = 0, i, it = 0, itac = 0;
  double total_time = 0;
  int *keys, *perm;
  PDICT pdict;
  int ppos;

  if (!metodo || !generator || (order != SORTED && order != NOT_SORTED) || N <= 0 || !ptime)
  {
    return -1;
  }

  pdict = init_dictionary(N, order);

  if (!pdict){
    return -1;
  }

  perm = generate_perm(N);
  if (!perm){
    return -1;
  }
  if (massive_insertion_dictionary(pdict, perm, N) == -1){
    return -1;
  }


  keys = (int *)malloc(sizeof(int) * n_times * N);
  if (!keys){
    return -1;
  }

  generator(keys, N * n_times, N);
  for (i = 0; i < N * n_times; i++)
  {
    ini = clock();
    itac = search_dictionary(pdict, keys[i], &ppos, metodo);
    if (ppos == ERR)
    {

      free_dictionary(pdict);
      free(keys);

      fprintf(stderr, "ERROR");
      return ERR;
    }
    it = it + itac;
    fin = clock();
    if (ini == -1 || fin == -1)
    {
      /*Control errores*/
      free_dictionary(pdict);
      free(keys);

      fprintf(stderr, "ERROR");
      return ERR;
    }
    if (itac > max)
    {
      max = itac;
    }
    if (itac < min || min == 0)
    {
      min = itac;
    }
    total_time = total_time + (double)(fin - ini) / CLOCKS_PER_SEC;
  }
  ptime->average_ob = (double)it / (n_times*N);
  ptime->max_ob = max;
  ptime->min_ob = min;
  ptime->N = N;
  ptime->n_elems = n_times;
  ptime->time = total_time / (N * n_times);

  free(perm);
  free_dictionary(pdict);
  free(keys);
  return OK;
}
