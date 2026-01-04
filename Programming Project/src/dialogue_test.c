/** 
 * @brief It tests dialogue module
 * 
 * @file dialogue_test.c
 * @author Antonio Moroño
 * @version 3.1 
 * @date 27-03-2023
 * @copyright GNU Public License
 */

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "dialogue.h"
#include "dialogue_test.h"
#include "command.h"
#include "test.h"

#define MAX_TESTS 26 /*!< The maximum number of tests */

/** 
 * @brief Main function for DIALOGUE unit tests. 
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

  if (argc < 2) {
    printf("Running all test for module Dialogue:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 && test > MAX_TESTS) {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
    }
  }


  if (all || test == 1) test1_dialogue_create();
  if (all || test == 2) test2_dialogue_create();
  if (all || test == 3) test1_dialogue_destroy();
  if (all || test == 4) test2_dialogue_destroy();
  if (all || test == 5) test1_dialogue_set_command_result();
  if (all || test == 6) test2_dialogue_set_command_result();
  if (all || test == 7) test1_dialogue_get_command_result();
  if (all || test == 8) test2_dialogue_get_command_result();
  if (all || test == 9) test1_dialogue_set_previous_command();
  if (all || test == 10) test2_dialogue_set_previous_command();
  if (all || test == 11) test1_dialogue_get_previous_command();
  if (all || test == 12) test2_dialogue_get_previous_command();
  if (all || test == 13) test1_dialogue_set_previous_command_status();
  if (all || test == 14) test2_dialogue_set_previous_command_status();
  if (all || test == 15) test1_dialogue_get_previous_command_status();
  if (all || test == 16) test2_dialogue_get_previous_command_status();
  if (all || test == 17) test1_dialogue_set_previous_additional_information();
  if (all || test == 18) test2_dialogue_set_previous_additional_information();
  if (all || test == 19) test1_dialogue_get_previous_additional_information();
  if (all || test == 20) test2_dialogue_get_previous_additional_information();
  if (all || test == 21) test1_dialogue_set_previous_player_location();
  if (all || test == 22) test2_dialogue_set_previous_player_location();
  if (all || test == 23) test1_dialogue_get_previous_player_location();
  if (all || test == 24) test2_dialogue_get_previous_player_location();
  if (all || test == 25) test1_dialogue_print();
  if (all || test == 26) test2_dialogue_print();

  PRINT_PASSED_PERCENTAGE;

  return 1;
}

/** tet1_dialogue_create tests dialogue creation
  */
void test1_dialogue_create() {
  int result;
  Dialogue *s;
  s = dialogue_create();
  result=s!=NULL ;
  PRINT_TEST_RESULT(result);
  dialogue_destroy(s);
}
/** tet2_dialogue_create tests dialogue creation
  */
void test2_dialogue_create() {
  Dialogue *s;
  s = dialogue_create();
  PRINT_TEST_RESULT(dialogue_get_previous_command(s)==NO_CMD);
  dialogue_destroy(s);
}

/** tet1_dialogue_destroy tests dialogue destruction
  */
void test1_dialogue_destroy() {
  Dialogue *s;
  s = dialogue_create();
  PRINT_TEST_RESULT(dialogue_destroy(s)==OK);
}
/** tet2_dialogue_destroy tests dialogue destruction
  */
void test2_dialogue_destroy() {
  Dialogue *s;
  s = NULL;
  PRINT_TEST_RESULT(dialogue_destroy(s)==ERROR);
}

/** test1_dialogue_set_command_result test function for setting the command result
  */
void test1_dialogue_set_command_result() {
  Dialogue *s;
  s = dialogue_create();
  PRINT_TEST_RESULT(dialogue_set_command_result(s, "TEST DIALOGUE COMMAND RESULT")==OK);
  dialogue_destroy(s);
}
/** test2_dialogue_set_command_result test function for setting the command result
  */
void test2_dialogue_set_command_result() {
  Dialogue *s;
  s = dialogue_create();
  PRINT_TEST_RESULT(dialogue_set_command_result(s, NULL)==ERROR);
  dialogue_destroy(s);
}

/** test1_dialogue_get_command_result test function for getting the command result
  */
void test1_dialogue_get_command_result() {
  Dialogue *s;
  s = dialogue_create();
  dialogue_set_command_result(s,"TEST DIALOGUE COMMAND RESULT"); 
  PRINT_TEST_RESULT(strcmp(dialogue_get_command_result(s), "TEST DIALOGUE COMMAND RESULT")==0);
  dialogue_destroy(s);
}
/** test2_dialogue_get_command_result test function for getting the command result
  */
void test2_dialogue_get_command_result() {
  PRINT_TEST_RESULT(dialogue_get_command_result(NULL)==NULL);
}

/** test1_dialogue_set_previous_command test function for setting the previous command result
  */
void test1_dialogue_set_previous_command() {
  Dialogue *s;
  s = dialogue_create();
  PRINT_TEST_RESULT(dialogue_set_previous_command(s, ATTACK)==OK);
  dialogue_destroy(s);
}
/** test2_dialogue_set_previous_command test function for setting the previous command 
  */
void test2_dialogue_set_previous_command() {
  Dialogue *s;
  s = dialogue_create();
  PRINT_TEST_RESULT(dialogue_set_previous_command(s, NO_CMD)==ERROR);
  dialogue_destroy(s);
}

/** test1_dialogue_get_previous_command test function for getting the previous command
  */
void test1_dialogue_get_previous_command() {
  Dialogue *s;
  s = dialogue_create();
  dialogue_set_previous_command(s, ATTACK); 
  PRINT_TEST_RESULT(dialogue_get_previous_command(s)==ATTACK);
  dialogue_destroy(s);
}
/** test2_dialogue_get_previous_command test function for getting the previous command
  */
void test2_dialogue_get_previous_command() {
  Dialogue *s;
  s = NULL;
  PRINT_TEST_RESULT(dialogue_get_previous_command(s)==NO_CMD);
}

/** test1_dialogue_set_previous_command_status test function for setting the previous command status
  */
void test1_dialogue_set_previous_command_status() {
  Dialogue *s;
  s = dialogue_create();
  PRINT_TEST_RESULT(dialogue_set_previous_command_status(s, ERROR)==OK);
  dialogue_destroy(s);
}
/** test2_dialogue_set_previous_command_status test function for setting the previous command status
  */
void test2_dialogue_set_previous_command_status() {
  PRINT_TEST_RESULT(dialogue_set_previous_command_status(NULL, ERROR)==ERROR);
}

/** test1_dialogue_get_previous_command_status test function for getting the previous command status
  */
void test1_dialogue_get_previous_command_status() {
  Dialogue *s;
  s = dialogue_create();
  dialogue_set_previous_command_status(s, OK);
  PRINT_TEST_RESULT(dialogue_get_previous_command_status(s)==OK);
  dialogue_destroy(s);
}
/** test2_dialogue_get_previous_command_status test function for setting the previous command status
  */
void test2_dialogue_get_previous_command_status() {
  PRINT_TEST_RESULT(dialogue_get_previous_command_status(NULL)==ERROR);
}


/** test1_dialogue_set_previous_additional_information test function for setting the previous command additional information
  */
void test1_dialogue_set_previous_additional_information() {
  Dialogue *s;
  s = dialogue_create();
  PRINT_TEST_RESULT(dialogue_set_previous_additional_information(s, "TEST COMMAND PREVIOUS")==OK);
  dialogue_destroy(s);
}
/** test2_dialogue_set_previous_additional_information test function for setting the previous command additional information
  */
void test2_dialogue_set_previous_additional_information() {
  Dialogue *s;
  s = dialogue_create();
  PRINT_TEST_RESULT(dialogue_set_previous_additional_information(s, NULL)==ERROR);
  dialogue_destroy(s);
}

/** test1_dialogue_get_previous_additional_information test function for getting the previous command additional information
  */
void test1_dialogue_get_previous_additional_information() {
  PRINT_TEST_RESULT(dialogue_get_previous_additional_information(NULL)==NULL);
}
/** test2_dialogue_set_previous_additional_information test function for setting the previous command additional information
  */
void test2_dialogue_get_previous_additional_information() {
  Dialogue *s;
  s = dialogue_create();
  dialogue_set_previous_additional_information(s, "TESTS COMMAND PREVIOUS");
  PRINT_TEST_RESULT(strcmp(dialogue_get_previous_additional_information(s),"TESTS COMMAND PREVIOUS")==0);
  dialogue_destroy(s);
}

/** test1_dialogue_set_previous_player_location test function for setting the previous player location
  */
void test1_dialogue_set_previous_player_location() {
  Dialogue *s;
  s = dialogue_create();
  PRINT_TEST_RESULT(dialogue_set_previous_player_location(s, 101)==OK);
  dialogue_destroy(s);
}
/** test2_dialogue_set_previous_player_location test function for setting the previous player location
  */
void test2_dialogue_set_previous_player_location() {
  PRINT_TEST_RESULT(dialogue_set_previous_player_location(NULL, 101)==ERROR);
}

/** test1_dialogue_get_previous_player_location test function for getting the previous player location
  */
void test1_dialogue_get_previous_player_location() {
  Dialogue *s;
  s = dialogue_create();
  dialogue_set_previous_player_location(s, 101);
  PRINT_TEST_RESULT(dialogue_get_previous_player_location(s)==101);
  dialogue_destroy(s);
}
/** test2_dialogue_get_previous_player_location test function for getting the previous player location
  */
void test2_dialogue_get_previous_player_location() {
  PRINT_TEST_RESULT(dialogue_get_previous_player_location(NULL)==NO_ID);
}

/** test1_dialogue_print test function for printing dialogue
  */
void test1_dialogue_print() {
  Dialogue *s;
  s = dialogue_create();
  dialogue_set_previous_command(s, ATTACK);
  dialogue_set_command_result(s, "COMMAND RESULT");
  dialogue_set_previous_command_status(s, OK);
  dialogue_set_previous_additional_information(s, "PREVIOUS RESULT");
  dialogue_set_previous_player_location(s, 101);
  PRINT_TEST_RESULT(dialogue_print(s)==OK);
  dialogue_destroy(s);
}
/**  test2_dialogue_print test function for printing dialogue
  */
void test2_dialogue_print() {
  PRINT_TEST_RESULT(dialogue_print(NULL)==ERROR);
}
