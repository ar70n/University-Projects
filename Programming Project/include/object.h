/**
 * @brief It defines the object
 *
 * @file object.h
 * @author Antonio Moroño and Sergio Saúco
 * @version 1.1
 * @date 24-03-2023
 * @copyright GNU Public License
 */




#ifndef OBJECT_H
#define OBJECT_H

#include "types.h"

/**
 * @brief Object
 *
 * Stores the information about
 * the object (id, name, description, dependency,
 * open and booleans: hidden, movable, illuminate
 * and turnedon)
 */
typedef struct _Object Object;

#define MAX_OBJECTS 100 /*!< The maximum number of objects */


/**
  * @brief It creates a new object, allocating memory and initializing its memebers
  * @author Antonio Moroño
  *
  * @param id the identification number for the new object
  * @return a new object, initialized
  */
Object* object_create(Id id);

/**
  * @brief It destroys an object, freeing the allocated memory
  * @author Antonio Moroño
  *
  * @param object a pointer to the object that must be destroyed
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS object_destroy(Object* object);

/**
  * @brief It gets the id of an object
  * @author Antonio Moroño
  *
  * @param object a pointer to the object
  * @return the id of object
  */
Id object_get_id(Object* object);

/**
  * @brief It sets the name of an object
  * @author Antonio Moroño
  *
  * @param object a pointer to the object
  * @param name a string with the name to store
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS object_set_name(Object* object, char* name);

/**
  * @brief It gets the name of an object
  * @author Antonio Moroño
  *
  * @param object a pointer to the object
  * @return  a string with the name of the object
  */
char* object_get_name(Object* object);

/**
  * @brief It sets the description of an object
  * @author Sergio Saúco
  *
  * @param object a pointer to the object
  * @param desc a string with the description to store
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS object_set_description(Object* object, char* desc);

/**
  * @brief It gets the description of an object
  * @author Sergio Saúco
  *
  * @param object a pointer to the object
  * @return  a string with the description of the object
  */
char* object_get_description(Object* object);

/**
  * @brief It prints the object information
  * @author Antonio Moroño
  *
  * @param object a pointer to the object
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS object_print(Object* object);

/**
  * @brief It gets the link unlocked by an object
  * @author Miguel Campo
  *
  * 
  * @param object a pointer to the object
  * @return The id of the link opened
  */
Id object_get_open(Object* object);

/**
  * @brief It sets the link unlocked by an object
  * @author Miguel Campo
  *
  * 
  * @param object a pointer to the object
  * @param id the id of the link
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS object_set_open(Object* object, Id id);

/**
  * @brief It sets the movility of an object
  * @author Antonio Moroño
  *
  * @param object a pointer to the object
  * @param st, a boolean to the status of the movility
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS object_set_movable(Object* object, BOOL st);

/**
  * @brief It gets the movility of an object
  * @author Antonio Moroño
  *
  * @param object a pointer to the object
  * @return a boolean with the object movility
  */
BOOL object_get_movable(Object* object);

/**
  * @brief It sets wether the object is hidden or not
  * @author Sergio Saúco
  *
  * 
  * @param object a pointer to the object
  * @param st a boolean with the status of hidden
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS object_set_hidden(Object* object, BOOL st);

/**
  * @brief It gets wether the object is hidden or not
  * @author Sergio Saúco
  *
  * 
  * @param object a pointer to the object
  * @return FALSE, if the object is not hidden or TRUE, if there was some error
  * or the object is hidden
  */
BOOL object_get_hidden(Object* object);


/**
  * @brief It sets the turnedon of an object
  * @author Antonio Moroño
  *
  * @param object a pointer to the object
  * @param st a boolean to the status of the turnedon
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS object_set_turnedon(Object* object, BOOL st);

/**
  * @brief It gets the turnedon of an object
  * @author Antonio Moroño
  *
  * @param object a pointer to the object
  * @return a boolean with the object turnedon status
  */
BOOL object_get_turnedon(Object* object);

/**
  * @brief It sets wether the object can illuminate a space or not
  * @author Sergio Saúco
  *
  * 
  * @param object a pointer to the object
  * @param st a boolean with the status of illuminate
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS object_set_illuminate(Object* object, BOOL st);

/**
  * @brief It gets wether the object can illuminate a space or not
  * @author Sergio Saúco
  *
  * 
  * @param object a pointer to the object
  * @return TRUE, if the object can illuminate or FALSE, if there was some mistake
  * or the object can't illuminate
  */
BOOL object_get_illuminate(Object* object);


/**
  * @brief It sets the dependency of an object
  * @author Jorge Jiménez
  *
  * @param object a pointer to the object
  * @param dependency the id of the object that will be set as the dependency
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS object_set_dependency(Object* object, Id dependency);


/**
  * @brief It gets the dependency of an object
  * @author Jorge Jiménez
  *
  * @param object a pointer to the object
  * @return The id of the dependency or NO_ID if something went wrong
  */
Id object_get_dependency(Object* object);


#endif
