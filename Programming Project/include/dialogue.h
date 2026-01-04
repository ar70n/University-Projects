/**
 * @brief It defines the dialogue interface
 *
 * @file dialogue.h
 * @author Sergio Saúco
 * @version 1.0
 * @date 27-04-2023
 * @copyright GNU Public License
 */

#ifndef DIALOGUE_H
#define DIALOGUE_H

#include "command.h"
#include "types.h"
#include "game.h"

/**
 * @brief Dialogue
 *
 * Stores the information about
 * the dialogue (string with command result, previous 
 * command, previous command status, previous additional
 * information and previous player location)
 */
typedef struct _Dialogue Dialogue;

/**
  * @brief It creates a new dialogue, allocating memory and initializing its memebers
  * @author Sergio Saúco
  * 
  * @return a new dialogue, initialized
  */
Dialogue *dialogue_create();

/**
  * @brief It destroys a dialogue, freeing the allocated memory
  * @author Sergio Saúco
  * 
  * @param dialogue a pointer to the dialoguethat must be destroyed  
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS dialogue_destroy(Dialogue *dialogue);

/**
  * @brief It sets the command result of a command
  * @author Sergio Saúco
  * 
  * @param dialogue a pointer to the dialogue
  * @param name a string with the command result to store
  * @return OK, if everything goes well or ERROR if there was some mistake 
  */
STATUS dialogue_set_command_result(Dialogue *dialogue, char *information);
/**
  * @brief It gets the command result of a command
  * @author Sergio Saúco
  * 
  * @param dialogue a pointer to the dialogue
  * @return a string with the command result of a command
  */
char *dialogue_get_command_result(Dialogue *dialogue);

/**
  * @brief It sets the previous command
  * @author Sergio Saúco
  * 
  * @param dialogue a pointer to the dialogue
  * @param command the command to be set
  * @return OK, if everything goes well or ERROR if there was some mistake 
  */
STATUS dialogue_set_previous_command(Dialogue *dialogue, T_Command command);
/**
  * @brief It gets the previous command
  * @author Sergio Saúco
  * 
  * @param dialogue a pointer to the dialogue
  * @return the previois command
  */
T_Command dialogue_get_previous_command(Dialogue *dialogue);

/**
  * @brief It sets the previous command status
  * @author Sergio Saúco
  * 
  * @param dialogue a pointer to the dialogue
  * @param st the status to be set
  * @return OK, if everything goes well or ERROR if there was some mistake 
  */
STATUS dialogue_set_previous_command_status(Dialogue *dialogue, STATUS st);
/**
  * @brief It gets the previous command status
  * @author Sergio Saúco
  * 
  * @param dialogue a pointer to the dialogue
  * @return the previous command status
  */
STATUS dialogue_get_previous_command_status(Dialogue *dialogue);

/**
  * @brief It sets the previous additional information of a command input
  * @author Sergio Saúco
  * 
  * @param dialogue a pointer to the dialogue
  * @param information a string with the previous additional information
  * to be stored
  * @return OK, if everything goes well or ERROR if there was some mistake 
  */
STATUS dialogue_set_previous_additional_information(Dialogue *dialogue, char *information);
/**
  * @brief It gets the previous additional information of a command input
  * @author Sergio Saúco
  * 
  * @param dialogue a pointer to the dialogue
  * @return the previous additional infotmation of a command input
  */
char *dialogue_get_previous_additional_information(Dialogue *dialogue);

/**
  * @brief It sets the previous player location
  * @author Sergio Saúco
  * 
  * @param dialogue a pointer to the dialogue
  * @param player_location the player location to be set
  * @return OK, if everything goes well or ERROR if there was some mistake 
  */
STATUS dialogue_set_previous_player_location(Dialogue *dialogue, Id player_location);
/**
  * @brief It gets the previous player location
  * @author Sergio Saúco
  * 
  * @param dialogue a pointer to the dialogue
  * @return the id of the previous player location
  */
Id dialogue_get_previous_player_location(Dialogue *dialogue);

/**
  * @brief It prints the dialogue information
  * @author Sergio Saúco
  *
  * @param dialogue a pointer to the dialogue
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS dialogue_print(Dialogue *dialogue);

#endif
