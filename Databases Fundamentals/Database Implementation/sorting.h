/**
 * @file sorting.h
 * @brief Header file for sorting functions
 *
 * This file contains the declarations of various sorting functions.
 * These functions are used to sort arrays of integers in different ways.
 * The functions included in this file are:
 * - partition: Partitions an array based on a pivot element.
 * - merge: Merges two sorted subarrays into a single sorted array.
 * - SelectSort: Sorts an array using the selection sort algorithm.
 * - SelectSortInv: Sorts an array in descending order using the selection sort algorithm.
 * - min: Finds the minimum element in an array.
 * - mergesort: Sorts an array using the merge sort algorithm.
 * - quicksort: Sorts an array using the quicksort algorithm.
 * - median_avg: Finds the median of an array using the average of medians algorithm.
 * - median: Finds the median of an array using the median of medians algorithm.
 * - swap: Swaps two elements in an array.
 * - median_stat: Finds the median of an array using statistical analysis.
 */

#ifndef SORTING_H
#define SORTING_H

/* constants */

#ifndef ERR
  #define ERR -1
  #define OK (!(ERR))
#endif

/* type definitions */
typedef int (* pfunc_sort)(int*, int, int);

/* Functions */

/**
 * @brief Partitions an array based on a pivot element.
 *
 * This function takes an array, a lower index, an upper index, and a pointer to store the position of the pivot element.
 * It rearranges the elements in the array such that all elements smaller than the pivot are placed before it,
 * and all elements greater than the pivot are placed after it.
 *
 * @param tabla The array to be partitioned.
 * @param ip The lower index of the array.
 * @param iu The upper index of the array.
 * @param pos Pointer to store the position of the pivot element.
 * @return The position of the pivot element after partitioning.
 */
int partition(int *tabla, int ip, int iu, int *pos);

/**
 * @brief Merges two sorted subarrays into a single sorted array.
 *
 * This function takes an array, a lower index, an upper index, and the index of the middle element.
 * It merges the two subarrays [ip, imedio] and [imedio+1, iu] into a single sorted array.
 *
 * @param tabla The array to be merged.
 * @param ip The lower index of the first subarray.
 * @param iu The upper index of the second subarray.
 * @param imedio The index of the middle element.
 * @return 0 if the merge is successful, -1 otherwise.
 */
int merge(int* tabla, int ip, int iu, int imedio);

/**
 * @brief Sorts an array using the selection sort algorithm.
 *
 * This function takes an array, a lower index, and an upper index.
 * It sorts the elements in the array between the given indices using the selection sort algorithm.
 *
 * @param array The array to be sorted.
 * @param ip The lower index of the array.
 * @param iu The upper index of the array.
 * @return 0 if the sort is successful, -1 otherwise.
 */
int SelectSort(int* array, int ip, int iu);

/**
 * @brief Sorts an array in descending order using the selection sort algorithm.
 *
 * This function takes an array, a lower index, and an upper index.
 * It sorts the elements in the array between the given indices in descending order using the selection sort algorithm.
 *
 * @param array The array to be sorted.
 * @param ip The lower index of the array.
 * @param iu The upper index of the array.
 * @return 0 if the sort is successful, -1 otherwise.
 */
int SelectSortInv(int* array, int ip, int iu);

/**
 * @brief Finds the minimum element in an array.
 *
 * This function takes an array, a lower index, and an upper index.
 * It finds the minimum element in the array between the given indices.
 *
 * @param array The array to find the minimum element in.
 * @param ip The lower index of the array.
 * @param iu The upper index of the array.
 * @return The minimum element in the array.
 */
int min(int* array, int ip, int iu);

/**
 * @brief Sorts an array using the merge sort algorithm.
 *
 * This function takes an array, a lower index, and an upper index.
 * It sorts the elements in the array between the given indices using the merge sort algorithm.
 *
 * @param tabla The array to be sorted.
 * @param ip The lower index of the array.
 * @param iu The upper index of the array.
 * @return 0 if the sort is successful, -1 otherwise.
 */
int mergesort(int* tabla, int ip, int iu);

/**
 * @brief Sorts an array using the quicksort algorithm.
 *
 * This function takes an array, a lower index, and an upper index.
 * It sorts the elements in the array between the given indices using the quicksort algorithm.
 *
 * @param tabla The array to be sorted.
 * @param ip The lower index of the array.
 * @param iu The upper index of the array.
 * @return 0 if the sort is successful, -1 otherwise.
 */
int quicksort(int* tabla, int ip, int iu);

/**
 * @brief Finds the median of an array using the average of medians algorithm.
 *
 * This function takes an array, a lower index, an upper index, and a pointer to store the position of the median element.
 * It finds the median element in the array between the given indices using the average of medians algorithm.
 *
 * @param tabla The array to find the median element in.
 * @param ip The lower index of the array.
 * @param iu The upper index of the array.
 * @param pos Pointer to store the position of the median element.
 * @return The median element in the array.
 */
int median_avg(int *tabla, int ip, int iu, int *pos);

/**
 * @brief Finds the median of an array using the median of medians algorithm.
 *
 * This function takes an array, a lower index, an upper index, and a pointer to store the position of the median element.
 * It finds the median element in the array between the given indices using the median of medians algorithm.
 *
 * @param tabla The array to find the median element in.
 * @param ip The lower index of the array.
 * @param iu The upper index of the array.
 * @param pos Pointer to store the position of the median element.
 * @return The median element in the array.
 */
int median(int *tabla, int ip, int iu, int *pos);

/**
 * @brief Swaps two elements in an array.
 *
 * This function takes an array and two indices.
 * It swaps the elements at the given indices in the array.
 *
 * @param tabla The array containing the elements to be swapped.
 * @param i The index of the first element.
 * @param j The index of the second element.
 * @return 0 if the swap is successful, -1 otherwise.
 */
int swap(int *tabla, int i, int j);

/**
 * @brief Finds the median of an array using statistical analysis.
 *
 * This function takes an array, a lower index, an upper index, and a pointer to store the position of the median element.
 * It finds the median element in the array between the given indices using statistical analysis.
 *
 * @param tabla The array to find the median element in.
 * @param ip The lower index of the array.
 * @param iu The upper index of the array.
 * @param pos Pointer to store the position of the median element.
 * @return The median element in the array.
 */
int median_stat(int *tabla, int ip, int iu, int *pos);

#endif
