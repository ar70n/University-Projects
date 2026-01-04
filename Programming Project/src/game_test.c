/** 
 * @brief It tests inventory module
 * 
 * @file game_test.c
 * @author Jorge Jiménez
 * @version 1
 * @date 02-04-2023
 * @copyright GNU Public License
 */

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "game.h"
#include "game_test.h"
#include "link.h"
#include "test.h"
#include "space.h"
#include "player.h"


#define MAX_TESTS 76 /*!< The maximum number of tests */

/** 
 * @brief Main function for GAME unit tests. 
 * 
 * You may execute ALL or a SINGLE test
 *   1.- No parameter -> ALL test are executed 
 *   2.- A number means a particular test (the one identified by that number) 
 *       is executed
 *  
 */
int main(int argc, char** argv) {

  int test = 0;
  int all = 1;

  if (argc == 1) {
    printf("Use: %s <game_data_file>\n", argv[0]);
    return 1;
  }
  else if (argc < 3) {
    printf("Running all test for module Game (game_data_file : %s):\n", argv[1]);
  } else {
    test = atoi(argv[2]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 && test > MAX_TESTS) {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
    }
  }


  if (all || test == 1) test1_game_create();
  if (all || test == 2) test2_game_create();
  if (all || test == 3) test1_game_create_from_file(argv[1]);
  if (all || test == 4) test2_game_create_from_file();
  if (all || test == 5) test1_game_destroy();
  if (all || test == 6) test2_game_destroy();
  if (all || test == 7) test1_game_is_over();
  if (all || test == 8) test2_game_is_over();
  if (all || test == 9) test1_game_get_space();
  if (all || test == 10) test2_game_get_space();
  if (all || test == 11) test3_game_get_space();
  if (all || test == 12) test1_game_get_player_location();
  if (all || test == 13) test2_game_get_player_location();
  if (all || test == 14) test1_game_get_object_location();
  if (all || test == 15) test2_game_get_object_location();
  if (all || test == 16) test1_game_get_enemy_location();
  if (all || test == 17) test2_game_get_enemy_location();
  if (all || test == 18) test1_game_get_player_health();
  if (all || test == 19) test2_game_get_player_health();
  if (all || test == 20) test1_game_get_enemy_health();
  if (all || test == 21) test2_game_get_enemy_health();
  if (all || test == 22) test1_game_set_last_command();
  if (all || test == 23) test2_game_set_last_command();
  if (all || test == 24) test1_game_get_last_command();
  if (all || test == 25) test2_game_get_last_command();
  if (all || test == 26) test1_game_get_last_command_status();
  if (all || test == 27) test2_game_get_last_command_status();
  if (all || test == 28) test1_game_add_space();
  if (all || test == 29) test2_game_add_space();
  if (all || test == 30) test1_game_add_link();
  if (all || test == 31) test2_game_add_link();
  if (all || test == 32) test1_game_add_object();;
  if (all || test == 33) test2_game_add_object();;
  if (all || test == 34) test3_game_add_object();;
  if (all || test == 35) test1_game_set_player();
  if (all || test == 36) test2_game_set_player();
  if (all || test == 37) test1_game_add_enemy();
  if (all || test == 38) test2_game_add_enemy();
  if (all || test == 39) test1_game_get_all_space_ids();
  if (all || test == 40) test2_game_get_all_space_ids();
  if (all || test == 41) test1_game_get_objects();
  if (all || test == 42) test2_game_get_objects();
  if (all || test == 43) test1_game_get_player();
  if (all || test == 44) test2_game_get_player();
  if (all || test == 45) test1_game_get_enemy();
  if (all || test == 46) test2_game_get_enemy();
  if (all || test == 47) test1_game_get_object();
  if (all || test == 48) test2_game_get_object();
  if (all || test == 49) test1_game_set_last_command_status();
  if (all || test == 50) test2_game_set_last_command_status();
  if (all || test == 51) test1_game_init();
  if (all || test == 52) test1_game_get_connection_status();
  if (all || test == 53) test2_game_get_connection_status();
  if (all || test == 54) test1_game_get_connection();
  if (all || test == 55) test2_game_get_connection();
  if (all || test == 56) test1_game_link_exists();
  if (all || test == 57) test2_game_link_exists();
  if (all || test == 58) test1_game_print_data();
  if (all || test == 59) test2_game_print_data();
  if (all || test == 60) test1_object_id_to_name();
  if (all || test == 61) test2_object_id_to_name();
  if (all || test == 62) test3_object_id_to_name();
  if (all || test == 63) test1_game_get_object_from_id();
  if (all || test == 64) test2_game_get_object_from_id();
  if (all || test == 65) test1_game_get_space_from_index();
  if (all || test == 66) test2_game_get_space_from_index();
  if (all || test == 67) test1_game_get_link_from_index();
  if (all || test == 68) test2_game_get_link_from_index();
  if (all || test == 69) test1_game_get_space_description();
  if (all || test == 70) test2_game_get_space_description();
  if (all || test == 71) test1_game_get_space_name();
  if (all || test == 72) test2_game_get_space_name();
  if (all || test == 73) test1_game_get_dialogue_command_result();
  if (all || test == 74) test2_game_get_dialogue_command_result();
  if (all || test == 75) test1_game_player_can_illuminate();
  if (all || test == 76) test2_game_player_can_illuminate();

  PRINT_PASSED_PERCENTAGE;

  return 1;
}


/** test1_game_create tests game creation
  */
void test1_game_create() {
  Game *g = NULL;
  g = game_init();
  PRINT_TEST_RESULT(game_create(g) == OK);
  game_destroy(g);
  free(g);
}
/** test2_game_create tests game creation
  */
void test2_game_create() {
  Game *g = NULL;
  PRINT_TEST_RESULT(game_create(g) == ERROR);
}

/** test1_game_create_from_file tests game creation from a specific file
 */
void test1_game_create_from_file(char *filename) {
  Game *g = NULL;
  g = game_init();
  PRINT_TEST_RESULT(game_create_from_file(g, filename) == OK);
  game_destroy(g);
  free(g);
}
/** test2_game_create_from_file tests game creation from a specific file
 */
void test2_game_create_from_file() {
  Game *g = NULL;
  char *file_name = NULL;
  g = game_init();
  PRINT_TEST_RESULT(game_create_from_file(g, file_name) == ERROR);
  free(g);
}

/** test1_game_destroy tests game destruction
  */
void test1_game_destroy() {
  Game *g = NULL;
  g = game_init();
  game_create(g);
  PRINT_TEST_RESULT(game_destroy(g) == OK);
  free(g);
}
/** test2_game_destroy tests game destruction
  */
void test2_game_destroy() {
  PRINT_TEST_RESULT(game_destroy(NULL) == ERROR);
}

/** test1_game_is_over tests getting the game over
*/
void test1_game_is_over() {
  Game*g = NULL;
  g = game_init();
  game_create(g);
  PRINT_TEST_RESULT(game_is_over(g) == FALSE);
  game_destroy(g);
  free(g);
}
/** test2_game_is_over() tests getting the game over
*/
void test2_game_is_over() {
  Game *g = NULL;
  Player *p = NULL;
  g = game_init();
  game_create(g);
  p = player_create(12);
  game_set_player(g, p);
  player_set_health(game_get_player(g), 0);
  PRINT_TEST_RESULT(game_is_over(g) == TRUE);
  game_destroy(g);
  free(g);
}

/** test1_game_get_space tests game getting space from id
  */
void test1_game_get_space() {
  Game *g = NULL;
  Space *s = NULL;
  g = game_init();
  game_create(g);
  s = space_create(12);
  game_add_space(g, s);
  PRINT_TEST_RESULT(game_get_space(g, 12) == s);
  game_destroy(g);
  free(g);
}
/** test2_game_get_space tests game getting space from id
  */
void test2_game_get_space() {
  Game *g = NULL;
  g = game_init();
  game_create(g);
  PRINT_TEST_RESULT(game_get_space(g, NO_ID) == NULL);
  game_destroy(g);
  free(g);
}
/** test3_game_get_space tests game getting space from id
  */
void test3_game_get_space() {
  Game *g = NULL;
  Space *s = NULL;
  g = game_init();
  game_create(g);
  s = space_create(12);
  game_add_space(g, s);
  PRINT_TEST_RESULT(game_get_space(g, 1) == NULL);
  game_destroy(g);
  free(g);
}

/** test1_game_get_player_location tests game getting player location
  */
void test1_game_get_player_location() {
  Game *g = NULL;
  Space *s = NULL;
  Player *p = NULL;
  g = game_init();
  game_create(g);
  s = space_create(12);
  game_add_space(g, s);
  p = player_create(13);
  player_set_location(p, 12);
  game_set_player(g, p);
  PRINT_TEST_RESULT(game_get_player_location(g) == 12);
  game_destroy(g);
  free(g);
}
/** test2_game_get_player_location tests game getting player location
  */
void test2_game_get_player_location() {
  Game *g = NULL;
  g = game_init();
  game_create(g);
  PRINT_TEST_RESULT(game_get_player_location(g) == NO_ID);
  game_destroy(g);
  free(g);
}

/** test1_game_get_object_location tests game getting object location
  */
void test1_game_get_object_location() {
  Game *g = NULL;
  Space *s = NULL;
  Object *o = NULL;
  g = game_init();
  game_create(g);
  s = space_create(12);
  game_add_space(g, s);
  o = object_create(13);
  game_add_object(g, o, 12);
  PRINT_TEST_RESULT(game_get_object_location(g, 13) == 12);
  game_destroy(g);
  free(g);
}
/** test2_game_get_object_location tests game getting object location
  */
void test2_game_get_object_location() {
  Game *g = NULL;
  g = game_init();
  game_create(g);
  PRINT_TEST_RESULT(game_get_object_location(g, NO_ID) == NO_ID);
  game_destroy(g);
  free(g);
}

/** test1_game_get_enemy_location tests game getting enemy location
  */
void test1_game_get_enemy_location() {
  Game *g = NULL;
  Space *s = NULL;
  Enemy *e = NULL;
  g = game_init();
  game_create(g);
  s = space_create(12);
  game_add_space(g, s);
  e = enemy_create(13);
  enemy_set_location(e, 12);
  game_add_enemy(g, e);
  PRINT_TEST_RESULT(game_get_enemy_location(g, 0) == 12);
  game_destroy(g);
  free(g);
}
/** test2_game_get_enemy_location tests game getting enemy location
  */
void test2_game_get_enemy_location() {
  Game *g = NULL;
  g = game_init();
  game_create(g);
  PRINT_TEST_RESULT(game_get_enemy_location(g, 0) == NO_ID);
  game_destroy(g);
  free(g);
}

/** test1_game_get_player_health tests game getting player health
  */
void test1_game_get_player_health() {
  Game *g = NULL;
  Player *p = NULL;
  g = game_init();
  game_create(g);
  p = player_create(12);
  player_set_health(p, 5);
  game_set_player(g, p);
  PRINT_TEST_RESULT(game_get_player_health(g) == 5);
  game_destroy(g);
  free(g);
}
/** test2_game_get_player_health tests game getting player health
  */
void test2_game_get_player_health() {
  Game *g = NULL;
  g = game_init();
  game_create(g);
  PRINT_TEST_RESULT(game_get_player_health(g) == -1);
  game_destroy(g);
  free(g);
}

/** test1_game_get_enemy_health tests game getting enemy health
  */
void test1_game_get_enemy_health() {
  Game *g = NULL;
  Enemy *e = NULL;
  g = game_init();
  game_create(g);
  e = enemy_create(12);
  enemy_set_health(e, 5);
  game_add_enemy(g, e);
  PRINT_TEST_RESULT(game_get_enemy_health(g, 0) == 5);
  game_destroy(g);
  free(g);
}
/** test2_game_get_enemy_health tests game getting enemy health
  */
void test2_game_get_enemy_health() {
  Game *g = NULL;
  g = game_init();
  game_create(g);
  PRINT_TEST_RESULT(game_get_enemy_health(g, 0) == -1);
  game_destroy(g);
  free(g);
}

/** test1_game_set_last_command tests game setting last command
  */
void test1_game_set_last_command() {
  Game *g = NULL;
  g = game_init();
  game_create(g);
  PRINT_TEST_RESULT(game_set_last_command(g, TAKE) == OK);
  game_destroy(g);
  free(g);
}
/** test2_game_set_last_command tests game setting last command
  */
void test2_game_set_last_command() {
  Game *g = NULL;
  g = game_init();
  game_create(g);
  game_set_last_command(g, TAKE);
  PRINT_TEST_RESULT(game_get_last_command(g) == TAKE);
  game_destroy(g);
  free(g);
}

/** test1_game_get_last_command tests game getting last command
  */
void test1_game_get_last_command() {
  Game *g = NULL;
  g = game_init();
  game_create(g);
  PRINT_TEST_RESULT(game_get_last_command(g) == NO_CMD);
  game_destroy(g);
  free(g);
}
/** test2_game_get_last_command tests game getting last command
  */
void test2_game_get_last_command() {
  Game *g = NULL;
  g = game_init();
  game_create(g);
  game_set_last_command(g, TAKE);
  PRINT_TEST_RESULT(game_get_last_command(g) == TAKE);
  game_destroy(g);
  free(g);
}

/** test1_game_get_last_command_status tests
 *  game getting last command status
 */
void test1_game_get_last_command_status() {
  Game *g = NULL;
  g = game_init();
  game_create(g);
  PRINT_TEST_RESULT(game_get_last_command_status(g) == ERROR);
  game_destroy(g);
  free(g);
}
/** test2_game_get_last_command_status tests
 *  game getting last command status
 */
void test2_game_get_last_command_status() {
  Game *g = NULL;
  g = game_init();
  game_create(g);
  game_set_last_command_status(g, OK);
  PRINT_TEST_RESULT(game_get_last_command_status(g) == OK);
  game_destroy(g);
  free(g);
}

/** test1_game_add_space tests game adding a space to the game
  */
void test1_game_add_space() {
  Game *g = NULL;
  Space *s = NULL;
  g = game_init();
  game_create(g);
  s = space_create(12);
  PRINT_TEST_RESULT(game_add_space(g, s) == OK);
  game_destroy(g);
  free(g);
}
/** test2_game_add_space tests game adding a space to the game
  */
void test2_game_add_space() {
  Game *g = NULL;
  g = game_init();
  game_create(g);
  PRINT_TEST_RESULT(game_add_space(g, NULL) == ERROR);
  game_destroy(g);
  free(g);
}

/** test1_game_add_link tests game adding a link to the game
  */
void test1_game_add_link() {
  Game *g = NULL;
  Link *l = NULL;
  g = game_init();
  game_create(g);
  l = link_create(12);
  PRINT_TEST_RESULT(game_add_link(g, l) == OK);
  game_destroy(g);
  free(g);
}
/** test2_game_add_link tests game adding a link to the game
  */
void test2_game_add_link() {
  Game *g = NULL;
  g = game_init();
  game_create(g);
  PRINT_TEST_RESULT(game_add_link(g, NULL) == ERROR);
  game_destroy(g);
  free(g);
}

/** test1_game_add_object tests game adding an object to the game
  */
void test1_game_add_object() {
  Game *g = NULL;
  Space *s = NULL;
  Object *o = NULL;
  g = game_init();
  game_create(g);
  s = space_create(12);
  game_add_space(g, s);
  o = object_create(11);
  PRINT_TEST_RESULT(game_add_object(g, o, 12) == OK);
  game_destroy(g);
  free(g);
}
/** test2_game_add_object tests game adding an object to the game
  */
void test2_game_add_object() {
  Game *g = NULL;
  Space *s = NULL;
  g = game_init();
  game_create(g);
  s = space_create(12);
  game_add_space(g, s);
  PRINT_TEST_RESULT(game_add_object(g, NULL, 12) == ERROR);
  game_destroy(g);
  free(g);
}
/** test3_game_add_object tests game adding an object to the game
  */
void test3_game_add_object() {
  Game *g = NULL;
  Object *o = NULL;
  g = game_init();
  game_create(g);
  o = object_create(12);
  PRINT_TEST_RESULT(game_add_object(g, o, NO_ID) == OK);
  game_destroy(g); 
  free(g);
}

/** test1_game_set_player tests game setting 
  *  the player of the game
  */
void test1_game_set_player() {
  Game *g = NULL;
  Player *p = NULL;
  g = game_init();
  game_create(g);
  p = player_create(12);
  PRINT_TEST_RESULT(game_set_player(g, p) == OK);
  game_destroy(g);
  free(g);
}
/** test2_game_set_player tests game setting 
  *  the player of the game
  */
void test2_game_set_player() {
  Game *g = NULL;
  g = game_init();
  game_create(g);
  PRINT_TEST_RESULT(game_set_player(g, NULL) == ERROR);
  game_destroy(g);
  free(g);
}

/** test1_game_set_enemy tests game setting 
  *  the enemy of the game
  */
void test1_game_add_enemy() {
  Game *g = NULL;
  Enemy *e= NULL;
  g = game_init();
  game_create(g);
  e = enemy_create(12);
  PRINT_TEST_RESULT(game_add_enemy(g, e) == OK);
  game_destroy(g);
  free(g);
}
/** test2_game_set_enemy tests game setting 
  *  the enemy of the game
  */
void test2_game_add_enemy() {
  Game *g = NULL;
  g = game_init();
  game_create(g);
  PRINT_TEST_RESULT(game_add_enemy(g, NULL) == ERROR);
  game_destroy(g);
  free(g);
}

/** test1_game_get_all_space_ids tests game getting
  * all spaces id's
  */
void test1_game_get_all_space_ids() {
  Game *g = NULL;
  Id ids[MAX_IDS];
  Space *s1 = NULL, *s2 = NULL;
  int i;

  g = game_init();
  if(g) game_create(g);
  if(g == NULL){
    PRINT_TEST_RESULT(0);
  }

  s1 = space_create(1);
  game_add_space(g, s1);
  s2 = space_create(2);
  game_add_space(g, s2);

  for (i = 0; i < MAX_IDS; i++) {
    ids[i] = NO_ID;
  }

  PRINT_TEST_RESULT(game_get_all_space_ids(NULL, ids) == ERROR && game_get_all_space_ids(g, NULL) == ERROR && game_get_all_space_ids(NULL, NULL) == ERROR);
  game_destroy(g);
  free (g);
}
/** test2_game_get_all_space_ids tests game getting
  * all spaces id's
  */
void test2_game_get_all_space_ids() {
  Game *g = NULL;
  Id ids[MAX_IDS];
  Space *s1 = NULL, *s2 = NULL;
  int i;

  g = game_init();
  game_create(g);

  s1 = space_create(1);
  game_add_space(g, s1);
  s2 = space_create(2);
  game_add_space(g, s2);

  for (i = 0; i < MAX_IDS; i++) {
    ids[i] = NO_ID;
  }

  PRINT_TEST_RESULT(game_get_all_space_ids(g, ids) == OK && ids[0] == 1 && ids[1] == 2);
  game_destroy(g);
  free (g);
}


/** test1_game_get_objects tests game getting
  * all objects id's
  */
void test1_game_get_objects() {
  Game *g = NULL;
  Id* objects = NULL;
  int result;

  g = game_init();
  game_create(g);

  objects = malloc(sizeof(Id) * 10);

  result = (game_get_objects(NULL, objects) == ERROR && game_get_objects(g, NULL) == ERROR && game_get_objects(NULL, NULL) == ERROR);

  game_destroy(g);
  free(g);
  free(objects);

  PRINT_TEST_RESULT(result);
}
/** test2_game_get_objects tests game getting
  * all objects id's
  */
void test2_game_get_objects(){
  Game *g = NULL;
  Id objects[MAX_OBJECTS];
  Object *o1 = NULL, *o2 = NULL;
  int i;

  g = game_init();
  game_create(g);

  o1 = object_create(1);
  game_add_object(g, o1, 12);
  o2 = object_create(2);
  game_add_object(g, o2, 14);

  for (i = 0; i < MAX_OBJECTS; i++) {
    objects[i] = NO_ID;
  }

  PRINT_TEST_RESULT(game_get_objects(g, objects) == OK && objects[0] == 1 && objects[1] == 2);

  game_destroy(g);
  free(g);  
}

/** test1_game_get_player tests game geting player
  */
void test1_game_get_player() {
  PRINT_TEST_RESULT(game_get_player(NULL) == NULL);
}
/** test2_game_get_player tests game geting player
  */
void test2_game_get_player() {
  Game *g = NULL;
  Player *p = NULL;

  g = game_init();
  game_create(g);
  
  p = player_create(12);
  game_set_player(g, p);

  PRINT_TEST_RESULT(game_get_player(g) == p);

  game_destroy(g);
  free(g);
}

/** test1_game_get_enemy tests game geting enemy
  */
void test1_game_get_enemy() {
  PRINT_TEST_RESULT(game_get_enemy(NULL, 0) == NULL);
}
/** test2_game_get_enemy tests game geting enemy
  */
void test2_game_get_enemy() {
  Game *g = NULL;
  Enemy *e = NULL;

  g = game_init();
  game_create(g);

  e = enemy_create(1);
  game_add_enemy(g, e);

  PRINT_TEST_RESULT(game_get_enemy(g, 0) == e);

  game_destroy(g);
  free(g);
}

/** test1_game_get_object tests game geting an object
  */
void test1_game_get_object() {
  Game *g = NULL;
  g = game_init();
  game_create(g);

  PRINT_TEST_RESULT(game_get_object(g, -1) == NULL && game_get_object(NULL, 0) == NULL && game_get_object(NULL, -1) == NULL);

  game_destroy(g);
  free(g);
}
/** test2_game_get_object tests game geting an object
  */
void test2_game_get_object() {
  Game *g = NULL;
  Object *o = NULL;
  g = game_init();
  game_create(g);
  o = object_create(1);
  game_add_object(g, o, 14);
  PRINT_TEST_RESULT(game_get_object(g, 0) == o);
  game_destroy(g);
  free(g);
}

/** test1_game_set_last_command_status tests 
  * game setting last command status
  */
void test1_game_set_last_command_status() {
  PRINT_TEST_RESULT(game_set_last_command_status(NULL, ERROR) == ERROR);
}
/** test2_game_set_last_command_status tests 
  * game setting last command status
  */
void test2_game_set_last_command_status() {
  Game *g = NULL;

  g = game_init(g);
  game_create(g);

  PRINT_TEST_RESULT(game_set_last_command_status(g, ERROR) == OK);

  game_destroy(g);
  free(g);
}

/** test1_game_init tests game initialization
  */
void test1_game_init() {
  int result;
  Game *g = NULL;

  g = game_init();
  result = (g!=NULL);
  PRINT_TEST_RESULT(result);
  free(g);
}

/** test1_game_get_connection_status tests 
  * game getting connection status
  */
void test1_game_get_connection_status() {
  PRINT_TEST_RESULT(game_get_connection_status(NULL, NO_ID, W) == -1);
}
/** test2_game_get_connection_status tests 
  * game getting connection status
  */
void test2_game_get_connection_status() {
  Space *s1 = NULL, *s2 = NULL;
  Link *l = NULL;
  Id s1_id = 1, s2_id = 2, link_id = 3;
  Game *game = NULL;
  int result = 1;

  /*We create a game and add two spaces to it. We first check there is no
  link between them. After that, we add a link connecting the two spaces
  and change it's state, checking with every change that the status is right*/
  game = game_init();
  game_create(game);

  s1 = space_create(s1_id);
  s2 = space_create(s2_id);

  game_add_space(game, s1);
  game_add_space(game, s2);

  /*We check the spaces are not connected in any direction*/
  if(game_get_connection_status(game, s1_id, S) != -1){
    
    game_destroy(game);
    free(game);
    PRINT_TEST_RESULT(0);
  }

  /*We add the link and check it is connected, checking also if there has been any errors*/
  l = link_create(link_id);
  link_set_origin(l, s1_id);
  link_set_destination(l, s2_id);
  link_set_direction(l, S);
  link_set_name(l, "test_link");
  link_set_status(l, CLOSE);

  game_add_link(game, l);

  result = game_get_connection_status(game, s1_id, S) == CLOSE;

  link_set_status(l, OPEN);
  if(result) result = game_get_connection_status(game, s1_id, S) == OPEN;

  game_destroy(game);
  free(game);

  PRINT_TEST_RESULT(result);
}

/** test1_game_get_connection tests game getting the id of
  * the space connected to a space
  */
void test1_game_get_connection() {
  PRINT_TEST_RESULT(game_get_connection(NULL, NO_ID, W) == NO_ID);
}
/** test2_game_get_connection tests game getting the id of
  * the space connected to a space
  */
void test2_game_get_connection(){
  Game *g = NULL;
  Space *s1 = NULL, *s2 = NULL;
  Link *l = NULL;
  Id s1_id = 12, s2_id = 13;

  g = game_init();
  game_create(g);

  s1 = space_create(s1_id);
  game_add_space(g, s1);
  s2 = space_create(s2_id);
  game_add_space(g, s2);

  l = link_create(14);
  link_set_origin(l, s1_id);
  link_set_destination(l, s2_id);
  link_set_direction(l, S);
  link_set_status(l, CLOSE);
  game_add_link(g, l);

  PRINT_TEST_RESULT(game_get_connection(g, s1_id, S) == s2_id);
  game_destroy(g);
  free(g);
}

/** test1_game_link_exists tests game getting wether a link
  * exists or not between 2 spaces
  */
void test1_game_link_exists() {
  PRINT_TEST_RESULT(game_link_exists(NULL, NO_ID, S) == FALSE);
}
/** test2_game_link_exists tests game getting wether a link
  * exists or not between 2 spaces
  */
void test2_game_link_exists() {
  Game *g = NULL;
  Space *s1 = NULL, *s2 = NULL;
  Link *l = NULL;
  Id s1_id = 12, s2_id = 13;
  int result = 1;

  g = game_init();
  game_create(g);

  s1 = space_create(s1_id);
  game_add_space(g, s1);
  s2 = space_create(s2_id);
  game_add_space(g, s2);

  l = link_create(14);
  link_set_origin(l, 12);
  link_set_destination(l, 13);
  link_set_direction(l, S);
  link_set_status(l, OPEN);

  if(game_link_exists(g, s1_id, S)){
    result = 0;
  }

  game_add_link(g, l);

  if(result) result = game_link_exists(g, s1_id, S) == TRUE;

  PRINT_TEST_RESULT(result);
  game_destroy(g);
  free(g);
}

/** test1_game_print_data tests game printing data
  */
void test1_game_print_data() {
  Game *g = NULL;
  g = game_init();
  game_create(g);
  PRINT_TEST_RESULT(game_print_data(g) == OK);
  game_destroy(g);
  free(g);
}

/** test2_game_print_data tests game printing data
  */
void test2_game_print_data() {
  PRINT_TEST_RESULT(game_print_data(NULL) == ERROR);
}

/** test1_object_id_to_name tests game getting the 
  * name of an object with its id
  */
void test1_object_id_to_name() {
  PRINT_TEST_RESULT(game_object_id_to_name(NULL, 13) == NULL);
}

/** test2_object_id_to_name tests game getting the 
  * name of an object with its id
  */
void test2_object_id_to_name() {
  Game *g = NULL;
  g = game_init();
  game_create(g);
  PRINT_TEST_RESULT(game_object_id_to_name(g, NO_ID) == NULL);
  game_destroy(g);
  free(g);
}

/** test3_object_id_to_name tests game getting the 
  * name of an object with its id
  */
void test3_object_id_to_name() {
  Game *g = NULL;
  Object *o = NULL;
  char *name = NULL;
  g = game_init();
  game_create(g);
  o = object_create(12);
  object_set_name(o, "Grain");
  game_add_object(g, o, 13);
  name = game_object_id_to_name(g, 12);
  PRINT_TEST_RESULT(strcmp(name, "Grain") == 0);
  game_destroy(g);
  free(g);
}

/** test1_game_get_object_from_id tests game getting the 
  * an object from an id
  */
void test1_game_get_object_from_id() {
  Game *g = NULL;
  Object *o = NULL;
  g = game_init();
  game_create(g);
  o = object_create(12);
  game_add_object(g, o, 13);
  PRINT_TEST_RESULT(game_get_object_from_id(g, 12) == o);
  game_destroy(g);
  free(g);
}

/** test2_game_get_object_from_id tests game getting the 
  * an object from an id
  */
void test2_game_get_object_from_id() {
  PRINT_TEST_RESULT(game_get_object_from_id(NULL, 12) == NULL);
}

/** test1_game_get_space_from_index tests game getting the space 
  * from a game with some index
  */
void test1_game_get_space_from_index() {
  Game *g = NULL;
  Space *s = NULL;
  g = game_init();
  game_create(g);
  s = space_create(12);
  game_add_space(g, s);
  PRINT_TEST_RESULT(game_get_space_from_index(g, 0) == s);
  game_destroy(g);
  free(g);
}

/** test2_game_get_space_from_index tests game getting the space 
  * from a game with some index
  */
void test2_game_get_space_from_index() {
  PRINT_TEST_RESULT(game_get_space_from_index(NULL, 0) == NULL);
}

/** test1_game_get_link_from_index tests game getting the link 
  * from a game with some index
  */
void test1_game_get_link_from_index() {
  Game *g = NULL;
  Link *l = NULL;
  g = game_init();
  game_create(g);
  l = link_create(12);
  game_add_link(g, l);
  PRINT_TEST_RESULT(game_get_link_from_index(g, 0) == l);
  game_destroy(g);
  free(g);
}

/** test2_game_get_link_from_index tests game getting the link 
  * from a game with some index
  */
void test2_game_get_link_from_index() {
  PRINT_TEST_RESULT(game_get_link_from_index(NULL, 0) == NULL);
}

/** test1_game_get_space_description tests game getting the description of the space
  */
void test1_game_get_space_description() {
  Game *g = NULL;
  Space *s = NULL;
  g = game_init();
  game_create(g);
  s = space_create(12);
  space_set_description(s, "hola");
  game_add_space(g, s);
  PRINT_TEST_RESULT(strcmp(game_get_space_description(g, 12), "hola") == 0);
  game_destroy(g);
  free(g);
}

/** test2_game_get_space_description tests game getting the description of the space
  */
void test2_game_get_space_description() {
  PRINT_TEST_RESULT(game_get_space_description(NULL, 12) == NULL);
}

/** test1_game_get_space_name tests game getting the name of the space
  */
void test1_game_get_space_name() {
  Game *g = NULL;
  Space *s = NULL;
  g = game_init();
  game_create(g);
  s = space_create(12);
  space_set_name(s, "adios");
  game_add_space(g, s);
  PRINT_TEST_RESULT(strcmp(game_get_space_name(g, 12), "adios") == 0);
  game_destroy(g);
  free(g);
}

/** test2_game_get_space_name tests game getting the name of the space
  */
void test2_game_get_space_name() {
  PRINT_TEST_RESULT(game_get_space_name(NULL, 12) == NULL);
}

/** test1_game_get_dialogue_command_result tests game getting the dialogue 
  * string with command result
  */
void test1_game_get_dialogue_command_result() {
  Game *g = NULL;
  g = game_init();
  game_create(g);
  PRINT_TEST_RESULT(strcmp(game_get_dialogue_command_result(g), "Introduce un comando de la lista superior.") == 0);
  game_destroy(g);
  free(g);
}

/** test2_game_get_dialogue_command_result tests game getting the dialogue 
  * string with command result
  */
void test2_game_get_dialogue_command_result() {
  PRINT_TEST_RESULT(game_get_dialogue_command_result(NULL) == NULL);
}

/** test1_game_player_can_illuminate tests game getting wether the player 
  * has a turnedon object to illuminate
  */
void test1_game_player_can_illuminate() {
  Game *g = NULL;
  Object *o = NULL;
  Player *p = NULL;
  g = game_init();
  game_create(g);
  o = object_create(12);
  object_set_turnedon(o, TRUE);
  object_set_illuminate(o, TRUE);
  game_add_object(g, o, 13);
  p = player_create(11);
  game_set_player(g, p);
  player_add_object_to_inventory(p, 12);
  PRINT_TEST_RESULT(game_player_can_illuminate(g) == TRUE);
  game_destroy(g);
  free(g);
}

/** test2_game_player_can_illuminate tests game getting wether the player 
  * has a turnedon object to illuminate
  */
void test2_game_player_can_illuminate() {
  PRINT_TEST_RESULT(game_player_can_illuminate(NULL) == FALSE);
}

