/** 
 * @brief It tests game_rules module
 * 
 * @file game_rules_test.c
 * @author Sergio Saúco
 * @version 1.0 
 * @date 01-05-2023
 * @copyright GNU Public License
 */

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "game_rules.h"
#include "game_rules_test.h"
#include "test.h"

#define MAX_TESTS 3 /*!< The maximum number of tests */

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

  if (all || test == 1) test1_game_rules_run();
  if (all || test == 2) test2_game_rules_run();
  if (all || test == 3) test3_game_rules_run(argv[1]);

  PRINT_PASSED_PERCENTAGE;
  return 1;
}

/** test1_game_rules_run tests game creation
  */
void test1_game_rules_run() {
  PRINT_TEST_RESULT(game_rules_run(NULL, "linm.2") == ERROR);
}
/** test2_game_rules_run tests game creation
  */
void test2_game_rules_run() {
  Game *g = NULL;
  g = game_init();
  game_create(g);
  PRINT_TEST_RESULT(game_rules_run(g, NULL) == ERROR);
  game_destroy(g);
  free(g);
}
/** test3_game_rules_run tests game creation
  */
void test3_game_rules_run(char *filename) {
  Game *g = NULL;
  g = game_init();
  game_create_from_file(g, filename);
  PRINT_TEST_RESULT(game_rules_run(g, "linm.2") == OK);
  game_destroy(g);
  free(g);
}
