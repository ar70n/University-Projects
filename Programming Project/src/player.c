/** 
 * @brief It implements the player module
 * 
 * @file player.c
 * @author Sergio Saúco
 * @version 1.0 
 * @date 06-02-2023
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"
#include "inventory.h"

/**
 * @brief Player
 *
 * This struct stores all the information of a player.
 */
struct _Player {
  Id id;                       /*!< Id number of the player, it must be unique */
  char name[WORD_SIZE + 1];    /*!< Name of the player */
  Id location;                 /*!< Id of the player's location */
  Inventory *objects;          /*!< Id's of the objects carried by the player */
  short health;                /*!< Player's health points */
  short power;                 /*!< The hp the player takes if the attack is successful */
};

/** player_create allocates memory for a new player
  * and initializes its members
  */
Player* player_create(Id id) {
  Player *newPlayer = NULL;

  /* Error control */
  if (id == NO_ID)
    return NULL;

  newPlayer = (Player *) malloc(sizeof (Player));
  if (newPlayer == NULL) {
    return NULL;
  }

  /* Initialization of an empty player*/
  newPlayer->id = id;
  newPlayer->name[0] = '\0';
  newPlayer->location = NO_ID;
  newPlayer->objects = inventory_create();
  if (newPlayer->objects == NULL) {
    return NULL;
  }
  newPlayer->health = -1;
  newPlayer->power = 0;

  return newPlayer;
}

/** player_destroy frees the previous memory allocation 
  * for a player
  */
STATUS player_destroy(Player* player) {
  if (!player) {
    return ERROR;
  }

  inventory_destroy(player->objects);
  free(player);
  player = NULL;
  return OK;
}

/** player_get_id gets the id of a player
  */
Id player_get_id(Player* player) {
  if (!player) {
    return NO_ID;
  }
  return player->id;
}

/** player_set_name sets the name of a player
  */
STATUS player_set_name(Player* player, char* name) {
  if (!player || !name) {
    return ERROR;
  }

  if (!strcpy(player->name, name)) {
    return ERROR;
  }
  return OK;
}
/** player_set_name gets the name of a player
  */
const char* player_get_name(Player* player) {
  if (!player) {
    return NULL;
  }
  return player->name;
}

/** player_set_location sets the id of the player's location
  */
STATUS player_set_location(Player* player, Id id) {
  if (!player) {
    return ERROR;
  }
  player->location = id;
  return OK;
}
/** player_get_location gets the id of the player's location
  */
Id player_get_location(Player* player) {
  if (!player) {
    return NO_ID;
  }
  return player->location;
}

/** player_add_object_to_inventory adds 
  * an id of an object to the player's inventory
  */
STATUS player_add_object_to_inventory(Player* player, Id id) {
  if (!player || id == NO_ID) {
    return ERROR;
  }
  if (inventory_add_object(player->objects, id) == ERROR) {
    return ERROR;
  }
  return OK;
}
/** player_del_object_from_inventory deletes
  * an id of an object from the player's inventory
  */
STATUS player_del_object_from_inventory(Player* player, Id id) {
  if (!player || id == NO_ID) {
    return ERROR;
  }
  if (inventory_del_object(player->objects, id) == ERROR) {
    return ERROR;
  }
  return OK;
}

/** player_get_objects gets the id's of the objects carried by the player
  */
Id* player_get_objects(Player* player) {
  Id *player_objects = NULL;
  if (!player) {
    return NULL;
  }
  player_objects = inventory_get_objects(player->objects);
  if (player_objects == NULL) {
    return NULL;
  }
  return player_objects;
}
/** player_inventory_stores checks wether the player inventory stores
  * an object or not
  */
BOOL player_inventory_stores(Player* player, Id id) {
  if (!player || id == NO_ID) {
    return FALSE;
  }
  if (inventory_stores_object(player->objects, id) == FALSE) {
    return FALSE;
  }
  else {
    return TRUE;
  }
}

/** player_get_n_objects gets the number of objects
  * carried by the player
  */
long player_get_n_objects(Player *player) {
  long number_objects = -1;
  if (!player) {
    return -1;
  }
  number_objects = inventory_get_n_objects(player->objects);
  if (number_objects == -1) {
    return -1;
  } 
  return number_objects;
}

/** player_set_health sets the player's health
  */
STATUS player_set_health(Player *player, short health) {
  if (health < 0 || !player) {
    return ERROR;
  }

  player->health = health;

  return OK;
}
/** player_get_health gets player's health
  */
short player_get_health(Player *player) {
  if (player==NULL)
  {
    return -1;
  }
  else{
    return player->health;
  }
}

/** player_set_power sets the player's power
  */
STATUS player_set_power(Player *player, short power) {
  if (power < 0 || !player) {
    return ERROR;
  }

  player->power = power;

  return OK;
}

/** player_get_power gets player's power
  */
short player_get_power(Player *player) {
  if (player==NULL)
  {
    return -1;
  }
  else{
    return player->power;
  }
}

/** player_print prints the player information
  */
STATUS player_print(Player* player) {
  Id idaux = NO_ID;
  short aux_health = -1;
  int n_ids;

  /* Error Control */
  if (!player) {
    return ERROR;
  }

  /* 1. Print the id and the name of the player */
  fprintf(stdout, "--> Player (Id: %ld; Name: %s)\n", player->id, player->name);
 
  /* 2. Print the id of the location where the player is located */ 
  idaux = player_get_location(player);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> Id player's location: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No player's location id.\n");
  }

  /* 3. Print the players's health points */
  aux_health = player_get_health(player);
  if (aux_health == -1)
  {
    fprintf(stdout, "---> No player\n");
  }
  else
  {
    fprintf(stdout, "---> Player health: %d.\n", aux_health);
  }

  /* 4. Print the id's of the objects carried by the player */
  n_ids = player_get_n_objects(player);
  if (0 != n_ids) {
    fprintf(stdout, "---> Objects: \n");
    inventory_print(player->objects);
  } else {
    fprintf(stdout, "---> No objects carried by the player.\n");
  }

  return OK;
}

/** player_get_inventory returns the inventory of the player
  */
Inventory *player_get_inventory(Player *player){
  if (player==NULL)
  {
    return NULL;
  }

  return player->objects;
}



