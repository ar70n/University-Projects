/**
 * Descriptions: Declarations of the search functions and data
 *
 * File: search.h
 * Author: Carlos Aguirre and Javier Sanz-Cruzado
 * Version: 1.0
 * Date: 14-11-2019
 *
 * This header file contains the declarations of various search functions and data structures for a dictionary.
 * The dictionary is implemented using a table and supports operations like initialization, insertion, and searching.
 * The search functions include binary search, linear search, and linear search with auto-increment.
 * The key generation functions generate keys within a specified range.
 *
 * The dictionary structure (DICT) contains information about the size of the table, the number of entries,
 * the order of the table (sorted or unsorted), and a pointer to the data table.
 *
 * The header file also defines constants for error codes, search types, and key generation types.
 */

#ifndef SEARCH_H_
#define SEARCH_H_

/* constantes */

#ifndef ERR
#define ERR -1
#define OK (!ERR)
#endif


#define NOT_FOUND -2

#define SORTED 1
#define NOT_SORTED 0
#define AUMENT 2

/* type definitions */
typedef struct dictionary {
  int size; /* table size */
  int n_data; /* number of entries in the table */
  char order;  /* sorted or unsorted table */
  int *table;  /* data table */
} DICT, *PDICT;

typedef int (* pfunc_search)(int*, int, int, int, int*);
typedef void (* pfunc_key_generator)(int*, int, int);

/**
 * Initializes a dictionary with the specified size and order.
 *
 * @param size The size of the dictionary table.
 * @param order The order of the dictionary table (sorted or unsorted).
 * @return A pointer to the initialized dictionary.
 */
PDICT init_dictionary (int size, char order);

/**
 * Frees the memory allocated for the dictionary.
 *
 * @param pdict A pointer to the dictionary.
 */
void free_dictionary(PDICT pdict);

/**
 * Inserts a key into the dictionary.
 *
 * @param pdict A pointer to the dictionary.
 * @param key The key to be inserted.
 * @return 1 if the insertion is successful, -1 otherwise.
 */
int insert_dictionary(PDICT pdict, int key);

/**
 * Inserts multiple keys into the dictionary.
 *
 * @param pdict A pointer to the dictionary.
 * @param keys An array of keys to be inserted.
 * @param n_keys The number of keys to be inserted.
 * @return The number of successful insertions.
 */
int massive_insertion_dictionary (PDICT pdict,int *keys, int n_keys);

/**
 * Searches for a key in the dictionary using the specified search method.
 *
 * @param pdict A pointer to the dictionary.
 * @param key The key to be searched.
 * @param ppos A pointer to store the position of the key in the dictionary.
 * @param method The search method to be used (bin_search, lin_search, or lin_auto_search).
 * @return 1 if the key is found, -2 if the key is not found.
 */
int search_dictionary(PDICT pdict, int key, int *ppos, pfunc_search method);

/**
 * Performs a binary search for a key in the table.
 *
 * @param table The table to be searched.
 * @param F The first index of the table.
 * @param L The last index of the table.
 * @param key The key to be searched.
 * @param ppos A pointer to store the position of the key in the table.
 * @return 1 if the key is found, -2 if the key is not found.
 */
int bin_search(int *table,int F,int L,int key, int *ppos);

/**
 * Performs a linear search for a key in the table.
 *
 * @param table The table to be searched.
 * @param F The first index of the table.
 * @param L The last index of the table.
 * @param key The key to be searched.
 * @param ppos A pointer to store the position of the key in the table.
 * @return 1 if the key is found, -2 if the key is not found.
 */
int lin_search(int *table,int F,int L,int key, int *ppos);

/**
 * Performs a linear search with auto-increment for a key in the table.
 *
 * @param table The table to be searched.
 * @param F The first index of the table.
 * @param L The last index of the table.
 * @param key The key to be searched.
 * @param ppos A pointer to store the position of the key in the table.
 * @return 1 if the key is found, -2 if the key is not found.
 */
int lin_auto_search(int *table,int F,int L,int key, int *ppos);

/**
 * Generates keys uniformly within a specified range.
 *
 * @param keys An array to store the generated keys.
 * @param n_keys The number of keys to be generated.
 * @param max The maximum value of the generated keys.
 */
void uniform_key_generator(int *keys, int n_keys, int max);

/**
 * Generates potential keys within a specified range.
 *
 * @param keys An array to store the generated keys.
 * @param n_keys The number of keys to be generated.
 * @param max The maximum value of the generated keys.
 */
void potential_key_generator(int *keys, int n_keys, int max);

#endif
