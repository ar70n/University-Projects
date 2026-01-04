/** 
 * @brief It implements the game interface and all the associated calls
 * for each command
 * 
 * @file game.c
 * @author Profesores PPROG
 * @version 4.0
 * @date 26-01-2023 
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "game.h"
#include "game_management.h"
#include "object.h"
#include "player.h"
#include "enemy.h"
#include "link.h"
#include "space.h"
#include "game_rules.h"

/**
 * @brief Game
 *
 * This struct stores all the information of a game.
 */
struct _Game{
  Player *player; /*!< Pointer to the player of the game */
  Object *objects[MAX_OBJECTS]; /*!< Pointer to the array of objects of the game */
  Space *spaces[MAX_SPACES]; /*!< Pointer to the array of spaces of the game */
  Link *links[MAX_LINKS]; /*!< Pointer to the array of links of the game */
  Enemy *enemies[MAX_ENEMIES]; /*!< Pointer to the array of enemies of the game */
  T_Command last_cmd; /*!< Last command which has been introduced */
  STATUS last_cmd_status; /*!< Last status of the command which has been introduced */
  char descriptions[MAX_DESCRIPTIONS][WORD_SIZE]; /*!< The last MAX_DESCRIPTIONS descriptions in the game */
  Dialogue *dialogue; /*!< Pointer to the dialogue of the game */
};


/**
   Private functions
*/

Id game_get_space_id_at(Game *game, int position);
/** game_set_player_location sets player's location
  */
STATUS game_set_player_location(Game *game, Id id);
/** game_set_player_location sets enemies's location
  */
STATUS game_set_enemy_location(Game *game, Id id, int index);
/** game_set_object_location sets object's location
  */
STATUS game_set_object_location(Game *game, Id space_id, Id object_id);
/** game_get_object_id_from_name gets the id of the 
  * object with a given name
  */
Id game_get_object_id_from_name(Game *game, char *object_name);
/** game_get_object_from_name gets a pointer to the
  * object with a given name
  */
Object *game_get_object_from_name(Game *game, char *object_name);

/** game_command_unknown implements the "unknown"
  * command
  */
void game_command_unknown(Game *game);
/** game_command_exit implements the "exit"
  * command
  */
void game_command_exit(Game *game);
/** game_command_move implements the "move"
  * command
  */
void game_command_move(Game *game, char *dir);
/** game_command_take implements the "take"
  * command
  */
void game_command_take(Game *game, char *objetc_to_take);
/** game_command_drop implements the "drop"
  * command
  */
void game_command_drop(Game *game, char *object_to_drop);
/** game_command_attack implements the "attack"
  * command
  */
void game_command_attack(Game *game, char *aditional_information);
/** game_command_inspect implements the "inspect"
  * command
  */
void game_command_inspect(Game *game, char *to_inspect_name);

/** game_command_save implements the "save"
  * command
  */
void game_command_save(Game *game, char *filename);
/** game_command_load implements the "load"
  * command
  */
void game_command_load(Game *game, char *filename);
/** game_command_turnon implements the "turnon"
  * command
  */
void game_command_turnon(Game *game, char *name);

/** game_command_turnoff implements the "turnoff"
  * command
  */
void game_command_turnoff(Game *game, char *name);

/** game_command_open implements the "open"
  * command
  */
void game_command_open(Game *game, char *info);


/**
   Game interface implementation
*/



/** game_create creates a new game
  */
STATUS game_create(Game *game) {
  int i;
	
  if (!game) {
    return ERROR;
  }

  for (i = 0; i < MAX_SPACES; i++) {
    game->spaces[i] = NULL;
  }

  for (i = 0; i < MAX_OBJECTS; i++) {
    game->objects[i] = NULL;
  }

 for (i = 0; i < MAX_LINKS; i++) {
    game->links[i] = NULL;
  }
	
  for (i = 0; i < MAX_DESCRIPTIONS; i++) {
    game->descriptions[i][0] = '\0';
  }

  for (i = 0; i < MAX_ENEMIES; i++) {
    game->enemies[i] = NULL;
  }

  game->player = NULL;
  game->last_cmd = NO_CMD;
  game->last_cmd_status = ERROR;
  game->dialogue = dialogue_create();
  if (!game->dialogue) {
    return ERROR;
  }
  if (dialogue_set_command_result(game->dialogue, "Introduce un comando de la lista superior.") == ERROR) {
    return ERROR;
  }

  return OK;
}

/** game_create_from_file It creates a game from a specific file
  */
STATUS  game_create_from_file(Game *game, char *filename) {
  if (!game || !filename) {
    return ERROR;
  }

	
  if (game_create(game) == ERROR) {
    return ERROR;
  }

  if (game_management_load_spaces(game, filename) == ERROR) {
    return ERROR;
  }

  if (game_management_load_player(game, filename) == ERROR) {
    return ERROR;
  }


  if (game_management_load_objects(game, filename) == ERROR) {
    return ERROR;
  }


  if (game_management_load_links(game, filename) == ERROR) {
    return ERROR;
  }

  if (game_management_load_enemies(game, filename) == ERROR) {
    return ERROR;
  }

  return OK;
}

/** game_destroy destroys the game
  */
STATUS game_destroy(Game *game) {
  int i = 0;

  if (!game) {
    return ERROR;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    space_destroy(game->spaces[i]);
  }
  for (i = 0; i<MAX_OBJECTS && game->objects[i] != NULL; i++) {
    object_destroy(game->objects[i]);
  }
  for (i = 0; i<MAX_LINKS && game->links[i] != NULL; i++) {
    link_destroy(game->links[i]);
  }
  for (i = 0; i<MAX_ENEMIES && game->enemies[i] != NULL; i++) {
    enemy_destroy(game->enemies[i]);
  }


  player_destroy(game->player);
  dialogue_destroy(game->dialogue);

  return OK;
}


/** game_add_space adds space to the game
  */
STATUS game_add_space(Game *game, Space *space) {
  int i = 0;

  /* Error control */
  if (game == NULL || space == NULL) {
    return ERROR;
  }

  while (i < MAX_SPACES && game->spaces[i] != NULL) {
    i++;
  }
  
  /* Error control */
  if (i >= MAX_SPACES) {
    return ERROR;
  }

  game->spaces[i] = space;

  return OK;
}

STATUS game_add_link(Game *game, Link *link) {
  int i = 0;

  /* Error control */
  if (game == NULL || link == NULL) {
    return ERROR;
  }

  while (i < MAX_LINKS && game->links[i] != NULL) {
    i++;
  }
  
  /* Error control */
  if (i >= MAX_LINKS) {
    return ERROR;
  }

  game->links[i] = link;

  return OK;
}

/** game_add_object adds an object to the game
  */
STATUS game_add_object(Game *game, Object *object, Id location) {
  int i = 0;
  /* Error control */
  if(! game || !object)
  {
    return ERROR;
  }

  while (i < MAX_OBJECTS && game->objects[i] != NULL) {
    i++;
  }
  
  /* Error control */
  if (i >= MAX_OBJECTS) {
    return ERROR;
  }

  if(location != NO_ID) space_set_object(game_get_space(game,location),object_get_id(object));
  
  game->objects[i] = object;
  return OK;
}

/** game_set_player sets the player of the game
  */
STATUS game_set_player(Game *game, Player *player) {
  if (!game || !player) {
    return ERROR;
  }

  game->player = player;
  return OK;
}

/** game_add_enemy adds an enemy to the game
  */
STATUS game_add_enemy(Game *game, Enemy *enemy) {
  int i = 0;
  /* Error control */
  if(! game || !enemy)
  {
    return ERROR;
  }

  while (i < MAX_ENEMIES && game->enemies[i] != NULL) {
    i++;
  }
  
  /* Error control */
  if (i >= MAX_ENEMIES) {
    return ERROR;
  }
  
  game->enemies[i] = enemy;
  return OK;
}

/** game_get_space_id_at gets the id from a space in the game
  */
Id game_get_space_id_at(Game *game, int position) {
  if (position < 0 || position >= MAX_SPACES) {
    return NO_ID;
  }

  return space_get_id(game->spaces[position]);
}

/** game_get_space gets the space for the game
  */
Space *game_get_space(Game *game, Id id) {
  int i = 0;

  if (!game || id == NO_ID) {
    return NULL;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    if (id == space_get_id(game->spaces[i])) {
      return game->spaces[i];
    }
  }

  return NULL;
}


/**
   Game interface implementation
*/

/** game_set_player_location sets player's location
  */
STATUS game_set_player_location(Game *game, Id id) {

  /* Error control */
  if (!game || id == NO_ID) {
    return ERROR;
  }

  if(player_set_location(game->player, id) == ERROR)
  {
    return ERROR;
  }

  return OK;
}

/** game_set_enemy_location sets enemies's location
  */
STATUS game_set_enemy_location(Game *game, Id id, int index) {

  /* Error control */
  if (!game || id == NO_ID) {
    return ERROR;
  }

  if(enemy_set_location(game->enemies[index], id) == ERROR)
  {
    return ERROR;
  }

  return OK;
}

/** game_set_object_location sets object's location
  */
STATUS game_set_object_location(Game *game, Id space_id, Id object_id) {


  /* Error control */
  if (!game || object_id == NO_ID) {
    return ERROR;
  }
  

  if (space_set_object(game_get_space(game, space_id), object_id)==ERROR)
  {
    return ERROR;
  }

  return OK;
}

/** game_get_player_location gets the
  * location of the player
  */
Id game_get_player_location(Game *game) {
  if(!game){
    return NO_ID;
  }
  return player_get_location(game->player);
}

/** game_get_player_health gets the
  * health of the player
  */
short game_get_player_health(Game *game) {
  if(!game){
    return -1;
  }

  return player_get_health(game->player);
}

/** game_get_object_location gets the
  * location of an object
  */
Id game_get_object_location(Game *game, Id id) {

  int i;
  
  if (id == NO_ID || game == NULL) {
    return NO_ID;
  }

  for(i = 0; i < MAX_SPACES; i++) {
    if (space_search_object(game->spaces[i], id) == TRUE) {
      return space_get_id(game->spaces[i]);
    }
  }

  return NO_ID;
}

/** game_get_enemy_location gets the
  * location of the enemies
  */
Id game_get_enemy_location(Game *game, int index) {
  if(!game){
    return NO_ID;
  }
  return enemy_get_location(game->enemies[index]);
}

/** game_get_enemy_health gets the
  * health of the enemies
  */
short game_get_enemy_health(Game *game, int index) {
  if(!game){
    return -1;
  }
  return enemy_get_health(game->enemies[index]);
}

Id game_get_object_id_from_name(Game *game, char *object_name) {
  int i, flag;
  Id objects[MAX_OBJECTS], object_id;

  if (!object_name) {
    return NO_ID;
  }

  /* Every object of objects to NO_ID */
  for (i = 0; i < MAX_OBJECTS; i++) {
    objects[i] = NO_ID;
  }

  /* Getting every object in the game */
  if (game_get_objects(game, objects) == ERROR) {
    return NO_ID;
  }

  /* Finding the id of the object with that name */
  for (i = 0, flag = 0; i < MAX_OBJECTS && objects[i] != NO_ID && flag == 0; i++) {
    if (strcmp(object_get_name(game->objects[i]), object_name) == 0) {
      object_id = object_get_id(game->objects[i]);
      flag = 1;
    }
  }

  if (flag == 0) {
    return NO_ID;
  }

  return object_id;
}

Object *game_get_object_from_name(Game *game, char *object_name) {
  int i, flag;
  Id objects[MAX_OBJECTS];
  Object *object = NULL;

  if (!object_name) {
    return NULL;
  }

  /* Every object of objects to NO_ID */
  for (i = 0; i < MAX_OBJECTS; i++) {
    objects[i] = NO_ID;
  }

  /* Getting every object in the game */
  if (game_get_objects(game, objects) == ERROR) {
    return NULL;
  }

  /* Finding the id of the object with that name */
  for (i = 0, flag = 0; i < MAX_OBJECTS && objects[i] != NO_ID && flag == 0; i++) {
    if (strcmp(object_get_name(game->objects[i]), object_name) == 0) {
      object = game->objects[i];
      flag = 1;
    }
  }

  if (flag == 0) {
    return NULL;
  }

  return object;
}

STATUS game_set_last_description(Game *game, char *description) {
  int i = 0;

  if (!game || !description) {
    return ERROR;
  }

  for (i = 0; i < game_get_n_descriptions(game); i++) {
    if (strcmp(game_get_description(game, i), description) == 0) {
      return ERROR;
    }
  }
  if (MAX_DESCRIPTIONS == game_get_n_descriptions(game)) {
    
    game->descriptions[MAX_DESCRIPTIONS - 1][0] = '\0';
    if (!strcpy(game->descriptions[MAX_DESCRIPTIONS - 1], description)) {
      return ERROR;
    }
  }
  else {
    if (!strcpy(game->descriptions[game_get_n_descriptions(game)], description)) {
      return ERROR;
    }
  }
  return OK;
}
char *game_get_description(Game *game, int desc_to_get) {
  if (!game || desc_to_get < 0 || desc_to_get >= MAX_DESCRIPTIONS) {
    return NULL;
  }
  return game->descriptions[desc_to_get];
}

int game_get_n_descriptions(Game *game) {
  int i, n = 0;
  if (!game) {
    return -1;
  }
  for (i = 0; i < MAX_DESCRIPTIONS; i++) {
    if (game->descriptions[i][0] != '\0') {
      n++;
    }
  }
  return n;
}

/** game_update updates the status
  * of the game
  */
STATUS game_update(Game *game, T_Command cmd, char *aditional_information) {
  if(!game) return ERROR;
  game_set_last_command(game, cmd);
  
  switch (cmd) {
    case UNKNOWN:
      game_command_unknown(game);
      break;

    case EXIT:
      game_command_exit(game);
      break;

    case MOVE:
      game_command_move(game, aditional_information);
      break;
	
    case TAKE:
      game_command_take(game, aditional_information);
      break;
    
    case DROP:
      game_command_drop(game, aditional_information);
      break;
    
    case ATTACK:
      game_command_attack(game, aditional_information);
      break;

    case INSPECT:
      game_command_inspect(game, aditional_information);
      break;

    case SAVE:
      game_command_save(game, aditional_information);
      break;

    case LOAD:
      game_command_load(game, aditional_information);
      break;

    case TURNON:
      game_command_turnon(game, aditional_information);
      break;

    case TURNOFF:
      game_command_turnoff(game, aditional_information);
      break;
	  
    case OPENC:
      game_command_open(game, aditional_information);
      break;

    default:
      break;
  }

  if (game_rules_run(game, aditional_information) == ERROR) {
    return ERROR;
  }

  return OK;
}

/** game_get_last_command sets the
  * last command of the game
  */
STATUS game_set_last_command(Game *game, T_Command last_command) {
  if (!game) {
    return ERROR;
  }
  game->last_cmd = last_command;
  return OK;
}

/** game_get_last_command gets the
  * last command of the game
  */
T_Command game_get_last_command(Game *game) {
  return game->last_cmd;
}

/** game_get_last_command gets the status of
  * last command introduced in the game
  */
STATUS game_get_last_command_status(Game *game) {
  return game->last_cmd_status;
}

/** game_print_data prints game's data
  */
STATUS game_print_data(Game *game) {
  int i = 0;
	
  if (!game) {
    return ERROR;
  }

  printf("\n\n-------------\n\n");

  printf("=> Spaces: \n");
  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    if (space_print(game->spaces[i]) == ERROR) {
      return ERROR;
    }
  }

  printf("=> Objects: \n");
  for (i = 0; i < MAX_OBJECTS && game->objects[i] != NULL; i++) {
    if (object_print(game->objects[i]) == ERROR) {
      return ERROR;
    }
  }

  printf("=> Links: \n");
  for (i = 0; i < MAX_LINKS && game->links[i] != NULL; i++) {
    if (link_print(game->links[i]) == ERROR) {
      return ERROR;
    }
  }
  printf("=> Enemies: \n");
  for (i = 0; i < MAX_ENEMIES && game->enemies[i] != NULL; i++) {
    if (enemy_print(game->enemies[i]) == ERROR) {
      return ERROR;
    }
  }

  printf("=> Player location: %d\n", (int)player_get_location(game->player));

  return OK;
}

/** game_is_over gets the game over 
  */
BOOL game_is_over(Game *game) {
  short player_health = game_get_player_health(game);

  if (player_health == 0) {
    return TRUE;
  }

  return FALSE;
}

/**
   Calls implementation for each action 
*/

/** game_command_unknown game command unknown
  */
void game_command_unknown(Game *game) {
  dialogue_set_previous_command(game->dialogue, UNKNOWN);
  dialogue_set_previous_command_status(game->dialogue, ERROR);
  dialogue_set_command_result(game->dialogue, "Comando desconocido. Prueba otra accion.");
  game_set_last_command_status(game, ERROR);
  return;
}

/** game_command_exit game command to exit
  * the game
  */
void game_command_exit(Game *game) {
  game_set_last_command_status(game, OK);
  return;
}


/** game_command_take game command to
  * get the object in the space
  */
void game_command_take(Game *game, char *object_to_take) {
  Id player_location = NO_ID, object_location = NO_ID, object_id = NO_ID, dependency = NO_ID;
  Id objects[MAX_OBJECTS];
  Space *player_space = NULL;
  Object *object = NULL, *object_dependency = NULL;
  int i, flag;
  char cmd_result[WORD_SIZE] = "";
  

  /* Error control */
  if (!object_to_take || !game) {
    if (dialogue_get_previous_command(game->dialogue) == TAKE && dialogue_get_previous_command_status(game->dialogue) == ERROR
    && strcmp(dialogue_get_previous_additional_information(game->dialogue), object_to_take) == 0
    && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
      dialogue_set_previous_command(game->dialogue, TAKE);
      dialogue_set_previous_command_status(game->dialogue, ERROR);
      dialogue_set_previous_additional_information(game->dialogue, object_to_take);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
      game_set_last_command_status(game, ERROR);
      return;
    }
    dialogue_set_previous_command(game->dialogue, TAKE);
    dialogue_set_previous_command_status(game->dialogue, ERROR);
    dialogue_set_previous_additional_information(game->dialogue, object_to_take);
    dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
    dialogue_set_command_result(game->dialogue, "No se pudo coger. Prueba otra accion.");
    game_set_last_command_status(game, ERROR);
    return;
  }


  if (object_to_take[0] == '\0') {
    if (dialogue_get_previous_command(game->dialogue) == TAKE && dialogue_get_previous_command_status(game->dialogue) == ERROR
    && strcmp(dialogue_get_previous_additional_information(game->dialogue), object_to_take) == 0
    && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
      dialogue_set_previous_command(game->dialogue, TAKE);
      dialogue_set_previous_command_status(game->dialogue, ERROR);
      dialogue_set_previous_additional_information(game->dialogue, object_to_take);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
      game_set_last_command_status(game, ERROR);
      return;
    }
    dialogue_set_previous_command(game->dialogue, TAKE);
    dialogue_set_previous_command_status(game->dialogue, ERROR);
    dialogue_set_previous_additional_information(game->dialogue, object_to_take);
    dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
    dialogue_set_command_result(game->dialogue, "Debes introducir: 'take <nombre_objeto>'.");
    game_set_last_command_status(game, ERROR);
    return;
  }

  player_location = game_get_player_location(game);
  if (player_location == NO_ID) {
    if (dialogue_get_previous_command(game->dialogue) == TAKE && dialogue_get_previous_command_status(game->dialogue) == ERROR
    && strcmp(dialogue_get_previous_additional_information(game->dialogue), object_to_take) == 0
    && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
      dialogue_set_previous_command(game->dialogue, TAKE);
      dialogue_set_previous_command_status(game->dialogue, ERROR);
      dialogue_set_previous_additional_information(game->dialogue, object_to_take);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
      game_set_last_command_status(game, ERROR);
      return;
    }
    dialogue_set_previous_command(game->dialogue, TAKE);
    dialogue_set_previous_command_status(game->dialogue, ERROR);
    dialogue_set_previous_additional_information(game->dialogue, object_to_take);
    dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
    dialogue_set_command_result(game->dialogue, "No se pudo coger. Prueba otra accion.");
    game_set_last_command_status(game, ERROR);
    return;
  }

  /* Every object of objects to NO_ID */
  for (i = 0; i < MAX_OBJECTS; i++) {
    objects[i] = NO_ID;
  }

  /* Getting every object in the game */
  if (game_get_objects(game, objects) == ERROR) {
    if (dialogue_get_previous_command(game->dialogue) == TAKE && dialogue_get_previous_command_status(game->dialogue) == ERROR
    && strcmp(dialogue_get_previous_additional_information(game->dialogue), object_to_take) == 0
    && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
      dialogue_set_previous_command(game->dialogue, TAKE);
      dialogue_set_previous_command_status(game->dialogue, ERROR);
      dialogue_set_previous_additional_information(game->dialogue, object_to_take);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
      game_set_last_command_status(game, ERROR);
      return;
    }
    dialogue_set_previous_command(game->dialogue, TAKE);
    dialogue_set_previous_command_status(game->dialogue, ERROR);
    dialogue_set_previous_additional_information(game->dialogue, object_to_take);
    dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
    dialogue_set_command_result(game->dialogue, "No se pudo coger. Prueba otra accion.");
    game_set_last_command_status(game, ERROR);
    return;
  }


  /* Checking if there are objects in the same space as the player */
  for (i = 0, flag = 0; i < MAX_OBJECTS && objects[i] != NO_ID && flag == 0; i++) {
    if (game_get_object_location(game, objects[i]) == player_location) {
      flag = 1;
    } 
  }

  if (flag == 0) {
    if (dialogue_get_previous_command(game->dialogue) == TAKE && dialogue_get_previous_command_status(game->dialogue) == ERROR
    && strcmp(dialogue_get_previous_additional_information(game->dialogue), object_to_take) == 0
    && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
      dialogue_set_previous_command(game->dialogue, TAKE);
      dialogue_set_previous_command_status(game->dialogue, ERROR);
      dialogue_set_previous_additional_information(game->dialogue, object_to_take);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
      game_set_last_command_status(game, ERROR);
      return;
    }
    dialogue_set_previous_command(game->dialogue, TAKE);
    dialogue_set_previous_command_status(game->dialogue, ERROR);
    dialogue_set_previous_additional_information(game->dialogue, object_to_take);
    dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
    dialogue_set_command_result(game->dialogue, "No hay objetos en tu espacio. Prueba otra accion.");
    game_set_last_command_status(game, ERROR);
    return;
  }

  object_id = game_get_object_id_from_name(game, object_to_take);
  if (object_id == NO_ID) {
    if (dialogue_get_previous_command(game->dialogue) == TAKE && dialogue_get_previous_command_status(game->dialogue) == ERROR
    && strcmp(dialogue_get_previous_additional_information(game->dialogue), object_to_take) == 0
    && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
      dialogue_set_previous_command(game->dialogue, TAKE);
      dialogue_set_previous_command_status(game->dialogue, ERROR);
      dialogue_set_previous_additional_information(game->dialogue, object_to_take);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
      game_set_last_command_status(game, ERROR);
      return;
    }
    dialogue_set_previous_command(game->dialogue, TAKE);
    dialogue_set_previous_command_status(game->dialogue, ERROR);
    dialogue_set_previous_additional_information(game->dialogue, object_to_take);
    dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
    sprintf(cmd_result, "No existe el objeto '%s'. Prueba otra accion.", object_to_take);
    dialogue_set_command_result(game->dialogue, cmd_result);
    game_set_last_command_status(game, ERROR);
    return;
  }
	
  object = game_get_object_from_name(game, object_to_take);
  if (!object) {
    if (dialogue_get_previous_command(game->dialogue) == TAKE && dialogue_get_previous_command_status(game->dialogue) == ERROR
    && strcmp(dialogue_get_previous_additional_information(game->dialogue), object_to_take) == 0
    && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
      dialogue_set_previous_command(game->dialogue, TAKE);
      dialogue_set_previous_command_status(game->dialogue, ERROR);
      dialogue_set_previous_additional_information(game->dialogue, object_to_take);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
      game_set_last_command_status(game, ERROR);
      return;
    }
    dialogue_set_previous_command(game->dialogue, TAKE);
    dialogue_set_previous_command_status(game->dialogue, ERROR);
    dialogue_set_previous_additional_information(game->dialogue, object_to_take);
    dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
    sprintf(cmd_result, "No existe el objeto '%s'. Prueba otra accion.", object_to_take);
    dialogue_set_command_result(game->dialogue, cmd_result);
    game_set_last_command_status(game, ERROR);
    return;
  }

  if (object_get_hidden(object) == TRUE) {
    if (dialogue_get_previous_command(game->dialogue) == TAKE && dialogue_get_previous_command_status(game->dialogue) == ERROR
    && strcmp(dialogue_get_previous_additional_information(game->dialogue), object_to_take) == 0
    && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
      dialogue_set_previous_command(game->dialogue, TAKE);
      dialogue_set_previous_command_status(game->dialogue, ERROR);
      dialogue_set_previous_additional_information(game->dialogue, object_to_take);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
      game_set_last_command_status(game, ERROR);
      return;
    }
    dialogue_set_previous_command(game->dialogue, TAKE);
    dialogue_set_previous_command_status(game->dialogue, ERROR);
    dialogue_set_previous_additional_information(game->dialogue, object_to_take);
    dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
    sprintf(cmd_result, "El objeto '%s' esta escondido. Prueba otra accion.", object_to_take);
    dialogue_set_command_result(game->dialogue, cmd_result);
    game_set_last_command_status(game, ERROR);
    return;
  }
  
  object_location = game_get_object_location(game, object_id);
  if (object_location == NO_ID) {
    if (dialogue_get_previous_command(game->dialogue) == TAKE && dialogue_get_previous_command_status(game->dialogue) == ERROR
    && strcmp(dialogue_get_previous_additional_information(game->dialogue), object_to_take) == 0
    && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
      dialogue_set_previous_command(game->dialogue, TAKE);
      dialogue_set_previous_command_status(game->dialogue, ERROR);
      dialogue_set_previous_additional_information(game->dialogue, object_to_take);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
      game_set_last_command_status(game, ERROR);
      return;
    }
    dialogue_set_previous_command(game->dialogue, TAKE);
    dialogue_set_previous_command_status(game->dialogue, ERROR);
    dialogue_set_previous_additional_information(game->dialogue, object_to_take);
    dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
    sprintf(cmd_result, "No se pudo coger '%s'. Prueba otra accion.", object_to_take);
    dialogue_set_command_result(game->dialogue, cmd_result);
    game_set_last_command_status(game, ERROR);
    return;
  }
	
  if(object_get_movable(game_get_object_from_id(game, object_id)) == 0){
    if (dialogue_get_previous_command(game->dialogue) == TAKE && dialogue_get_previous_command_status(game->dialogue) == ERROR
    && strcmp(dialogue_get_previous_additional_information(game->dialogue), object_to_take) == 0
    && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
      dialogue_set_previous_command(game->dialogue, TAKE);
      dialogue_set_previous_command_status(game->dialogue, ERROR);
      dialogue_set_previous_additional_information(game->dialogue, object_to_take);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
      game_set_last_command_status(game, ERROR);
      return;
    }
    dialogue_set_previous_command(game->dialogue, TAKE);
    dialogue_set_previous_command_status(game->dialogue, ERROR);
    dialogue_set_previous_additional_information(game->dialogue, object_to_take);
    dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
    sprintf(cmd_result, "El objeto '%s' es inamovible. Prueba otra accion.", object_to_take);
    dialogue_set_command_result(game->dialogue, cmd_result);
    game_set_last_command_status(game, ERROR);
    return;
  }

  /* Getting the id of the object that the object depends on */
  dependency = object_get_dependency(object);

  /* The player takes the object if the object doesn't depend on any objects */
  if (player_location == object_location && dependency == NO_ID) {
    if (player_add_object_to_inventory(game->player, object_id) == ERROR) {
      if (dialogue_get_previous_command(game->dialogue) == TAKE && dialogue_get_previous_command_status(game->dialogue) == ERROR
      && strcmp(dialogue_get_previous_additional_information(game->dialogue), object_to_take) == 0
      && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
        dialogue_set_previous_command(game->dialogue, TAKE);
        dialogue_set_previous_command_status(game->dialogue, ERROR);
        dialogue_set_previous_additional_information(game->dialogue, object_to_take);
        dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
        dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
        game_set_last_command_status(game, ERROR);
        return;
      }
      dialogue_set_previous_command(game->dialogue, TAKE);
      dialogue_set_previous_command_status(game->dialogue, ERROR);
      dialogue_set_previous_additional_information(game->dialogue, object_to_take);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      sprintf(cmd_result, "No se pudo coger '%s'. Prueba otra accion.", object_to_take);
      dialogue_set_command_result(game->dialogue, cmd_result);
      game_set_last_command_status(game, ERROR);
      return;
    }
    
    player_space = game_get_space(game ,(player_location));
    if (player_space == NULL) {
      if (dialogue_get_previous_command(game->dialogue) == TAKE && dialogue_get_previous_command_status(game->dialogue) == ERROR
      && strcmp(dialogue_get_previous_additional_information(game->dialogue), object_to_take) == 0
      && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
        dialogue_set_previous_command(game->dialogue, TAKE);
        dialogue_set_previous_command_status(game->dialogue, ERROR);
        dialogue_set_previous_additional_information(game->dialogue, object_to_take);
        dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
        dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
        game_set_last_command_status(game, ERROR);
        return;
      }
      dialogue_set_previous_command(game->dialogue, TAKE);
      dialogue_set_previous_command_status(game->dialogue, ERROR);
      dialogue_set_previous_additional_information(game->dialogue, object_to_take);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      sprintf(cmd_result, "No se pudo coger '%s'. Prueba otra accion.", object_to_take);
      dialogue_set_command_result(game->dialogue, cmd_result);
      game_set_last_command_status(game, ERROR);
      return;
    }
    if (space_unset_object(player_space, object_id) == ERROR){
      if (dialogue_get_previous_command(game->dialogue) == TAKE && dialogue_get_previous_command_status(game->dialogue) == ERROR
      && strcmp(dialogue_get_previous_additional_information(game->dialogue), object_to_take) == 0
      && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
        dialogue_set_previous_command(game->dialogue, TAKE);
        dialogue_set_previous_command_status(game->dialogue, ERROR);
        dialogue_set_previous_additional_information(game->dialogue, object_to_take);
        dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
        dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
        game_set_last_command_status(game, ERROR);
        return;
      }
      dialogue_set_previous_command(game->dialogue, TAKE);
      dialogue_set_previous_command_status(game->dialogue, ERROR);
      dialogue_set_previous_additional_information(game->dialogue, object_to_take);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      sprintf(cmd_result, "No se pudo coger '%s'. Prueba otra accion.", object_to_take);
      dialogue_set_command_result(game->dialogue, cmd_result);
      game_set_last_command_status(game, ERROR);
      return;
    }


    if(object_id == 9 || object_id == 14){
      player_set_power(game->player, player_get_power(game->player) + 1);
    }

    dialogue_set_previous_command(game->dialogue, TAKE);
    dialogue_set_previous_command_status(game->dialogue, OK);
    dialogue_set_previous_additional_information(game->dialogue, object_to_take);
    dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
    sprintf(cmd_result, "'%s' guardado en el inventario correctamente.", object_to_take);
    dialogue_set_command_result(game->dialogue, cmd_result);
    game_set_last_command_status(game, OK);
    return;
  }
  /* The player takes the object or not if the object depends on an object */
  else if (player_location == object_location && dependency != NO_ID) {
    /* The player takes the object if the object with id dependency is in the inventory */
    if (player_inventory_stores(game_get_player(game), dependency) == TRUE) {
      if (player_add_object_to_inventory(game->player, object_id) == ERROR) {
        if (dialogue_get_previous_command(game->dialogue) == TAKE && dialogue_get_previous_command_status(game->dialogue) == ERROR
        && strcmp(dialogue_get_previous_additional_information(game->dialogue), object_to_take) == 0
        && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
        dialogue_set_previous_command(game->dialogue, TAKE);
        dialogue_set_previous_command_status(game->dialogue, ERROR);
        dialogue_set_previous_additional_information(game->dialogue, object_to_take);
        dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
        dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
        game_set_last_command_status(game, ERROR);
        return;
      }
      dialogue_set_previous_command(game->dialogue, TAKE);
      dialogue_set_previous_command_status(game->dialogue, ERROR);
      dialogue_set_previous_additional_information(game->dialogue, object_to_take);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      sprintf(cmd_result, "No se pudo coger '%s'. Prueba otra accion.", object_to_take);
      dialogue_set_command_result(game->dialogue, cmd_result);
      game_set_last_command_status(game, ERROR);
      return;
    }

    
    player_space = game_get_space(game ,(player_location));
    if (player_space == NULL) {
      if (dialogue_get_previous_command(game->dialogue) == TAKE && dialogue_get_previous_command_status(game->dialogue) == ERROR
      && strcmp(dialogue_get_previous_additional_information(game->dialogue), object_to_take) == 0
      && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
        dialogue_set_previous_command(game->dialogue, TAKE);
        dialogue_set_previous_command_status(game->dialogue, ERROR);
        dialogue_set_previous_additional_information(game->dialogue, object_to_take);
        dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
        dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
        game_set_last_command_status(game, ERROR);
        return;
      }
      dialogue_set_previous_command(game->dialogue, TAKE);
      dialogue_set_previous_command_status(game->dialogue, ERROR);
      dialogue_set_previous_additional_information(game->dialogue, object_to_take);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      sprintf(cmd_result, "No se pudo coger '%s'. Prueba otra accion.", object_to_take);
      dialogue_set_command_result(game->dialogue, cmd_result);
      game_set_last_command_status(game, ERROR);
      return;
    }
    if (space_unset_object(player_space, object_id) == ERROR){
      if (dialogue_get_previous_command(game->dialogue) == TAKE && dialogue_get_previous_command_status(game->dialogue) == ERROR
      && strcmp(dialogue_get_previous_additional_information(game->dialogue), object_to_take) == 0
      && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
        dialogue_set_previous_command(game->dialogue, TAKE);
        dialogue_set_previous_command_status(game->dialogue, ERROR);
        dialogue_set_previous_additional_information(game->dialogue, object_to_take);
        dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
        dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
        game_set_last_command_status(game, ERROR);
        return;
      }
      dialogue_set_previous_command(game->dialogue, TAKE);
      dialogue_set_previous_command_status(game->dialogue, ERROR);
      dialogue_set_previous_additional_information(game->dialogue, object_to_take);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      sprintf(cmd_result, "No se pudo coger '%s'. Prueba otra accion.", object_to_take);
      dialogue_set_command_result(game->dialogue, cmd_result);
      game_set_last_command_status(game, ERROR);
      return;
    }

    if(object_id == 9 || object_id == 14){
      player_set_power(game->player, player_get_power(game->player) + 1);
    }

    dialogue_set_previous_command(game->dialogue, TAKE);
    dialogue_set_previous_command_status(game->dialogue, OK);
    dialogue_set_previous_additional_information(game->dialogue, object_to_take);
    dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
    sprintf(cmd_result, "'%s' guardado en el inventario correctamente.", object_to_take);
    dialogue_set_command_result(game->dialogue, cmd_result);
    game_set_last_command_status(game, OK);
    return;
    }
    /* The player doesn't take the object if the object with id dependency is not the inventory */
    else {
      object_dependency = game_get_object_from_id(game, dependency);
      if (!object_dependency) {
        if (dialogue_get_previous_command(game->dialogue) == TAKE && dialogue_get_previous_command_status(game->dialogue) == ERROR
        && strcmp(dialogue_get_previous_additional_information(game->dialogue), object_to_take) == 0
        && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
          dialogue_set_previous_command(game->dialogue, TAKE);
          dialogue_set_previous_command_status(game->dialogue, ERROR);
          dialogue_set_previous_additional_information(game->dialogue, object_to_take);
          dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
          dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
          game_set_last_command_status(game, ERROR);
          return;
        }
        dialogue_set_previous_command(game->dialogue, TAKE);
        dialogue_set_previous_command_status(game->dialogue, ERROR);
        dialogue_set_previous_additional_information(game->dialogue, object_to_take);
        dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
        sprintf(cmd_result, "No se pudo coger '%s'. Prueba otra accion.", object_to_take);
        dialogue_set_command_result(game->dialogue, cmd_result);
        game_set_last_command_status(game, ERROR);
        return;
      }
      if (dialogue_get_previous_command(game->dialogue) == TAKE && dialogue_get_previous_command_status(game->dialogue) == ERROR
      && strcmp(dialogue_get_previous_additional_information(game->dialogue), object_to_take) == 0
      && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
        dialogue_set_previous_command(game->dialogue, TAKE);
        dialogue_set_previous_command_status(game->dialogue, ERROR);
        dialogue_set_previous_additional_information(game->dialogue, object_to_take);
        dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
        dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
        game_set_last_command_status(game, ERROR);
        return;
      }
      dialogue_set_previous_command(game->dialogue, TAKE);
      dialogue_set_previous_command_status(game->dialogue, ERROR);
      dialogue_set_previous_additional_information(game->dialogue, object_to_take);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      sprintf(cmd_result, "No se pudo coger '%s' necesitas '%s'. Prueba otra accion.", object_to_take, object_get_name(object_dependency));
      dialogue_set_command_result(game->dialogue, cmd_result);
      game_set_last_command_status(game, ERROR);
      return;
    }
  }

  if (dialogue_get_previous_command(game->dialogue) == TAKE && dialogue_get_previous_command_status(game->dialogue) == ERROR
  && strcmp(dialogue_get_previous_additional_information(game->dialogue), object_to_take) == 0
  && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
    dialogue_set_previous_command(game->dialogue, TAKE);
    dialogue_set_previous_command_status(game->dialogue, ERROR);
    dialogue_set_previous_additional_information(game->dialogue, object_to_take);
    dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
    dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
    game_set_last_command_status(game, ERROR);
    return;
  }
  dialogue_set_previous_command(game->dialogue, TAKE);
  dialogue_set_previous_command_status(game->dialogue, ERROR);
  dialogue_set_previous_additional_information(game->dialogue, object_to_take);
  dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
  sprintf(cmd_result, "No se pudo coger '%s'. Prueba otra accion.", object_to_take);
  dialogue_set_command_result(game->dialogue, cmd_result);
  game_set_last_command_status(game, ERROR);
  return;
}

/** game_command_drop game command to
  * drop the object in the space
  */
void game_command_drop(Game *game, char *object_to_drop) {
  Id player_object = NO_ID, player_location = NO_ID;
  Space *player_space = NULL;
  char cmd_result[WORD_SIZE] = "";

	
  /* Error control */
  if (!game || !object_to_drop) {
    if (dialogue_get_previous_command(game->dialogue) == DROP && dialogue_get_previous_command_status(game->dialogue) == ERROR
    && strcmp(dialogue_get_previous_additional_information(game->dialogue), object_to_drop) == 0
    && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
      dialogue_set_previous_command(game->dialogue, DROP);
      dialogue_set_previous_command_status(game->dialogue, ERROR);
      dialogue_set_previous_additional_information(game->dialogue, object_to_drop);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
      game_set_last_command_status(game, ERROR);
      return;
    }
    dialogue_set_previous_command(game->dialogue, DROP);
    dialogue_set_previous_command_status(game->dialogue, ERROR);
    dialogue_set_previous_additional_information(game->dialogue, object_to_drop);
    dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
    dialogue_set_command_result(game->dialogue, "No se pudo soltar. Prueba otra accion.");
    game_set_last_command_status(game, ERROR);
    return;
  }

  if (object_to_drop[0] == '\0') {
    if (dialogue_get_previous_command(game->dialogue) == DROP && dialogue_get_previous_command_status(game->dialogue) == ERROR
    && strcmp(dialogue_get_previous_additional_information(game->dialogue), object_to_drop) == 0
    && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
      dialogue_set_previous_command(game->dialogue, DROP);
      dialogue_set_previous_command_status(game->dialogue, ERROR);
      dialogue_set_previous_additional_information(game->dialogue, object_to_drop);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
      game_set_last_command_status(game, ERROR);
      return;
    }
    dialogue_set_previous_command(game->dialogue, DROP);
    dialogue_set_previous_command_status(game->dialogue, ERROR);
    dialogue_set_previous_additional_information(game->dialogue, object_to_drop);
    dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
    dialogue_set_command_result(game->dialogue, "Debes introducir: 'drop <nombre_objeto>'.");
    game_set_last_command_status(game, ERROR);
    return;
  }

  player_object = game_get_object_id_from_name(game, object_to_drop);
  if (player_object == NO_ID) {
    if (dialogue_get_previous_command(game->dialogue) == DROP && dialogue_get_previous_command_status(game->dialogue) == ERROR
    && strcmp(dialogue_get_previous_additional_information(game->dialogue), object_to_drop) == 0
    && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
      dialogue_set_previous_command(game->dialogue, DROP);
      dialogue_set_previous_command_status(game->dialogue, ERROR);
      dialogue_set_previous_additional_information(game->dialogue, object_to_drop);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
      game_set_last_command_status(game, ERROR);
      return;
    }
    dialogue_set_previous_command(game->dialogue, DROP);
    dialogue_set_previous_command_status(game->dialogue, ERROR);
    dialogue_set_previous_additional_information(game->dialogue, object_to_drop);
    dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
    sprintf(cmd_result, "No existe '%s'. Prueba otra accion.", object_to_drop);
    dialogue_set_command_result(game->dialogue, cmd_result);
    game_set_last_command_status(game, ERROR);
    return;
  }

  player_location = game_get_player_location(game);
  if (player_location == NO_ID) {
    if (dialogue_get_previous_command(game->dialogue) == DROP && dialogue_get_previous_command_status(game->dialogue) == ERROR
    && strcmp(dialogue_get_previous_additional_information(game->dialogue), object_to_drop) == 0
    && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
      dialogue_set_previous_command(game->dialogue, DROP);
      dialogue_set_previous_command_status(game->dialogue, ERROR);
      dialogue_set_previous_additional_information(game->dialogue, object_to_drop);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
      game_set_last_command_status(game, ERROR);
      return;
    }
    dialogue_set_previous_command(game->dialogue, DROP);
    dialogue_set_previous_command_status(game->dialogue, ERROR);
    dialogue_set_previous_additional_information(game->dialogue, object_to_drop);
    dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
    sprintf(cmd_result, "No se pudo soltar '%s'. Prueba otra accion.", object_to_drop);
    dialogue_set_command_result(game->dialogue, cmd_result);
    game_set_last_command_status(game, ERROR);
    return;
  }

  /* The player drops the object */
  if (player_inventory_stores(game->player, player_object) == TRUE) {
    player_space = game_get_space(game, player_location);
    if (player_space == NULL) {
      if (dialogue_get_previous_command(game->dialogue) == DROP && dialogue_get_previous_command_status(game->dialogue) == ERROR
      && strcmp(dialogue_get_previous_additional_information(game->dialogue), object_to_drop) == 0
      && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
        dialogue_set_previous_command(game->dialogue, DROP);
        dialogue_set_previous_command_status(game->dialogue, ERROR);
        dialogue_set_previous_additional_information(game->dialogue, object_to_drop);
        dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
        dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
        game_set_last_command_status(game, ERROR);
        return;
      }
      dialogue_set_previous_command(game->dialogue, DROP);
      dialogue_set_previous_command_status(game->dialogue, ERROR);
      dialogue_set_previous_additional_information(game->dialogue, object_to_drop);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      sprintf(cmd_result, "No se pudo soltar '%s'. Prueba otra accion.", object_to_drop);
      dialogue_set_command_result(game->dialogue, cmd_result);
      game_set_last_command_status(game, ERROR);
      return;
    }
    if (space_set_object(player_space, player_object) == ERROR) {
      if (dialogue_get_previous_command(game->dialogue) == DROP && dialogue_get_previous_command_status(game->dialogue) == ERROR
      && strcmp(dialogue_get_previous_additional_information(game->dialogue), object_to_drop) == 0
      && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
        dialogue_set_previous_command(game->dialogue, DROP);
        dialogue_set_previous_command_status(game->dialogue, ERROR);
        dialogue_set_previous_additional_information(game->dialogue, object_to_drop);
        dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
        dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
        game_set_last_command_status(game, ERROR);
        return;
      }
      dialogue_set_previous_command(game->dialogue, DROP);
      dialogue_set_previous_command_status(game->dialogue, ERROR);
      dialogue_set_previous_additional_information(game->dialogue, object_to_drop);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      sprintf(cmd_result, "No se pudo soltar '%s'. Prueba otra accion.", object_to_drop);
      dialogue_set_command_result(game->dialogue, cmd_result);
      game_set_last_command_status(game, ERROR);
      return;
    }
    if (player_del_object_from_inventory(game->player, player_object) == ERROR) {
      if (dialogue_get_previous_command(game->dialogue) == DROP && dialogue_get_previous_command_status(game->dialogue) == ERROR
      && strcmp(dialogue_get_previous_additional_information(game->dialogue), object_to_drop) == 0
      && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
        dialogue_set_previous_command(game->dialogue, DROP);
        dialogue_set_previous_command_status(game->dialogue, ERROR);
        dialogue_set_previous_additional_information(game->dialogue, object_to_drop);
        dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
        dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
        game_set_last_command_status(game, ERROR);
        return;
      }
      dialogue_set_previous_command(game->dialogue, DROP);
      dialogue_set_previous_command_status(game->dialogue, ERROR);
      dialogue_set_previous_additional_information(game->dialogue, object_to_drop);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      sprintf(cmd_result, "No se pudo soltar '%s'. Prueba otra accion.", object_to_drop);
      dialogue_set_command_result(game->dialogue, cmd_result);
      game_set_last_command_status(game, ERROR);
      return;
    }

    if(strcmp(object_to_drop, "chuleta") == 0 || strcmp(object_to_drop, "GPT-4") == 0){
      player_set_power(game->player, player_get_power(game->player) - 1);
    }

    dialogue_set_previous_command(game->dialogue, DROP);
    dialogue_set_previous_command_status(game->dialogue, OK);
    dialogue_set_previous_additional_information(game->dialogue, object_to_drop);
    dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
    sprintf(cmd_result, "'%s' soltado correctamente.", object_to_drop);
    dialogue_set_command_result(game->dialogue, cmd_result);
    game_set_last_command_status(game, OK);
    return;
  }

  if (dialogue_get_previous_command(game->dialogue) == DROP && dialogue_get_previous_command_status(game->dialogue) == ERROR
  && strcmp(dialogue_get_previous_additional_information(game->dialogue), object_to_drop) == 0
  && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
    dialogue_set_previous_command(game->dialogue, DROP);
    dialogue_set_previous_command_status(game->dialogue, ERROR);
    dialogue_set_previous_additional_information(game->dialogue, object_to_drop);
    dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
    dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
    game_set_last_command_status(game, ERROR);
    return;
  }
  dialogue_set_previous_command(game->dialogue, DROP);
  dialogue_set_previous_command_status(game->dialogue, ERROR);
  dialogue_set_previous_additional_information(game->dialogue, object_to_drop);
  dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
  sprintf(cmd_result, "No tienes '%s' en el inventario. Prueba otra accion.", object_to_drop);
  dialogue_set_command_result(game->dialogue, cmd_result);
  game_set_last_command_status(game, ERROR);
  return;
}


/** game_command_move game command to
  * move the player to the directoin specified
  */
void game_command_move(Game *g, char* dir){
  Id current_id = NO_ID;
  Id space_id = NO_ID;
  DIRECTION enum_dir = I;
  char cmd_result[WORD_SIZE] = "", cmd_dir[7] = "";
  int i;

  if (!g || !dir) {
    if (dialogue_get_previous_command(g->dialogue) == MOVE && dialogue_get_previous_command_status(g->dialogue) == ERROR
    && strcmp(dialogue_get_previous_additional_information(g->dialogue), dir) == 0
    && dialogue_get_previous_player_location(g->dialogue) == game_get_player_location(g)) {
      dialogue_set_previous_command(g->dialogue, MOVE);
      dialogue_set_previous_command_status(g->dialogue, ERROR);
      dialogue_set_previous_additional_information(g->dialogue, dir);
      dialogue_set_previous_player_location(g->dialogue, game_get_player_location(g));
      dialogue_set_command_result(g->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
      game_set_last_command_status(g, ERROR);
      return;
    }
    dialogue_set_previous_command(g->dialogue, MOVE);
    dialogue_set_previous_command_status(g->dialogue, ERROR);
    dialogue_set_previous_additional_information(g->dialogue, dir);
    dialogue_set_previous_player_location(g->dialogue, game_get_player_location(g));
    dialogue_set_command_result(g->dialogue, "No se pudo mover. Prueba otra accion.");
    game_set_last_command_status(g, ERROR);
    return;
  }

  if (dir[0] == '\0') {
    if (dialogue_get_previous_command(g->dialogue) == MOVE && dialogue_get_previous_command_status(g->dialogue) == ERROR
    && strcmp(dialogue_get_previous_additional_information(g->dialogue), dir) == 0
    && dialogue_get_previous_player_location(g->dialogue) == game_get_player_location(g)) {
      dialogue_set_previous_command(g->dialogue, MOVE);
      dialogue_set_previous_command_status(g->dialogue, ERROR);
      dialogue_set_previous_additional_information(g->dialogue, dir);
      dialogue_set_previous_player_location(g->dialogue, game_get_player_location(g));
      dialogue_set_command_result(g->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
      game_set_last_command_status(g, ERROR);
      return;
    }
    dialogue_set_previous_command(g->dialogue, MOVE);
    dialogue_set_previous_command_status(g->dialogue, ERROR);
    dialogue_set_previous_additional_information(g->dialogue, dir);
    dialogue_set_previous_player_location(g->dialogue, game_get_player_location(g));
    dialogue_set_command_result(g->dialogue, "Debes introducir: 'move <direccion>'.");
    game_set_last_command_status(g, ERROR);
    return;
  }

  if(strcmp(dir, "n") == 0) {
    enum_dir = N;
    strcpy(cmd_dir, "norte");
  }
  else if(strcmp(dir, "e") == 0) {
    enum_dir = E;
    strcpy(cmd_dir, "este");
  }
  else if(strcmp(dir, "s") == 0) {
    enum_dir = S;
    strcpy(cmd_dir, "sur");
  }
  else if(strcmp(dir, "w") == 0) {
    enum_dir = W;
    strcpy(cmd_dir, "oeste");
  }
  else if(strcmp(dir, "u") == 0) {
    enum_dir = U;
    strcpy(cmd_dir, "arriba");
  }
  else if(strcmp(dir, "d") == 0) {
    enum_dir = D;
    strcpy(cmd_dir, "abajo");
  }
  else if(strcmp(dir, "north") == 0) {
    enum_dir = N;
    strcpy(cmd_dir, "norte");
  }
  else if(strcmp(dir, "east") == 0) {
    enum_dir = E;
    strcpy(cmd_dir, "este");
  }
  else if(strcmp(dir, "south") == 0) {
    enum_dir = S;
    strcpy(cmd_dir, "sur");
  }
  else if(strcmp(dir, "west") == 0) {
    enum_dir = W;
    strcpy(cmd_dir, "este");
  }
  else if(strcmp(dir, "up") == 0) {
    enum_dir = U;
    strcpy(cmd_dir, "arriba");
  }
  else if(strcmp(dir, "down") == 0) {
    enum_dir = D;
    strcpy(cmd_dir, "abajo");
  }
  else {
    if (dialogue_get_previous_command(g->dialogue) == MOVE && dialogue_get_previous_command_status(g->dialogue) == ERROR
    && strcmp(dialogue_get_previous_additional_information(g->dialogue), dir) == 0
    && dialogue_get_previous_player_location(g->dialogue) == game_get_player_location(g)) {
      dialogue_set_previous_command(g->dialogue, MOVE);
      dialogue_set_previous_command_status(g->dialogue, ERROR);
      dialogue_set_previous_additional_information(g->dialogue, dir);
      dialogue_set_previous_player_location(g->dialogue, game_get_player_location(g));
      dialogue_set_command_result(g->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
      game_set_last_command_status(g, ERROR);
      return;
    }
    dialogue_set_previous_command(g->dialogue, MOVE);
    dialogue_set_previous_command_status(g->dialogue, ERROR);
    dialogue_set_previous_additional_information(g->dialogue, dir);
    dialogue_set_previous_player_location(g->dialogue, game_get_player_location(g));
    sprintf(cmd_result, "'%s' no es una direccion valida. Prueba otra accion.", dir);
    dialogue_set_command_result(g->dialogue, cmd_result);
    game_set_last_command_status(g, ERROR);
    return;
  }

  space_id = game_get_player_location(g);
  if (space_id == NO_ID) {
    if (dialogue_get_previous_command(g->dialogue) == MOVE && dialogue_get_previous_command_status(g->dialogue) == ERROR
    && strcmp(dialogue_get_previous_additional_information(g->dialogue), dir) == 0
    && dialogue_get_previous_player_location(g->dialogue) == game_get_player_location(g)) {
      dialogue_set_previous_command(g->dialogue, MOVE);
      dialogue_set_previous_command_status(g->dialogue, ERROR);
      dialogue_set_previous_additional_information(g->dialogue, dir);
      dialogue_set_previous_player_location(g->dialogue, game_get_player_location(g));
      dialogue_set_command_result(g->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
      game_set_last_command_status(g, ERROR);
      return;
    }
    dialogue_set_previous_command(g->dialogue, MOVE);
    dialogue_set_previous_command_status(g->dialogue, ERROR);
    dialogue_set_previous_additional_information(g->dialogue, dir);
    dialogue_set_previous_player_location(g->dialogue, game_get_player_location(g));
    sprintf(cmd_result, "No se pudo mover a '%s'. Prueba otra accion", cmd_dir);
    dialogue_set_command_result(g->dialogue, "No se pudo mover. Prueba otra accion.");
    game_set_last_command_status(g, ERROR);
    return;
  }

  if (enum_dir != I) {
    if (game_get_connection_status(g, space_id, enum_dir) == OPEN) {
      current_id = game_get_connection(g, space_id, enum_dir);
    }
    else if (game_get_connection_status(g, space_id, enum_dir) == CLOSE){
      for (i = 0; i < MAX_LINKS && g->links[i] != NULL; i++) {
        if (link_get_origin(g->links[i]) == space_id && link_get_direction(g->links[i]) == enum_dir) {
          if (dialogue_get_previous_command(g->dialogue) == MOVE && dialogue_get_previous_command_status(g->dialogue) == ERROR
          && strcmp(dialogue_get_previous_additional_information(g->dialogue), dir) == 0
          && dialogue_get_previous_player_location(g->dialogue) == game_get_player_location(g)) {
            dialogue_set_previous_command(g->dialogue, MOVE);
            dialogue_set_previous_command_status(g->dialogue, ERROR);
            dialogue_set_previous_additional_information(g->dialogue, dir);
            dialogue_set_previous_player_location(g->dialogue, game_get_player_location(g));
            dialogue_set_command_result(g->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
            game_set_last_command_status(g, ERROR);
            return;
          }
          dialogue_set_previous_command(g->dialogue, MOVE);
          dialogue_set_previous_command_status(g->dialogue, ERROR);
          dialogue_set_previous_additional_information(g->dialogue, dir);
          dialogue_set_previous_player_location(g->dialogue, game_get_player_location(g));
          sprintf(cmd_result, "No se pudo mover el enlace '%s' esta cerrado. Prueba otra accion.", link_get_name(g->links[i]));
          dialogue_set_command_result(g->dialogue, cmd_result);
          game_set_last_command_status(g, ERROR);
          return;
        }
      }
    }
  }  

  if (current_id != NO_ID) {
    game_set_player_location(g, current_id);
    dialogue_set_previous_command(g->dialogue, MOVE);
    dialogue_set_previous_command_status(g->dialogue, OK);
    dialogue_set_previous_additional_information(g->dialogue, dir);
    dialogue_set_previous_player_location(g->dialogue, game_get_player_location(g));
    sprintf(cmd_result, "Te has movido a '%s' ahora estas en el espacio '%ld'.", cmd_dir, current_id);
    dialogue_set_command_result(g->dialogue, cmd_result);
    game_set_last_command_status(g, OK);
    return;
  }
  
  if (dialogue_get_previous_command(g->dialogue) == MOVE && dialogue_get_previous_command_status(g->dialogue) == ERROR
  && strcmp(dialogue_get_previous_additional_information(g->dialogue), dir) == 0
  && dialogue_get_previous_player_location(g->dialogue) == game_get_player_location(g)) {
    dialogue_set_previous_command(g->dialogue, MOVE);
    dialogue_set_previous_command_status(g->dialogue, ERROR);
    dialogue_set_previous_additional_information(g->dialogue, dir);
    dialogue_set_previous_player_location(g->dialogue, game_get_player_location(g));
    dialogue_set_command_result(g->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
    game_set_last_command_status(g, ERROR);
    return;
  }
  dialogue_set_previous_command(g->dialogue, MOVE);
  dialogue_set_previous_command_status(g->dialogue, ERROR);
  dialogue_set_previous_additional_information(g->dialogue, dir);
  dialogue_set_previous_player_location(g->dialogue, game_get_player_location(g));
  sprintf(cmd_result, "No hay enlace hacia '%s'. Prueba otra accion.", cmd_dir);
  dialogue_set_command_result(g->dialogue, cmd_result);
  game_set_last_command_status(g, ERROR);
  return;
}

/** game_command_attack game command to
  * attack the enemies 
  */
void game_command_attack(Game *game, char *enemies_name) {
  short random_number = -1, player_health = -1, enemy_health = -1;
  Id enemy_location = NO_ID;
  Id player_location = NO_ID;
  int i;
  char cmd_result[WORD_SIZE] = "";

  if (!game || !enemies_name) {
    if (dialogue_get_previous_command(game->dialogue) == ATTACK && dialogue_get_previous_command_status(game->dialogue) == ERROR
    && strcmp(dialogue_get_previous_additional_information(game->dialogue), enemies_name) == 0
    && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
      dialogue_set_previous_command(game->dialogue, ATTACK);
      dialogue_set_previous_command_status(game->dialogue, ERROR);
      dialogue_set_previous_additional_information(game->dialogue, enemies_name);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
      game_set_last_command_status(game, ERROR);
      return;
    }
    dialogue_set_previous_command(game->dialogue, ATTACK);
    dialogue_set_previous_command_status(game->dialogue, ERROR);
    dialogue_set_previous_additional_information(game->dialogue, enemies_name);
    dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
    dialogue_set_command_result(game->dialogue, "No se pudo atacar. Prueba otra accion.");
    game_set_last_command_status(game, ERROR);
    return;
  }

  if (enemies_name[0] == '\0') {
    if (dialogue_get_previous_command(game->dialogue) == ATTACK && dialogue_get_previous_command_status(game->dialogue) == ERROR
    && strcmp(dialogue_get_previous_additional_information(game->dialogue), enemies_name) == 0
    && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
      dialogue_set_previous_command(game->dialogue, ATTACK);
      dialogue_set_previous_command_status(game->dialogue, ERROR);
      dialogue_set_previous_additional_information(game->dialogue, enemies_name);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
      game_set_last_command_status(game, ERROR);
      return;
    }
    dialogue_set_previous_command(game->dialogue, ATTACK);
    dialogue_set_previous_command_status(game->dialogue, ERROR);
    dialogue_set_previous_additional_information(game->dialogue, enemies_name);
    dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
    dialogue_set_command_result(game->dialogue, "Debes introducir: 'attack <nombre_enemigo>'.");
    game_set_last_command_status(game, ERROR);
    return;
  }

  player_location = game_get_player_location(game);
  if (player_location == NO_ID) {
    if (dialogue_get_previous_command(game->dialogue) == ATTACK && dialogue_get_previous_command_status(game->dialogue) == ERROR
    && strcmp(dialogue_get_previous_additional_information(game->dialogue), enemies_name) == 0
    && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
      dialogue_set_previous_command(game->dialogue, ATTACK);
      dialogue_set_previous_command_status(game->dialogue, ERROR);
      dialogue_set_previous_additional_information(game->dialogue, enemies_name);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
      game_set_last_command_status(game, ERROR);
      return;
    }
    dialogue_set_previous_command(game->dialogue, ATTACK);
    dialogue_set_previous_command_status(game->dialogue, ERROR);
    dialogue_set_previous_additional_information(game->dialogue, enemies_name);
    dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
    sprintf(cmd_result, "No se pudo atacar a '%s'. Prueba otra accion.", enemies_name);
    dialogue_set_command_result(game->dialogue, cmd_result);
    game_set_last_command_status(game, ERROR);
    return;
  }

  for (i = 0; i < MAX_ENEMIES && game->enemies[i] != NULL && enemy_location == NO_ID; i++){
    if (strcmp(enemy_get_name(game->enemies[i]), enemies_name) == 0){
      enemy_location = enemy_get_location(game->enemies[i]);
    }
  }

  if (enemy_location == NO_ID) {
    if (dialogue_get_previous_command(game->dialogue) == ATTACK && dialogue_get_previous_command_status(game->dialogue) == ERROR
    && strcmp(dialogue_get_previous_additional_information(game->dialogue), enemies_name) == 0
    && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
      dialogue_set_previous_command(game->dialogue, ATTACK);
      dialogue_set_previous_command_status(game->dialogue, ERROR);
      dialogue_set_previous_additional_information(game->dialogue, enemies_name);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
      game_set_last_command_status(game, ERROR);
      return;
    }
    dialogue_set_previous_command(game->dialogue, ATTACK);
    dialogue_set_previous_command_status(game->dialogue, ERROR);
    dialogue_set_previous_additional_information(game->dialogue, enemies_name);
    dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
    sprintf(cmd_result, "'%s' no existe. Prueba otra accion.", enemies_name);
    dialogue_set_command_result(game->dialogue, cmd_result);
    game_set_last_command_status(game, ERROR);
    return;
  }
  
  if (player_location == enemy_location) {
    enemy_health = enemy_get_health(game->enemies[i-1]);
    if (enemy_health == 0) {
      if (dialogue_get_previous_command(game->dialogue) == ATTACK && dialogue_get_previous_command_status(game->dialogue) == ERROR
      && strcmp(dialogue_get_previous_additional_information(game->dialogue), enemies_name) == 0
      && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
        dialogue_set_previous_command(game->dialogue, ATTACK);
        dialogue_set_previous_command_status(game->dialogue, ERROR);
        dialogue_set_previous_additional_information(game->dialogue, enemies_name);
        dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
        dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
        game_set_last_command_status(game, ERROR);
        return;
      }
      dialogue_set_previous_command(game->dialogue, ATTACK);
      dialogue_set_previous_command_status(game->dialogue, ERROR);
      dialogue_set_previous_additional_information(game->dialogue, enemies_name);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      sprintf(cmd_result, "'%s' ha sido ya derrotado. Prueba otra accion.", enemies_name);
      dialogue_set_command_result(game->dialogue, cmd_result);
      game_set_last_command_status(game, ERROR);
      return;
    }
    player_health = player_get_health(game->player);

    srand(time(NULL));
    random_number = rand() % 10;
    if (random_number >= 0 && random_number <= 4) {
      player_set_health(game->player, player_health-1);
      dialogue_set_previous_command(game->dialogue, ATTACK);
      dialogue_set_previous_command_status(game->dialogue, OK);
      dialogue_set_previous_additional_information(game->dialogue, enemies_name);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      sprintf(cmd_result, "'%s' te ha atacado tu salud es de: %d puntos.", enemies_name, player_get_health(game->player));
      dialogue_set_command_result(game->dialogue, cmd_result);
      game_set_last_command_status(game, OK);
      return;
    }
    else {
      enemy_set_health(game->enemies[i-1], enemy_health - player_get_power(game->player));
      dialogue_set_previous_command(game->dialogue, ATTACK);
      dialogue_set_previous_command_status(game->dialogue, OK);
      dialogue_set_previous_additional_information(game->dialogue, enemies_name);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      sprintf(cmd_result, "Has atacado a '%s' su salud es de: %d puntos.", enemies_name, enemy_get_health(game->enemies[i-1]));
      dialogue_set_command_result(game->dialogue, cmd_result);
      game_set_last_command_status(game, OK);
      return;
    }
  }
  
  if (dialogue_get_previous_command(game->dialogue) == ATTACK && dialogue_get_previous_command_status(game->dialogue) == ERROR
  && strcmp(dialogue_get_previous_additional_information(game->dialogue), enemies_name) == 0
  && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
    dialogue_set_previous_command(game->dialogue, ATTACK);
    dialogue_set_previous_command_status(game->dialogue, ERROR);
    dialogue_set_previous_additional_information(game->dialogue, enemies_name);
    dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
    dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
    game_set_last_command_status(game, ERROR);
    return;
  }
  dialogue_set_previous_command(game->dialogue, ATTACK);
  dialogue_set_previous_command_status(game->dialogue, ERROR);
  dialogue_set_previous_additional_information(game->dialogue, enemies_name);
  dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
  sprintf(cmd_result, "No estas en el mismo espacio que '%s'. Prueba otra accion.", enemies_name);
  dialogue_set_command_result(game->dialogue, cmd_result);
  game_set_last_command_status(game, ERROR);
  return;
}

/** game_command_inspect game command to
  * get the description of an object or a space
  */
void game_command_inspect(Game *game, char *to_inspect_name) {
  Id *objects_in_space = NULL;
  int n_objects_in_space = 0;
  Id object_id = NO_ID, player_location = NO_ID, object_location = NO_ID;
  Object *object = NULL;
  char *aux_desc = NULL, desc[WORD_SIZE] = "";
  Space* space = NULL;
  int i = 0;
  char cmd_result[WORD_SIZE] = "";

  if (!game || !to_inspect_name) {
    if (dialogue_get_previous_command(game->dialogue) == INSPECT && dialogue_get_previous_command_status(game->dialogue) == ERROR
    && strcmp(dialogue_get_previous_additional_information(game->dialogue), to_inspect_name) == 0
    && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
      dialogue_set_previous_command(game->dialogue, INSPECT);
      dialogue_set_previous_command_status(game->dialogue, ERROR);
      dialogue_set_previous_additional_information(game->dialogue, to_inspect_name);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
      game_set_last_command_status(game, ERROR);
      return;
    }
    dialogue_set_previous_command(game->dialogue, INSPECT);
    dialogue_set_previous_command_status(game->dialogue, ERROR);
    dialogue_set_previous_additional_information(game->dialogue, to_inspect_name);
    dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
    dialogue_set_command_result(game->dialogue, "No se pudo inspeccionar. Prueba otra accion.");
    game_set_last_command_status(game, ERROR);
    return;
  }

  if (to_inspect_name[0] == '\0') {
    if (dialogue_get_previous_command(game->dialogue) == INSPECT && dialogue_get_previous_command_status(game->dialogue) == ERROR
    && strcmp(dialogue_get_previous_additional_information(game->dialogue), to_inspect_name) == 0
    && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
      dialogue_set_previous_command(game->dialogue, INSPECT);
      dialogue_set_previous_command_status(game->dialogue, ERROR);
      dialogue_set_previous_additional_information(game->dialogue, to_inspect_name);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
      game_set_last_command_status(game, ERROR);
      return;
    }
    dialogue_set_previous_command(game->dialogue, INSPECT);
    dialogue_set_previous_command_status(game->dialogue, ERROR);
    dialogue_set_previous_additional_information(game->dialogue, to_inspect_name);
    dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
    dialogue_set_command_result(game->dialogue, "Debes introducir: 'inspect <nombre_objeto>' o 'inspect space'");
    game_set_last_command_status(game, ERROR);
    return;
  }

  player_location = game_get_player_location(game);

  if (strcmp(to_inspect_name,"space") == 0 || strcmp(to_inspect_name,"s") == 0) {	
    if (player_location == NO_ID) {
      if (dialogue_get_previous_command(game->dialogue) == INSPECT && dialogue_get_previous_command_status(game->dialogue) == ERROR
      && strcmp(dialogue_get_previous_additional_information(game->dialogue), to_inspect_name) == 0
      && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
        dialogue_set_previous_command(game->dialogue, INSPECT);
        dialogue_set_previous_command_status(game->dialogue, ERROR);
        dialogue_set_previous_additional_information(game->dialogue, to_inspect_name);
        dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
        dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
        game_set_last_command_status(game, ERROR);
        return;
      }
      dialogue_set_previous_command(game->dialogue, INSPECT);
      dialogue_set_previous_command_status(game->dialogue, ERROR);
      dialogue_set_previous_additional_information(game->dialogue, to_inspect_name);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      sprintf(cmd_result, "No se pudo inspeccionar el espacio actual. Prueba otra accion.");
      dialogue_set_command_result(game->dialogue, cmd_result);
      game_set_last_command_status(game, ERROR);
      return;
    }

    space = game_get_space(game,player_location);
    if(space == NULL){
      if (dialogue_get_previous_command(game->dialogue) == INSPECT && dialogue_get_previous_command_status(game->dialogue) == ERROR
      && strcmp(dialogue_get_previous_additional_information(game->dialogue), to_inspect_name) == 0
      && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
        dialogue_set_previous_command(game->dialogue, INSPECT);
        dialogue_set_previous_command_status(game->dialogue, ERROR);
        dialogue_set_previous_additional_information(game->dialogue, to_inspect_name);
        dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
        dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
        game_set_last_command_status(game, ERROR);
        return;
      }
      dialogue_set_previous_command(game->dialogue, INSPECT);
      dialogue_set_previous_command_status(game->dialogue, ERROR);
      dialogue_set_previous_additional_information(game->dialogue, to_inspect_name);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      sprintf(cmd_result, "No se pudo inspeccionar el espacio actual. Prueba otra accion.");
      dialogue_set_command_result(game->dialogue, cmd_result);
      game_set_last_command_status(game, ERROR);
      return;
    }
    
    if (space_get_light(space) == TRUE || game_player_can_illuminate(game) == TRUE) {
      aux_desc = space_get_detailed_desc(space);
      if (!aux_desc){
        if (dialogue_get_previous_command(game->dialogue) == INSPECT && dialogue_get_previous_command_status(game->dialogue) == ERROR
        && strcmp(dialogue_get_previous_additional_information(game->dialogue), to_inspect_name) == 0
        && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
          dialogue_set_previous_command(game->dialogue, INSPECT);
          dialogue_set_previous_command_status(game->dialogue, ERROR);
          dialogue_set_previous_additional_information(game->dialogue, to_inspect_name);
          dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
          dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
          game_set_last_command_status(game, ERROR);
          return;
        }
        dialogue_set_previous_command(game->dialogue, INSPECT);
        dialogue_set_previous_command_status(game->dialogue, ERROR);
        dialogue_set_previous_additional_information(game->dialogue, to_inspect_name);
        dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
        sprintf(cmd_result, "No se pudo inspeccionar el espacio %ld. Prueba otra accion.", player_location);
        dialogue_set_command_result(game->dialogue, cmd_result);
        game_set_last_command_status(game, ERROR);
        return;
      }
      sprintf(desc, "%s %ld - %s", "espacio", player_location, aux_desc);
      if (game_set_last_description(game, desc) == ERROR){
        if (dialogue_get_previous_command(game->dialogue) == INSPECT && dialogue_get_previous_command_status(game->dialogue) == ERROR
        && strcmp(dialogue_get_previous_additional_information(game->dialogue), to_inspect_name) == 0
        && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
          dialogue_set_previous_command(game->dialogue, INSPECT);
          dialogue_set_previous_command_status(game->dialogue, ERROR);
          dialogue_set_previous_additional_information(game->dialogue, to_inspect_name);
          dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
          dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
          game_set_last_command_status(game, ERROR);
          return;
        }
        dialogue_set_previous_command(game->dialogue, INSPECT);
        dialogue_set_previous_command_status(game->dialogue, ERROR);
        dialogue_set_previous_additional_information(game->dialogue, to_inspect_name);
        dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
        sprintf(cmd_result, "Espacio %ld ya inspeccionado. Prueba otra accion.", player_location);
        dialogue_set_command_result(game->dialogue, cmd_result);
        game_set_last_command_status(game, ERROR);
        return;
      }

      objects_in_space = space_get_objects(space);
      n_objects_in_space = space_get_n_objects(space);

      for (i = 0; i < n_objects_in_space; i++) {
        object = game_get_object_from_id(game, objects_in_space[i]);
        if(object != NULL) {
          object_set_hidden(object, FALSE);
        }
      }  
    }
    else {
      if (dialogue_get_previous_command(game->dialogue) == INSPECT && dialogue_get_previous_command_status(game->dialogue) == ERROR
      && strcmp(dialogue_get_previous_additional_information(game->dialogue), to_inspect_name) == 0
      && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
        dialogue_set_previous_command(game->dialogue, INSPECT);
        dialogue_set_previous_command_status(game->dialogue, ERROR);
        dialogue_set_previous_additional_information(game->dialogue, to_inspect_name);
        dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
        dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
        game_set_last_command_status(game, ERROR);
        return;
      }
      dialogue_set_previous_command(game->dialogue, INSPECT);
      dialogue_set_previous_command_status(game->dialogue, ERROR);
      dialogue_set_previous_additional_information(game->dialogue, to_inspect_name);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      sprintf(cmd_result, "Espacio %ld apagado. Prueba otra accion.", player_location);
      dialogue_set_command_result(game->dialogue, cmd_result);
      game_set_last_command_status(game, ERROR);
      return;
    }

    dialogue_set_previous_command(game->dialogue, INSPECT);
    dialogue_set_previous_command_status(game->dialogue, OK);
    dialogue_set_previous_additional_information(game->dialogue, to_inspect_name);
    dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
    sprintf(cmd_result, "Espacio %ld inspeccionado correctamente.", player_location);
    dialogue_set_command_result(game->dialogue, cmd_result);
    game_set_last_command_status(game, OK);
    return;
  }

  object_id = game_get_object_id_from_name(game, to_inspect_name);
  if (object_id == NO_ID) {
    if (dialogue_get_previous_command(game->dialogue) == INSPECT && dialogue_get_previous_command_status(game->dialogue) == ERROR
    && strcmp(dialogue_get_previous_additional_information(game->dialogue), to_inspect_name) == 0
    && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
      dialogue_set_previous_command(game->dialogue, INSPECT);
      dialogue_set_previous_command_status(game->dialogue, ERROR);
      dialogue_set_previous_additional_information(game->dialogue, to_inspect_name);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
      game_set_last_command_status(game, ERROR);
      return;
    }
    dialogue_set_previous_command(game->dialogue, INSPECT);
    dialogue_set_previous_command_status(game->dialogue, ERROR);
    dialogue_set_previous_additional_information(game->dialogue, to_inspect_name);
    dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
    sprintf(cmd_result, "No existe '%s'. Prueba otra accion.", to_inspect_name);
    dialogue_set_command_result(game->dialogue, cmd_result);
    game_set_last_command_status(game, ERROR);
    return;
  }

  object = game_get_object_from_name(game, to_inspect_name);
  if (object == NULL) {
    if (dialogue_get_previous_command(game->dialogue) == INSPECT && dialogue_get_previous_command_status(game->dialogue) == ERROR
    && strcmp(dialogue_get_previous_additional_information(game->dialogue), to_inspect_name) == 0
    && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
      dialogue_set_previous_command(game->dialogue, INSPECT);
      dialogue_set_previous_command_status(game->dialogue, ERROR);
      dialogue_set_previous_additional_information(game->dialogue, to_inspect_name);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
      game_set_last_command_status(game, ERROR);
      return;
    }
    dialogue_set_previous_command(game->dialogue, INSPECT);
    dialogue_set_previous_command_status(game->dialogue, ERROR);
    dialogue_set_previous_additional_information(game->dialogue, to_inspect_name);
    dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
    sprintf(cmd_result, "No existe '%s'. Prueba otra accion.", to_inspect_name);
    dialogue_set_command_result(game->dialogue, cmd_result);
    game_set_last_command_status(game, ERROR);
    return;
  }

  player_location = game_get_player_location(game);
  if (player_location == NO_ID) {
    if (dialogue_get_previous_command(game->dialogue) == INSPECT && dialogue_get_previous_command_status(game->dialogue) == ERROR
    && strcmp(dialogue_get_previous_additional_information(game->dialogue), to_inspect_name) == 0
    && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
      dialogue_set_previous_command(game->dialogue, INSPECT);
      dialogue_set_previous_command_status(game->dialogue, ERROR);
      dialogue_set_previous_additional_information(game->dialogue, to_inspect_name);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
      game_set_last_command_status(game, ERROR);
      return;
    }
    dialogue_set_previous_command(game->dialogue, INSPECT);
    dialogue_set_previous_command_status(game->dialogue, ERROR);
    dialogue_set_previous_additional_information(game->dialogue, to_inspect_name);
    dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
    sprintf(cmd_result, "No se pudo inspeccionar '%s'. Prueba otra accion.", to_inspect_name);
    dialogue_set_command_result(game->dialogue, cmd_result);
    game_set_last_command_status(game, ERROR);
    return;
  }
  object_location = game_get_object_location(game, object_id);
  if ( object_location == player_location  || player_inventory_stores(game_get_player(game), object_id) == TRUE ) {
    if (space_get_light(game_get_space(game, player_location)) == FALSE && game_player_can_illuminate(game) == FALSE){
      if (dialogue_get_previous_command(game->dialogue) == INSPECT && dialogue_get_previous_command_status(game->dialogue) == ERROR
      && strcmp(dialogue_get_previous_additional_information(game->dialogue), to_inspect_name) == 0
      && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
        dialogue_set_previous_command(game->dialogue, INSPECT);
        dialogue_set_previous_command_status(game->dialogue, ERROR);
        dialogue_set_previous_additional_information(game->dialogue, to_inspect_name);
        dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
        dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
        game_set_last_command_status(game, ERROR);
        return;
      }
      dialogue_set_previous_command(game->dialogue, INSPECT);
      dialogue_set_previous_command_status(game->dialogue, ERROR);
      dialogue_set_previous_additional_information(game->dialogue, to_inspect_name);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      sprintf(cmd_result, "'%s' no inspeccionado: espacio %ld apagado. Prueba otra accion.", to_inspect_name, player_location);
      dialogue_set_command_result(game->dialogue, cmd_result);
      game_set_last_command_status(game, ERROR);
      return;
    }
    aux_desc = object_get_description(object);
    if (!aux_desc) {
      if (game_set_last_description(game, desc) == ERROR) {
        if (dialogue_get_previous_command(game->dialogue) == INSPECT && dialogue_get_previous_command_status(game->dialogue) == ERROR
        && strcmp(dialogue_get_previous_additional_information(game->dialogue), to_inspect_name) == 0
        && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
          dialogue_set_previous_command(game->dialogue, INSPECT);
          dialogue_set_previous_command_status(game->dialogue, ERROR);
          dialogue_set_previous_additional_information(game->dialogue, to_inspect_name);
          dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
          dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
          game_set_last_command_status(game, ERROR);
          return;
        }
        dialogue_set_previous_command(game->dialogue, INSPECT);
        dialogue_set_previous_command_status(game->dialogue, ERROR);
        dialogue_set_previous_additional_information(game->dialogue, to_inspect_name);
        dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
        sprintf(cmd_result, "No se pudo inspeccionar '%s'. Prueba otra accion.", to_inspect_name);
        dialogue_set_command_result(game->dialogue, cmd_result);
        game_set_last_command_status(game, ERROR);
        return;
      }
    }
    sprintf(desc, "%s - %s", to_inspect_name, aux_desc);
    if (game_set_last_description(game, desc) == ERROR) {
      if (dialogue_get_previous_command(game->dialogue) == INSPECT && dialogue_get_previous_command_status(game->dialogue) == ERROR
      && strcmp(dialogue_get_previous_additional_information(game->dialogue), to_inspect_name) == 0
      && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
        dialogue_set_previous_command(game->dialogue, INSPECT);
        dialogue_set_previous_command_status(game->dialogue, ERROR);
        dialogue_set_previous_additional_information(game->dialogue, to_inspect_name);
        dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
        dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
        game_set_last_command_status(game, ERROR);
        return;
      }
      dialogue_set_previous_command(game->dialogue, INSPECT);
      dialogue_set_previous_command_status(game->dialogue, ERROR);
      dialogue_set_previous_additional_information(game->dialogue, to_inspect_name);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      sprintf(cmd_result, "'%s' ya inspeccionado. Prueba otra accion.", to_inspect_name);
      dialogue_set_command_result(game->dialogue, cmd_result);
      game_set_last_command_status(game, ERROR);
      return;
    }
    dialogue_set_previous_command(game->dialogue, INSPECT);
    dialogue_set_previous_command_status(game->dialogue, OK);
    dialogue_set_previous_additional_information(game->dialogue, to_inspect_name);
    dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
    sprintf(cmd_result, "'%s' inspeccionado correctamente.", to_inspect_name);
    dialogue_set_command_result(game->dialogue, cmd_result);
    game_set_last_command_status(game, OK);
    return;
  } 

  if (dialogue_get_previous_command(game->dialogue) == INSPECT && dialogue_get_previous_command_status(game->dialogue) == ERROR
  && strcmp(dialogue_get_previous_additional_information(game->dialogue), to_inspect_name) == 0
  && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
    dialogue_set_previous_command(game->dialogue, INSPECT);
    dialogue_set_previous_command_status(game->dialogue, ERROR);
    dialogue_set_previous_additional_information(game->dialogue, to_inspect_name);
    dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
    dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
    game_set_last_command_status(game, ERROR);
    return;
  }
  dialogue_set_previous_command(game->dialogue, INSPECT);
  dialogue_set_previous_command_status(game->dialogue, ERROR);
  dialogue_set_previous_additional_information(game->dialogue, to_inspect_name);
  dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
  sprintf(cmd_result, "'%s' no se encuentra en el espacio actual. Prueba otra accion.", to_inspect_name);
  dialogue_set_command_result(game->dialogue, cmd_result);
  game_set_last_command_status(game, ERROR);
  return;
}

/** game_command_turnoff game command to turn off an object from the game
  */
void game_command_turnoff(Game *game, char *name){
  Id obj_id = NO_ID;
  Object* obj = NULL;
  char cmd_result[WORD_SIZE] = "";

  if (!game || !name) {
    if (dialogue_get_previous_command(game->dialogue) == TURNOFF && dialogue_get_previous_command_status(game->dialogue) == ERROR
    && strcmp(dialogue_get_previous_additional_information(game->dialogue), name) == 0
    && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
      dialogue_set_previous_command(game->dialogue, TURNOFF);
      dialogue_set_previous_command_status(game->dialogue, ERROR);
      dialogue_set_previous_additional_information(game->dialogue, name);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
      game_set_last_command_status(game, ERROR);
      return;
    }
    dialogue_set_previous_command(game->dialogue, TURNOFF);
    dialogue_set_previous_command_status(game->dialogue, ERROR);
    dialogue_set_previous_additional_information(game->dialogue, name);
    dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
    dialogue_set_command_result(game->dialogue, "No se pudo apagar. Prueba otra accion.");
    game_set_last_command_status(game, ERROR);
    return;
  }
  if(name[0] == '\0') {
    if (dialogue_get_previous_command(game->dialogue) == TURNOFF && dialogue_get_previous_command_status(game->dialogue) == ERROR
    && strcmp(dialogue_get_previous_additional_information(game->dialogue), name) == 0
    && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
      dialogue_set_previous_command(game->dialogue, TURNOFF);
      dialogue_set_previous_command_status(game->dialogue, ERROR);
      dialogue_set_previous_additional_information(game->dialogue, name);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
      game_set_last_command_status(game, ERROR);
      return;
    }
    dialogue_set_previous_command(game->dialogue, TURNOFF);
    dialogue_set_previous_command_status(game->dialogue, ERROR);
    dialogue_set_previous_additional_information(game->dialogue, name);
    dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
    dialogue_set_command_result(game->dialogue, "Debes introducir: 'turnoff <nombre_objeto>'.");
    game_set_last_command_status(game, ERROR);
    return;
  }
  obj_id = game_get_object_id_from_name(game,name);
  if (obj_id == NO_ID) {
    if (dialogue_get_previous_command(game->dialogue) == TURNOFF && dialogue_get_previous_command_status(game->dialogue) == ERROR
    && strcmp(dialogue_get_previous_additional_information(game->dialogue), name) == 0
    && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
      dialogue_set_previous_command(game->dialogue, TURNOFF);
      dialogue_set_previous_command_status(game->dialogue, ERROR);
      dialogue_set_previous_additional_information(game->dialogue, name);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
      game_set_last_command_status(game, ERROR);
      return;
    }
    dialogue_set_previous_command(game->dialogue, TURNOFF);
    dialogue_set_previous_command_status(game->dialogue, ERROR);
    dialogue_set_previous_additional_information(game->dialogue, name);
    dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
    sprintf(cmd_result, "No existe '%s'. Prueba otra accion.", name);
    dialogue_set_command_result(game->dialogue, cmd_result);
    game_set_last_command_status(game, ERROR);
    return;
  }
  obj = game_get_object_from_name(game,name);
  if (obj == NULL) {
    if (dialogue_get_previous_command(game->dialogue) == TURNOFF && dialogue_get_previous_command_status(game->dialogue) == ERROR
    && strcmp(dialogue_get_previous_additional_information(game->dialogue), name) == 0
    && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
      dialogue_set_previous_command(game->dialogue, TURNOFF);
      dialogue_set_previous_command_status(game->dialogue, ERROR);
      dialogue_set_previous_additional_information(game->dialogue, name);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
      game_set_last_command_status(game, ERROR);
      return;
    }
    dialogue_set_previous_command(game->dialogue, TURNOFF);
    dialogue_set_previous_command_status(game->dialogue, ERROR);
    dialogue_set_previous_additional_information(game->dialogue, name);
    dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
    sprintf(cmd_result, "No existe '%s'. Prueba otra accion.", name);
    dialogue_set_command_result(game->dialogue, cmd_result);
    game_set_last_command_status(game, ERROR);
    return;
  }
  if (player_inventory_stores(game->player, obj_id) == TRUE) {
    if (object_get_turnedon(obj) == TRUE) {
      if (object_set_turnedon(obj, FALSE) == ERROR) {
        if (dialogue_get_previous_command(game->dialogue) == TURNOFF && dialogue_get_previous_command_status(game->dialogue) == ERROR
        && strcmp(dialogue_get_previous_additional_information(game->dialogue), name) == 0
        && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
          dialogue_set_previous_command(game->dialogue, TURNOFF);
          dialogue_set_previous_command_status(game->dialogue, ERROR);
          dialogue_set_previous_additional_information(game->dialogue, name);
          dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
          dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
          game_set_last_command_status(game, ERROR);
          return;
        }
        dialogue_set_previous_command(game->dialogue, TURNOFF);
        dialogue_set_previous_command_status(game->dialogue, ERROR);
        dialogue_set_previous_additional_information(game->dialogue, name);
        dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
        sprintf(cmd_result, "No se pudo apagar '%s'. Prueba otra accion.", name);
        dialogue_set_command_result(game->dialogue, cmd_result);
        game_set_last_command_status(game, ERROR);
        return;
      }
    }
    else {
      if (dialogue_get_previous_command(game->dialogue) == TURNOFF && dialogue_get_previous_command_status(game->dialogue) == ERROR
      && strcmp(dialogue_get_previous_additional_information(game->dialogue), name) == 0
      && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
        dialogue_set_previous_command(game->dialogue, TURNOFF);
        dialogue_set_previous_command_status(game->dialogue, ERROR);
        dialogue_set_previous_additional_information(game->dialogue, name);
        dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
        dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
        game_set_last_command_status(game, ERROR);
        return;
      }
      dialogue_set_previous_command(game->dialogue, TURNOFF);
      dialogue_set_previous_command_status(game->dialogue, ERROR);
      dialogue_set_previous_additional_information(game->dialogue, name);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      sprintf(cmd_result, "'%s' esta apagado ya. Prueba otra accion.", name);
      dialogue_set_command_result(game->dialogue, cmd_result);
      game_set_last_command_status(game, ERROR);
      return;
    }
  }
  else {
    if (dialogue_get_previous_command(game->dialogue) == TURNOFF && dialogue_get_previous_command_status(game->dialogue) == ERROR
      && strcmp(dialogue_get_previous_additional_information(game->dialogue), name) == 0
      && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
      dialogue_set_previous_command(game->dialogue, TURNOFF);
      dialogue_set_previous_command_status(game->dialogue, ERROR);
      dialogue_set_previous_additional_information(game->dialogue, name);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
      game_set_last_command_status(game, ERROR);
      return;
    }
    dialogue_set_previous_command(game->dialogue, TURNOFF);
    dialogue_set_previous_command_status(game->dialogue, ERROR);
    dialogue_set_previous_additional_information(game->dialogue, name);
    dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
    sprintf(cmd_result, "No tienes'%s' en el inventario. Prueba otra accion.", name);
    dialogue_set_command_result(game->dialogue, cmd_result);
    game_set_last_command_status(game, ERROR);
    return;
  }
  dialogue_set_previous_command(game->dialogue, TURNOFF);
  dialogue_set_previous_command_status(game->dialogue, OK);
  dialogue_set_previous_additional_information(game->dialogue, name);
  dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
  sprintf(cmd_result, "'%s' apagado correctamente.", name);
  dialogue_set_command_result(game->dialogue, cmd_result);
  game_set_last_command_status(game, OK);
  return;
}


/** game_command_turnon game command to turn on an object from the game
  */
void game_command_turnon(Game *game, char *name){
  Id obj_id = NO_ID;
  Object* obj = NULL;
  char cmd_result[WORD_SIZE] = "";

  if (!game || !name) {
    if (dialogue_get_previous_command(game->dialogue) == TURNON && dialogue_get_previous_command_status(game->dialogue) == ERROR
    && strcmp(dialogue_get_previous_additional_information(game->dialogue), name) == 0
    && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
      dialogue_set_previous_command(game->dialogue, TURNON);
      dialogue_set_previous_command_status(game->dialogue, ERROR);
      dialogue_set_previous_additional_information(game->dialogue, name);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
      game_set_last_command_status(game, ERROR);
      return;
    }
    dialogue_set_previous_command(game->dialogue, TURNON);
    dialogue_set_previous_command_status(game->dialogue, ERROR);
    dialogue_set_previous_additional_information(game->dialogue, name);
    dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
    dialogue_set_command_result(game->dialogue, "No se pudo encender. Prueba otra accion.");
    game_set_last_command_status(game, ERROR);
    return;
  }
  if(name[0] == '\0') {
    if (dialogue_get_previous_command(game->dialogue) == TURNON && dialogue_get_previous_command_status(game->dialogue) == ERROR
    && strcmp(dialogue_get_previous_additional_information(game->dialogue), name) == 0
    && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
      dialogue_set_previous_command(game->dialogue, TURNON);
      dialogue_set_previous_command_status(game->dialogue, ERROR);
      dialogue_set_previous_additional_information(game->dialogue, name);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
      game_set_last_command_status(game, ERROR);
      return;
    }
    dialogue_set_previous_command(game->dialogue, TURNON);
    dialogue_set_previous_command_status(game->dialogue, ERROR);
    dialogue_set_previous_additional_information(game->dialogue, name);
    dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
    dialogue_set_command_result(game->dialogue, "Debes introducir: 'turnon <nombre_objeto>'.");
    game_set_last_command_status(game, ERROR);
    return;
  }
  obj_id = game_get_object_id_from_name(game,name);
  if (obj_id == NO_ID) {
    if (dialogue_get_previous_command(game->dialogue) == TURNON && dialogue_get_previous_command_status(game->dialogue) == ERROR
    && strcmp(dialogue_get_previous_additional_information(game->dialogue), name) == 0
    && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
      dialogue_set_previous_command(game->dialogue, TURNON);
      dialogue_set_previous_command_status(game->dialogue, ERROR);
      dialogue_set_previous_additional_information(game->dialogue, name);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
      game_set_last_command_status(game, ERROR);
      return;
    }
    dialogue_set_previous_command(game->dialogue, TURNON);
    dialogue_set_previous_command_status(game->dialogue, ERROR);
    dialogue_set_previous_additional_information(game->dialogue, name);
    dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
    sprintf(cmd_result, "No existe '%s'. Prueba otra accion.", name);
    dialogue_set_command_result(game->dialogue, cmd_result);
    game_set_last_command_status(game, ERROR);
    return;
  }
  obj = game_get_object_from_name(game,name);
  if (obj == NULL) {
    if (dialogue_get_previous_command(game->dialogue) == TURNON && dialogue_get_previous_command_status(game->dialogue) == ERROR
    && strcmp(dialogue_get_previous_additional_information(game->dialogue), name) == 0
    && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
      dialogue_set_previous_command(game->dialogue, TURNON);
      dialogue_set_previous_command_status(game->dialogue, ERROR);
      dialogue_set_previous_additional_information(game->dialogue, name);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
      game_set_last_command_status(game, ERROR);
      return;
    }
    dialogue_set_previous_command(game->dialogue, TURNON);
    dialogue_set_previous_command_status(game->dialogue, ERROR);
    dialogue_set_previous_additional_information(game->dialogue, name);
    dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
    sprintf(cmd_result, "No existe '%s'. Prueba otra accion.", name);
    dialogue_set_command_result(game->dialogue, cmd_result);
    game_set_last_command_status(game, ERROR);
    return;
  }
  if (player_inventory_stores(game->player, obj_id) == TRUE) {
    if (object_get_turnedon(obj) == FALSE) {
      if (object_set_turnedon(obj, TRUE) == ERROR) {
        if (dialogue_get_previous_command(game->dialogue) == TURNON && dialogue_get_previous_command_status(game->dialogue) == ERROR
        && strcmp(dialogue_get_previous_additional_information(game->dialogue), name) == 0
        && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
          dialogue_set_previous_command(game->dialogue, TURNON);
          dialogue_set_previous_command_status(game->dialogue, ERROR);
          dialogue_set_previous_additional_information(game->dialogue, name);
          dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
          dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
          game_set_last_command_status(game, ERROR);
          return;
        }
        dialogue_set_previous_command(game->dialogue, TURNON);
        dialogue_set_previous_command_status(game->dialogue, ERROR);
        dialogue_set_previous_additional_information(game->dialogue, name);
        dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
        sprintf(cmd_result, "No se pudo encender '%s'. Prueba otra accion.", name);
        dialogue_set_command_result(game->dialogue, cmd_result);
        game_set_last_command_status(game, ERROR);
        return;
      }
    }
    else {
      if (dialogue_get_previous_command(game->dialogue) == TURNON && dialogue_get_previous_command_status(game->dialogue) == ERROR
      && strcmp(dialogue_get_previous_additional_information(game->dialogue), name) == 0
      && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
        dialogue_set_previous_command(game->dialogue, TURNON);
        dialogue_set_previous_command_status(game->dialogue, ERROR);
        dialogue_set_previous_additional_information(game->dialogue, name);
        dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
        dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
        game_set_last_command_status(game, ERROR);
        return;
      }
      dialogue_set_previous_command(game->dialogue, TURNON);
      dialogue_set_previous_command_status(game->dialogue, ERROR);
      dialogue_set_previous_additional_information(game->dialogue, name);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      sprintf(cmd_result, "'%s' esta encendido ya. Prueba otra accion.", name);
      dialogue_set_command_result(game->dialogue, cmd_result);
      game_set_last_command_status(game, ERROR);
      return;
    }
  }
  else {
    if (dialogue_get_previous_command(game->dialogue) == TURNON && dialogue_get_previous_command_status(game->dialogue) == ERROR
      && strcmp(dialogue_get_previous_additional_information(game->dialogue), name) == 0
      && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
      dialogue_set_previous_command(game->dialogue, TURNON);
      dialogue_set_previous_command_status(game->dialogue, ERROR);
      dialogue_set_previous_additional_information(game->dialogue, name);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
      game_set_last_command_status(game, ERROR);
      return;
    }
    dialogue_set_previous_command(game->dialogue, TURNON);
    dialogue_set_previous_command_status(game->dialogue, ERROR);
    dialogue_set_previous_additional_information(game->dialogue, name);
    dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
    sprintf(cmd_result, "No tienes'%s' en el inventario. Prueba otra accion.", name);
    dialogue_set_command_result(game->dialogue, cmd_result);
    game_set_last_command_status(game, ERROR);
    return;
  }
  dialogue_set_previous_command(game->dialogue, TURNON);
  dialogue_set_previous_command_status(game->dialogue, OK);
  dialogue_set_previous_additional_information(game->dialogue, name);
  dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
  sprintf(cmd_result, "'%s' encendido correctamente.", name);
  dialogue_set_command_result(game->dialogue, cmd_result);
  game_set_last_command_status(game, OK);
  return;
}

/** game_command_open game command to open a link with an object
  */
void game_command_open(Game *game, char *info){
  int i = 0, flag = 0, spaces;
  char link[64] = "", obj[64] = "", *toks = NULL; 
  Id open_id = NO_ID;
  Link *l = NULL;
  Object *o = NULL;
  char cmd_result[WORD_SIZE] = "", info_copy[WORD_SIZE] = "";

  if (!game || !info){
    if (dialogue_get_previous_command(game->dialogue) == OPENC && dialogue_get_previous_command_status(game->dialogue) == ERROR
    && strcmp(dialogue_get_previous_additional_information(game->dialogue), info) == 0
    && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
      dialogue_set_previous_command(game->dialogue, OPENC);
      dialogue_set_previous_command_status(game->dialogue, ERROR);
      dialogue_set_previous_additional_information(game->dialogue, info);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
      game_set_last_command_status(game, ERROR);
      return;
    }
    dialogue_set_previous_command(game->dialogue, OPENC);
    dialogue_set_previous_command_status(game->dialogue, ERROR);
    dialogue_set_previous_additional_information(game->dialogue, info);
    dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
    dialogue_set_command_result(game->dialogue, "No se pudo abrir. Prueba otra accion.");
    game_set_last_command_status(game, ERROR);
    return;
  }

  if (info[0] == '\0') {
    if (dialogue_get_previous_command(game->dialogue) == OPENC && dialogue_get_previous_command_status(game->dialogue) == ERROR
    && strcmp(dialogue_get_previous_additional_information(game->dialogue), info) == 0
    && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
      dialogue_set_previous_command(game->dialogue, OPENC);
      dialogue_set_previous_command_status(game->dialogue, ERROR);
      dialogue_set_previous_additional_information(game->dialogue, info);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
      game_set_last_command_status(game, ERROR);
      return;
    }
    dialogue_set_previous_command(game->dialogue, OPENC);
    dialogue_set_previous_command_status(game->dialogue, ERROR);
    dialogue_set_previous_additional_information(game->dialogue, info);
    dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
    dialogue_set_command_result(game->dialogue, "Debes introducir: 'open <nombre_enlace> with <nombre_objeto>'.");
    game_set_last_command_status(game, ERROR);
    return;
  }

  for (spaces = 0, i = 0; info[i] != '\0'; i++){
    if (info[i] == ' '){
      spaces++;
    }
  }
  if (spaces != 2){
    if (dialogue_get_previous_command(game->dialogue) == OPENC && dialogue_get_previous_command_status(game->dialogue) == ERROR
    && strcmp(dialogue_get_previous_additional_information(game->dialogue), info) == 0
    && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
      dialogue_set_previous_command(game->dialogue, OPENC);
      dialogue_set_previous_command_status(game->dialogue, ERROR);
      dialogue_set_previous_additional_information(game->dialogue, info);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
      game_set_last_command_status(game, ERROR);
      return;
    }
    dialogue_set_previous_command(game->dialogue, OPENC);
    dialogue_set_previous_command_status(game->dialogue, ERROR);
    dialogue_set_previous_additional_information(game->dialogue, info);
    dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
    dialogue_set_command_result(game->dialogue, "Debes introducir: 'open <nombre_enlace> with <nombre_objeto>'.");
    game_set_last_command_status(game, ERROR);
    return;
  }

  strcpy(info_copy, info);

  toks = strtok(info, " ");
  strcpy(link, toks);

  toks = strtok(NULL, " ");
  if (strcmp(toks, "with") != 0){
    if (dialogue_get_previous_command(game->dialogue) == OPENC && dialogue_get_previous_command_status(game->dialogue) == ERROR
    && strcmp(dialogue_get_previous_additional_information(game->dialogue), info_copy) == 0
    && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
      dialogue_set_previous_command(game->dialogue, OPENC);
      dialogue_set_previous_command_status(game->dialogue, ERROR);
      dialogue_set_previous_additional_information(game->dialogue, info_copy);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
      game_set_last_command_status(game, ERROR);
      return;
    }
    dialogue_set_previous_command(game->dialogue, OPENC);
    dialogue_set_previous_command_status(game->dialogue, ERROR);
    dialogue_set_previous_additional_information(game->dialogue, info_copy);
    dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
    dialogue_set_command_result(game->dialogue, "Debes introducir: 'open <nombre_enlace> with <nombre_objeto>'.");
    game_set_last_command_status(game, ERROR);
    return;
  }

  toks = strtok(NULL, " ");
  strcpy(obj, toks);


  o = game_get_object_from_name(game, obj);
  if (!o) {
    if (dialogue_get_previous_command(game->dialogue) == OPENC && dialogue_get_previous_command_status(game->dialogue) == ERROR
    && strcmp(dialogue_get_previous_additional_information(game->dialogue), info_copy) == 0
    && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
      dialogue_set_previous_command(game->dialogue, OPENC);
      dialogue_set_previous_command_status(game->dialogue, ERROR);
      dialogue_set_previous_additional_information(game->dialogue, info_copy);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
      game_set_last_command_status(game, ERROR);
      return;
    }
    dialogue_set_previous_command(game->dialogue, OPENC);
    dialogue_set_previous_command_status(game->dialogue, ERROR);
    dialogue_set_previous_additional_information(game->dialogue, info_copy);
    dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
    sprintf(cmd_result, "El objeto '%s' no existe. Prueba otra accion.", obj);
    dialogue_set_command_result(game->dialogue, cmd_result);
    game_set_last_command_status(game, ERROR);
    return;
  }
  open_id = object_get_open(o);
  if (open_id == NO_ID){
    if (dialogue_get_previous_command(game->dialogue) == OPENC && dialogue_get_previous_command_status(game->dialogue) == ERROR
    && strcmp(dialogue_get_previous_additional_information(game->dialogue), info_copy) == 0
    && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
      dialogue_set_previous_command(game->dialogue, OPENC);
      dialogue_set_previous_command_status(game->dialogue, ERROR);
      dialogue_set_previous_additional_information(game->dialogue, info_copy);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
      game_set_last_command_status(game, ERROR);
      return;
    }
    dialogue_set_previous_command(game->dialogue, OPENC);
    dialogue_set_previous_command_status(game->dialogue, ERROR);
    dialogue_set_previous_additional_information(game->dialogue, info_copy);
    dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
    sprintf(cmd_result, "El objeto '%s' no abre ningun enlace. Prueba otra accion.", obj);
    dialogue_set_command_result(game->dialogue, cmd_result);
    game_set_last_command_status(game, ERROR);
    return;
  }

  for (i = 0; game_get_link_from_index(game, i) != NULL; i++){
    l = game_get_link_from_index(game, i);
    if (link_get_id(l) == open_id && strcmp(link_get_name(l), link) == 0){
      flag = 1;
      if (link_set_status(l, OPEN) == ERROR){
        if (dialogue_get_previous_command(game->dialogue) == OPENC && dialogue_get_previous_command_status(game->dialogue) == ERROR
        && strcmp(dialogue_get_previous_additional_information(game->dialogue), info_copy) == 0
        && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
          dialogue_set_previous_command(game->dialogue, OPENC);
          dialogue_set_previous_command_status(game->dialogue, ERROR);
          dialogue_set_previous_additional_information(game->dialogue, info_copy);
          dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
          dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
          game_set_last_command_status(game, ERROR);
          return;
        } 
        dialogue_set_previous_command(game->dialogue, OPENC);
        dialogue_set_previous_command_status(game->dialogue, ERROR);
        dialogue_set_previous_additional_information(game->dialogue, info_copy);
        dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
        sprintf(cmd_result, "No se pudo abrir '%s' con '%s'. Prueba otra accion.", link, obj);
        dialogue_set_command_result(game->dialogue, cmd_result);
        game_set_last_command_status(game, ERROR);
        return;
      }
    }
  }
  if(flag == 0){
    if (dialogue_get_previous_command(game->dialogue) == OPENC && dialogue_get_previous_command_status(game->dialogue) == ERROR
    && strcmp(dialogue_get_previous_additional_information(game->dialogue), info_copy) == 0
    && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
      dialogue_set_previous_command(game->dialogue, OPENC);
      dialogue_set_previous_command_status(game->dialogue, ERROR);
      dialogue_set_previous_additional_information(game->dialogue, info_copy);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
      game_set_last_command_status(game, ERROR);
      return;
    }
    dialogue_set_previous_command(game->dialogue, OPENC);
    dialogue_set_previous_command_status(game->dialogue, ERROR);
    dialogue_set_previous_additional_information(game->dialogue, info_copy);
    dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
    sprintf(cmd_result, "No se pudo abrir '%s' con '%s'. Prueba otra accion.", link, obj);
    dialogue_set_command_result(game->dialogue, cmd_result);
    game_set_last_command_status(game, ERROR);
    return;
  }

  dialogue_set_previous_command(game->dialogue, OPENC);
  dialogue_set_previous_command_status(game->dialogue, OK);
  dialogue_set_previous_additional_information(game->dialogue, info_copy);
  dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
  sprintf(cmd_result, "'%s' abierto con '%s'.", link, obj);
  dialogue_set_command_result(game->dialogue, cmd_result);
  game_set_last_command_status(game, OK);
  return;
}



/** game_command_save game command to save the game
  */
void game_command_save(Game *game, char *filename){
  char cmd_result[WORD_SIZE] = "";

  if (!game || !filename) {
    if (dialogue_get_previous_command(game->dialogue) == SAVE && dialogue_get_previous_command_status(game->dialogue) == ERROR
    && strcmp(dialogue_get_previous_additional_information(game->dialogue), filename) == 0
    && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
      dialogue_set_previous_command(game->dialogue, SAVE);
      dialogue_set_previous_command_status(game->dialogue, ERROR);
      dialogue_set_previous_additional_information(game->dialogue, filename);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
      game_set_last_command_status(game, ERROR);
      return;
    }
    dialogue_set_previous_command(game->dialogue, SAVE);
    dialogue_set_previous_command_status(game->dialogue, ERROR);
    dialogue_set_previous_additional_information(game->dialogue, filename);
    dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
    dialogue_set_command_result(game->dialogue, "No se pudo guardar. Prueba otra accion.");
    game_set_last_command_status(game, ERROR);
  }

  if (filename[0] == '\0') {
    if (dialogue_get_previous_command(game->dialogue) == SAVE && dialogue_get_previous_command_status(game->dialogue) == ERROR
    && strcmp(dialogue_get_previous_additional_information(game->dialogue), filename) == 0
    && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
      dialogue_set_previous_command(game->dialogue, SAVE);
      dialogue_set_previous_command_status(game->dialogue, ERROR);
      dialogue_set_previous_additional_information(game->dialogue, filename);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
      game_set_last_command_status(game, ERROR);
      return;
    }
    dialogue_set_previous_command(game->dialogue, SAVE);
    dialogue_set_previous_command_status(game->dialogue, ERROR);
    dialogue_set_previous_additional_information(game->dialogue, filename);
    dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
    dialogue_set_command_result(game->dialogue, "Debes introducir: 'save <nombre_archivo>'.");
    game_set_last_command_status(game, ERROR);
    return;
  }
  if (game_management_save(game, filename) == ERROR) {
    if (dialogue_get_previous_command(game->dialogue) == SAVE && dialogue_get_previous_command_status(game->dialogue) == ERROR
    && strcmp(dialogue_get_previous_additional_information(game->dialogue), filename) == 0
    && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
      dialogue_set_previous_command(game->dialogue, SAVE);
      dialogue_set_previous_command_status(game->dialogue, ERROR);
      dialogue_set_previous_additional_information(game->dialogue, filename);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
      game_set_last_command_status(game, ERROR);
      return;
    }
    dialogue_set_previous_command(game->dialogue, SAVE);
    dialogue_set_previous_command_status(game->dialogue, ERROR);
    dialogue_set_previous_additional_information(game->dialogue, filename);
    dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
    sprintf(cmd_result, "No se pudo guardar la partida en '%s'. Prueba otra accion", filename);
    dialogue_set_command_result(game->dialogue, cmd_result);
    game_set_last_command_status(game, ERROR);
    return;
  }
  dialogue_set_previous_command(game->dialogue, SAVE);
  dialogue_set_previous_command_status(game->dialogue, OK);
  dialogue_set_previous_additional_information(game->dialogue, filename);
  dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
  sprintf(cmd_result, "Partida guardada correctamente en '%s'.", filename);
  dialogue_set_command_result(game->dialogue, cmd_result);
  game_set_last_command_status(game, OK);
  return;
}

/** game_command_load game command to load a save
  */
void game_command_load(Game *game, char *filename){
  char cmd_result[WORD_SIZE] = "";

  if (!game || !filename) {
    if (dialogue_get_previous_command(game->dialogue) == LOAD && dialogue_get_previous_command_status(game->dialogue) == ERROR
    && strcmp(dialogue_get_previous_additional_information(game->dialogue), filename) == 0
    && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
      dialogue_set_previous_command(game->dialogue, LOAD);
      dialogue_set_previous_command_status(game->dialogue, ERROR);
      dialogue_set_previous_additional_information(game->dialogue, filename);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
      game_set_last_command_status(game, ERROR);
      return;
    }
    dialogue_set_previous_command(game->dialogue, LOAD);
    dialogue_set_previous_command_status(game->dialogue, ERROR);
    dialogue_set_previous_additional_information(game->dialogue, filename);
    dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
    dialogue_set_command_result(game->dialogue, "No se pudo cargar. Prueba otra accion.");
    game_set_last_command_status(game, ERROR);
    return;
  }

  if (filename[0] == '\0') {
    if (dialogue_get_previous_command(game->dialogue) == LOAD && dialogue_get_previous_command_status(game->dialogue) == ERROR
    && strcmp(dialogue_get_previous_additional_information(game->dialogue), filename) == 0
    && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
      dialogue_set_previous_command(game->dialogue, LOAD);
      dialogue_set_previous_command_status(game->dialogue, ERROR);
      dialogue_set_previous_additional_information(game->dialogue, filename);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
      game_set_last_command_status(game, ERROR);
      return;
    }
    dialogue_set_previous_command(game->dialogue, LOAD);
    dialogue_set_previous_command_status(game->dialogue, ERROR);
    dialogue_set_previous_additional_information(game->dialogue, filename);
    dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
    dialogue_set_command_result(game->dialogue, "Debes introducir: 'load <nombre_archivo>'.");
    game_set_last_command_status(game, ERROR);
    return;
  }
  if (game_management_load(game, filename) == ERROR) {
    if (dialogue_get_previous_command(game->dialogue) == LOAD && dialogue_get_previous_command_status(game->dialogue) == ERROR
    && strcmp(dialogue_get_previous_additional_information(game->dialogue), filename) == 0
    && dialogue_get_previous_player_location(game->dialogue) == game_get_player_location(game)) {
      dialogue_set_previous_command(game->dialogue, LOAD);
      dialogue_set_previous_command_status(game->dialogue, ERROR);
      dialogue_set_previous_additional_information(game->dialogue, filename);
      dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
      dialogue_set_command_result(game->dialogue, "Ya has introducido ese comando sin exito. Prueba otra accion.");
      game_set_last_command_status(game, ERROR);
      return;
    }
    dialogue_set_previous_command(game->dialogue, LOAD);
    dialogue_set_previous_command_status(game->dialogue, ERROR);
    dialogue_set_previous_additional_information(game->dialogue, filename);
    dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
    sprintf(cmd_result, "No se pudo cargar la partida '%s'. Prueba otra accion.", filename);
    dialogue_set_command_result(game->dialogue, cmd_result);
    game_set_last_command_status(game, ERROR);
    return;
  }
  dialogue_set_previous_command(game->dialogue, LOAD);
  dialogue_set_previous_command_status(game->dialogue, OK);
  dialogue_set_previous_additional_information(game->dialogue, filename);
  dialogue_set_previous_player_location(game->dialogue, game_get_player_location(game));
  sprintf(cmd_result, "Partida '%s' cargada correctamente.", filename);
  dialogue_set_command_result(game->dialogue, cmd_result);
  game_set_last_command_status(game, OK);
  return;
}

/** game_get_all_space_ids gets 
  * all spaces ids in the game
  */
STATUS game_get_all_space_ids(Game *game,Id *ids) {
  int i;

  if (game == NULL||ids==NULL) {
    return ERROR;
  }
	
  for (i = 0; i < MAX_SPACES; i++) {
    ids[i] = space_get_id(game->spaces[i]);
  }

  return OK;
}

/** game_get_objects gets an array of the objects ids in the game
  */
STATUS game_get_objects(Game *game, Id* objects)
{
  int i,j=0;
  if (game==NULL||objects==NULL){
    return ERROR;
  }

  for (i=0;i<MAX_OBJECTS;i++)
  {
    if(object_get_id(game->objects[i]) == NO_ID){
      continue;			
    }

    objects[j] = object_get_id(game->objects[i]);
    j++;
  }
  return OK;
}

/** game_get_player gets a pointer to the player on a game
  */
Player* game_get_player(Game *game){
  if(!game){
    return NULL;
  }

  return game->player;
}

/** game_get_enemies gets a pointer to an enemies on a game
  */
Enemy* game_get_enemy(Game *game, int index){
  if(!game || index < 0){
    return NULL;
  }

  return game->enemies[index];
}

/** game_get_object gets a pointer to a requested 
  * object on a game, based on an index
  */
Object* game_get_object(Game *game, int index){
  if(!game || index < 0){
    return NULL;
  }

  return game->objects[index];
}

/** game_get_space_from_index gets the space 
  * from a game with some index
  */
Space* game_get_space_from_index(Game *game, int index){
  if(!game || index < 0){
    return NULL;
  }

  return game->spaces[index];
}

/** game_get_link_from_index gets the link
  * from a game with some index
  */
Link* game_get_link_from_index(Game *game, int index){
  if(!game || index < 0){
    return NULL;
  }

  return game->links[index];
}

/** game_set_last_command_status sets the last command status
  */
STATUS game_set_last_command_status(Game *game, STATUS status){
  if(!game){
    return ERROR;
  }

  game->last_cmd_status = status;
  return OK;
}

/** game_init creates a game, allocationg memory for it
  */
Game *game_init(){
  Game *game = NULL;
  game = (Game *) malloc(sizeof(Game));
  if (!game) {
    return NULL;
  }

  return game;
}

/** game_get_connection_status returns wether a link from a space with a 
  * determined direction is open or closed
  */
CONNECTION game_get_connection_status(Game *g, Id space_id, DIRECTION direction){
  int i;

  if(!g || space_id == NO_ID){
    return -1;
  }

  for (i = 0; i < MAX_SPACES && g->links[i] != NULL; i++)
  {
    if(link_get_origin(g->links[i]) == space_id && link_get_direction(g->links[i]) == direction){
      return link_get_status(g->links[i]);
    }
  }
  
  return -1;
}

/** game_get_connection returns the id of the space 
  * connected to the space with id space_id by a direction
  */
Id game_get_connection(Game *g, Id space_id, DIRECTION direction){
  int i;

  if(!g || space_id == NO_ID){
    return NO_ID;
  }

  for (i = 0; i < MAX_LINKS && g->links[i] != NULL; i++)
  {
    if(link_get_origin(g->links[i]) == space_id && link_get_direction(g->links[i]) == direction){
      return link_get_destination(g->links[i]);
    }
  }
  
  return NO_ID;
}

/** game_link_exists determinates if a connection exists
  */
BOOL game_link_exists(Game *game, Id space, DIRECTION direction){
  int i;
	
  if(!game || space == NO_ID){
    return FALSE;
  }

  for (i=0; i<MAX_LINKS && game->links[i] != NULL; i++){
    if(link_get_origin(game->links[i]) == space && link_get_direction(game->links[i]) == direction && link_get_status(game->links[i]) == 0){
      return TRUE;
    }
  }

  return FALSE;
}

/** game_get_object_from_id gets an object from an id
  */
Object *game_get_object_from_id(Game *game, Id id){
  int i;

  if(!game || id == NO_ID){
    return NULL;
  }

  for(i=0; game->objects[i] != NULL && i < MAX_OBJECTS; i++){
    if (object_get_id(game->objects[i]) == id){
      return game->objects[i];
    }
  }
  return NULL;
}

/** game_object_id_to_name gets the
  * name of an object with its id
  */
char *game_object_id_to_name(Game *game, Id id){
  int i;

  if(!game || id == NO_ID){
    return NULL;
  }

  for(i=0; game->objects[i] != NULL  && i < MAX_OBJECTS; i++){
    if (id == object_get_id(game->objects[i])){
      return object_get_name(game->objects[i]);
    }
  }
  return NULL;
}

/** game_object_name_to_id gets the
  * id of an object with its name
  */
Id game_object_name_to_id(Game *game, char* name){
  int i;

  if(!game || !name){
    return NO_ID;
  }

  for(i=0; game->objects[i] != NULL; i++){
    if (strcmp(name,object_get_name(game->objects[i]))==0){
      return object_get_id(game->objects[i]);
    }
  }
  return NO_ID;
}




/** game_get_space_description gets the
  * description of the space
  */
char *game_get_space_description(Game *game, Id space_id) {
  Space *space = NULL;

  if (!game || space_id == NO_ID) {
    return NULL;
  }

  space = game_get_space(game, space_id);

  return space_get_description(space);
}

/** game_get_space_name gets the name of the space
  */
const char *game_get_space_name(Game *game, Id space_id) {
  Space *space = NULL;

  if (!game || space_id == NO_ID) {
    return NULL;
  }

  space = game_get_space(game, space_id);

  return space_get_name(space);
}

/** game_get_dialogue_command_result gets the dialogue string with command result
  */
char *game_get_dialogue_command_result(Game *game) {
  if (!game) {
    return NULL;
  }
  return dialogue_get_command_result(game->dialogue);
}

/** game_player_can_illuminate gets wether the player has a turnedon object to illuminate
  */
BOOL game_player_can_illuminate(Game *game){
  Inventory *inv = NULL;
  Id *ids = NULL;
  int n_objs, i;
	
  if (!game) {
    return FALSE;
  }

  inv = player_get_inventory(game_get_player(game));
  if(inv == NULL){
    return FALSE;
  }

  ids = inventory_get_objects(inv);
  n_objs = inventory_get_n_objects(inv);

  for (i = 0; i < n_objs; i++)
  {
    if(object_get_turnedon(game_get_object_from_id(game, ids[i])) == TRUE && object_get_illuminate(game_get_object_from_id(game, ids[i])) == TRUE){
      return TRUE;
    }
  }
  
  return FALSE;
}
