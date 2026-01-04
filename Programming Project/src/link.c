/** 
 * @brief It implements the link module
 * 
 * @file link.c
 * @author Antonio Moroño
 * @version 1.0 
 * @date 20-3-2023 
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "link.h"

/**
 * @brief Link
 *
 * This struct stores all the information of a link.
 */
struct _Link {
  Id id;                                     /*!< Id number of the link, it must be unique */
  char name[WORD_SIZE + 1];                  /*!< Name of the link */
  Id origin;                                 /*!< Id of the origin space */
  Id destination;                            /*!< Id of the destination space */
  DIRECTION direction;                       /*!< Link's direction */
  CONNECTION status;                         /*!< Determines the links status */
};

/** link_create allocates memory for a new link
  * and initializes its members
  */
Link* link_create(Id id) {
  Link *newLink = NULL;
 
  /* Error control */
  if (id == NO_ID){
    return NULL;
  }

  newLink = (Link *) malloc(sizeof (Link));
  if (newLink == NULL) {
    return NULL;
  }

  /* Initialization of an empty link*/
  newLink->id = id;
  newLink->name[0] = '\0';
  newLink->origin = NO_ID;
  newLink->destination = NO_ID;
  newLink->direction = I;
  newLink->status = CLOSE;

  return newLink;
}

/** link_destroy frees the previous memory allocation 
  * for a link
  */
STATUS link_destroy(Link* link) {

  if (!link) {
    return ERROR;
  }

  free(link);
  link = NULL;
  return OK;
}

/** link_get_id gets the id of a link
  */
Id link_get_id(Link* link) {
  if (!link) {
    return NO_ID;
  }
  return link->id;
}

/** link_set_name sets the name of a link
  */
STATUS link_set_name(Link* link, char* name) {
  if (!link || !name) {
    return ERROR;
  }

  if (!strcpy(link->name, name)) {
    return ERROR;
  }
  return OK;
}
/** link_get_name gets the link of a link
  */
const char * link_get_name(Link* link) {
  if (!link) {
    return NULL;
  }
  return link->name;
}


/** link_set_origin sets the origin of a link
  */
STATUS link_set_origin(Link* link, Id origin) {
 if (!link)
 {
   return ERROR;
 }
  link->origin = origin;
  return OK;
}

/** link_get_origin gets the origin of a link
  */
Id link_get_origin(Link* link) {
  if (!link)
  {
    return NO_ID;
  }
  return link->origin;
}

/** link_set_destination sets the destination of a link
  */
STATUS link_set_destination(Link* link, Id destination) {
 if (!link)
 {
   return ERROR;
 }
  link->destination = destination;
  return OK;
}

/** link_get_destination gets the destination of a link
  */
Id link_get_destination(Link* link) {
  if (!link)
  {
    return NO_ID;
  }
  return link->destination;
}

/** link_set_direction sets the direction of a link
  */
STATUS link_set_direction(Link* link, DIRECTION direction) {
 if (!link)
 {
   return ERROR;
 }
  link->direction = direction;
  return OK;
}

/** link_get_direction gets the direction of a link
  */
DIRECTION link_get_direction(Link* link) {
  if (!link)
  {
    return I;
  }
  return link->direction;
}



/** link_set_connection sets the connection of a link
  */
STATUS link_set_status(Link* link, CONNECTION status) {
 if (!link)
 {
   return ERROR;
 }
  link->status = status;
  return OK;
}

/** link_get_connection gets the status of a link
  */
CONNECTION link_get_status(Link* link) {
  if (!link)
  {
    return NO_ID;
  }
  return link->status;
}


/** link_print prints the link information
  */
STATUS link_print(Link* link) {
  
  /* Error Control */
  if (!link) {
    return ERROR;
  }
  fprintf(stdout, "--> Link (Id: %ld; Name: %s)\n", link->id, link->name);
  fprintf(stdout, "--> Link (Origin: %ld; Destination: %ld)\n", link->origin, link->destination);
  fprintf(stdout, "--> Link (Direction: %d; Status: %d)\n", link->direction, link->status);
  
 
  return OK;
}