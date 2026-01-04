#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "stack.h"

#define INIT_CAPACITY 2 /* init stack capacity */
#define FCT_CAPACITY 2 /* multiply the stack capacity */


struct _Stack {
 void **item; /*!<Static array of elements*/
 int top; /*!<index of the top element in the stack*/
 int capacity; /*!<xcapacity of the stack*/
};


/*
 * @brief: private functions
*/
Status stack_grow(Stack *s);

Bool stack_isfull(Stack *s);

Stack *stack_init (){
  Stack *newstack = malloc(sizeof(Stack));
  if (!newstack)
    return NULL;
  newstack->item = malloc(sizeof(void *) * INIT_CAPACITY); 
  if (!newstack->item) {
    free(newstack);
    return NULL;
  }
  newstack->capacity = INIT_CAPACITY;
  newstack->top = 0;
  return newstack;

}

void stack_free (Stack *s){
    void *aux = NULL;
	if (s==NULL)
	{
		return;
	}
	while (stack_isEmpty(s)==FALSE)
	{
		aux = stack_pop(s);
		free(aux);
	}
	free(s->item);
    free(s);
}

Status stack_grow(Stack *s){

  int new_size;
  void **aux;

  if (!s || !s->item)
    return ERROR;
  new_size = s->capacity * FCT_CAPACITY;
  aux = realloc(s->item, sizeof(void *) * new_size);

  if (!aux) {
    return ERROR;
  }
  /* update SList fields */
  s->capacity = new_size;
  s->item = aux;
  return OK;
}

Bool stack_isfull(Stack *s){
  if (!s)
    return TRUE;
  return s->capacity == s->top;
}

Status stack_push (Stack *s, const void *ele){
    
  if(!s || !ele ){
    return ERROR;
  }

  if((stack_isfull(s))==TRUE){
    if(stack_grow(s)==ERROR){
      return ERROR;
    }
  }

  s->item[s->top]=(void*)ele;
  (s->top)++;

  return OK;
}

void * stack_pop (Stack *s) {
  
  void *ele_popped;

  if(!s|| !(s->item)){
    return NULL;
  }

  if(stack_isEmpty (s)==TRUE){
    return NULL;
  }

  ele_popped = s->item[(s->top)-1];

  s->item[(s->top)-1]=NULL;
  (s->top)--;

  return ele_popped;
}


void * stack_top (const Stack *s){

  if(!s|| !(s->item)){
    return NULL;
  }
  
  return s->item[(s->top)-1];

}

Bool stack_isEmpty (const Stack *s){
  if (!s || !(s->item))
    return TRUE;
  return (s->top == 0);
}


size_t stack_size (const Stack *s){
  if (!s)
    return 0;
  return s->top;
}

int stack_print(FILE* fp, const Stack *s,  P_stack_ele_print f){

    int size,i;
    int characters=0;

    if(!fp || !s || !(s->item) || !f){
        return -1;
    }

    size=stack_size(s);
    characters+=fprintf(fp,"SIZE :%d\n", size);
    for(i=0;i<size; i++){
        characters+=f(fp, s->item[i]);
        fprintf(fp,"\n");
    }

    return characters;

}