/** 
 * @brief It implements the set module
 * 
 * @file set.c
 * @author Antonio Moroño
 * @version 1.0 
 * @date 24-02-2023 
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"

/**
 * @brief Set
 *
 * This struct stores all the information of a set.
 */
struct _Set {
  Id *ids;                   /*!< Id an array of unique ids of the elements in the set  */
  long n_ids;                /*!< The number of ids stored in the array */
};

/** set_create allocates memory for a new set
  * and initializes its members
  */
Set* set_create() {
  Set *newSet = NULL;
  int i;
  newSet = (Set *) malloc(sizeof (Set));

  if (newSet == NULL) {
    return NULL;
  }

  newSet->ids = (Id *) malloc(sizeof(Id)*MAX_IDS);
  if (newSet->ids == NULL) {
    return NULL;
  }
  
  /* Initialization of an empty set*/
  newSet->n_ids = 0;
  for (i = 0; i < MAX_IDS; i++) {
    newSet->ids[i] = NO_ID;
  }

  return newSet;
}
/** set_destroy frees the previous memory allocation 
  * for a set
  */
STATUS set_destroy(Set* set) {
  int i;

  if (set == NULL) {
    return ERROR;
  }

  for (i = 0; i < MAX_IDS; i++) {
    set_del(set,set->ids[i]);
  }

  free(set->ids);
  free(set);
  set = NULL;

  return OK;
} 

/*set_get_n_ids gets the number of ids in the set */ 
long set_get_n_ids(Set* set) {
  if (set == NULL) {
   return -1;
  }
  return set->n_ids;
}

/** set_add adds an id to the set
  */
STATUS set_add(Set* set , Id id) {
  int i, flag;
  
  if (set == NULL || id == NO_ID) {
    return ERROR;
  }
  
  for (i = 0, flag = 0; i < MAX_IDS && flag == 0; i++) {
    if (set->ids[i]==id) {
      return ERROR;
    }
    else if (set->ids[i] == NO_ID) {
      set->ids[i] = id;
      flag = 1;
    }
  }
  
  if (flag == 0) {
    return ERROR;
  }
  else {
    set->n_ids++;
    return OK;
  } 
}
/** set_del deletes an id from the set
  */
STATUS set_del(Set* set , Id id) {
  int i, flag, n_ids = -1;

  if (set == NULL || id == NO_ID) {
    return ERROR;
  }

  n_ids = set_get_n_ids(set);

  for (i = 0, flag = 0; i < n_ids && flag == 0; i++) {
    if (set->ids[i] == id) {
      set->ids[i] = set->ids[n_ids - 1];
      set->ids[n_ids - 1] = NO_ID;
      flag = 1;
    }
  }

  if (flag == 0) {
    return ERROR;
  }
  else {
    set->n_ids--;
    return OK;
  }
}

/** set_get_ids gets the ids in the set
  */
Id* set_get_ids(Set* set) {
  if (set == NULL) {
    return NULL;
  }
  return set->ids;
}

/** set_print prints the set information
  */
STATUS set_print(Set* set) {
  int i;
  /* Error Control */
  if (set == NULL) {
    return ERROR;
  }

  /* 1. Print the id's stored in the set */
  for (i = 0; i < MAX_IDS; i++) {
    if (set->ids[i] != NO_ID) {
      fprintf(stdout, "-->Id: %ld\n)",set->ids[i]);
    }
  }

  /* 2. Print the number of id's stored in the set */
  if (set_get_n_ids(set) != -1) {
    fprintf(stdout, "-->Number of id's: %ld\n", set_get_n_ids(set));
  }
  else {
    fprintf(stdout, "-->No id's in the set\n");
  }

  return OK;
}

