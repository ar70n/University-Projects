#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "graph.h"
#include "vertex.h"
#include "list.h"
#include "queue.h"
#include "file_utils.h"


int main(int argc, char *argv[])
{


    /*Inicializamos variables*/
    FILE *pf;
    int i,size;
    long order;
    List* pl,*pl_aux1;
    float* info;
    float aux;

    /*Leemos los argumentos*/
    if (argc<3)
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
    order =atol(argv[2]);
    if(order !=1 && order !=-1){
        fprintf(stderr, "%ld is not a correct order number\n", order);
        fclose(pf);
        return 1;
    }

    
    pl = list_new();
    fscanf(pf,"%d\n",&size);

    for(i=1;i<=size;i++)
    {
	    fscanf(pf,"%f\n",&aux);
        if(i%2==1){
            if(list_pushBack(pl,float_init(aux))==ERROR){
                list_free(pl);
                fclose(pf);
            	return 1;
	    }
        }
        else{
            if(list_pushFront(pl,float_init(aux))==ERROR){
                list_free(pl);
                fclose(pf);
            	return 1;
	    }
        }
    }
    
   if (list_print(stdout, pl,float_print)<0)
   {
/*	fprintf(stderr,"\n[DEBUG]: Aqui da error 0.\n"); */
	list_free(pl);
	fclose(pf);
	return 1;
	 		
   }


    pl_aux1 = list_new();

    fprintf(stdout,"\nFinished inserting. Now we extract from the beginning and insert in order: \n");
    for(i=1;i<=(size)/2;i++){
        info =(float*)list_popFront(pl);
        float_print(stdout,info);
        fprintf(stdout," ");
        if(list_pushInOrder(pl_aux1, info, float_cmp, order)==ERROR)
	{
                /*fprintf(stderr,"\n[DEBUG]: Aqui da error 1.\n");*/
		list_free(pl);
                fclose(pf);
		list_free(pl_aux1);
 		return 1;
	}
    }

    fprintf(stdout,"\nNow we extract from the end and insert in order:\n");

    for(;i<=(size);i++){
        info =(float*)list_popBack(pl);
        float_print(stdout,info);
        fprintf(stdout," ");
        if(list_pushInOrder(pl_aux1, info, float_cmp, order)==ERROR)
	{
             /*   fprintf(stderr,"\n[DEBUG]: Aqui da error 2.\n"); */
                list_free(pl);
                fclose(pf);
		list_free(pl_aux1);
 		return 1;
	}

    }

    fprintf(stdout,"\n");
    
   if (list_print(stdout, pl_aux1,float_print)<0)
   {
	/*fprintf(stderr,"\n[DEBUG]: Aqui da error 3.\n"); */
	list_free(pl);
	fclose(pf);
	list_free(pl_aux1);

	return 1;
	 		
   }

    fprintf(stdout,"\n");
    fclose(pf);
return 0;
}
