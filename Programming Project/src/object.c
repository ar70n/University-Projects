/** 
 * @brief It determines the characteristics of an object, i.e. its name, its description, whether it can change location, etc. 
 * @file object.c
 * @author Antonio Moroño
 * @version 1.0
 * @date 06-02-2023 
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "object.h"

/**
 * @brief Object
 *
 * This struct stores all the information of an object.
 */
struct _Object {
  Id id;                              /*!< Id number of the object, it must be unique */
  char name[WORD_SIZE + 1];           /*!< Name of the object */
  char description[WORD_SIZE];       /*!< Description of the object */
  Id open;                            /*!< Id of the link the object unlocks*/
  Id dependency;                      /*!< Id of the object needed to take this one */
  BOOL movable;                       /*!< Determines whether the object is movable */
  BOOL hidden;                        /*!< Determines whether the object is hidden */
  BOOL turnedon;                      /*!< Determines whether the object is turnedon */
  BOOL illuminate;                    /*!< Determines whether the object can illuminate an space */
};

/** object_create allocates memory for a new object
  * and initializes its members
  */
Object* object_create(Id id) {
  Object *newObject = NULL;

  /* Error control */
  if (id == NO_ID)
    return NULL;

  newObject = (Object *) malloc(sizeof (Object));
  if (newObject == NULL) {
    return NULL;
  }

  /* Initialization of an empty object*/
  newObject->id = id;
  newObject->name[0] = '\0';
  newObject->description[0] = '\0';
  newObject->open = NO_ID;
  newObject->dependency = NO_ID;
  newObject->movable = FALSE;
  newObject->hidden = TRUE;
  newObject->turnedon = FALSE;
  newObject->illuminate = FALSE;
  return newObject;
}
/** object_destroy frees the previous memory allocation 
  * for an object
  */
STATUS object_destroy(Object* object)
{
  if (!object) {
    return ERROR;
  }

  free(object);
  object = NULL;
  return OK;

}

/** object_get_id gets the id of an object
  */
Id object_get_id(Object* object) {
  if (!object) {
    return NO_ID;
  }
  return object->id;
}

/* object_get_open gets the id of the link opened by the object
  */
Id object_get_open(Object* object) {
  if (!object) {
    return NO_ID;
  }
  return object->open;
}

/* object_set_open sets the link ob the id unlocked by the object*/
STATUS object_set_open(Object* object, Id id) {
  if (!object) {
    return ERROR;
  }

  object->open = id;

  return OK;
}

/** object_set_name sets the name of an object
  */
STATUS object_set_name(Object* object, char* name) {
  if (!object || !name) {
    return ERROR;
  }

  if (!strcpy(object->name, name)) {
    return ERROR;
  }
  return OK;
}

/** object_get_name gets the name of an object
  */
char * object_get_name(Object* object) {
  if (!object) {
    return NULL;
  }
  return object->name;
}

/** object_set_description sets the description of an object
  */
STATUS object_set_description(Object* object, char* desc) {
  if (!object || !desc) {
    return ERROR;
  }

  if (!strcpy(object->description, desc)) {
    return ERROR;
  }
  return OK;
}

/** object_get_description gets the description of an object
  */
char* object_get_description(Object* object) {
  if (!object) {
    return NULL;
  }
  return object->description;
}


STATUS object_set_dependency(Object* object, Id dependency){
  if(!object || dependency == NO_ID){
    return ERROR;
  }

  object->dependency = dependency;
  return OK;
}


Id object_get_dependency(Object* object){
  if(!object){
    return NO_ID;
  }

  return object->dependency;
}


/** object_set_movable sets the movility of an object 
  */
STATUS object_set_movable(Object* object, BOOL st) {
  if (!object) {
    return ERROR;
  }

  object->movable = st;
  
  return OK;
}

/** object_get_movable gets the movility of an object
  */
BOOL object_get_movable(Object* object) {
  if (!object) {
    return FALSE;
  }
  return object->movable;
}

/** object_set_hidden sets wether 
  * the object is hidden or not
  */
STATUS object_set_hidden(Object* object, BOOL st) {
  if (!object) {
    return ERROR;
  }

  object->hidden = st;

  return OK;
}

/** object_get_hidden gets wether 
  * the object is hidden or not
  */
BOOL object_get_hidden(Object* object) {
  if (!object) {
    return TRUE;
  }
  return object->hidden;
}

/** object_set_turnedon sets the turnedon of an object 
  */
STATUS object_set_turnedon(Object* object, BOOL st) {
  if (!object) {
    return ERROR;
  }

  object->turnedon = st;
  
  return OK;
}

/** object_get_turnedon gets the turnedon of an object
  */
BOOL object_get_turnedon(Object* object) {
  if (!object) {
    return FALSE;
  }
  return object->turnedon;
}

/** object_set_illuminate sets wether the object 
  * can illuminate a space or not
  */
STATUS object_set_illuminate(Object* object, BOOL st) {
  if (!object) {
    return ERROR;
  }

  object->illuminate = st;

  return OK;
}

/** object_get_illuminate gets wether the object 
  * can illuminate a space or not
  */
BOOL object_get_illuminate(Object* object) {
  if (!object) {
    return FALSE;
  }
  return object->illuminate;
}

/** object_print prints the object information
  */
STATUS object_print(Object* object) {
  char *desc = NULL;
  Id open = NO_ID, dependency = NO_ID;
  BOOL movable = FALSE, hidden = TRUE, turnedon = FALSE, illuminate = FALSE;
  

  /* Error Control */
  if (!object) {
    return ERROR;
  }

  /* Print the id and the name of the object */
  fprintf(stdout, "--> Object (Id: %ld; Name: %s)\n", object->id, object->name);

  /* Print the description of the object */
  desc = object_get_description(object);
  if (desc != NULL) {
    fprintf(stdout, "--> Description: %s\n", desc);
  }
  else {
    fprintf(stdout, "--> No description \n");
  }

  /* Print the id of the link that the object can open */
  open = object_get_open(object);
  if (open != NO_ID) {
    fprintf(stdout, "The object can open the link with id: %ld\n", open);
  }
  else {
    fprintf(stdout, "The object can't open any links\n");
  }
  
  dependency = object_get_dependency(object);
  if (dependency != NO_ID) {
    fprintf(stdout, "The object depends on the object with id: %ld\n", dependency);
  }
  else {
    fprintf(stdout, "The object doesn't depend on any objects\n");
  }

  /* Print the movility of the object */
  movable = object_get_movable(object);
  if (movable == TRUE) {
    fprintf(stdout, "The object is movable\n");
  }
  else {
    fprintf(stdout, "The object is not movable\n");
  }

  /* Print the wether the object is hidden */
  hidden = object_get_hidden(object);
  if (hidden == TRUE) {
    fprintf(stdout, "The object is hidden\n");
  }
  else {
    fprintf(stdout, "The object is not hidden\n");
  }

  /* Print the wether the object can illuminate */
  illuminate = object_get_illuminate(object);
  if (illuminate == TRUE) {
    fprintf(stdout, "The object can illuminate spaces\n");
  }
  else {
    fprintf(stdout, "The object can't illuminate spaces\n");
  }

  /* Print the if the object is turned on or turned off */
  turnedon = object_get_turnedon(object);
  if (turnedon == TRUE) {
    fprintf(stdout, "The object is turned on\n");
  }
  else {
    fprintf(stdout, "The object is turned off\n");
  }


  return OK;
}
