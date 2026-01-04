/**
 * @brief It defines the space interface
 *
 * @file space.h
 * @author Profesores PPROG
 * @version 2.0
 * @date 29-11-2021
 * @copyright GNU Public License
 */

#ifndef SPACE_H
#define SPACE_H

#include "types.h"
#include "set.h"

/**
 * @brief Space
 *
 * Stores the information about
 * the enemy (id, name, objects,
 * graphic description, detailed
 * description and light)
 */
typedef struct _Space Space;

#define MAX_SPACES 100 /*!< The maximum number of spaces */
#define FIRST_SPACE 1 /*!< The first space */
#define LENGTH_GDESC 5 /*!< The length of the gdesc */
#define MAX_STR 10 /*!< The maximum number of characters in gdesc */

/**
  * @brief It creates a new space, allocating memory and initializing its memebers
  * @author Profesores PPROG
  * 
  * @param id the identification number for the new space
  * @return a new space, initialized
  */
Space* space_create(Id id);

/**
  * @brief It destroys a space, freeing the allocated memory
  * @author Profesores PPROG
  * 
  * @param space a pointer to the space that must be destroyed  
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS space_destroy(Space* space);

/**
  * @brief It gets the id of a space
  * @author Profesores PPROG
  * 
  * @param space a pointer to the space  
  * @return the id of space
  */
Id space_get_id(Space* space);

/**
  * @brief It sets the name of a space
  * @author Profesores PPROG
  * 
  * @param space a pointer to the space
  * @param name a string with the name to store
  * @return OK, if everything goes well or ERROR if there was some mistake 
  */
STATUS space_set_name(Space* space, char* name);

/**
  * @brief It gets the name of a space
  * @author Profesores PPROG
  * 
  * @param space a pointer to the space
  * @return  a string with the name of the space
  */
const char* space_get_name(Space* space);

/**
  * @brief It sets the description of a space
  * @author Antonio Moroño
  * 
  * @param space a pointer to the space
  * @param desc a string with the description to store
  * @return OK, if everything goes well or ERROR if there was some mistake 
  */
STATUS space_set_description(Space* space, char* desc);

/**
  * @brief It gets the description of a space
  * @author Antonio Moroño
  * 
  * @param space a pointer to the space
  * @return  a string with the description of the space
  */
char* space_get_description(Space* space);

/**
  * @brief It sets the detailed description of a space
  * @author Sergio Saúco
  * 
  * @param space a pointer to the space
  * @param desc a string with the detailed description to store
  * @return OK, if everything goes well or ERROR if there was some mistake 
  */
STATUS space_set_detailed_desc(Space* space, char* desc);

/**
  * @brief It gets the detailed description of a space
  * @author Sergio Saúco
  * 
  * @param space a pointer to the space
  * @return  a string with the detailed description of the space
  */
char* space_get_detailed_desc(Space* space);

/**
  * @brief It sets the id of the object in the space
  * @author Profesores PPROG
  *
  * @param space a pointer to the space
  * @param id the id number of the object
  * @return OK, if everything goes well or ERROR if there was some mistake 
  */
STATUS space_set_object(Space* space, Id id);
/**
  * @brief It unsets the id of the object in the space
  * @author Sergio Saúco
  *
  * @param space a pointer to the space
  * @param id the id number of the object
  * @return OK, if everything goes well or ERROR if there was some mistake 
  */
STATUS space_unset_object(Space *space, Id id);
/**
  * @brief It gets the id of the objects in the space
  * @author Profesores PPROG
  *
  * @param space a pointer to the space
  * @return the id number of the object
  */
Id* space_get_objects(Space* space);

/**
  * @brief It gets the number of the objects in the space
  * @author Profesores PPROG
  *
  * @param space a pointer to the space
  * @return the id number of the object
  */
int space_get_n_objects(Space *space);

/**
  * @brief It sets the graphic description of a space
  * @author Sergio Saúco
  * 
  * @param space a pointer to the space
  * @param desc an array of string with the graphic description
  * @return OK, if everything goes well or ERROR if there was some mistake 
  */
STATUS space_set_gdesc(Space *space, char (*desc)[MAX_STR]);
/**
  * @brief It gets a row from the graphic description of a space
  * @author Sergio Saúco
  * 
  * @param space a pointer to the space
  * @param row the row to get
  * @return a string with the graphic description row or NULL if there was some mistake
  */
char* space_get_gdesc_row(Space *space, int row);

/**
  * @brief It searchs if an object is in the space
  * @author Antonio Moroño
  *
  * @param space a pointer to the space
  * @param id the id of the searched object
  * @return TRUE if the object is in the space or FALSE otherwise
  */

BOOL space_search_object(Space* space, Id id);

/**
  * @brief It sets the light of a space
  * @author Antonio Moroño
  * 
  * @param space a pointer to the space
  * @param st a boolean with the status of the light of the space
  * @return OK, if everything goes well or ERROR if there was some mistake 
  */
STATUS space_set_light(Space* space, BOOL st);

/**
  * @brief It gets the light of a space
  * @author Antonio Moroño
  * 
  * @param space a pointer to the space
  * @return a boolean with the light of the space
  */
BOOL space_get_light(Space* space);


/**
  * @brief It prints the space information
  * @author Profesores PPROG
  *
  * This function shows the id and name of the space, the spaces that surrounds it and the ids of the objects in the space.
  * @param space a pointer to the space
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS space_print(Space* space);



#endif
