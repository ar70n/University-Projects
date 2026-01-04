/**
 * @brief It defines the set interface
 *
 * @file set.h
 * @author Antonio Moroño
 * @version 1.0
 * @date 24-02-2023
 * @copyright GNU Public License
 */

#ifndef SET_H
#define SET_H

#include "types.h"

/**
 * @brief Set
 *
 * Stores the information about
 * the set (id's and number of id's)
 */
typedef struct _Set Set;

#define MAX_IDS 100 /*!< The maximum number of id's in a set */

/**
  * @brief It creates a new set, allocating memory and initializing its memebers
  * @author Antonio Moroño
  * 
  * @return a new set, initialized
  */
Set* set_create();
/**
  * @brief It destroys a set, freeing the allocated memory
  * @author Antonio Moroño
  * 
  * @param set a pointer to the set that must be destroyed  
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS set_destroy(Set* set);

/**
  * @brief It sets the number of ids of a set
  * @author Antonio Moroño
  * 
  * @param set the set in which the number of ids will be set
  * @param n_ids the number of ids that will be in set
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS set_set_n_ids(Set* set, long n_ids);
/**
  * @brief It gets the number of ids of a set
  * @author Antonio Moroño
  * 
  * @param set a pointer to the set
  * @return the number of id's or -1 if there was some mistake
  */
long set_get_n_ids(Set* set);

/**
  * @brief It adds a new id to the set 
  * @author Antonio Moroño
  * 
  * @param set the set in wich the id will be added
  * @param id the identification number that will be added to the set
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS set_add(Set* set ,Id id);
/**
  * @brief It deletes an id from the set 
  * @author Antonio Moroño
  * 
  * @param set the set from which the id will be deleted
  * @param id the identification number that will be deleted from the set
  * @return  OK, if everything goes well or ERROR if there was some mistake
  */
STATUS set_del(Set* set ,Id id);


/**
  * @brief It gets the ids in the set
  * @author Antonio Moroño
  * 
  * @param set a pointer to the set where the id's are
  * @return Id a pointer to the array of ids
  */
Id* set_get_ids(Set* set);

/**
  * @brief It prints the set information
  * @author Antonio Moroño
  *
  * This function shows the id's stored in the set and the number of id's in the set.
  * @param set a pointer to the set
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS set_print(Set* set);

#endif
