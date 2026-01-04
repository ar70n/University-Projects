/**
 * @brief It defines the game interface
 *
 * @file game.h
 * @author Profesores PPROG
 * @version 2.0
 * @date 29-11-2021
 * @copyright GNU Public License
 */

#ifndef GAME_H
#define GAME_H

#define MAX_DESCRIPTIONS 1 /*!< The maximum number of inspect descriptions to be shown */

#include "command.h"
#include "space.h"
#include "types.h"
#include "object.h"
#include "player.h"
#include "enemy.h"
#include "link.h"
#include "dialogue.h"



/**
 * @brief Game
 *
 * Stores the information about
 * the game (objects, player, spaces,
 * links, enemy, command input, status
 * command input, descriptions and dialogue)
 */
typedef struct _Game Game;

/**
  * @brief It creates the game
  * @author Profesores PPROG
  *
  * @param game a pointer to the game that must be created
  * @return OK
  */
STATUS game_create(Game *game);

/**
  * @brief It creates a game from a specific file
  * @author Profesores PPROG
  *
  * @param game a pointer to the game that must be created
  * @param filename a string with the name of the file
  * @return ERROR, if there's an error creating the game or loading the spaces for the game, or OK if everything goes well
  */
STATUS game_create_from_file(Game *game, char *filename);


/**
  * @brief It updates the status of the game
  * @author Profesores PPROG
  *
  * @param game a pointer to the game that must be updated
  * @param cmd a command
  * @param aditional_information the information needed by some commands
  * @return OK
  */
STATUS game_update(Game *game, T_Command cmd, char *aditional_information);

/**
  * @brief It destroys the game
  * @author Profesores PPROG
  *
  * @param game a pointer to the game that must be destroyed
  * @return OK
  */
STATUS game_destroy(Game *game);

/**
  * @brief It gets the game over
  * @author Profesores PPROG
  *
  * @param game a pointer to the game that is over
  * @return a boolean (FALSE)
  */
BOOL game_is_over(Game *game);

/**
  * @brief It prints the data of the game
  * @author Profesores PPROG
  *
  * @param game a pointer to the game that must get its data printed
  * @return OK, if everything goes well or ERROR if there was some mistake 
  */
STATUS game_print_data(Game *game);

/**
  * @brief It gets the space for the game
  * @author Profesores PPROG
  *
  * @param game a pointer to the game that must get the space
  * @param id the identification number for the space
  * @return NULL, if there's no id or it doesn't get space, or the spaces for the game if everything goes well
  */
Space *game_get_space(Game *game, Id id);

/**
  * @brief It gets the location of the player
  * @author Profesores PPROG
  *
  * @param game a pointer to the game that must get the player's location 
  * @return the player's location
  */
Id game_get_player_location(Game *game);

/**
  * @brief It gets the location of an object
  * @author Sergio Saúco
  *
  * @param game a pointer to the game that must get the object's location 
  * @param id the identification number for the object
  * @return the object's location
  */
Id game_get_object_location(Game *game, Id id);

/**
  * @brief It gets the location of the enemy
  * @author Sergio Saúco
  *
  * @param game a pointer to the game that must get the enemy's location 
  * @param index the index of the enemy in the array
  * @return the enemy's location
  */
Id game_get_enemy_location(Game *game, int index);

/**
  * @brief It gets the health of the player
  * @author Sergio Saúco
  *
  * @param game a pointer to the game that must get the player's health 
  * @return the player's health
  */
short game_get_player_health(Game *game);

/**
  * @brief It gets the health of the enemy
  * @author Sergio Saúco
  *
  * @param game a pointer to the game that must get the enemy's health 
  * @param index the index of the enemy in the array
  * @return the enemy's health
  */
short game_get_enemy_health(Game *game, int index);

/**
  * @brief It sets the last command of the game
  * @author Sergio Saúco
  *
  * @param game a pointer to the game that must set the game's last command
  * @param last_command the last command to be set
  * @return OK, if everything goes well or ERROR if there was some mistake 
  */
STATUS game_set_last_command(Game *game, T_Command last_command);

/**
  * @brief It gets the last command of the game
  * @author Profesores PPROG
  *
  * @param game a pointer to the game that must get the game's last command
  * @return the game's last command
  */
T_Command game_get_last_command(Game *game);

/**
  * @brief It gets the status of last command introduced in the game 
  * @author Sergio Saúco
  * 
  * @param game a pointer to the game that must get the game's last command status
  * @return the game's last command status
  */
STATUS game_get_last_command_status(Game *game);

/**
  * @brief It adds space to the game
  * @author Profesores PPROG
  *
  * @param game a pointer to the game that must get space added
  * @param space a pointer to the space that will be added
  * @return STATUS to inform if the function had any errors
  */
STATUS game_add_space(Game *game, Space *space);

/**
  * @brief It adds link to the game
  * @author Sergio Saúco
  *
  * @param game a pointer to the game that must get link added
  * @param link a pointer to the link that will be added
  * @return OK or ERROR if there was some mistake
  */
STATUS game_add_link(Game *game, Link *link);

/**
  * @brief It adds an object to the game
  * @author Profesores PPROG
  *
  * @param game a pointer to the game that must get an object added
  * @param object a pointer to the object that will be added
  * @param location the id of the space where the object will be located
  * @return OK or ERROR if there was some mistake
  */
STATUS game_add_object(Game *game, Object *object, Id location);

/**
  * @brief It sets the player of the game
  * @author Sergio Saúco
  *
  * @param game a pointer to the game that must set the player
  * @param player a pointer to the player that will be set
  * @return OK, if everything goes well or ERROR if there was some mistake 
  */
STATUS game_set_player(Game *game, Player *player);

/**
  * @brief It adds an enemy to the game
  * @author Miguel Campo
  *
  * @param game a pointer to the game that must get an enemy added
  * @param enemy a pointer to the enmey that will be added
  * @return OK, if everything goes well or ERROR if there was some mistake 
  */
STATUS game_add_enemy(Game *game, Enemy *enemy);

/**
  * @brief It gets all spaces ids in the game
  * @author Antonio Moroño
  *
  * @param game a pointer to the game that must get the spaces ids
  * @param ids a pointer to the array of ids 
  * @return OK or ERROR if there was some mistake
  */
STATUS game_get_all_space_ids(Game *game,Id* ids);

/**
  * @brief It gets an array of the objects ids in the game
  * @author Antonio Moroño
  *
  * @param game a pointer to the game that must get the spaces ids
  * @param objects a pointer to the array of ids 
  * @return OK or ERROR if there was some mistake
  */
STATUS game_get_objects(Game *game,Id* objects);

/**
  * @brief It gets a pointer to the player on a game
  * @author Miguel Campo
  *
  * @param game a pointer to the game that must get the player id
  * @return Pointer to the player in the game
  */
Player* game_get_player(Game* game);

/**
  * @brief It gets a pointer to the enemy on a game
  * @author Miguel Campo
  *
  * @param game a pointer to the game that must get the enemy id
  * @param index the index of the enemy in the array
  * @return Pointer to the enemy in the game
  */
Enemy* game_get_enemy(Game *game, int index);

/**
  * @brief It gets a pointer to a requested object on a game, based on an index
  * @author Miguel Campo
  *
  * @param game a pointer to the game that must get the object id
  * @param index the position of the requested object in the set
  * @return Pointer to the requested object in the game
  */
Object* game_get_object(Game *game, int index);

/**
  * @brief It sets the last command status
  * @author Jorge Jiménez
  *
  * @param game a pointer to the game where the status must be changed
  * @param status the status to be set
  * @return OK or ERROR if there was some mistake
  */
STATUS game_set_last_command_status(Game *game, STATUS status);

/**
  * @brief It sets the last description
  * @author Sergio Saúco
  *
  * @param game a pointer to the game where the description will be changed
  * @param description the description to be included as last description
  * @return OK or ERROR if there was some mistake
  */
STATUS game_set_last_description(Game *game, char *description);

/**
  * @brief It gets the description
  * @author Sergio Saúco
  *
  * @param game a pointer to the game where the description will be obtained
  * @param desc_to_get the index of the description in the array
  * @return Requested description
  */
char *game_get_description(Game *game, int desc_to_get);

/**
  * @brief It gets the number of descriptions
  * @author Sergio Saúco
  *
  * @param game a pointer to the game where the number of descriptions will be obtained
  * @return Number of descriptions
  */
int game_get_n_descriptions(Game *game);

/**
  * @brief It creates a game, allocationg memory for it
  * @author Sergio Saúco
  *
  * @return Initialized game
  */
Game *game_init();

/**
  * @brief Returns wether a link from a space with a determined direction is open or closed
  * @author Jorge Jiménez
  *
  * @param g a pointer to the game in whose spaces we will search the connection
  * @param space_id the id of the space in which we want to look for the status of the link with direction "direction"
  * @param direction the id of the space in which we want to look for the status of the link with direction "direction"
  * @return The connection status or -1 if there was some error
  */
CONNECTION game_get_connection_status(Game *g, Id space_id, DIRECTION direction);

/**
  * @brief It gets a connection
  * @author Sergio Saúco
  * 
  * Returns the id of the space connected to the space with id space_id by a direction
  * Returns NO_ID in case of error
  * 
  * @param g a pointer to the game in whose spaces we will search the connection
  * @param space_id the id of the space in which we want to look for the connection
  * @param direction the id of the space in which we want to look for the connection with direction "direction"
  * @return id of the other space in the connection
  */
Id game_get_connection(Game *g, Id space_id, DIRECTION direction);

/**
  * @brief It determinates if a connection exists
  * @author Miguel Campo
  * 
  * @param game a pointer to the game in whose spaces we will search the connection
  * @param space the id of the space in which we want to look for the connection
  * @param direction the id of the space in which we want to look for the connection with direction "direction"
  * @return TRUE if th connection exists, FALSE if not
  */
BOOL game_link_exists(Game *game, Id space, DIRECTION direction);

/**
  * @brief It gets the name of an object with its id
  * @author Miguel Campo
  * 
  * @param game a pointer to the game that contains the object
  * @param id the id of the object
  * @return the name of the object
  */
char *game_object_id_to_name(Game *game, Id id);

/**
  * @brief It gets an object from an id
  * @author Jorge Jiménez
  * 
  * @param game a pointer to the game that contains the object
  * @param id the id of the object
  * @return the object
  */
Object *game_get_object_from_id(Game *game, Id id);

/**
  * @brief It gets the space from a game with some index
  * @author Miguel Campo
  * 
  * @param game a pointer to the game that contains the space
  * @param index index of the space
  * @return the space
  */
Space* game_get_space_from_index(Game *game, int index);

/**
  * @brief It gets the link from a game with some index
  * @author Miguel Campo
  * 
  * @param game a pointer to the game that contains the link
  * @param index index of the link
  * @return the link
  */
Link* game_get_link_from_index(Game *game, int index);

/**
  * @brief It gets the description of the space
  * @author Sergio Saúco
  * 
  * @param game a pointer to the game that gets the description
  * @param space_id the id of the space
  * @return the detailed description of the space
  */
char *game_get_space_description(Game *game, Id space_id);

/**
  * @brief It gets the name of the space
  * @author Sergio Saúco
  * 
  * @param game a pointer to the game that gets the name
  * @param space_id the id of the space
  * @return the name of the space
  */
const char *game_get_space_name(Game *game, Id space_id);

/**
  * @brief It gets the dialogue string with command result
  * @author Sergio Saúco
  * 
  * @param game a pointer to the game that gets the command result
  * @return the command result string
  */
char *game_get_dialogue_command_result(Game *game);

/**
  * @brief It gets wether the player has a turnedon object to illuminate
  * @author Jorge Jimenez
  * 
  * @param game a pointer to the game
  * @return if player has a turned on object that can illuminate the space he is in
  */
BOOL game_player_can_illuminate(Game *game);

#endif
