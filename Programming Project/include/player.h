/**
 * @brief It defines the player interface
 *
 * @file player.h
 * @author Sergio Saúco
 * @version 1.0
 * @date 06-02-2023
 * @copyright GNU Public License
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "types.h"
#include "inventory.h"

/**
 * @brief Player
 *
 * Stores the information about
 * the player (id, name, location, objects and
 * health)
 */
typedef struct _Player Player;


/**
  * @brief It creates a new player, allocating memory and initializing its memebers
  * @author Sergio Saúco
  * 
  * @param id the identification number for the new player
  * @return a new player, initialized
  */
Player* player_create(Id id);

/**
  * @brief It destroys a player, freeing the allocated memory
  * @author Sergio Saúco
  * 
  * @param player a pointer to the player that must be destroyed  
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS player_destroy(Player* player);

/**
  * @brief It gets the id of a player
  * @author Sergio Saúco
  * 
  * @param player a pointer to the player  
  * @return the id of player
  */
Id player_get_id(Player* player);

/**
  * @brief It sets the name of a player
  * @author Sergio Saúco
  * 
  * @param player a pointer to the player
  * @param name a string with the name to store
  * @return OK, if everything goes well or ERROR if there was some mistake 
  */
STATUS player_set_name(Player* player, char* name);
/**
  * @brief It gets the name of a player
  * @author Sergio Saúco
  * 
  * @param player a pointer to the player
  * @return  a string with the name of the player
  */
const char* player_get_name(Player* player);

/**
  * @brief It sets the id of the player's location
  * @author Sergio Saúco
  * 
  * @param player a pointer to the player
  * @param id the id number of the player's location
  * @return OK, if everything goes well or ERROR if there was some mistake 
  */
STATUS player_set_location(Player* player, Id id);
/**
  * @brief It gets the id of the player's location
  * @author Sergio Saúco
  *
  * @param player a pointer to the player
  * @return the id number of the player's location
  */
Id player_get_location(Player* player);

/**
  * @brief It adds an id of an object to the player's inventory
  * @author Sergio Saúco
  *
  * @param player a pointer to the player
  * @param id the identification number of the object
  * @return OK, if everything goes well or ERROR if there was some mistake 
  */
STATUS player_add_object_to_inventory(Player* player, Id id);
/**
  * @brief It deletes an id of an object from the player's inventory
  * @author Sergio Saúco
  *
  * @param player a pointer to the player
  * @param id the identification number of the object
  * @return OK, if everything goes well or ERROR if there was some mistake 
  */
STATUS player_del_object_from_inventory(Player* player, Id id);

/**
  * @brief It gets the id's of the objects carried by the player
  * @author Sergio Saúco
  *
  * @param player a pointer to the player
  * @return the id number of the object
  */
Id* player_get_objects(Player* player);
/**
  * @brief It checks wether the player inventory stores
  * an object or not
  * @author Sergio Saúco
  *
  * @param player a pointer to the player
  * @param id the identification number of the object
  * @return TRUE, if the inventory stores the object
  * or FALSE otherwise
  */
BOOL player_inventory_stores(Player* player, Id id);

/**
  * @brief It gets the number of objects carried by the player
  * @author Sergio Saúco
  *
  * @param player a pointer to the player
  * @return the number of objects or -1 if there was some mistake
  */
long player_get_n_objects(Player *player);

/**
  * @brief It sets the player's health
  * @author Antonio Moroño
  *
  * @param player a pointer to the player
  * @param health the helth points to be set
  * @return OK, if everything goes well or ERROR if there was some mistake 
  */
STATUS player_set_health(Player *player, short health);

/**
  * @brief It gets the player's health
  * @author Antonio Moroño
  *
  * @param player a pointer to the player
  * @return short player's health, if everything goes well or -1 if there was some mistake
  */
short player_get_health(Player *player);

/**
  * @brief It prints the player information
  * @author Sergio Saúco
  *
  * This fucntion shows the id and name of the player, the id of the location where the player is located
  * and the id's of the objects carried by the player.
  * @param player a pointer to the player
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS player_print(Player* player);

/**
  * @brief It gets the inventory from the player
  * @author Sergio Saúco
  *
  * @param player a pointer to the player
  * @return pointer to the player's inventory
  */
Inventory *player_get_inventory(Player *player);

/**
  * @brief It sets the player's power
  * @author Miguel Campo
  *
  * @param player a pointer to the player
  * @param power the power points to be set
  * @return OK, if everything goes well or ERROR if there was some mistake 
  */
STATUS player_set_power(Player *player, short power);

/**
  * @brief It gets the player's power
  * @author Miguel Campo
  *
  * @param player a pointer to the player
  * @return short player's power, if everything goes well or -1 if there was some mistake
  */
short player_get_power(Player *player);

#endif
