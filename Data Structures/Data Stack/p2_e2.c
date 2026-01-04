#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include "file_utils.h"
#include "algorithms.h"
#include "types.h"
#include "graph.h"
#include "vertex.h"

int main(int argc, char *argv[])
{
  
    
    /*Inicializamos variables*/
    FILE *f1;
    long *orig,*dest;
    Graph* graph;
    Vertex  *vertice_orig, *vertice_dest;



    /*Leemos los argumentos*/
    if (argc<4)
    {
        fprintf(stderr, "Too few arguments");
        return 1;
    }

    f1 = fopen(argv[1], "r");
    if (f1==NULL)
    {
        fprintf(stderr, "ERROR while opening %s\n", argv[1]);
		return 1;
    }

    orig = malloc(sizeof(long));
    dest = malloc(sizeof(long));
    *orig = atoi(argv[2]);
    *dest = atoi(argv[3]);

    
    

    /*Inicializamos grafo*/
    graph = graph_init();

    /*Leemos grafo desde archivo*/
    if(graph_readFromFile(f1,graph)==ERROR)
    {
	    fprintf(stderr, "ERROR while reading file");
        free(orig);
	    free(dest);
    	graph_free(graph);
    	fclose(f1);
	return 1;

    }


    fclose(f1);
    /*Printeamos grafo inicial*/
    fprintf(stdout, "Input graph:\n");
    graph_print(stdout,graph);

    fprintf(stdout, "From vertex id: %ld\n", (*orig));
    fprintf(stdout, "To vertex id: %ld\n", (*dest));

    fprintf(stdout, "Output:\n");
   
	vertice_orig = graph_get_vertex_from_id(graph, *orig);
	vertice_dest = graph_get_vertex_from_id(graph, *dest);

    free(orig);
    free(dest);

    if (depth_first_search(graph, vertice_orig, vertice_dest)==ERROR)
    {
	graph_free(graph);
    	return 1;
    }
    
    graph_free(graph);
    return 0;
}



