/**
 * @brief It defines the link interface
 *
 * @file link.h
 * @author Antonio Moroño
 * @version 1.0
 * @date 8-03-2022
 * @copyright GNU Public License
 */

#ifndef LINK_H
#define LINK_H

#include "types.h"
#include "set.h"

/**
 * @brief Link
 *
 * Stores the information about
 * the link (id, name, origin, destination,
 * direction and status)
 */
typedef struct _Link Link;

#define MAX_LINKS MAX_SPACES*4 /*!< The maximum number of links */
#define FIRST_LINK 1 /*!< The first link */
#define MAX_STR 10 /*!< The maximum number of characters */

/**
  * @brief It creates a new link, allocating memory and initializing its memebers
  * @author Antonio Moroño
  * 
  * @param id the identification number for the new link
  * @return a new link, initialized
  */
Link* link_create(Id id);

/**
  * @brief It destroys a link, freeing the allocated memory
  * @author Antonio Moroño
  * 
  * @param link a pointer to the link that must be destroyed  
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS link_destroy(Link* link);

/**
  * @brief It gets the id of a link
  * @author Antonio Moroño
  * 
  * @param link a pointer to the link  
  * @return the id of link
  */
Id link_get_id(Link* link);

/**
  * @brief It sets the name of a link
  * @author Antonio Moroño
  * 
  * @param link a pointer to the link
  * @param name a string with the name to store
  * @return OK, if everything goes well or ERROR if there was some mistake 
  */
STATUS link_set_name(Link* link, char* name);

/**
  * @brief It gets the name of a link
  * @author Antonio Moroño
  * 
  * @param link a pointer to the link
  * @return  a string with the name of the link
  */
const char* link_get_name(Link* link);

/**
  * @brief It sets the origin of a link
  * @author Antonio Moroño
  * 
  * @param link a pointer to the link
  * @param origin a id to the origin space
  * @return OK, if everything goes well or ERROR if there was some mistake 
  */
STATUS link_set_origin(Link* link, Id origin);

/**
  * @brief It gets the origin of a link
  * @author Antonio Moroño
  * 
  * @param link a pointer to the link
  * @return  the id of the origin space
  */
Id link_get_origin(Link* link);


/**
  * @brief It sets the destination of a link
  * @author Antonio Moroño
  * 
  * @param link a pointer to the link
  * @param destination a id to the destination space
  * @return OK, if everything goes well or ERROR if there was some mistake 
  */
STATUS link_set_destination(Link* link, Id destination);

/**
  * @brief It gets the destination of a link
  * @author Antonio Moroño
  * 
  * @param link a pointer to the link
  * @return  the id of the destination space
  */
Id link_get_destination(Link* link);


/**
  * @brief It sets the direction of a link
  * @author Antonio Moroño
  * 
  * @param link a pointer to the link
  * @param direction the direction being set to the link
  * @return OK, if everything goes well or ERROR if there was some mistake 
  */
STATUS link_set_direction(Link* link, DIRECTION direction);

/**
  * @brief It gets the direction of a link
  * @author Antonio Moroño
  * 
  * @param link a pointer to the link
  * @return  the direction of the link
  */
DIRECTION link_get_direction(Link* link);


/**
  * @brief It sets the status of a link
  * @author Antonio Moroño
  * 
  * @param link a pointer to the link
  * @param status the status being set to the link
  * @return OK, if everything goes well or ERROR if there was some mistake 
  */
STATUS link_set_status(Link* link, CONNECTION status);

/**
  * @brief It gets the status of a link
  * @author Antonio Moroño
  * 
  * @param link a pointer to the link
  * @return  the status of the link
  */
CONNECTION link_get_status(Link* link);





/**
  * @brief It prints the link information
  * @author Antonio Moroño
  *
  * This function shows the id and name of the link, the links that surrounds it and the ids of the objects in the link.
  * @param link a pointer to the link
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS link_print(Link* link);



#endif
