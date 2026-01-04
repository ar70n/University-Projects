/**
 * @file  graph.c
 * @author Javier Asensio, Antonio Moroño
 * @date 2 February 2021
 * @version 1.0
 * @brief Library to manage ADT Vertex
 *
 * @details 
 * 
 * @see
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vertex.h"
#include "graph.h"

#define MAX_VTX 4096


struct _Graph {
    Vertex *vertices[MAX_VTX];
    Bool connections[MAX_VTX][MAX_VTX];
    int num_vertices;
    int num_edges;
};



Vertex * graph_get_vertex_from_id(const Graph *g, long id){
    int i;

    for(i=0;i<(g->num_vertices);i++){
        if(vertex_getId(g->vertices[i])==id){
        return g->vertices[i];
        }
    }

    return NULL;
}


Graph * graph_init()
{
    Graph *grafo;
    int i,j;

    grafo = (Graph*) malloc(sizeof(Graph));
    if (grafo==NULL)
    {
        return NULL;
    }

    for (i=0;i<MAX_VTX;i++)
    {
        grafo->vertices[i] = NULL;

        for (j=0;j<MAX_VTX;j++)
        {
            grafo->connections[i][j] = FALSE;
        }
    }
    grafo->num_vertices = 0;
    grafo->num_edges = 0;

    return grafo;
}

void graph_free(Graph *g)
{
    int i;
  
    for (i=0;i<g->num_vertices;i++)
    {
        vertex_free(g->vertices[i]);
        
    }
    free(g);


}


Status graph_newVertex(Graph *g, char *desc)
{
    int i;
    Vertex *v;

    if (g==NULL||desc==NULL)
    {
        return ERROR;
    }
    
    v = vertex_initFromString(desc);
    if (v==NULL)
    {
        return ERROR;
    }

    for (i=0; i<(g->num_vertices);i++)
    {
        if (vertex_cmp(v,g->vertices[i])==0)
        {
            return OK;
        }
    }
    g->vertices[g->num_vertices] = v;
    (g->num_vertices)++;

    return OK;
}

Status graph_newEdge(Graph *g, long orig, long dest)
{
    
    
    if (g==NULL)
    {
        return ERROR;
    }

    if(graph_connectionExists(g,orig,dest)==TRUE)
    {   
        return ERROR;
    }

    if (graph_contains(g,orig)==TRUE && graph_contains(g,dest)==TRUE)
    {
        g->connections[orig][dest] = TRUE;
        g->num_edges++;
        return OK;
    }
    return ERROR;

}

Bool graph_contains(const Graph *g, long id)
{   
    int i;
    long id_aux;
    if (g==NULL)
    {
        return FALSE;
    }

    for (i=0;i<g->num_vertices;i++)
    {
        id_aux = vertex_getId(g->vertices[i]);
        if (id_aux==id)
        {
            return TRUE;
        }
    }
    return FALSE;
}

int graph_getNumberOfVertices(const Graph *g)
{
    if (g==NULL)
    {
        return -1;
    }    
    return g->num_vertices;
}

int graph_getNumberOfEdges(const Graph *g)
{
    if (g==NULL)
    {
        return -1;
    }
    return g->num_edges;
}

Bool graph_connectionExists(const Graph *g, long orig, long dest)
{
    if (g==NULL)
    {
        return FALSE;
    }
    if (g->connections[orig][dest]==TRUE)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

int graph_getNumberOfConnectionsFromId(const Graph *g, long id)
{   
    int i;
    int NumberOfConnectionsFromId=0;

    if (g==NULL)
    {
        return -1;
    }
    if (graph_contains(g, id)==FALSE)
    {
        return -1;
    }

    for (i=0 ;i<(MAX_VTX);i++)
    {
        if (g->connections[id][i] ==TRUE)
        {
            NumberOfConnectionsFromId++;
        }
    }
    return NumberOfConnectionsFromId;
}

long *graph_getConnectionsFromId(const Graph *g, long id)
{
    int i,j=0;
    long *ConnectionsFromId;
    if (g==NULL)
    {
        return NULL;
    }
    ConnectionsFromId=malloc(sizeof(long)*graph_getNumberOfConnectionsFromId(g,id));
   for (i=0;i<MAX_VTX;i++)
    {
        if (g->connections[id][i] ==TRUE)
        {
            ConnectionsFromId[j]= i;
            j++;
        }
    }
    return ConnectionsFromId;
}


int graph_getNumberOfConnectionsFromTag(const Graph *g, char *tag){
    int i;
    int flag=0;
    int idVertex=-1;


    if(g == NULL || tag == NULL){
        return -1;
    }

    for(i=0;i<MAX_VTX;i++){
        if(strcmp(vertex_getTag(g->vertices[i]),tag)==0){
            flag=1;
            break;
        }
    }
    if(flag==0){
        return -1;
    }

    idVertex=vertex_getId(g->vertices[i]);
    if(idVertex==-1){
        return -1;
    }

    return graph_getNumberOfConnectionsFromId(g, idVertex);




}

long *graph_getConnectionsFromTag(const Graph *g, char *tag)
{
    int i;
    int flag=0;
    int idVertex=-1;


    if(g == NULL || tag == NULL){
        return NULL;
    }

    for(i=0;i<MAX_VTX;i++){
        if(strcmp(vertex_getTag(g->vertices[i]),tag)==0){
            flag=1;
            break;
        }
    }
    if(flag==0){
        return NULL;
    }

    idVertex=vertex_getId(g->vertices[i]);
    if(idVertex==-1){
        return NULL;
    }

    return graph_getConnectionsFromId(g, idVertex);
}

int graph_print (FILE *pf, const Graph *g){
    int i;
    int j;
    long id;
    int num_connections;
    int flag=0;

    if (g==NULL)
    {
        return -1;
    }

    for(i=0; i<(g->num_vertices); i++){
        id = vertex_getId(g->vertices[i]);
        if (id!=-1)
        {
            vertex_print(pf, g->vertices[i]);
            fprintf(pf,": ");
            
            num_connections = graph_getNumberOfConnectionsFromId(g,id);
            if (num_connections==-1)
            {
                return -1;
            }


            for(j=0,flag=0;j<(MAX_VTX) && flag<num_connections;j++){
                if(g->connections[id][j]==TRUE){
                    vertex_print(pf, graph_get_vertex_from_id(g, j));
                    flag++;
                }
            }

        }
 
        
        fprintf(pf,"\n");
    }

    return 0;

}

Status graph_readFromFile (FILE *fin, Graph *g)
{
    int i, num_vertices;
    long id;
    long origin,destination;
    char tag[TAG_LENGTH];
    Vertex *v[MAX_VTX];
	
    if (fin==NULL || g==NULL)
    {
      return ERROR;
    }
    
    fscanf(fin,"%d \n",&num_vertices);

    for(i=0;i<num_vertices;i++){
        v[i]=vertex_init();
    }

    for (i=0;i<num_vertices;i++)
    {
        fscanf(fin,"id:%ld tag:%s \n", &id, tag);


        if(vertex_setId(v[i],id)==ERROR)
        {
        return ERROR;
        }

        if(vertex_setTag(v[i],tag)==ERROR)
        {
        return ERROR;
        }
        
            g->vertices[g->num_vertices] = v[i];
            (g->num_vertices)++;
    
    }

    while(fscanf(fin, "%ld %ld\n", &origin, &destination)==2){
        if(graph_newEdge(g, origin, destination)==ERROR){
            return ERROR;
        }
    }

    fclose(fin);
    return OK;




}





