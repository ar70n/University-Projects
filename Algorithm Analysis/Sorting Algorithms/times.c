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

  ptime = malloc(sizeof(TIME_AA) * ((num_max - num_min) / incr + 1));
  if (!ptime)
  {
    return -1;
  }

  for (i = num_min; i <= num_max; i = i + incr)
  {
    if (average_sorting_time(method, n_perms, i, &ptime[j]) == -1)
    {
      free(ptime);
      return -1;
    }
    j++;
  }

  if (save_time_table(file, ptime, (num_max - num_min) / incr) == -1)
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

  int i;

  FILE *entrada;

  if (file == NULL || n_times < 1 || !ptime)
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
    fprintf(entrada, "%d\t%f\t%f\t%d\t%d\n", ptime[i].N, ptime[i].time, ptime[i].average_ob, ptime[i].max_ob, ptime[i].min_ob);
  }

  fclose(entrada);

  return OK;
}
