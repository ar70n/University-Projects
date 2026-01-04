#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "queue.h"

#define INIT_CAPACITY 2 /* init queue capacity */
#define FCT_CAPACITY 2 /* multiply the queue capacity */
#define MAX_QUEUE 100

struct _Queue {
 void *data[MAX_QUEUE]; /*!<Static array of elements*/
 void **front;
 void **rear; 
};


/*
 * @brief: private functions
*/

Bool queue_isfull(Queue *q);


/**
 * Public functions
 */
Queue *queue_new (){
  
  int i;	
  Queue *newqueue = malloc(sizeof(Queue));
  
  if (!newqueue)
    return NULL;
  
  
  for (i=0;i<MAX_QUEUE;i++)
  {
  	newqueue->data[i]=NULL;
  }

  newqueue->front = &(newqueue->data[0]);
  newqueue->rear = &(newqueue->data[0]);

  return newqueue;

}

void queue_free (Queue *q){
	
	if (q==NULL)
	{
		return;
	}

	free(q);
}


Bool _queue_isfull(Queue *q){
  if (!q)
    return TRUE;

  if((q->rear+1-q->front)%MAX_QUEUE==0){
  	return TRUE;
  }
  return FALSE;
}

Status queue_push (Queue *q, void *ele){
    
  if(!q || !ele || _queue_isfull(q)==TRUE){
    return ERROR;
  }

  if((_queue_isfull(q))==TRUE){
 
	  return ERROR;
  }

  *(q->rear) = (void *) ele;
  q->rear = q->data + (q->rear + 1 - q->data) % MAX_QUEUE;

  return OK;
}

void * queue_pop (Queue *q) {
  
  void *ele_popped;

  if(!q|| queue_isEmpty(q)==TRUE){
    return NULL;
  }

  ele_popped = *(q->front);

  *(q->front) = NULL;

  q->front = q->data+(q->front+1-q->data) % MAX_QUEUE;



  return ele_popped;
}


void * queue_getFront (const Queue *q){

  if((!q)||queue_isEmpty(q)==TRUE){
    return NULL;
  }
  
  return *(q->front);

}

Bool queue_isEmpty (const Queue *q){
  if (!q || !(q->data))
    return TRUE;
  
  if (q->rear==q->front)
  {
  	return TRUE;
  }
  return FALSE;
  
}



void *queue_getBack(const Queue *q){
	
	void **last_elem;

	if (q==NULL||queue_isEmpty(q)==TRUE){
		return NULL;
	}
	if (q->rear == q->data) {
		last_elem = (( Queue *) q)->data + MAX_QUEUE - 1;
	} else {
		last_elem = q->rear - 1;
	}
	return * last_elem ;
}



size_t queue_size (const Queue *q){
  if (!q)
    return 0;

  return (q->rear - q->front + MAX_QUEUE) % MAX_QUEUE;

}


int queue_print(FILE* fp, const Queue *q, P_queue_ele_print f){

    int size,i;
    int characters=0;

    if(!fp || !q || !(q->data) || !f){
        return -1;
    }

    size=queue_size(q);
    characters+=fprintf(stdout,"SIZE :%d\n", size);
    for(i=0;i<size; i++){
      
      characters+=f(fp, q->data[i]);
      fprintf(fp,"\n");
    }

    return characters;

}
