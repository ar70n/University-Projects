/** 
 * @brief It tests command module
 * 
 * @file command_test.c
 * @author Jorge Jiménez
 * @version 1.0
 * @date 31-03-2023
 * @copyright GNU Public License
 */

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "command.h"
#include "command_test.h"
#include "test.h"
#include "types.h"
#define MAX_TESTS 2 /*!< The maximum number of tests */
#define TEST_STRING_MAX 100 /*!< The maximum number of characters of the test string */

/** 
 * @brief Main function for COMMAND unit tests. 
 * 
 * You may execute ALL or a SINGLE test
 *   1.- No parameter -> ALL test are executed 
 *   2.- A number means a particular test (the one identified by that number) 
 *       is executed
 *  
 */
int main(int argc, char* argv[TEST_STRING_MAX]) {
  FILE *f;
  int test = 0;
  int all = 1;

  if (argc == 1) {
    printf("Use: %s <Set of command inputs>\n", argv[0]);
    return 1;
  }
  else if (argc < 3) {
    printf("Running all test for command Set: %s\n", argv[1]);
   
  } else {
    test = atoi(argv[2]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 && test > MAX_TESTS) {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
    }
  }
  if((f = fopen(argv[1], "r")) == NULL){
    printf("Error opening file");
    return 1;
  }

  if (all || test == 1) test1_command_get_user_input(f);
  if (all || test == 2) test2_command_get_user_input(f);

  fclose(f);

  PRINT_PASSED_PERCENTAGE;

  return 1;
}

/** test1_command_get_user_input tests the function in charge of getting the user input
  */
void test1_command_get_user_input(FILE *f) {
  char *aditional_information = NULL;
  PRINT_TEST_RESULT(command_get_user_input(aditional_information, f) == UNKNOWN);
}

/** test2_command_get_user_input tests the function in charge of getting the user input
  */
void test2_command_get_user_input(FILE *f) {
  char *aditional_information = malloc(TEST_STRING_MAX*sizeof(char));
  int result = 1;

    

  T_Command cmd = command_get_user_input(aditional_information, f);
  if (cmd != MOVE) {
    result = 0;
  }

  cmd = command_get_user_input(aditional_information, f);
  if (cmd != TAKE) {
    result = 0;
  }

  cmd = command_get_user_input(aditional_information, f);
  if (cmd != DROP) {
    result = 0;
  }

  cmd = command_get_user_input(aditional_information, f);
  if (cmd != INSPECT) {
    result = 0;
  }

  cmd = command_get_user_input(aditional_information, f);
  if (cmd != UNKNOWN) {
    result = 0;
  }

  cmd = command_get_user_input(aditional_information, f);
  if (cmd != EXIT) {
    result = 0;
  }

  free(aditional_information);
  PRINT_TEST_RESULT(result);
}
