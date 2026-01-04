/** 
 * @brief It implements the space module
 * 
 * @file space.c
 * @author Profesores PPROG
 * @version 2.0 
 * @date 29-11-2021 
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "space.h"

/**
 * @brief Space
 *
 * This struct stores all the information of a space.
 */
struct _Space {
  Id id;                                     /*!< Id number of the space, it must be unique */
  char name[WORD_SIZE + 1];                  /*!< Name of the space */
  Set* objects;                              /*!< Set of objects */
  char gdesc[LENGTH_GDESC][MAX_STR];         /*!< Space graphic description */
  char description[WORD_SIZE];               /*!< Description of the object */
  char detailed_desc[WORD_SIZE];             /*!< Detailed description of the space */
  BOOL light;                                /*!<  Light of the space */
};

/** space_create allocates memory for a new space
  * and initializes its members
  */
Space* space_create(Id id) {
  Space *newSpace = NULL;
  int i;

  /* Error control */
  if (id == NO_ID)
    return NULL;

  newSpace = (Space *) malloc(sizeof (Space));
  if (newSpace == NULL) {
    return NULL;
  }

  /* Initialization of an empty space*/
  newSpace->id = id;
  newSpace->name[0] = '\0';
  newSpace->description[0] = '\0';
  newSpace->light = TRUE;
  newSpace->objects = set_create();
  if(newSpace->objects == NULL)
  {
    return NULL;
  }
  for (i = 0; i < LENGTH_GDESC; i++) {
    newSpace->gdesc[i][0] = '\0';
  }

  return newSpace;
}

/** space_destroy frees the previous memory allocation 
  * for a space
  */
STATUS space_destroy(Space* space) {
  int i;

  if (!space) {
    return ERROR;
  }

  set_destroy(space->objects);

  for (i = 0; i < LENGTH_GDESC; i++) {
    space->gdesc[i][0] = '\0';
  }

  free(space);
  space = NULL;
  return OK;
}

/** space_get_id gets the id of a space
  */
Id space_get_id(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->id;
}

/** space_set_name sets the name of a space
  */
STATUS space_set_name(Space* space, char* name) {
  if (!space || !name) {
    return ERROR;
  }

  if (!strcpy(space->name, name)) {
    return ERROR;
  }
  return OK;
}

/** space_get_name gets the name of a space
  */
const char * space_get_name(Space* space) {
  if (!space) {
    return NULL;
  }
  return space->name;
}


/** space_set_description sets the description of a space
  */
STATUS space_set_description(Space* space, char* desc) {
  if (!space || !desc) {
    return ERROR;
  }

  if (!strcpy(space->description, desc)) {
    return ERROR;
  }
  return OK;
}

/** space_get_description gets the description of a space
  */
char * space_get_description(Space* space) {
  if (!space) {
    return NULL;
  }
  return space->description;
}

/** space_set_detailed_desc sets the detailed description of a space
  */
STATUS space_set_detailed_desc(Space* space, char* desc) {
  if (!space || !desc) {
    return ERROR;
  }

  if (!strcpy(space->detailed_desc, desc)) {
    return ERROR;
  }
  return OK;
}

/** space_get_detailed_desc gets the detailed description of a space
  */
char * space_get_detailed_desc(Space* space) {
  if (!space) {
    return NULL;
  }
  return space->detailed_desc;
}

/** space_set_object adds the id of an object to the space
  */
STATUS space_set_object(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  if (set_add(space->objects,id)==ERROR) {
    return ERROR;
  }
  
  return OK;
}

/** space_unset_object unsets the id of the object in the space
  */
STATUS space_unset_object(Space *space, Id id) {

  if (!space || id == NO_ID) {
    return ERROR;
  }

  if (set_del(space->objects, id) == ERROR) {
    return ERROR;
  }

  return OK;
}

/** space_get_objects gets the id of the object in the space
  */
Id* space_get_objects(Space* space) {

  if (!space) {
    return NULL;
  }

  return set_get_ids(space->objects);
}

/** space_get_n_objects gets the number of the objects in the space
 */
int space_get_n_objects(Space *space){
  if(!space){
    return -1;
  }

  return set_get_n_ids(space->objects);
}

/** space_set_gdesc sets the graphic description of a space
 */
STATUS space_set_gdesc(Space *space, char (*desc)[MAX_STR]) {
  int i;

  if (!space || !desc) {
    return ERROR;
  }

  for (i = 0; i < LENGTH_GDESC; i++) {
    strcpy(space->gdesc[i], desc[i]);
  }

  return OK;
}
/** space_get_gdesc_row gets the graphic description of a space
 */
char* space_get_gdesc_row(Space *space, int row) {
  if (!space || row < 1) {
    return NULL;
  }
  row = row -1;

  return space->gdesc[row];
}

/** space_search_object searchs if an object is in the space
 */
BOOL space_search_object(Space* space, Id id) {
  Id* ids;
  int i;

  if (!space || id == NO_ID) {
    return FALSE;
  }

  ids = set_get_ids(space->objects);
  if (ids == NULL)
  {
    return FALSE;
  }

  for(i = 0; i < MAX_IDS; i++)
  {
    if (id == ids[i])
    {
      return TRUE;
    }
  }
  return FALSE;
}

/** space_set_light sets the light of a space
  */
STATUS space_set_light(Space* space, BOOL st) {
  if (!space) {
    return ERROR;
  }
  
  space->light = st;
  
  return OK;
}

/** space_get_light gets the light of a space
  */
BOOL space_get_light(Space* space) {
  if (!space) {
    return FALSE;
  }
  return space->light;
}



/** space_print prints the space information
  */
STATUS space_print(Space* space) {
  Id* idaux2 = NULL;
  int i, flag;

  /* Error Control */
  if (!space) {
    return ERROR;
  }

  /* 1. Print the id, the name and the description of the space */
  fprintf(stdout, "--> Space (Id: %ld; Name: %s; Description: %s;Light: %d)\n", space->id, space->name, space->description, (int)space->light);

  /* 2. Print the id of the object */
  idaux2 = space_get_objects(space);
  if (NULL != idaux2) {
    fprintf(stdout,"--> Objects: \n");
    set_print(space->objects);
  } else {
    fprintf(stdout, "---> No objects in space.\n");
  }

  /* 4. Print the graphic description */
  for (i = 1, flag = 0; i <= LENGTH_GDESC && flag == 0; i++) {
    if (space_get_gdesc_row(space, i) == NULL) {
      flag = 1;
    }
    if (strcmp("\0", space_get_gdesc_row(space, i)) == 0) {
      flag = 1;
    }
  }
  if (flag == 0) {
    fprintf(stdout, "---> Graphic description: \n");
    for (i = 1; i <= LENGTH_GDESC; i++) {
      fprintf(stdout, "%s\n", space_get_gdesc_row(space, i));
    }
  } else {
    fprintf(stdout, "---> No graphic description of the space.\n");
  }

  return OK;
}

