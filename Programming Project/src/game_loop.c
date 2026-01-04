/**
 * @brief It defines the game loop
 *
 * @file game_loop.c
 * @author Profesores PPROG
 * @version 2.0
 * @date 30-11-2020
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graphic_engine.h"
#include "game.h"
#include "command.h"

/** game_loop_init initializes the game
  */
int game_loop_init(Game *game, Graphic_engine **gengine, char *file_name);

/** game_loop_run runs the game
  */
void game_loop_run(Game *game, Graphic_engine *gengine, FILE* log);

/** game_loop_cleanup destroys
  * the game
  */
void game_loop_cleanup(Game *game, Graphic_engine *gengine);

/** game_loop_log_print prints the info in the log
  */
void game_loop_log_print(FILE *log, T_Command command, char* aditional_info, STATUS result);

/** main calls the functions
  * to run and destroy the game
  */
int main(int argc, char *argv[]) {
  Game *game = NULL;
  Graphic_engine *gengine = NULL;
  FILE *log = NULL;

  /* Error control */
  if (argc != 2 && argc != 4) {
    fprintf(stderr, "Use: %s <game_data_file>\n", argv[0]);
    return 1;
  }

  if(argc == 4){
    if(strcmp(argv[2], "-l") == 0){
      log = fopen(strcat(argv[3], ".txt"), "w");
    }
  }

  game = game_init();
 
  if (game_loop_init(game, &gengine, argv[1]) == 0) {
    game_loop_run(game, gengine, log);
    game_loop_cleanup(game, gengine);
  }

  if(log) fclose(log);

  free(game);

  return 0;
}

/** game_loop_init initializes the game
  */
int game_loop_init(Game *game, Graphic_engine **gengine, char *file_name) {
  /* Error control */
  if(game == NULL){
    return 1;
  }

  /* Error control */
  if (game_create_from_file(game, file_name) == ERROR) {
    fprintf(stderr, "Error while initializing game (game create from file error)\n");
    return 1;
  }

  /* Error control */
  if ((*gengine = graphic_engine_create()) == NULL) {
    fprintf(stderr, "Error while initializing graphic engine.\n");
    game_destroy(game);
    return 1;
  }

  return 0;
}

/** game_loop_run runs the game
  */
void game_loop_run(Game *game, Graphic_engine *gengine, FILE *log) {
  T_Command command = NO_CMD;
  char aditional_information[WORD_SIZE] = "";

  while ((command != EXIT) && !game_is_over(game)) {
    graphic_engine_paint_game(gengine, game);
    command = command_get_user_input(aditional_information, stdin);
    game_update(game, command, aditional_information);
    if(log) game_loop_log_print(log, command, aditional_information, game_get_last_command_status(game));
  }
}

/** game_loop_cleanup destroys
  * the game
  */
void game_loop_cleanup(Game *game, Graphic_engine *gengine) {
  game_destroy(game);
  graphic_engine_destroy(gengine);
}

/** game_loop_log_print prints the info in the log
  */
void game_loop_log_print(FILE *log, T_Command command, char* aditional_info, STATUS result){
  char message[16];

  if(!log){
    return;
  }
  
  switch(command){
    case NO_CMD:
      strcpy(message, "no_cmd");
      break;  

    case UNKNOWN:
      strcpy(message, "unknown");
      break;  

    case EXIT:
      strcpy(message, "exit");
      break;  

    case MOVE:
      strcpy(message, "move");
      break;

    case TAKE:
      strcpy(message, "take");
      break;  
      
    case DROP:
      strcpy(message, "drop");
      break;  
      
    case ATTACK:
      strcpy(message, "attack");
      break;  
      
    case INSPECT:
      strcpy(message, "inspect");
      break; 

    case SAVE:
      strcpy(message, "save");
      break; 

    case TURNON:
      strcpy(message, "turnon");
      break; 
    
    case TURNOFF:
      strcpy(message, "turnoff");
      break; 
    
    case LOAD:
      strcpy(message, "load");
      break; 
    
    case OPENC:
      strcpy(message, "open");
      break; 
    
  }

  fprintf(log, "%s", message);

  if(aditional_info != NULL && strcmp(aditional_info,"") != 0){
    fprintf(log, " %s", aditional_info);
  }

  fprintf(log, ": ");
  if(result == OK){
    fprintf(log, "OK\n");
  }
  else{
    fprintf(log, "ERROR\n");
  }
}
