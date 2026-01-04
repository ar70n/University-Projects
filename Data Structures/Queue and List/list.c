#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "list.h"

#define INIT_CAPACITY 2 /* init list capacity */
#define FCT_CAPACITY 2 /* multiply the list capacity */
#define MAX_LIST 100

typedef struct _NodeList {
  void* data;
  struct _NodeList *next;
} NodeList;

struct _List {
  NodeList *last;
};

/*
 * @brief: private functions
*/

Bool list_isfull(List *q);

NodeList * node_new () {
  NodeList *pn = NULL;
  pn = (NodeList *) malloc ( sizeof (NodeList));
  if (!pn) {
    return NULL;
  }
  pn->data = NULL;
  pn->next = NULL;
  return pn;
}


/**
 * Public functions
 */
List *list_new () {
  List *pl = NULL;
  pl = (List *) malloc ( sizeof (List));
  if (pl == NULL) {
    return NULL;
  }
  pl->last = NULL;
  return pl;
}

Bool list_isEmpty ( const List *pl) {
  NodeList* pn;

  if (pl == NULL) {
    return TRUE;
  }
  pn = pl->last;
  if (pn == NULL) {
    return TRUE;
  }
  return FALSE;
}


Status list_pushFront ( List *pl ,  void *e) {
  NodeList *pn = NULL;
  if (pl == NULL || e == NULL) {
    return ERROR ;
  }
  pn = node_new ();
  if (pn == NULL) {
  return ERROR;
  }
  pn ->data = (void *)e;
  if (list_isEmpty (pl)) {
    pn->next = pn;
    pl->last = pn;
  } else {
  pn->next = pl->last->next;
  pl->last->next = pn;
  }
  return OK;
}


Status list_pushBack ( List *pl ,  void *e) {
  NodeList *pn = NULL;
  if (pl == NULL || e == NULL) {
    return ERROR;
  }
  pn = node_new ();
  if (pn == NULL) {
    return ERROR;
  }
  pn ->data = (void *)e;

  if ( list_isEmpty (pl) == TRUE) {
    pn->next = pn;
    pl->last = pn;
  } else {
    pn->next = pl->last->next;
    pl->last->next = pn;
    pl->last = pn;
  }
  return OK;
}

Status list_pushInOrder(List *pl, void *e, P_ele_cmp f, int order) {

    NodeList *new_node = (NodeList *)malloc(sizeof(NodeList));

    if (pl == NULL || f == NULL) {
        return ERROR;
    }
    
    if (new_node == NULL) {
        return ERROR;
    }
    new_node->data = e;
    if (list_isEmpty(pl)) { /* Lista vacía*/
        pl->last = new_node;
        new_node->next = new_node;
    } else {
        NodeList *current_node = pl->last->next;
        while (f(current_node->data, e) * order < 0 && current_node != pl->last) {
            current_node = current_node->next;
        }
        if (f(current_node->data, e) * order >= 0) { /* El nuevo elemento es menor o igual que el elemento actual */
            new_node->next = current_node;
            if (current_node == pl->last) {
                pl->last = new_node;
            }
        } else { /* El nuevo elemento es mayor que todos los elementos de la lista */
            new_node->next = current_node->next;
            current_node->next = new_node;
        }
    }
    return OK;
}


void *list_popFront ( List *pl) {
  NodeList *pn = NULL;
  void *pe = NULL;
  if (pl == NULL || list_isEmpty (pl) == TRUE) {
    return NULL;
  }
  pn = pl->last->next;
  pe = pn ->data;

  if (pl->last->next == pl->last) {
    pl->last = NULL;
  } else {
    pl->last->next = pn->next;
  }
  free(pn);
  return pe;
}


void *list_popBack ( List *pl) {
  NodeList *pn = NULL;
  void *pe = NULL;
  if (pl == NULL || list_isEmpty (pl) == TRUE) {
    return NULL;
  }
  if (pl->last->next == pl->last) {
    pe = (pl->last)->data;
    free(pl->last);
    pl->last = NULL;
    return pe;
  }
  pn = pl->last;
  while (pn->next!= pl->last) {
    pn = pn->next;
  }
  pe = pl->last->data;
  pn->next = pl->last->next;
  free(pl->last);
  pl->last = pn;
  return pe;
}


void list_free(List *pl) {
   NodeList *pn, *qn;
 
   if (pl == NULL) {
     return;
   }
 
   pn = pl->last;
 
   while (pn != NULL) {
     qn = pn->next;
     free(pn);
     pn = qn;
   }
 
   free(pl);
 }


size_t list_size(const List *pl) {
  size_t size = 0;
  NodeList *node = pl->last;
  if (node != NULL) {
    /* Si hay al menos un nodo en la lista, aumenta el tamaño de la lista y avanza al siguiente nodo. */
    size++;
    node = node->next;
  }
  /* Sigue avanzando en la lista hasta que se regrese al nodo inicial. */
  while (node != NULL && node != pl->last) {
    size++;
    node = node->next;
  }
  return size;
}


int list_print(FILE *fp, const List *pl, P_ele_print f){

   NodeList *pn = NULL;
   int return_value = 0;
   int val = 0;
   size_t size,i=0;
 
   if (pl == NULL || fp == NULL) {
     return -1;
   }
 	
   size = list_size(pl);
   
   fprintf(fp, "SIZE:%ld \n", size);

   pn = (pl->last)->next;
   while (i<size) {
     val = f(fp, pn ->data);
     if (val < 0) {
       return val;
     }
     fprintf(fp, " ");
     return_value += val + 1;
     pn = pn->next;
     i++;
   }
 
   return return_value;
 }










