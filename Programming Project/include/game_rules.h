/**
 * @brief It defines the functions needed to running the game rules
 *
 * @file game_rules.h
 * @author Jorge Jiménez
 * @version 1.0
 * @date 27-03-2023
 * @copyright GNU Public License
 */
#include "game.h"

#ifndef GAME_RULES_H
#define GAME_RULES_H

/**
  * @brief It runs the game rules of the game
  * @author Jorge Jiménez
  *
  * @param game a pointer to the game where the rules will be run
  * @param aditional_info the additional info of the command 
  * @return OK or ERROR if there was some mistake
  */
STATUS game_rules_run(Game *game, char *aditional_info);

#endif
