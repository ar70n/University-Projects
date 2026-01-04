/** 
 * @brief It tests game_management module
 * 
 * @file game_management_test.c
 * @author Sergio Saúco
 * @version 1.0 
 * @date 13-04-2021
 * @copyright GNU Public License
 */

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "game_management.h"
#include "game_management_test.h"
#include "test.h"

#define MAX_TESTS 14 /*!< The maximum number of tests */

/** 
 * @brief Main function for ENEMY unit tests. 
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

  if (all || test == 1) test1_game_management_load_spaces(argv[1]);
  if (all || test == 2) test2_game_management_load_spaces();
  if (all || test == 3) test1_game_management_load_objects(argv[1]);
  if (all || test == 4) test2_game_management_load_objects();
  if (all || test == 5) test1_game_management_load_player(argv[1]);
  if (all || test == 6) test2_game_management_load_player();
  if (all || test == 7) test1_game_management_load_enemies(argv[1]);
  if (all || test == 8) test2_game_management_load_enemies();
  if (all || test == 9) test1_game_management_load_links(argv[1]);
  if (all || test == 10) test2_game_management_load_links();
  if (all || test == 11) test1_game_management_save();
  if (all || test == 12) test2_game_management_save(argv[1]);
  if (all || test == 13) test1_game_management_load(argv[1]);
  if (all || test == 14) test2_game_management_load();

  PRINT_PASSED_PERCENTAGE;
  return 1;
}

/** test1_game_management_load_spaces tests loading spaces 
  * from a specific file
  */
void test1_game_management_load_spaces(char *filename) {
  Game *g = NULL;
  g = game_init();
  game_create(g);
  PRINT_TEST_RESULT(game_management_load_spaces(g, filename) == OK);
  game_destroy(g);
  free (g);
}
/** test2_game_management_load_spaces tests loading spaces 
  * from a specific file
  */
void test2_game_management_load_spaces() {
  Game *g = NULL;
  g = game_init();
  PRINT_TEST_RESULT(game_management_load_spaces(g, NULL) == ERROR);
  free (g);
}

/** test1_game_management_load_objects tests loading objects 
  * from a specific file
  */
void test1_game_management_load_objects(char *filename) {
  Game *g = NULL;
  g = game_init();
  game_create(g);
  PRINT_TEST_RESULT(game_management_load_objects(g, filename) == OK);
  game_destroy(g);
  free (g);
}
/** test2_game_management_load_objects tests loading objects 
  * from a specific file
  */
void test2_game_management_load_objects() {
  Game *g = NULL;
  g = game_init();
  PRINT_TEST_RESULT(game_management_load_objects(g, NULL) == ERROR);
  free (g);
}

/** test1_game_management_load_player tests loading player 
  * from a specific file
  */
void test1_game_management_load_player(char *filename) {
  Game *g = NULL;
  g = game_init();
  game_create(g);
  PRINT_TEST_RESULT(game_management_load_player(g, filename) == OK);
  game_destroy(g);
  free (g);
}
/** test2_game_management_load_player tests loading player
  * from a specific file
  */
void test2_game_management_load_player() {
  Game *g = NULL;
  g = game_init();
  PRINT_TEST_RESULT(game_management_load_player(g, NULL) == ERROR);
  free (g);
}

/** test1_game_management_load_enemy tests loading enemy 
  * from a specific file
  */
void test1_game_management_load_enemies(char *filename) {
  Game *g = NULL;
  g = game_init();
  game_create(g);
  PRINT_TEST_RESULT(game_management_load_enemies(g, filename) == OK);
  game_destroy(g);
  free (g);
}
/** test2_game_management_load_enemy tests loading enemy 
  * from a specific file
  */
void test2_game_management_load_enemies() {
  Game *g = NULL;
  g = game_init();
  PRINT_TEST_RESULT(game_management_load_enemies(g, NULL) == ERROR);
  free (g);
}

/** test1_game_management_load_links tests loading links 
  * from a specific file
  */
void test1_game_management_load_links(char *filename) {
  Game *g = NULL;
  g = game_init();
  game_create(g);
  PRINT_TEST_RESULT(game_management_load_links(g, filename) == OK);
  game_destroy(g);
  free (g);
}

/** test2_game_management_load_links tests loading links 
  * from a specific file
  */
void test2_game_management_load_links() {
  Game *g = NULL;
  g = game_init();
  PRINT_TEST_RESULT(game_management_load_links(g, NULL) == ERROR);
  free (g);
}

/** test1_game_management_save tests saving 
  * a game
  */
void test1_game_management_save() {
  Game *g = NULL;
  PRINT_TEST_RESULT(game_management_save(g, "prueba1.txt") == ERROR);
}

/** test2_game_management_save tests saving
  * a game
  */
void test2_game_management_save(char *filename) {
  Game *g = NULL;
  char savename[] = "game_save_test_out";
  g = game_init();
  game_create_from_file(g, filename);
  PRINT_TEST_RESULT(game_management_save(g, savename) == OK);
  game_destroy(g);
  free(g);
}

/** test1_game_management_load tests game loading 
  * a game
 */
void test1_game_management_load(char *filename) {
  Game *g = NULL;
  char savename[] = "game_save_test", loadname[23];
  int i;
  g = game_init();
  game_create_from_file(g, filename);
  game_management_save(g, savename);
  for (i = 0; savename[i] != '.'; i++) {
    loadname[i] = savename[i];
  }
  loadname[i] = '\0';
  PRINT_TEST_RESULT(game_management_load(g, loadname) == OK);
  game_destroy(g);
  free(g);
}
/** test2_game_management_load tests game loading
  * a game
 */
void test2_game_management_load() {
  Game *g = NULL;
  char *file_name = NULL;
  g = game_init();
  PRINT_TEST_RESULT(game_management_load(g, file_name) == ERROR);
  free(g);
}

