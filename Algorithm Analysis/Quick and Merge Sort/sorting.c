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
#include <stdlib.h>
#include <stdio.h>

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

/***************************************************/
/* Function: mergesort        Date: 29-09-2023     */
/* Authors: Miguel Campo, Antonio Moroño           */
/* It implements the merge sort algorithm          */
/*                                                 */
/* Input:                                          */
/* array: elements to be sorted                    */
/* ip: first index                                 */
/* iu: last index                                  */
/* Output:                                         */
/* number of iterations                            */
/***************************************************/
int mergesort(int *tabla, int ip, int iu)
{

  int m, c, status;

  c = 0;
  status = 0;

  if (ip > iu || ip < 0 || iu < 0 || tabla == NULL)
  {
    return -1;
  }
  else if (iu == ip)
  {
    return 0;
  }
  m = (ip + iu) / 2;

  status = mergesort(tabla, ip, m);
  if (status == -1)
  {
    return -1;
  }
  else
  {
    c += status;
  }
  status = mergesort(tabla, m + 1, iu);
  if (status == -1)
  {
    return -1;
  }
  else
  {
    c += status;
  }
  status = merge(tabla, ip, iu, m);
  if (status == -1)
  {
    return -1;
  }
  else
  {
    c += status;
  }
  return c;
}

/***************************************************/
/* Function: mergesort        Date: 29-09-2023     */
/* Authors: Miguel Campo, Antonio Moroño           */
/* It implements the merge function                */
/*                                                 */
/* Input:                                          */
/* array: elements to be sorted                    */
/* ip: first index                                 */
/* iu: last index                                  */
/* imedio: mediddle index                          */
/* Output:                                         */
/* number of iterations                            */
/***************************************************/
int merge(int *tabla, int ip, int iu, int imedio)
{

  int *tabla2;
  int i, j, k, c;
  c = 0;
  i = ip;
  j = imedio + 1;
  k = 0;
  if (tabla == NULL || ip > iu || imedio > iu || imedio < ip || imedio < 0)
  {

    return -1;
  }
  tabla2 = (int *)malloc(sizeof(int) * (iu - ip + 1));
  if (tabla2 == NULL)
  {
    return -1;
  }
  while (i <= imedio && j <= iu)
  {
    c++;
    if (tabla[i] < tabla[j])
    {
      tabla2[k] = tabla[i];
      i++;
    }
    else
    {
      tabla2[k] = tabla[j];
      j++;
    }
    k++;
  }
  if (i > imedio)
  {

    while (j <= iu)
    {
      tabla2[k] = tabla[j];
      j++;
      k++;
    }
  }
  else if (j > iu)
  {

    while (i <= imedio)
    {
      tabla2[k] = tabla[i];
      i++;
      k++;
    }
  }
  for (i = ip; i <= iu; i++)
  {

    tabla[i] = tabla2[i - ip];
  }
  free(tabla2);
  return c;
}

/***************************************************/
/* Function: swap  Date: 27-10-2023                */
/* Authors: Miguel Campo, Antonio Moroño           */
/* Swaps two elements within a table               */
/*                                                 */
/* Input:                                          */
/* tabla: table                                    */
/* i: first element index                          */
/* j: second element index                         */
/* Output:                                         */
/* 0 if everything is correct, -1 otherwise        */
/***************************************************/
int swap(int *tabla, int i, int j)
{
  int aux;
  if (!tabla || i < 0 || j < 0)
  {
    return -1;
  }
  aux = tabla[i];
  tabla[i] = tabla[j];
  tabla[j] = aux;
  return 0;
}

/***************************************************/
/* Function: quicksort   Date: 27-10-2023          */
/* Authors: Miguel Campo, Antonio Moroño           */
/* Implements the quicksort algorithm              */
/*                                                 */
/* Input:                                          */
/* tabla: table to be sorted                       */
/* i: first element index                          */
/* iu: last element index                          */
/* Output:                                         */
/* Number of basic operations                      */
/***************************************************/
int quicksort(int *tabla, int ip, int iu)
{
  int *pos, ob = 0, status;
  
  if (ip > iu || !tabla || iu < 0 || ip < 0)
  {
    return -1;
  }
  
  
  pos = (int *)malloc(sizeof(int));
  if (pos == NULL)
  {
    return -1;
  }

  if (ip == iu)
  {
    free(pos);
    return 0;
  }
  else
  {
    status = partition(tabla, ip, iu, pos);
    if (status == -1){
      free(pos);
      return -1;
    }
    ob += status;
    if (ip < *pos - 1)
    {
      status = quicksort(tabla, ip, *pos - 1);
      if (status == -1){
        free(pos);
        return -1;
      }
      ob += status;
    }
    if (*pos + 1 < iu)
    {
      status = quicksort(tabla, *pos + 1, iu);
      if (status == -1){
        free(pos);
        return -1;
      }
      ob += status;
    }
  }

  free(pos);
  return ob;
}

/***************************************************/
/* Function: partition   Date: 27-10-2023          */
/* Authors: Miguel Campo, Antonio Moroño           */
/* Implements the quicksort algorithm              */
/*                                                 */
/* Input:                                          */
/* tabla: table to be sorted                       */
/* i: first element index                          */
/* iu: last element index                          */
/* pos: position of the pivot                      */
/* Output:                                         */
/* Number of basic operations                      */
/***************************************************/
int partition(int *tabla, int ip, int iu, int *pos)
{
  int k, i, obm, count = 0;
  
  if (ip > iu || !pos || !tabla || ip < 0 || iu < 0){
    return -1;
  }
  obm = median(tabla, ip, iu, pos);
  if (obm == -1){
    return -1;
  }
  k = tabla[*pos];
  if (swap(tabla, ip, *pos) == -1){
    return -1;
  }
  *pos = ip;
  for (i = ip + 1; i <= iu; i++)
  {
    count++;
    if (tabla[i] < k)
    {
      (*pos)++;
      if (swap(tabla, i, *pos) == -1){
        return -1;
      }
    }
  }
  if (swap(tabla, ip, *pos) == -1){
    return -1;
  }
  return count + obm;
}

int median(int *tabla, int ip, int iu, int *pos)
{
  *pos = ip;
  return 0;
}

int median_avg(int *tabla, int ip, int iu, int *pos)
{
  *pos = (ip + iu) / 2;
  return 0;
}

int median_stat(int *tabla, int ip, int iu, int *pos)
{
  int medio = (ip + iu) / 2;
  if (ip < 0 || iu < 0 || ip > iu)
  {
    return -1;
  }

  if ((tabla[ip] >= tabla[medio] && tabla[ip] <= tabla[iu]) || (tabla[ip] <= tabla[medio] && tabla[ip] >= tabla[iu]))
  {
    *pos = ip;
  }
  else if ((tabla[medio] >= tabla[ip] && tabla[medio] <= tabla[iu]) || (tabla[medio] <= tabla[ip] && tabla[medio] >= tabla[iu]))
  {
    *pos = medio;
  }
  else
  {
    *pos = iu;
  }

  return 3;
}