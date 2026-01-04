#include "bstree.h"

#include <stdio.h>
#include <stdlib.h>

/* START [_BSTNode] */
typedef struct _BSTNode {
  void *info;
  struct _BSTNode *left;
  struct _BSTNode *right;
} BSTNode;
/* END [_BSTNode] */

/* START [_BSTree] */
struct _BSTree {
  BSTNode *root;
  P_ele_print print_ele;
  P_ele_cmp cmp_ele;
};
/* END [_BSTree] */

/*** BSTNode TAD private functions ***/
BSTNode *_bst_node_new() {
  BSTNode *pn = NULL;

  pn = malloc(sizeof(BSTNode));
  if (!pn) {
    return NULL;
  }

  pn->left = NULL;
  pn->right = NULL;
  pn->info = NULL;

  return pn;
}

void _bst_node_free(BSTNode *pn) {
  if (!pn) {
    return;
  }

  free(pn);
}

void _bst_node_free_rec(BSTNode *pn) {
  if (!pn) {
    return;
  }


  _bst_node_free_rec(pn->left);
  _bst_node_free_rec(pn->right);
  _bst_node_free(pn);

  return;
}

void _bst_node_free_clean_rec(BSTNode *pn) {
  if (!pn) {
    return;
  }


  _bst_node_free_clean_rec(pn->left);
  _bst_node_free_clean_rec(pn->right);
  free(pn->info);
  _bst_node_free(pn);

  return;
}

int _bst_depth_rec(BSTNode *pn) {
  int depth_l, depth_r;

  if (!pn) {
    return 0;
  }

  depth_l = _bst_depth_rec(pn->left);
  depth_r = _bst_depth_rec(pn->right);

  if (depth_r > depth_l) {
    return depth_r + 1;
  } else {
    return depth_l + 1;
  }
}

int _bst_size_rec(BSTNode *pn) {
  int count = 0;

  if (!pn) {
    return count;
  }

  count += _bst_size_rec(pn->left);
  count += _bst_size_rec(pn->right);

  return count + 1;
}

int _bst_preOrder_rec(BSTNode *pn, FILE *pf, P_ele_print print_ele) {
  int count = 0;

  if (!pn) {
    return count;
  }

  count += print_ele(pf, pn->info);
  count += _bst_preOrder_rec(pn->left, pf, print_ele);
  count += _bst_preOrder_rec(pn->right, pf, print_ele);

  return count;
}

int _bst_inOrder_rec(BSTNode *pn, FILE *pf, P_ele_print print_ele) {
  int count = 0;

  if (!pn) {
    return count;
  }

  count += _bst_inOrder_rec(pn->left, pf, print_ele);
  count += print_ele(pf, pn->info);
  count += _bst_inOrder_rec(pn->right, pf, print_ele);

  return count;
}

int _bst_postOrder_rec(BSTNode *pn, FILE *pf, P_ele_print print_ele) {
  int count = 0;

  if (!pn) {
    return count;
  }

  count += _bst_postOrder_rec(pn->left, pf, print_ele);
  count += _bst_postOrder_rec(pn->right, pf, print_ele);
  count += print_ele(pf, pn->info);

  return count;
}

BSTNode* _bst_find_min_rec(BSTNode *pn){
  if(!pn){
    return NULL;
  }
  if(pn->left==NULL) return pn->left;
  
  else{
     return _bst_find_min_rec(pn->left);
  }

}

BSTNode* _bst_find_max_rec(BSTNode *pn){
  if(!pn){
    return NULL;
  }
  if(pn->right==NULL) return pn->right;
  else{
     return _bst_find_max_rec(pn->right);
  }

}

BSTNode* _bst_insert_rec(BSTNode *pn, P_ele_cmp cmp, const void* ele){
  if(!ele || !cmp){
    return NULL;
  }
  if(!pn){
    pn=_bst_node_new();
    if(!pn){
      return NULL;
    }
      pn->info=(void*)ele;
      return pn;

  }
  if(cmp(ele, pn->info)<0){
    pn->left=_bst_insert_rec(pn->left, cmp, ele);
  }
  else if(cmp(ele, pn->info)>0){
    pn->right=_bst_insert_rec(pn->right, cmp, ele);
  }

  return pn;


}


BSTNode* _bst_remove_rec(BSTNode *pn,const void *elem,P_ele_cmp cmp_ele){

  BSTNode *node_return=NULL,*aux_node=NULL;

  if (!pn ||!elem ||!cmp_ele) return NULL;

  if(cmp_ele(elem, pn->info)<0){
    pn->left=_bst_remove_rec(pn->left, elem, cmp_ele);
  }
  else if(cmp_ele(elem, pn->info)>0){
    pn->right=_bst_remove_rec(pn->right, elem, cmp_ele);
  }
  else if(cmp_ele(elem, pn->info)==0){
    if(pn->right==NULL && pn->left==NULL){
      _bst_node_free(pn);
      return NULL;
    }
    else if(pn->right!=NULL && pn->left==NULL){
      node_return=pn->right;
      _bst_node_free(pn);
      return node_return;
    } 
    else if(pn->right==NULL && pn->left!=NULL){
      node_return=pn->left;
      _bst_node_free(pn);
      return node_return;
    }  
    else if(pn->right!=NULL && pn->left!=NULL){
      aux_node=_bst_find_min_rec(pn->right);
      pn->info=aux_node->info;
      pn->right=_bst_remove_rec(pn->right,aux_node->info, cmp_ele);
      return pn;
    }  
  }

return pn;
}

/*** BSTree TAD functions ***/
BSTree *tree_init(P_ele_print print_ele, P_ele_cmp cmp_ele) {
  BSTree *tree;

  if (!print_ele || !cmp_ele) {
    return NULL;
  }

  tree = malloc(sizeof(BSTree));
  if (!tree) {
    return NULL;
  }

  tree->root = NULL;
  tree->print_ele = print_ele;
  tree->cmp_ele = cmp_ele;

  return tree;
}

void tree_destroy(BSTree *tree) {
  if (!tree) {
    return;
  }

  _bst_node_free_rec(tree->root);
  free(tree);

  return;
}

void tree_destroy_clean(BSTree *tree) {
  if (!tree) {
    return;
  }

  _bst_node_free_clean_rec(tree->root);
  free(tree);

  return;
}

Bool tree_isEmpty(const BSTree *tree) {
  if (!tree || !tree->root) {
    return TRUE;
  }
  return FALSE;
}

int tree_depth(const BSTree *tree) {
  if (!tree) {
    return -1;
  }

  return _bst_depth_rec(tree->root);
}

size_t tree_size(const BSTree *tree) {
  if (!tree) {
    return -1;
  }

  return _bst_size_rec(tree->root);
}

int tree_preOrder(FILE *f, const BSTree *tree) {
  if (!f || !tree) {
    return -1;
  }

  return _bst_preOrder_rec(tree->root, f, tree->print_ele) + fprintf(f, "\n");
}

int tree_inOrder(FILE *f, const BSTree *tree) {
  if (!f || !tree) {
    return -1;
  }

  return _bst_inOrder_rec(tree->root, f, tree->print_ele) + fprintf(f, "\n");
}

int tree_postOrder(FILE *f, const BSTree *tree) {
  if (!f || !tree) {
    return -1;
  }

  return _bst_postOrder_rec(tree->root, f, tree->print_ele) + fprintf(f, "\n");
}

void *tree_find_min(BSTree *tree){
  
	BSTNode *curr;

	if ( !tree||tree_isEmpty(tree)==TRUE) {
    		return NULL;
  	}
	curr = tree->root;

      	while (curr->left!=NULL){
		
		curr = curr->left;

	}	

	return curr->info;

}

void *tree_find_max(BSTree *tree){
  
	BSTNode *curr;

	if ( !tree||tree_isEmpty(tree)==TRUE) {
    		return NULL;
  	}
	curr = tree->root;

      	while (curr->right!=NULL){
		
		curr = curr->right;

	}	

	return curr->info;

}

Bool tree_contains(BSTree* tree, const void *elem){
	BSTNode *curr;
	int cmp_result;
	if (!tree || !elem){
		return FALSE;
	}

	curr = tree->root;

 	while (curr != NULL) {
        cmp_result = tree->cmp_ele(elem, curr->info);
        if (cmp_result == 0) {
            return TRUE;
        } else if (cmp_result < 0) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    return FALSE;
}
/*
Status tree_insert(BSTree *tree,const void *elem){
	BSTNode *pn,*curr;
	int cmp_result;
	if (!tree||!elem||!tree->root)
	{
		return ERROR;
	}

  curr=tree->root;

 	while (curr != NULL) {
       	cmp_result = tree->cmp_ele(elem, curr->info);
    	    if (cmp_result == 0) {
        	    return OK;
    	    } else if (cmp_result < 0) {
		  if(curr->left==NULL)
		  {
		  	pn = _bst_node_new();
			pn->info = elem;
			curr->left=pn;
			return OK;
		  }
          	  curr = curr->left;
        	} else {
		  if(curr->right==NULL)
		  {
		  	pn = _bst_node_new();
			pn->info = elem;
			curr->right=pn;
			return OK;
		  }
        
          	  curr = curr->right;
        	}
    	}
	return ERROR;


}*/


Status tree_insert(BSTree *tree, const void *elem) {
	BSTNode *new_node;

  if (!elem || !tree) {
    return ERROR;
  }

  new_node=_bst_insert_rec(tree->root,tree->cmp_ele, elem);
  if(!new_node){
    return ERROR;
  }

  tree->root=new_node;
  return OK;


}



Status tree_remove(BSTree *tree, const void *elem){
  if (!elem || !tree) {
    return ERROR;
  }

  _bst_remove_rec(tree->root,elem,tree->cmp_ele);
  return OK;

}

/**** TODO: find_min, find_max, insert, contains, remove ****/

