#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "vertex.h"

int main(){
    Vertex *vertex_1=NULL;
    Vertex *vertex_2=NULL;
    Vertex *vertex_3=NULL;
    const char *retorno;

    vertex_1= vertex_init();
    if(!vertex_1){
        return ERROR;
    }
    vertex_setId(vertex_1, 10);
    vertex_setTag(vertex_1, "one");
    vertex_setState(vertex_1, WHITE);

    vertex_2= vertex_init();
    if(!vertex_2){
        return ERROR;
    }

    vertex_setId(vertex_2, 20);
    vertex_setTag(vertex_2, "TWO");
    vertex_setState(vertex_2, BLACK);

    
    
    vertex_print(stdout, vertex_1);
    vertex_print(stdout, vertex_2);
    
    fprintf(stdout, "\n");
    fprintf(stdout, "Equals? ");

    if(vertex_cmp(vertex_1, vertex_2)==0){
        fprintf(stdout, "Yes\n");
    }
    else{
        fprintf(stdout, "No\n");
    }

    retorno=vertex_getTag(vertex_2);
    fprintf(stdout, "Vertex 2 tag: %s \n", retorno);

    

    vertex_3=vertex_copy(vertex_1);
    if(!vertex_3){
        return ERROR;
    }

    fprintf(stdout, "Vertex 3 id: %ld \n", vertex_getId(vertex_3));

    vertex_print(stdout, vertex_1);
    vertex_print(stdout, vertex_3);
    
    fprintf(stdout, "\n");
    fprintf(stdout, "Equals? ");

    if(vertex_cmp(vertex_1, vertex_3)==0){
        fprintf(stdout, "Yes\n");
    }
    else{
        fprintf(stdout, "No\n");
    }

    vertex_free(vertex_1);
    vertex_free(vertex_2);
    vertex_free(vertex_3);

}
