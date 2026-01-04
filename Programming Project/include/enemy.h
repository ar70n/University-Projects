/**
 * @brief It defines the enemy interface
 *
 * @file enemy.h
 * @author Sergio Saúco
 * @version 1.0
 * @date 27-02-2023
 * @copyright GNU Public License
 */

#ifndef ENEMY_H
#define ENEMY_H

#include "types.h"

#define MAX_ENEMIES 100 /*!< The maximum number of enemies */

/**
 * @brief Enemy
 *
 * Stores the information about
 * the enemy (id, name, location and
 * health)
 */
typedef struct _Enemy Enemy;


/**
  * @brief It creates a new enemy, allocating memory and initializing its memebers
  * @author Sergio Saúco
  * 
  * @param id the identification number for the new enemy
  * @return a new enemy, initialized
  */
Enemy* enemy_create(Id id);

/**
  * @brief It destroys an enemy, freeing the allocated memory
  * @author Sergio Saúco
  * 
  * @param enemy a pointer to the enemy that must be destroyed  
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS enemy_destroy(Enemy* enemy);

/**
  * @brief It gets the id of an enemy
  * @author Sergio Saúco
  * 
  * @param enemy a pointer to the enemy  
  * @return the id of enemy
  */
Id enemy_get_id(Enemy* enemy);

/**
  * @brief It sets the name of an enemy
  * @author Sergio Saúco
  * 
  * @param enemy a pointer to the enemy
  * @param name a string with the name to store
  * @return OK, if everything goes well or ERROR if there was some mistake 
  */
STATUS enemy_set_name(Enemy* enemy, char* name);
/**
  * @brief It gets the name of an enemy
  * @author Sergio Saúco
  * 
  * @param enemy a pointer to the enemy
  * @return  a string with the name of the enemy
  */
const char* enemy_get_name(Enemy* enemy);

/**
  * @brief It sets the id of the enemy's location
  * @author Sergio Saúco
  * 
  * @param enemy a pointer to the enemy
  * @param id the id number of the enemy's location
  * @return OK, if everything goes well or ERROR if there was some mistake 
  */
STATUS enemy_set_location(Enemy* enemy, Id id);
/**
  * @brief It gets the id of the enemy's location
  * @author Sergio Saúco
  *
  * @param enemy a pointer to the enemy
  * @return the id number of the enemy's location
  */
Id enemy_get_location(Enemy* enemy);

/**
  * @brief It sets the enemy's health
  * @author Sergio Saúco
  *
  * @param enemy a pointer to the enemy
  * @param health the helth points to be set
  * @return OK, if everything goes well or ERROR if there was some mistake 
  */
STATUS enemy_set_health(Enemy *enemy, short health);
/**
  * @brief It gets the enemy's health points
  * @author Sergio Saúco
  *
  * @param enemy a pointer to the enemy
  * @return the enemy's health points or -1 if there was some mistake
  */
short enemy_get_health(Enemy* enemy);

/**
  * @brief It prints the enemy information
  * @author Sergio Saúco
  *
  * This fucntion shows the id and name of the enemy, the id of the location where the enemy is located
  * and the enemy's health.
  * @param enemy a pointer to the enemy
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS enemy_print(Enemy* enemy);

#endif
