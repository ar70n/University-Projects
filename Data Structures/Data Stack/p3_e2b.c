#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "graph.h"
#include "vertex.h"
#include "delivery.h"
#include "queue.h"
#include "algorithms.h"

#define MAX_STRING_LENGTH 64

/**
* @brief Builds a delivery from the information read on the file.
*
* @param pf File descriptor. The file should contains the following
information:
* Firt line: delivery_name product_name
* Second line: number of cities/vertices
* Following lines: vertices description
*
* @return A pointer to the fullfilled delivery. If there have been
errors returns NULL.
*/
Delivery* build_delivery(FILE * pf)
{
	Delivery *delivery;
	char del_name[MAX_STRING_LENGTH], prod_name[MAX_STRING_LENGTH], tag[TAG_LENGTH];
	int num_prod, i;
	long id;

	Vertex* vertex;


	if(pf==NULL)
	{
		return NULL;
	}


	if(fscanf(pf,"%s %s\n", del_name, prod_name)!=2)
	{
		return NULL;
	}
	delivery = delivery_init(del_name, prod_name); 	
	if(delivery==NULL)
	{
		return NULL;
	}


	if(fscanf(pf, "%d\n", &num_prod)!=1)
	{
		delivery_free(delivery);
		return NULL;
	}

/*	fprintf(stdout,"\n[DEBUG]: num_prod = %d\n",num_prod);*/
	
	for(i=0;i<num_prod;i++)
	{

		
		if(fscanf(pf, "id:%ld tag:%s \n", &id, tag)!=2)
		{
			delivery_free_products(delivery,vertex_free);
			delivery_free(delivery);			
			return NULL;
		}

/*		fprintf(stdout, "\n[DEBUG]: tag = %s\n", tag);*/

		vertex = vertex_init();
		


		if (vertex==NULL)
		{
			delivery_free_products(delivery,vertex_free);
			delivery_free(delivery);
			return NULL;
		}


		if(vertex_setId(vertex, id)==ERROR)
		{
			delivery_free_products(delivery,vertex_free);
			delivery_free(delivery);
			return NULL;
		}
		
		if(vertex_setTag(vertex, tag)==ERROR)
		{
			delivery_free_products(delivery,vertex_free);
			delivery_free(delivery);
			return NULL;
		}
	

		if(delivery_add(stdout,delivery,vertex,vertex_print)==ERROR)
		{
			delivery_free_products(delivery,vertex_free);
			delivery_free(delivery);
			return NULL;
		}
	}

	return delivery;

}


int main(int argc, char *argv[])
{
  /*Hay que cambiar los printfs y eso*/
    
    /*Inicializamos variables*/
    FILE *f1;
    long *orig,*dest;
    Graph* graph;
    Vertex  *vertice_orig, *vertice_dest;



    /*Leemos los argumentos*/

    printf("%d\n", argc);
    if (argc!=4)
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

    if (graph_breathSearch(graph, vertice_orig, vertice_dest)==ERROR)
    {
	graph_free(graph);
    	return 1;
    }
    
    graph_free(graph);
    return 0;
}
