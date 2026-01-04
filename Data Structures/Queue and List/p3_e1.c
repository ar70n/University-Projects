#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "graph.h"
#include "vertex.h"
#include "delivery.h"
#include "queue.h"

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


    /*Inicializamos variables*/
    FILE *pf;
    Delivery* delivery;


    /*Leemos los argumentos*/
    if (argc<2)
    {
        fprintf(stderr, "Too few arguments\n");
        return 1;
    }

    pf = fopen(argv[1], "r");
    if (pf==NULL)
    {
        fprintf(stderr, "ERROR while opening %s\n", argv[1]);
		return 1;
    }


	delivery = build_delivery(pf);
	if (delivery == NULL)
	{
		fprintf(stderr, "ERROR while building delivery\n");
		fclose(pf);
		return 1;
	}


	if (delivery_run_plan(stdout,delivery,vertex_print, vertex_free)==ERROR)
	{
		fprintf(stderr, "ERROR while running plan\n");
		delivery_free_products(delivery,vertex_free);
		delivery_free(delivery);
		fclose(pf);
		return 1;
	}


	delivery_free_products(delivery,vertex_free);
	delivery_free(delivery);
	fclose(pf);
	return 0;

}
