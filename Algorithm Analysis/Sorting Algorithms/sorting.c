/**
 *
 * Descripcion: Implementation of sorting functions
 *
 * Fichero: sorting.c
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */

#include "sorting.h"

/***************************************************/
/* Function: SelectSort    Date: 29-09-2023        */
/* Authors: Miguel Campo, Antonio Moroño           */
/* It implements the select sort algorithm         */
/*                                                 */
/* Input:                                          */
/* array: elements to be sorted                    */
/* ip: first index                                 */
/* iu: last index                                  */
/* Output:                                         */
/* Number of iterations                            */
/***************************************************/
int SelectSort(int *array, int ip, int iu)
{
  int i, mini, aux, ob = 0;
  i = ip;

  if (!array || ip < 0 || iu < ip)
  {
    return -1;
  }

  while (i < iu)
  {
    mini = min(array, i, iu);
    ob = ob + iu - i;
    aux = array[i];
    array[i] = array[mini];
    array[mini] = aux;
    i++;
  }

  return ob;
}


/***************************************************/
/* Function: SelectSortInv    Date: 29-09-2023     */
/* Authors: Miguel Campo, Antonio Moroño           */
/* It implements the inverted select sort algorithm*/
/*                                                 */
/* Input:                                          */
/* array: elements to be sorted                    */
/* ip: first index                                 */
/* iu: last index                                  */
/* Output:                                         */
/* number of iterations                            */
/***************************************************/
int SelectSortInv(int *array, int ip, int iu)
{
  int i, mini, aux, ob = 0;
  i = iu;

  if (!array || ip < 0 || iu < ip)
  {
    return -1;
  }
  while (i > ip)
  {
    mini = min(array, ip, i);
    ob = ob + i - ip;
    aux = array[i];
    array[i] = array[mini];
    array[mini] = aux;
    i--;
  }

  return ob;
}

/***************************************************/
/* Function: min   Date: 29- 9-2023                */
/* Authors: Miguel Campo, Antonio Moroño           */
/* Returns the lowest element from a given subtable*/
/*                                                 */
/* Input:                                          */
/* array: elements to be sorted                    */
/* ip: first index                                 */
/* iu: last index                                  */
/* Output:                                         */
/* lowest element                                  */
/***************************************************/
int min(int *array, int ip, int iu)
{
  int j, min;
  min = ip;

  for (j = ip + 1; j <= iu; j++)
  {
    if (array[j] < array[min])
    {
      min = j;
    }
  }
  return min;
}

