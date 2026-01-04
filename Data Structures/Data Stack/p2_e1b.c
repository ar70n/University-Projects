#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include "file_utils.h"
#include "algorithms.h"
#include "graph.h"
#include "vertex.h"

/**
* @brief: Merges two stacks
*
* @param sin1, first input stack
* @param sin2, second input stack
* @param sout, result stack
* @return The function returns OK or ERROR
**/

/*
 * @brief: Auxiliary function to free stacks
 *
 *
 */
void clean_stack(Stack *stack);



int main(int argc, char *argv[])
{
	FILE *f1, *f2;
	Stack *stack_out, *stack1, *stack2;
	int num_stack1, num_stack2,i;
	Vertex *aux;
	char tag[TAG_LENGTH];
	long id;

	if (argc < 3) 
	{
    	fprintf(stderr, "Use: %s <cities text files>\n", argv[0]);
		return 1;
	}

	f1 = fopen(argv[1],"r");
	if (f1==NULL)
	{
		fprintf(stderr, "ERROR while opening %s\n", argv[1]);
		return 1;
	}

	f2 = fopen(argv[2],"r");
	if (f2==NULL)
	{
		fprintf(stderr, "ERROR while opening %s\n", argv[2]);
		fclose(f1);
		return 1;
	}

	stack1 = stack_init();
	if(stack1==NULL)
	{
		fclose(f1);
		fclose(f2);
		return 1;
	}
	stack2 = stack_init();
	stack_out = stack_init();

	fscanf(f1,"%d\n",&num_stack1);

	for (i=0;i<num_stack1;i++)
	{
		
		
		fscanf(f1,"id:%ld tag:%s \n", &id, tag);
		aux=vertex_init();
		if(vertex_setId(aux,id)==ERROR)
        {
        return 1;
        }

        if(vertex_setTag(aux,tag)==ERROR)
        {
        return 1;
        }
		vertex_print(stdout,aux);
	
		if (stack_push(stack1,aux)==ERROR)
		{
			clean_stack(stack1);
			clean_stack(stack2);
			clean_stack(stack_out);
			fclose(f1);
			fclose(f2);
			return 1;
	
		}
	}



	fscanf(f2,"%d\n",&num_stack2);

	for (i=0;i<num_stack2;i++)
	{
		fscanf(f2,"id:%ld tag:%s \n", &id, tag);
		aux=vertex_init();

        if(vertex_setId(aux,id)==ERROR)
        {
        return 1;
        }

		
        if(vertex_setTag(aux,tag)==ERROR)
        {
        return 1;
        }
	
		if (stack_push(stack2,aux)==ERROR)
		{
			clean_stack(stack1);
			clean_stack(stack2);
			clean_stack(stack_out);
			fclose(f1);
			fclose(f2);
			return 1;
	
		}
		
	}
	
	fprintf(stdout, "Ranking 0:\n");
	if(stack_print(stdout, stack1,vertex_print)<0){
		clean_stack(stack1);
		clean_stack(stack2);	
		clean_stack(stack_out);
		fclose(f1);
		fclose(f2);
		return 1;
	}

	fprintf(stdout, "Ranking 1:\n");
	if(stack_print(stdout, stack2, vertex_print)<0){
		clean_stack(stack1);
		clean_stack(stack2);
		clean_stack(stack_out);
		fclose(f1);
		fclose(f2);
		return 1;
	}

	

	if(mergeStacks(stack1, stack2, stack_out, vertex_cmp)==ERROR){
		clean_stack(stack1);
		clean_stack(stack2);
		clean_stack(stack_out);
		fclose(f1);
		fclose(f2);
		return 1;
	}



	fprintf(stdout, "Joint Ranking:\n");
	if(stack_print(stdout, stack_out, vertex_print)<0){
		clean_stack(stack1);
		clean_stack(stack2);
		clean_stack(stack_out);
		fclose(f1);
		fclose(f2);
		return 1;
	}

	clean_stack(stack1);
	clean_stack(stack2);
	clean_stack(stack_out);
	fclose(f1);
	fclose(f2);
	return 0;
	





}


void clean_stack(Stack *stack){
	Vertex *aux = NULL;
	if (stack==NULL)
	{
		return;
	}
	while (stack_isEmpty(stack)==FALSE)
	{
		aux = stack_pop(stack);
		vertex_free(aux);
	}
	stack_free(stack);
}
