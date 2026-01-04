#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include "file_utils.h"

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



Status mergeStacks (Stack *sin1, Stack *sin2, Stack *sout)
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
		
		if (*arg1 > *arg2)
		{
			value = (float*) stack_pop(sin1);
			if(value==NULL)
			{
				return ERROR;
			}
		
		}
		else
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

int main(int argc, char *argv[])
{
	FILE *f1, *f2;
	Stack *stack_out, *stack1, *stack2;
	int num_stack1, num_stack2,i;
	float aux;

	if (argc < 3) 
	{
    	fprintf(stderr, "Use: %s <grades text files>\n", argv[0]);
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

	fscanf(f1,"%d",&num_stack1);
	for (i=0;i<num_stack1;i++)
	{
		fscanf(f1,"%f",&aux);
	
		if (stack_push(stack1,float_init(aux))==ERROR)
		{
			clean_stack(stack1);
			clean_stack(stack2);
			clean_stack(stack_out);
			fclose(f1);
			fclose(f2);
			return 1;
	
		}
	}


	fscanf(f2,"%d",&num_stack2);
	for (i=0;i<num_stack2;i++)
	{
		fscanf(f2,"%f",&aux);
	
		if (stack_push(stack2,float_init(aux))==ERROR)
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
	if(stack_print(stdout, stack1,float_print)<0){
		clean_stack(stack1);
		clean_stack(stack2);
		clean_stack(stack_out);
		fclose(f1);
		fclose(f2);
		return 1;
	}

	fprintf(stdout, "Ranking 1:\n");
	if(stack_print(stdout, stack2, float_print)<0){
		clean_stack(stack1);
		clean_stack(stack2);
		clean_stack(stack_out);
		fclose(f1);
		fclose(f2);
		return 1;
	}

	

	if(mergeStacks(stack1, stack2, stack_out)==ERROR){
		clean_stack(stack1);
		clean_stack(stack2);
		clean_stack(stack_out);
		fclose(f1);
		fclose(f2);
		return 1;
	}



	fprintf(stdout, "Joint Ranking:\n");
	if(stack_print(stdout, stack_out, float_print)<0){
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


void clean_stack(Stack *stack)
{
	void *aux = NULL;
	if (stack==NULL)
	{
		return;
	}
	while (stack_isEmpty(stack)==FALSE)
	{
		aux = stack_pop(stack);
		free(aux);
	}
	stack_free(stack);
}
