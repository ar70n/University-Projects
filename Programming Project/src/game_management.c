/** 
 * @brief It implements reading file or files with the program configuration, i.e. to initialize the game (create the player, spaces, objects, etc.).
 * @file game_management.c
 * @author Antonio Moroño
 * @version 1.0
 * @date 03-02-2023 
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game_management.h"
#include "game.h"


/** game_management_load_spaces loads spaces to the game from a file
  */
STATUS game_management_load_spaces(Game *game, char *filename) {
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char description[WORD_SIZE] = "";
  char detailed_desc[WORD_SIZE] = "";
  char gdesc[LENGTH_GDESC][MAX_STR] = {{""}, {""}, {""}, {""}, {""}};
  BOOL light = TRUE;
  char *toks = NULL;
  Id id = NO_ID;
  Space *space = NULL;
  STATUS status = OK;
  int i;


  /* Error Control */
  if (!filename) {
    return ERROR;
  }

  file = fopen(filename, "r");
  /* Error Control */
  if (file == NULL) {
    return ERROR;
  }
  

  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#s:", line, 3) == 0) {
      toks = strtok(line + 3, "¿");
      id = atol(toks);
      toks = strtok(NULL, "¿");
      strcpy(name, toks);
      for (i = 0; i < LENGTH_GDESC; i++) {
        toks = strtok(NULL, "¿");
        if (toks != NULL) {
          strcpy(gdesc[i], toks);
        }
        else {
          gdesc[i][0] = '\0';
        }
      }
     toks = strtok(NULL, "¿");
     if (toks != NULL) {
        strcpy(detailed_desc, toks);
      }
      else {
        detailed_desc[0] = '\0';
      }
      toks = strtok(NULL, "¿");
      if (toks != NULL) {
        strcpy(description, toks);
      }
       else {
        description[0] = '\0';
      }
      toks = strtok(NULL, "¿");
      light = atol(toks);
#ifdef DEBUG
      printf("Leido: %ld¿%s¿%s¿%s¿%d\n", id, name, detailed_desc, description, light);
      for (i = 0; i < LENGTH_GDESC; i++) {
        printf("¿%s", gdesc[i]);
      }
      printf("\n");
#endif
      space = space_create(id);
      if (space != NULL) {
        space_set_name(space, name);
        space_set_gdesc(space, gdesc);
        space_set_detailed_desc(space, detailed_desc);
        space_set_description(space, description);
        space_set_light(space, light);
        game_add_space(game, space);
      }
      else {
        status = ERROR;
      }
    }
  }

  /* Error Control */
  if (ferror(file)) {
    status = ERROR;
  }

  if (status == ERROR) {
    if (space != NULL) free(space);
  }

  fclose(file);

  return status;
}

/** game_management_load_objects loads objects to the game from a file
  */
STATUS game_management_load_objects(Game *game, char *filename) {
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char description[WORD_SIZE] = "";
  BOOL movable = FALSE, hidden = TRUE, turnedon = FALSE, illuminate = FALSE;
  char *toks = NULL;
  Id id = NO_ID, initial_position = NO_ID, open = NO_ID, dependency = NO_ID;
  Object *object = NULL;
  STATUS status = OK;


  /* Error Control */
  if (!game || !filename) {
    return ERROR;
  }

  file = fopen(filename, "r");
  /* Error Control */
  if (file == NULL) {
    return ERROR;
  }

  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#o:", line, 3) == 0) {
      toks = strtok(line + 3, "¿");
      id = atol(toks);
      toks = strtok(NULL, "¿");
      strcpy(name, toks);
      toks = strtok(NULL, "¿");
      initial_position = atol(toks);
      toks = strtok(NULL, "¿");
      if (toks != NULL) {
        strcpy(description, toks);
      }
      else {
        description[0] = '\0';
      }
      toks = strtok(NULL, "¿");
      open = atol(toks);
      toks = strtok(NULL, "¿");
      dependency = atol(toks);
      toks = strtok(NULL, "¿");
      movable = atol(toks);
      toks = strtok(NULL, "¿");
      hidden = atol(toks);
      toks = strtok(NULL, "¿");
      turnedon = atol(toks);
      toks = strtok(NULL, "¿");
      illuminate = atol(toks);
#ifdef DEBUG
      printf("Leido: %ld¿%s¿%ld¿%s", id, name, initial_position, description);
      printf("¿%ld¿%ld¿%d¿%d¿%d¿%d\n", open, dependency, movable, hidden, turnedon, illuminate);
#endif
      object = object_create(id);
      if (object != NULL) {
        object_set_name(object, name);
        object_set_description(object, description);
        object_set_open(object, open);
        object_set_dependency(object, dependency);
        object_set_movable(object, movable);
        object_set_hidden(object, hidden);
        object_set_turnedon(object, turnedon);
        object_set_illuminate(object, illuminate);
        game_add_object(game, object, initial_position);
        if(initial_position == NO_ID){
          inventory_add_object(player_get_inventory(game_get_player(game)), id);
        }
      }
      else {
      	status = ERROR;
      }
    }
  }


  /* Error Control */
  if (ferror(file)) {
    status = ERROR;
  }

  if (status == ERROR) {
    if (object != NULL) free(object);
  }

  fclose(file);

  return status;
}

/** game_management_load_player loads the player to the game from a file
  */
STATUS game_management_load_player(Game *game, char *filename) {
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char *toks = NULL;
  Id id = NO_ID, loc = NO_ID, *objs;
  Player *player = NULL;
  STATUS status = OK;
  short health, max_inventory, power;
  int i = 0;



  /* Error Control */
  if (!filename || !game) {
    return ERROR;
  }

  file = fopen(filename, "r");
  /* Error Control */
  if (file == NULL) {
    return ERROR;
  }


  while (fgets(line, WORD_SIZE, file)) {    
    if (strncmp("#p:", line, 3) == 0) {
      toks = strtok(line + 3, "¿");
      id = atol(toks);
      toks = strtok(NULL, "¿");
      strcpy(name, toks);
      toks = strtok(NULL, "¿");
      loc = atol(toks);
      toks = strtok(NULL, "¿");
      health = atol(toks);
      toks = strtok(NULL, "¿");
      max_inventory = atol(toks);
      toks = strtok(NULL, "¿");
      power = atol(toks);
      objs = (Id*)malloc(max_inventory*sizeof(Id));

      i = 0;
      while(i < max_inventory){
        objs[i] = NO_ID;
        i++;
      }

      i = 0;
      while (i < max_inventory){
        toks = strtok(NULL, "¿");
        if(toks == NULL || toks[1] == '\n' || atol(toks) == NO_ID){
          if(toks != NULL) 
          break;
        }
        
        objs[i] = atol(toks);
        i++;
      }

#ifdef DEBUG
      printf("Leido: %ld¿%s¿%ld¿%d¿%d\n", id, name, loc, health, max_inventory);
#endif
      player = player_create(id);
      if (player != NULL) {
        player_set_name(player, name);
        player_set_location(player, loc);
        player_set_health(player, health);
        player_set_power(player, power);
        inventory_set_max_objs(player_get_inventory(player), max_inventory);
        for (i=0; i<max_inventory; i++){
          if (objs[i] != NO_ID){
            if (player_add_object_to_inventory(player, objs[i])== ERROR){
              return ERROR;
            }            
          }
        }
        
        game_set_player(game, player);
      }
      else {
        status = ERROR;
      }
    }
  }


  free(objs);


  if (ferror(file)) {
    status = ERROR;
  }

  if(status == ERROR) {
    if(player != NULL) free(player);
  }

  fclose(file);

  return status;
}

/** game_management_load_enemies loads the the enemies to the game from a file
  */
STATUS game_management_load_enemies(Game *game, char *filename) {
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char *toks = NULL;
  Id id = NO_ID, loc = NO_ID;
  Enemy *enemy = NULL;
  STATUS status = OK;
  int health;



  /* Error Control */
  if (!filename || !game) {
    return ERROR;
  }

  file = fopen(filename, "r");
  /* Error Control */
  if (file == NULL) {
    return ERROR;
  }

  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#e:", line, 3) == 0) {
      toks = strtok(line + 3, "¿");
      id = atol(toks);
      toks = strtok(NULL, "¿");
      strcpy(name, toks);
      toks = strtok(NULL, "¿");
      loc = atol(toks);
      toks = strtok(NULL, "¿");
      health = atol(toks);

#ifdef DEBUG
      printf("Leido: %ld¿%s¿%ld¿%d\n", id, name, loc, health);
#endif
      enemy = enemy_create(id);
      if (enemy != NULL) {
        enemy_set_name(enemy, name);
        enemy_set_location(enemy, loc);
        enemy_set_health(enemy, health);
        game_add_enemy(game, enemy);
      }
      else {
        status = ERROR;
      }
    }
  }

  if (ferror(file)) {
    status = ERROR;
  }

  if(status == ERROR) {
    if(enemy != NULL) free(enemy);
  }

  fclose(file);

  return status;
}

/** game_management_load_links loads the links to the game from a file
  */
STATUS game_management_load_links(Game *game, char *filename) {
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char *toks = NULL;
  Link *link = NULL;
  STATUS status = OK;
  Id link_id, link_orig, link_dest;
  DIRECTION direction;
  CONNECTION connection;

  /* Error Control */
  if (!filename) {
    return ERROR;
  }

  file = fopen(filename, "r");
  /* Error Control */
  if (file == NULL) {
    return ERROR;
  }

  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#l:", line, 3) == 0) {
      /*Pillar el id del link*/
      toks = strtok(line + 3, "¿");
      link_id = atol(toks);
      /*Pillar el nombre del link*/
      toks = strtok(NULL, "¿");
      strcpy(name, toks);
      /*Pillar el id del espacio origen*/
      toks = strtok(NULL, "¿");
      link_orig = atol(toks);
      /*Pillar el id del espacio destino*/
      toks = strtok(NULL, "¿");
      link_dest = atol(toks);
      /*Pillar la dirección del enlace*/
      toks = strtok(NULL, "¿");
      direction = atol(toks);
      /*Pillar el estado del enlace*/
      toks = strtok(NULL, "¿");
      connection = atol(toks);

      link = link_create(link_id);
      if(link != NULL) {
        if(link_set_name(link, name) == ERROR){
           status = ERROR;
           break;
        }
        if(link_set_origin(link, link_orig) == ERROR){
           status = ERROR;
           break;
        }
        if(link_set_destination(link, link_dest) == ERROR){
           status = ERROR;
           break;
        }
        if(link_set_direction(link, direction) == ERROR){
           status = ERROR;
           break;
        }
        if(link_set_status(link, connection) == ERROR){
           status = ERROR;
           break;
        }
        if(game_add_link(game, link) == ERROR){
          status = ERROR;
          break;
        }
      } 
    }
  }

  if (ferror(file)) {
    status = ERROR;
  }

  if(status == ERROR) {
    if(link != NULL) free(link);
  }

  fclose(file);
 
  return status;
}

/** game_management_save saves the game's information in a file
  */
STATUS game_management_save(Game *game, char *filename){
  FILE *f;
  Object *o = NULL;
  Id *player_obj;
  int i;

  if (!game || !filename){
    return ERROR;
  }

  if ((f = fopen (strcat(filename, ".dat"), "w"))== NULL){
    return ERROR;
  }

  for (i=0; game_get_space_from_index(game, i) != NULL; i++){
    fprintf(f, "#s:%d¿%s¿%s¿%s¿%s¿%s¿%s¿%s¿%s¿%d¿\n", (int)space_get_id(game_get_space_from_index(game, i)), space_get_name(game_get_space_from_index(game, i)), 
    space_get_gdesc_row(game_get_space_from_index(game, i), 1), space_get_gdesc_row(game_get_space_from_index(game, i), 2), 
    space_get_gdesc_row(game_get_space_from_index(game, i), 3), space_get_gdesc_row(game_get_space_from_index(game, i), 4), 
    space_get_gdesc_row(game_get_space_from_index(game, i), 5), space_get_detailed_desc(game_get_space_from_index(game, i)),
    space_get_description(game_get_space_from_index(game, i)), space_get_light(game_get_space_from_index(game, i)));
  }
  
  fprintf(f, "\n\n");

  for (i=0; game_get_link_from_index(game, i) != NULL; i++){
    fprintf(f, "#l:%d¿%s¿%d¿%d¿%d¿%d¿\n", (int)link_get_id(game_get_link_from_index(game, i)), link_get_name(game_get_link_from_index(game, i)), (int)link_get_origin(game_get_link_from_index(game, i)), (int)link_get_destination(game_get_link_from_index(game, i)), (int)link_get_direction(game_get_link_from_index(game, i)), (int)link_get_status(game_get_link_from_index(game, i)));
  }

  fprintf(f, "\n\n");

  fprintf(f, "#p:%d¿%s¿%d¿%d¿%d¿%d¿", (int)player_get_id(game_get_player(game)), player_get_name(game_get_player(game)), (int)player_get_location(game_get_player(game)), (int)player_get_health(game_get_player(game)), (int)inventory_get_max_objs(player_get_inventory(game_get_player(game))), player_get_power(game_get_player(game)));
  player_obj = player_get_objects(game_get_player(game));
  for (i=0; i<inventory_get_max_objs(player_get_inventory(game_get_player(game))); i++){
    if(player_obj != NULL){
      fprintf(f, "%d¿", (int)player_obj[i]);
    }else{
      fprintf(f, "-1¿");
    }
  }

  fprintf(f, "\n");

  for (i=0; game_get_enemy(game, i) != NULL; i++){
    fprintf(f, "#e:%d¿%s¿%d¿%d¿\n", (int)enemy_get_id(game_get_enemy(game, i)), enemy_get_name(game_get_enemy(game, i)), (int)enemy_get_location(game_get_enemy(game, i)), (int)enemy_get_health(game_get_enemy(game, i)));
  }

  for (i=0; game_get_object(game, i) != NULL; i++){
    o = game_get_object(game, i);

    fprintf(f, "#o:%d¿%s¿%d¿%s¿%ld¿%ld¿%d¿%d¿%d¿%d¿\n", 
    (int)object_get_id(o), 
    object_get_name(o), 
    (int)game_get_object_location(game, object_get_id(o)), 
    object_get_description(o),
    object_get_open(o),
    object_get_dependency(o),
    object_get_movable(o) == TRUE,
    object_get_hidden(o) == TRUE,
    object_get_turnedon(o) == TRUE,
    object_get_illuminate(o) == TRUE
    );
  }

  fclose(f);

  return OK;
}

/** game_management_load loads a game save
  */
STATUS game_management_load(Game *game, char *filename){
  FILE *f = NULL;
  char *file = NULL;

  if(!game || !filename){
    return ERROR;
  }

  file = strcat(filename, ".dat");

  /* Checking wether the file with name 'filename.dat' exists*/
  f = fopen(file, "r");
  if (!f) {
    return ERROR;
  }
  fclose(f);

  game_destroy(game);

  return game_create_from_file(game, file);
}
