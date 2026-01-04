
/**
 * @file  algorithms.h
 * @author Antonio Moroño y Javier Asensio
 * @date 7 March 2023
 * @version 1.0
 * @brief Library to manage Algorithms related to graphs
 *
 * @details 
 * 
 * @see
 */




#ifndef ALGORITHMS_H_
#define ALGORITHMS_H_
#define TAG_LENGTH 64


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "graph.h"
#include "stack.h"

/**
* @brief: Makes a search from the origin vertex to the destination vertex
of a graph using the depth-first search algorithm
* using an ADT Stack
*
* The function prints each visited vertex while traversing the graph
*
* @param g, Pointer to graph
* @param from_id, id of the origin Vertex
* @param to_id, id of the destination Vertex
* @return The function returns OK or ERROR
**/
Status depth_first_search(Graph *graph, long from_id, long to_id);

Status mergeStacks (Stack *sin1, Stack *sin2, Stack *sout, P_stack_ele_compare function);

Status graph_breathSearch (Graph *graph,  long from_id, long to_id);

#endif
