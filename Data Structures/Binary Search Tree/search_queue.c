#include "search_queue.h"
#include <stdio.h>
#include <stdlib.h>
#include "bstree.h"

struct _SearchQueue {
BSTree *data;
};



SearchQueue *search_queue_new(P_ele_print print_ele, P_ele_cmp cmp_ele){
	SearchQueue *new;
	
	if (!print_ele||!cmp_ele)
	{
		return NULL;
	}

	new = (SearchQueue*) malloc(sizeof(SearchQueue));
	if (new==NULL)
	{
		return NULL;
	}
	
	new->data = tree_init(print_ele, cmp_ele);
	if(new->data==NULL)
	{
		search_queue_free(new);
		return NULL;
	}
	return new;
}



void search_queue_free(SearchQueue *q){
	if (!q){
		return;
	}
	tree_destroy(q->data);
	free(q);
}

void search_queue_clean(SearchQueue *q){
	if (!q){
		return;
	}
	tree_destroy_clean(q->data);
	free(q);
}


Bool search_queue_isEmpty(const SearchQueue *q){

	if(!q||!q->data)
	{
		return TRUE;
	}
	if(tree_isEmpty(q->data)==TRUE)
	{
		return TRUE;
	}
	return FALSE;
}

Status search_queue_push(SearchQueue *q, void *ele){

	if(!q||!ele)
	{
		return ERROR;
	}
	if (tree_insert(q->data,ele)==ERROR)
	{
		return ERROR;
	}
	return OK;


}

void *search_queue_pop(SearchQueue *q){

	void *ele;
	if(!q)
	{
		return NULL;
	}
	ele = search_queue_getFront(q);
	tree_remove(q->data,ele);
	return ele;

}

void *search_queue_getFront(const SearchQueue *q){

	if(!q)
	{
		return NULL;
	}
	return tree_find_min(q->data);



}

void *search_queue_getBack(const SearchQueue *q){

	if(!q)
	{
		return NULL;
	}
	return tree_find_max(q->data);

}

size_t search_queue_size(const SearchQueue *q){
	if (!q)
	{
		return 0;
	}
	return tree_size(q->data);
}


int search_queue_print(FILE *fp, const SearchQueue *q){

	if (!fp || !q)
	{
		return -1;
	}
	return tree_inOrder(fp, q->data);


}



