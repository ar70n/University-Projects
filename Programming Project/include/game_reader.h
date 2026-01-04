/**
 * @brief It defines the functions needed to read file or files with the program configuration, i.e. to initialize the game (create the player, spaces, objects, etc.).
 *
 * @file game_reader.h
 * @author Antonio Moroño
 * @version 2.0
 * @date 03-03-2023
 * @copyright GNU Public License
 */

#ifndef GAME_READER_H
#define GAME_READER_H

#include "command.h"
#include "space.h"
#include "types.h"
#include "game.h"
#include "link.h"



/**
  * @brief It loads spaces to the game from a file
  * @author Antonio Moroño
  *
  * @param game a pointer to the game where the spaces are loaded
  * @param filename string to the filename with the spaces 
  * @return OK
  */
STATUS game_reader_load_spaces(Game *game, char *filename);

/**
  * @brief It loads objects to the game from a file
  * @author Sergio Saúco
  *
  * @param game a pointer to the game where the objects are loaded
  * @param filename string to the filename with the objects
  * @return OK
  */
STATUS game_reader_load_objects(Game *game, char *filename);

/**
  * @brief It loads the player to the game from a file
  * @author Miguel Campo
  *
  * @param game a pointer to the game where the player is loaded
  * @param filename string to the filename with the player
  * @return status of the operation
  */
STATUS game_reader_load_player(Game *game, char *filename);

/**
  * @brief It loads the enemy to the game from a file
  * @author Miguel Campo
  *
  * @param game a pointer to the game where the enemy is loaded
  * @param filename string to the filename with the enemy
  * @return status of the operation
  */
STATUS game_reader_load_enemy(Game *game, char *filename);


/**
  * @brief It loads the links to the game from a file
  * @author Jorge Jiménez
  *
  * @param game a pointer to the game where the links are loaded
  * @param filename string to the filename with the links
  * @return status of the operation
  */
STATUS game_reader_load_links(Game *game, char *filename);

/**
  * @brief It saves the game's information in a document
  * @author Miguel Campo
  *
  * @param game a pointer to the game to be saved
  * @param filename string to the filename to be written
  * @return status of the operation
  */
STATUS game_management_save(Game *game, char *filename);

/**
  * @brief It loads a game save
  * @author Jorge Jiménez
  *
  * @param game a pointer to the game where to load the save
  * @param filename string to the filename to load
  * @return status of the operation
  */
STATUS game_management_load(Game *game, char *filename);

#endif