#include "search.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

/**
 *  Key generation functions
 *
 *  Description: Receives the number of keys to generate in the n_keys
 *               parameter. The generated keys go from 1 to max. The
 * 				 keys are returned in the keys parameter which must be
 *				 allocated externally to the function.
 */

/**
 *  Function: uniform_key_generator
 *  Description: This function generates all keys from 1 to max in a sequential
 *               manner. If n_keys == max, each key will just be generated once.
 *  Parameters:
 *    - keys: An array to store the generated keys.
 *    - n_keys: The number of keys to generate.
 *    - max: The maximum value for the keys.
 *  Returns: void
 */
void uniform_key_generator(int *keys, int n_keys, int max)
{
  int i;

  for (i = 0; i < n_keys; i++)
    keys[i] = 1 + (i % max);

  return;
}

/**
 *  Function: potential_key_generator
 *  Description: This function generates keys following an approximately
 *               potential distribution. The smaller values are much more
 *               likely than the bigger ones. Value 1 has a 50%
 *               probability, value 2 a 17%, value 3 the 9%, etc.
 *  Parameters:
 *    - keys: An array to store the generated keys.
 *    - n_keys: The number of keys to generate.
 *    - max: The maximum value for the keys.
 *  Returns: void
 */
void potential_key_generator(int *keys, int n_keys, int max)
{
  int i;

  for (i = 0; i < n_keys; i++)
  {
    keys[i] = .5 + max / (1 + max * ((double)rand() / (RAND_MAX)));
  }

  return;
}

/**
 *  Function: init_dictionary
 *  Description: Initializes a dictionary with the specified size and order.
 *  Parameters:
 *    - size: The size of the dictionary.
 *    - order: The order of the dictionary (SORTED or NOT_SORTED).
 *  Returns:
 *    - PDICT: A pointer to the initialized dictionary.
 *    - NULL: If the initialization fails.
 */
PDICT init_dictionary(int size, char order)
{

  PDICT dictionary;

  if (size <= 0 || (order != SORTED && order != NOT_SORTED))
  {
    return NULL;
  }

  dictionary = (PDICT)malloc(sizeof(DICT));

  if (dictionary == NULL)
  {
    return NULL;
  }

  dictionary->size = size;
  dictionary->n_data = 0;
  dictionary->order = order;
  dictionary->table = (int *)malloc(sizeof(int) * size);

  if (dictionary->table == NULL)
  {
    return NULL;
  }

  return dictionary;
}

/**
 *  Function: free_dictionary
 *  Description: Frees the memory allocated for the dictionary.
 *  Parameters:
 *    - pdict: A pointer to the dictionary to be freed.
 *  Returns: void
 */
void free_dictionary(PDICT pdict)
{
  if (!pdict || !pdict->table)
  {
    return;
  }
  free(pdict->table);
  free(pdict);
}

/**
 *  Function: insert_dictionary
 *  Description: Inserts a key into the dictionary.
 *  Parameters:
 *    - pdict: A pointer to the dictionary.
 *    - key: The key to be inserted.
 *  Returns:
 *    - int: The number of key comparisons made during the insertion.
 *    - ERR: If the insertion fails.
 */
int insert_dictionary(PDICT pdict, int key)
{
  int i, ob = 0;
  if (!pdict || !pdict->table)
  {
    return ERR;
  }
  if (pdict->n_data >= pdict->size)
  {
    pdict->table = realloc(pdict->table, AUMENT * sizeof(pdict->table));
    if (!pdict->table)
    {
      return ERR;
    }
    pdict->size = AUMENT * pdict->size;
  }
  if (pdict->order == NOT_SORTED)
  {
    pdict->table[pdict->n_data] = key;
  }
  else if (pdict->order == SORTED)
  {
    pdict->table[pdict->n_data] = key;
    for (i = pdict->n_data - 1; i >= 0 && pdict->table[i] > key; i--)
    {
      ob++;
      pdict->table[i + 1] = pdict->table[i];
    }
    pdict->table[i + 1] = key;
  }
  else
  {
    return ERR;
  }
  pdict->n_data++;
  return ob;
}

/**
 *  Function: massive_insertion_dictionary
 *  Description: Inserts multiple keys into the dictionary.
 *  Parameters:
 *    - pdict: A pointer to the dictionary.
 *    - keys: An array of keys to be inserted.
 *    - n_keys: The number of keys to be inserted.
 *  Returns:
 *    - int: The total number of key comparisons made during the insertion.
 *    - ERR: If the insertion fails.
 */
int massive_insertion_dictionary(PDICT pdict, int *keys, int n_keys)
{
  int i, ob = 0, status;
  if (!pdict || !pdict->table || !keys || n_keys < 1)
  {
    return ERR;
  }
  for (i = 0; i < n_keys; i++)
  {
    status = insert_dictionary(pdict, keys[i]);
    if (status == ERR)
    {
      return ERR;
    }
    ob += status;
  }
  return ob;
}

/**
 *  Function: search_dictionary
 *  Description: Searches for a key in the dictionary using the specified search method.
 *  Parameters:
 *    - pdict: A pointer to the dictionary.
 *    - key: The key to search for.
 *    - ppos: A pointer to store the position of the key in the dictionary.
 *    - method: A function pointer to the search method to be used.
 *  Returns:
 *    - int: The number of key comparisons made during the search.
 *    - ERR: If the search fails.
 */
int search_dictionary(PDICT pdict, int key, int *ppos, pfunc_search method)
{
  if (!pdict || !pdict->table || !ppos || !method)
  {
    return ERR;
  }
  return method(pdict->table, 0, pdict->n_data - 1, key, ppos);
}

/**
 *  Function: bin_search
 *  Description: Performs a binary search for a key in a sorted table.
 *  Parameters:
 *    - table: The sorted table to search in.
 *    - F: The first index of the table.
 *    - L: The last index of the table.
 *    - key: The key to search for.
 *    - ppos: A pointer to store the position of the key in the table.
 *  Returns:
 *    - int: The number of key comparisons made during the search.
 *    - ERR: If the search fails.
 */
int bin_search(int *table, int F, int L, int key, int *ppos)
{
  int ob = 0, m;

  if (!table || F < 0 || L < F || !ppos)
  {
    return ERR;
  }

  while (F <= L)
  {
    m = (F + L) / 2;
    ob++;

    if (table[m] == key)
    {
      *ppos = m + 1;
      return ob;
    }
    else if (key < table[m])
    {
      L = m - 1;
    }
    else
    {
      F = m + 1;
    }
  }
  *ppos = NOT_FOUND;
  return ob;
}

/**
 *  Function: lin_search
 *  Description: Performs a linear search for a key in a table.
 *  Parameters:
 *    - table: The table to search in.
 *    - F: The first index of the table.
 *    - L: The last index of the table.
 *    - key: The key to search for.
 *    - ppos: A pointer to store the position of the key in the table.
 *  Returns:
 *    - int: The number of key comparisons made during the search.
 *    - ERR: If the search fails.
 */
int lin_search(int *table, int F, int L, int key, int *ppos)
{
  int i = F;
  if (!table || L < F || F < 0 || !ppos)
  {
    return ERR;
  }
  while (i <= L && table[i] != key)
  {
    i++;
  }
  if (i > L)
  {
    *ppos = NOT_FOUND;
  }
  else if (table[i] == key)
  {
    *ppos = i;
  }
  return i - F + 1;
}

/**
 *  Function: lin_auto_search
 *  Description: Performs a linear search for a key in a table and automatically moves the found key to the previous position.
 *  Parameters:
 *    - table: The table to search in.
 *    - F: The first index of the table.
 *    - L: The last index of the table.
 *    - key: The key to search for.
 *    - ppos: A pointer to store the position of the key in the table.
 *  Returns:
 *    - int: The number of key comparisons made during the search.
 *    - ERR: If the search fails.
 */
int lin_auto_search(int *table, int F, int L, int key, int *ppos)
{
  int i = F, aux;
  if (!table || F > L || F < 0 || !ppos)
  {
    return ERR;
  }
  while (i <= L && table[i] != key)
  {
    i++;
  }
  if (i > L)
  {
    *ppos = NOT_FOUND;
  }
  else if (table[i] == key)
  {
    if (i - 1 >= F)
    {
      aux = table[i - 1];
      table[i - 1] = table[i];
      table[i] = aux;
      *ppos = i;
    }
    else
    {
      *ppos = i;
    }
  }
  return i - F + 1;
}
