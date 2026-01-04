#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main(int argc, char* argv[]){

    Graph *g=NULL;
    FILE *f=NULL;
    if (argc<2)
    {
      fprintf(stderr, "Wrong number of arguments \n");
      return 1;
    }


    g=graph_init();
    if (g==NULL)
    {
      fprintf(stderr, "\nERROR while calling the function\n");
      return 1;
    }

    f=fopen(argv[1], "r");
    if (f==NULL)
    {
      fprintf(stderr, "\nERROR while calling the function\n");
      graph_free(g);
      return 1;
    }



    if(graph_readFromFile(f, g)==ERROR){
        fprintf(stderr, "\nERROR while calling the function\n");
        graph_free(g);
        return 1;
    }


    graph_print(stdout, g);
    graph_free(g);

    return 0;

}
