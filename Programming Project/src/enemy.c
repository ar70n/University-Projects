/**
 * @brief It implements the enemy module
 *
 * @file enemy.c
 * @author Sergio Saúco
 * @version 1.0
 * @date 27-02-2023
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "enemy.h"

/**
 * @brief Enemy
 *
 * This struct stores all the information of an enemy.
 */
struct _Enemy {
  Id id;                    /*!< Id number of the enemy, it must be unique */
  char name[WORD_SIZE + 1]; /*!< Name of the enemy */
  Id location;              /*!< Id of the enemy's location */
  short health;             /*!< Enemys's health points */
};

/** enemy_create allocates memory for a new enemy
 *  and initializes its members
 */
Enemy *enemy_create(Id id) {
  Enemy *newEnemy = NULL;

  /* Error control */
  if (id == NO_ID)
    return NULL;

  newEnemy = (Enemy *)malloc(sizeof(Enemy));
  if (newEnemy == NULL) {
    return NULL;
  }

  /* Initialization of an empty enemy*/
  newEnemy->id = id;
  newEnemy->name[0] = '\0';
  newEnemy->location = NO_ID;
  newEnemy->health = -1;

  return newEnemy;
}

/** enemy_destroy frees the previous memory allocation
 *  for an enemy
 */
STATUS enemy_destroy(Enemy *enemy) {
  if (!enemy) {
    return ERROR;
  }

  free(enemy);
  enemy = NULL;
  return OK;
}

/** enemy_get_id gets the id of an enemy
 */
Id enemy_get_id(Enemy *enemy) {
  if (!enemy) {
    return NO_ID;
  }
  return enemy->id;
}

/** enemy_set_name sets the name of an enemy
 */
STATUS enemy_set_name(Enemy *enemy, char *name) {
  if (!enemy || !name) {
    return ERROR;
  }

  if (!strcpy(enemy->name, name)) {
    return ERROR;
  }
  return OK;
}
/** enemy_set_name gets the name of an enemy
 */
const char *enemy_get_name(Enemy *enemy) {
  if (!enemy) {
    return NULL;
  }
  return enemy->name;
}

/** enemy_set_location sets the id of the enemy's location
 */
STATUS enemy_set_location(Enemy *enemy, Id id) {
  if (!enemy) {
    return ERROR;
  }
  enemy->location = id;
  return OK;
}
/** enemy_get_location gets the id of the enemy's location
 */
Id enemy_get_location(Enemy *enemy) {
  if (!enemy) {
    return NO_ID;
  }
  return enemy->location;
}

/** enemy_set_health sets the enemy's health
  */
STATUS enemy_set_health(Enemy *enemy, short health) {
  if (!enemy) {
    return ERROR;
  }
  if (health < 0){
    health = 0;
  }

  enemy->health = health;

  return OK;
}
/** enemy_get_health gets the enemy's health points
 */
short enemy_get_health(Enemy *enemy) {
  if (!enemy) {
    return -1;
  }

  return enemy->health;
}

/** enemy_print prints the enemy information
 */
STATUS enemy_print(Enemy *enemy) {
  Id idaux = NO_ID;
  short aux_health = -1;

  /* Error Control */
  if (!enemy) {
    return ERROR;
  }

  /* 1. Print the id and the name of the enemy */
  fprintf(stdout, "--> Enemy (Id: %ld; Name: %s)\n", enemy->id, enemy->name);

  /* 2. Print the id of the location where the enemy is located */
  idaux = enemy_get_location(enemy);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> Id enemy's location: %ld.\n", idaux);
  }
  else {
    fprintf(stdout, "---> No enemy's location id.\n");
  }

  /* 3. Print the enemy's health points */
  aux_health = enemy_get_health(enemy);
  if (aux_health == -1) {
    fprintf(stdout, "---> No enemy\n");
  }
  else {
    fprintf(stdout, "---> Enemy health: %d.\n", aux_health);
  }

  return OK;
}
