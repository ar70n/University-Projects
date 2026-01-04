
/**
 * @file  algorithms.c
 * @author Antonio Moroño y Javier Asensio
 * @date 7 March 2023
 * @version 1.0
 * @brief Implements Algorithms related to graphs
 *
 * @details 
 * 
 * @see
 */


#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "algorithms.h"
#include "graph.h"
#include "vertex.h"
#include "queue.h"
#include "stack.h"

Status depth_first_search(Graph *graph, long from_id, long to_id)
{
	int i;
	Stack* stack;
	Vertex* vf;
	Vertex* vt;
	Vertex* vertice_aux=NULL, *v0, **all_vertex=NULL;
	Status st=OK;
	long *connectionsFromId;
	int flag=0;

	if (graph==NULL||from_id<0 ||to_id<0)
	{
		return ERROR;
	}

	vf=graph_get_vertex_from_id(graph,from_id);
	vt=graph_get_vertex_from_id(graph,to_id);

	all_vertex = graph_get_all_vertex(graph);

	for (i=0;i<graph_getNumberOfVertices(graph);i++)
	{
		
		if(vertex_setState(all_vertex[i],WHITE)==ERROR)
		{
			return ERROR;
		}
		
	}

	

	stack = stack_init();
	if (stack==NULL)
	{
		return ERROR;
	}

	vertice_aux = (Vertex*) vertex_copy(vf);
	if (vertice_aux==NULL)
	{
		st = ERROR;
	}

	if (stack_push(stack,vertice_aux)==ERROR)
	{
		st = ERROR;
	}
	/*free(vertice_aux);*/
	while (stack_isEmpty(stack)==FALSE && flag==0)
	{
		v0 = stack_pop(stack);
		if (v0==NULL)
		{
			st = ERROR;
		}
		

		vertex_print(stdout,v0);
		fprintf(stdout, "\n");
		
		if (vertex_cmp(v0,vt)== 0)
		{

			/*free(v0);*/

			flag = 1;
		}
		
		
		else
		{
			if (vertex_getState(v0)==WHITE)
			{
				if (vertex_setState(v0,BLACK)==ERROR)
				{
					st = ERROR;
				}
				for(i=0;i<graph_getNumberOfConnectionsFromId(graph, vertex_getId(v0));i++)
				{
					connectionsFromId = graph_getConnectionsFromId(graph, vertex_getId(v0));


					if (vertex_getState(graph_get_vertex_from_id(graph,connectionsFromId[i]))==WHITE)
					{

						vertice_aux = (Vertex*) vertex_copy(graph_get_vertex_from_id(graph,connectionsFromId[i]));
						if (vertice_aux==NULL)
						{
							st = ERROR;
						}
						if (stack_push(stack,vertice_aux)==ERROR)
						{
							st = ERROR;
						}
						/*free(vertice_aux);*/

					}
					free(connectionsFromId);
				}
			
			}
		}
		free(v0);

	}

	while (stack_isEmpty(stack)==FALSE)
	{
		vertice_aux = stack_pop(stack);
		free(vertice_aux);
	}

	stack_free(stack);

	return st;

}

Status mergeStacks (Stack *sin1, Stack *sin2, Stack *sout, P_stack_ele_compare function)
{
	float *arg1, *arg2, *value;
	Stack* ps=NULL;

	if (sin1==NULL||sin2==NULL||sout==NULL)
	{
		return ERROR;
	}
	while(stack_isEmpty(sin1)==FALSE && stack_isEmpty(sin2)==FALSE)
	{
		arg1 = (float*) stack_top(sin1);
		if(arg1==NULL)
		{
			return ERROR;
		}

		arg2 = (float*) stack_top(sin2);
		if(arg2==NULL)
		{
			return ERROR;
		}
		
		if (function(arg1,arg2)>=0)
		{
			value = (float*) stack_pop(sin1);
			if(value==NULL)
			{
				return ERROR;
			}
		
		}
		else if(function(arg1,arg2)==-1)
		{
			value = (float*) stack_pop(sin2);
			if(value==NULL)
			{
				return ERROR;
			}
		}

		stack_push(sout,value);
	}
	if (stack_isEmpty(sin1)==TRUE)
	{
		ps = sin2;
	}
	else
	{
		ps = sin1;
	}
	while (stack_isEmpty(ps)==FALSE)
	{
		value = (float*) stack_pop(ps);
		if(stack_push(sout,value)==ERROR)
		{
			return ERROR;
		}
	}

	return OK;

}



Status graph_breathSearch(Graph *graph,  long from_id, long to_id)
{
	int i;
	Queue *queue;
	Vertex* vertice_aux=NULL, *v0, **all_vertex=NULL;
	Vertex* vf;
	Vertex* vt;
	Status st=OK;
	long *connectionsFromId;
	int flag=0;

	if (graph==NULL||from_id<0 ||to_id<0)
	{
		return ERROR;
	}

	vf=graph_get_vertex_from_id(graph,from_id);
	vt=graph_get_vertex_from_id(graph,to_id);

	all_vertex = graph_get_all_vertex(graph);

	for (i=0;i<graph_getNumberOfVertices(graph);i++)
	{
		
		if(vertex_setState(all_vertex[i],WHITE)==ERROR)
		{
			return ERROR;
		}
		
	}

	

	queue = queue_new();
	if (queue==NULL)
	{
		return ERROR;
	}

	vertice_aux = (Vertex*) vertex_copy(vf);
	if (vertice_aux==NULL)
	{
		st = ERROR;
	}

	if (queue_push(queue,vertice_aux)==ERROR)
	{
		st = ERROR;
	}
	/*free(vertice_aux);*/
	while (queue_isEmpty(queue)==FALSE && flag==0)
	{
		v0 = queue_pop(queue);
		if (v0==NULL)
		{
			st = ERROR;
		}
		

		vertex_print(stdout,v0);
		fprintf(stdout, "\n");
		
		if (vertex_cmp(v0,vt)== 0)
		{

			/*free(v0);*/

			flag = 1;
		}
		
		
		else
		{
			if (vertex_getState(v0)==WHITE)
			{
				if (vertex_setState(v0,BLACK)==ERROR)
				{
					st = ERROR;
				}
				for(i=0;i<graph_getNumberOfConnectionsFromId(graph, vertex_getId(v0));i++)
				{
					connectionsFromId = graph_getConnectionsFromId(graph, vertex_getId(v0));


					if (vertex_getState(graph_get_vertex_from_id(graph,connectionsFromId[i]))==WHITE)
					{

						vertice_aux = (Vertex*) vertex_copy(graph_get_vertex_from_id(graph,connectionsFromId[i]));
						if (vertice_aux==NULL)
						{
							st = ERROR;
						}
						if (queue_push(queue,vertice_aux)==ERROR)
						{
							st = ERROR;
						}
						/*free(vertice_aux);*/

					}
					free(connectionsFromId);
				}
			
			}
		}
		free(v0);

	}

	while (queue_isEmpty(queue)==FALSE)
	{
		vertice_aux = queue_pop(queue);
		free(vertice_aux);
	}

	queue_free(queue);

	return st;

}
