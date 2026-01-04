/** 
 * @brief It implements the inventory module
 * 
 * @file inventory.c
 * @author Sergio Saúco
 * @version 1.0 
 * @date 17-03-2023
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventory.h"

/**
 * @brief Inventory
 *
 * This struct stores all the information of a inventory.
 */
struct _Inventory {
  Set *objs;                    /*!< Set with the objects id's carried by the player */
  long max_objs;                 /*!< Maximum number of objects */
};

/** inventory_create allocates memory for a new inventory
  * and initializes its members
  */
Inventory* inventory_create() {
  Inventory *newInventory = NULL;

  newInventory = (Inventory *) malloc(sizeof (Inventory));
  if (newInventory == NULL) {
    return NULL;
  }

  /* Initialization of an empty inventory*/
  newInventory->objs = set_create();
  if(newInventory->objs == NULL) {
    return NULL;
  }
  newInventory->max_objs = -1;

  return newInventory;
}

/** inventory_destroy frees the previous memory allocation 
  * for a inventory
  */
STATUS inventory_destroy(Inventory* inventory) {
  if (!inventory) {
    return ERROR;
  }

  set_destroy(inventory->objs);

  free(inventory);
  inventory = NULL;
  return OK;
}

/** inventory_add_object adds an object to the inventory
  */
STATUS inventory_add_object(Inventory* inventory, Id object_id) {
  if (!inventory || object_id == NO_ID || set_get_n_ids(inventory->objs) == inventory_get_max_objs(inventory)) {
    return ERROR;
  }
  if (inventory_stores_object(inventory, object_id) == TRUE) {
    return ERROR;
  }
  if (set_add(inventory->objs, object_id) == ERROR) {
    return ERROR;
  } 
  return OK;
} 
/** inventory_del_object deletes an object from the inventory
  */
STATUS inventory_del_object(Inventory* inventory, Id object_id) {
  if (!inventory || object_id == NO_ID || inventory_stores_object(inventory, object_id) == FALSE) {
    return ERROR;
  }
  if (set_del(inventory->objs, object_id) == ERROR) {
    return ERROR;
  } 
  return OK;
}

/** inventory_get_objects gets the id's of the objects stored in the inventory
  */
Id* inventory_get_objects(Inventory* inventory) {
  Id *ids = NULL;
  if (!inventory) {
    return NULL;
  }
  ids = set_get_ids(inventory->objs);
  if (ids == NULL) {
    return NULL;
  }
  return ids;
}
/** inventory_stores_object checks wether the inventory stores
  * an object or not
  */
BOOL inventory_stores_object(Inventory* inventory, Id object_id) {
  Id *ids = NULL;
  long i, flag, max_objs = -1;
  if (!inventory || object_id == NO_ID) {
    return FALSE;
  }

  ids = inventory_get_objects(inventory);
  if (ids == NULL) {
    return FALSE;
  }

  max_objs = inventory_get_max_objs(inventory);
  if (max_objs == -1) {
    return FALSE;
  }
  for (i = flag = 0; i < max_objs && flag == 0; i++) {
    if (ids[i] == object_id) {
      flag = 1;
    }
  }

  if (flag == 0) {
    return FALSE;
  }
  else {
    return TRUE;
  }
}

/** inventory_get_n_objects gets the number of objects in the inventory 
  */
long inventory_get_n_objects(Inventory *inventory) {
  long number_objects = -1;
  if (!inventory) {
    return -1;
  }
  number_objects = set_get_n_ids(inventory->objs);
  if (number_objects == -1) {
    return -1;
  } 
  return number_objects;
}

/** inventory_set_max_objs sets the maximum number of objects 
  * that the inventory can store
  */
STATUS inventory_set_max_objs(Inventory* inventory, int max_objs){
  if (!inventory || max_objs < 0) {
    return ERROR;
  }
  inventory->max_objs = max_objs;
  return OK;
}
/** inventory_get_max_objs gets the maximum number of objects 
  * that the inventory can store
  */
long inventory_get_max_objs(Inventory* inventory) {
  if (!inventory) {
    return -1;
  }
  return inventory->max_objs;
}

/** inventory_print prints the inventory information
  */
STATUS inventory_print(Inventory* inventory) {
  long max_objs = -1;

  if (!inventory) {
    return ERROR;
  }

  /* 1. Print the id's stored in the inventory */
  if (set_print(inventory->objs) == ERROR) {
    return ERROR;
  }  

  /* 2. Print the the maximum number of objects that the inventory can store */
  max_objs = inventory_get_max_objs(inventory);
  if (max_objs == -1) {
    return ERROR;
  }

  return OK;
}

