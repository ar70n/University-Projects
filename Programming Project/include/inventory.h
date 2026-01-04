/**
 * @brief It defines the inventory interface
 *
 * @file inventory.h
 * @author Sergio Saúco
 * @version 1.0
 * @date 17-03-2023
 * @copyright GNU Public License
 */

#ifndef INVENTORY_H
#define INVENTORY_H

#include "types.h"
#include "set.h"

/**
 * @brief Inventory
 *
 * Stores the information about
 * the inventory (objects and
 * max objects)
 */
typedef struct _Inventory Inventory;


/**
  * @brief It creates a new inventory, allocating memory and initializing its memebers
  * @author Sergio Saúco
  * 
  * @return a new inventory, initialized
  */
Inventory* inventory_create();

/**
  * @brief It destroys an inventory, freeing the allocated memory
  * @author Sergio Saúco
  * 
  * @param inventory a pointer to the inventory that must be destroyed  
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS inventory_destroy(Inventory* inventory);

/**
  * @brief It adds an object to the inventory
  * @author Sergio Saúco
  * 
  * @param inventory a pointer to the inventory 
  * @param object_id the identification number of the object that must be added
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS inventory_add_object(Inventory* inventory, Id object_id);
/**
  * @brief It deletes an object from the inventory
  * @author Sergio Saúco
  * 
  * @param inventory a pointer to the inventory 
  * @param object_id the identification number of the object that must be deleted
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS inventory_del_object(Inventory* inventory, Id object_id);

/**
  * @brief It gets the id's of the objects stored in the inventory
  * @author Sergio Saúco
  * 
  * @param inventory a pointer to the inventory
  * @return the id's or NULL if there was some mistake
  */
Id* inventory_get_objects(Inventory* inventory);
/**
  * @brief It checks wether the inventory stores an object or not
  * @author Sergio Saúco
  * 
  * @param inventory a pointer to the inventory
  * @param object_id the identification number of the object
  * @return TRUE if the object is in the inventory or FALSE otherwise
  */
BOOL inventory_stores_object(Inventory* inventory, Id object_id);

/**
  * @brief It gets the number of objects in the inventory 
  * @author Sergio Saúco
  * 
  * @param inventory a pointer to the inventory
  * @return the number of objects in the inventory or -1 if there was some mistake
  */
long inventory_get_n_objects(Inventory *inventory);

/**
  * @brief It sets the maximum number of objects that the inventory can store
  * @author Sergio Saúco
  * 
  * @param inventory a pointer to the inventory
  * @param max_objs the maximum number to be set
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS inventory_set_max_objs(Inventory* inventory, int max_objs);
/**
  * @brief It gets the maximum number of objects that the inventory can store
  * @author Sergio Saúco
  * 
  * @param inventory a pointer to the inventory 
  * @return the maximum number of objects or -1 if there was some mistake
  */
long inventory_get_max_objs(Inventory* inventory);

/**
  * @brief It prints the inventory information
  * @author Sergio Saúco
  *
  * This function shows the id's stored in the inventory and the maximum number of objects
  * that can be stored.
  * @param inventory a pointer to the inventory
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS inventory_print(Inventory* inventory);

#endif
