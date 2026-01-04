#include <stdio.h>
#include "graph.h"
#include "vertex.h"

int main(){

    Graph *g=NULL;
    int i;
    long num_connections;
    long *array_connections = NULL;

    g = graph_init();

    fprintf(stdout ,"Inserting Madrid... result...: %d\n", graph_newVertex(g,"id:111 tag:Madrid state:WHITE"));
    fprintf(stdout ,"Inserting Toledo... result...: %d\n", graph_newVertex(g,"id:222 tag:Toledo state:WHITE"));

    fprintf(stdout ,"Inserting edge: 222 --> 111 \n");
    graph_newEdge(g, 222, 111);


    fprintf(stdout ,"111 --> 222? ");
    if (graph_connectionExists(g,111,222)==TRUE)
    {
        fprintf(stdout,"YES\n");
    }
    else
    {
        fprintf(stdout,"NO\n");
    }

   fprintf(stdout ,"222 --> 111? ");
    if (graph_connectionExists(g,222,111)==TRUE)
    {
        fprintf(stdout,"YES\n");
    }
    else
    {
        fprintf(stdout,"NO\n");
    }
    
    fprintf(stdout, "Number of connections from 111: %d\n", graph_getNumberOfConnectionsFromId(g,111));
    
    num_connections = graph_getNumberOfConnectionsFromTag(g,"Toledo");

    if(num_connections==-1)
    {
      graph_free(g);
      return 1;
    }

    fprintf(stdout, "Number of connections from Toledo: %ld\n", num_connections);


    fprintf(stdout, "Connections from Toledo:");

    array_connections = graph_getConnectionsFromTag(g,"Toledo");

    if(array_connections==NULL)
    {
      graph_free(g);
      return 1;
    }

    for (i=0;i<num_connections;i++)
    {
        fprintf(stdout," %ld",array_connections[i]);
    }
    fprintf(stdout, "\n");
    

    graph_print(stdout,g);

    graph_free(g);
    free(array_connections);



}
