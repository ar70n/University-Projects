/** 
 * @brief It tests link module
 * 
 * @file link_test.c
 * @author Miguel Campo
 * @version 1.0
 * @date 24-03-2023
 * @copyright GNU Public License
 */

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "link.h"
#include "link_test.h"
#include "test.h"

#define MAX_TESTS 29 /*!< The maximum number of tests */

/** 
 * @brief Main function for LINK unit tests. 
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
    printf("Running all test for module Link:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 && test > MAX_TESTS) {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
    }
  }


  if (all || test == 1) test1_link_create();
  if (all || test == 2) test2_link_create();
  if (all || test == 3) test1_link_set_name();
  if (all || test == 4) test2_link_set_name();
  if (all || test == 5) test3_link_set_name();
  if (all || test == 6) test1_link_get_name();
  if (all || test == 7) test2_link_get_name();
  if (all || test == 8) test1_link_get_id();
  if (all || test == 9) test2_link_get_id();
  if (all || test == 10) test1_link_destroy();
  if (all || test == 11) test2_link_destroy();
  if (all || test == 12) test1_link_get_direction();
  if (all || test == 13) test2_link_get_direction();
  if (all || test == 14) test1_link_set_direction();
  if (all || test == 15) test2_link_set_direction();
  if (all || test == 16) test1_link_get_status();
  if (all || test == 17) test2_link_get_status();
  if (all || test == 18) test1_link_set_status();
  if (all || test == 19) test2_link_set_status();
  if (all || test == 20) test1_link_print();
  if (all || test == 21) test2_link_print();
  if (all || test == 22) test1_link_get_origin();
  if (all || test == 23) test2_link_get_origin();
  if (all || test == 24) test1_link_set_origin();
  if (all || test == 25) test2_link_set_origin();
  if (all || test == 26) test1_link_get_destination();
  if (all || test == 27) test2_link_get_destination();
  if (all || test == 28) test1_link_set_destination();
  if (all || test == 29) test2_link_set_destination();


  PRINT_PASSED_PERCENTAGE;

  return 1;
}

/** test1_link_create tests link creation
  */
void test1_link_create() {
  int result;
  Link *s;
  s = link_create(5);
  result=s!=NULL;
  PRINT_TEST_RESULT(result);
  link_destroy(s);
}
/** test2_link_create tests link creation
  */
void test2_link_create() {
  Link *s;
  s = link_create(4);
  PRINT_TEST_RESULT(link_get_id(s) == 4);
  link_destroy(s);
}

/** test1_link_set_name test function for link_name setting
  */
void test1_link_set_name() {
  Link *s;
  s = link_create(5);
  PRINT_TEST_RESULT(link_set_name(s, "hola") == OK);
  link_destroy(s);
}
/** test2_link_set_name test function for link_name setting
  */
void test2_link_set_name() {
  Link *s = NULL;
  PRINT_TEST_RESULT(link_set_name(s, "hola") == ERROR);
}
/** test3_link_set_name test function for link_name setting
  */
void test3_link_set_name() {
  Link *s;
  s = link_create(5);
  PRINT_TEST_RESULT(link_set_name(s, NULL) == ERROR);
  link_destroy(s);
}

/** test1_link_get_name test function for link_name getting
  */
void test1_link_get_name() {
  Link *s;
  s = link_create(1);
  link_set_name(s, "adios");
  PRINT_TEST_RESULT(strcmp(link_get_name(s), "adios") == 0);
  link_destroy(s);
}
/** test2_link_get_name test function for link_name getting
  */
void test2_link_get_name() {
  Link *s = NULL;
  PRINT_TEST_RESULT(link_get_name(s) == NULL);
}

/** test1_link_get_id test function for link_id getting
  */
void test1_link_get_id() {
  Link *s;
  s = link_create(25);
  PRINT_TEST_RESULT(link_get_id(s) == 25);
  link_destroy(s);
}
/** test2_link_get_id test function for link_id getting
  */
void test2_link_get_id() {
  Link *s = NULL;
  PRINT_TEST_RESULT(link_get_id(s) == NO_ID);
}

/** test1_link_destroy test function 
  * for link memory freeing
  */
void test1_link_destroy(){
    Link *s;
    s = link_create(25);
    PRINT_TEST_RESULT(link_destroy(s) == OK);
}
/** test2_link_destroy test 
  * function for link memory freeing
  */
void test2_link_destroy(){
    Link *s = NULL;
    PRINT_TEST_RESULT(link_destroy(s) == ERROR);
}

/** test1_link_set_origin tests
  * link_origin setting
  */
void test1_link_set_origin(){
    Link *s;
    s = link_create(25);
    PRINT_TEST_RESULT(link_set_origin(s, 5) == OK);
    link_destroy(s);
}
/** test2_link_set_origin tests
  * link_origin setting
  */
void test2_link_set_origin(){
    Link *s = NULL;
    PRINT_TEST_RESULT(link_set_origin(s, 5) == ERROR);
}

/** test1_link_set_destination tests
  * link_destination setting
  */
void test1_link_set_destination(){
    Link *s;
    s = link_create(25);
    PRINT_TEST_RESULT(link_set_destination(s, 5) == OK);
    link_destroy(s);
}
/** test2_link_set_destination tests
  * link_destination setting
  */
void test2_link_set_destination(){
    Link *s = NULL;
    PRINT_TEST_RESULT(link_set_destination(s, 5) == ERROR);
}

/** test1_link_get_origin tests
  * link_origin getting
  */
void test1_link_get_origin(){
    Link *s;
    s = link_create(25);
    link_set_origin(s, 5);
    PRINT_TEST_RESULT(link_get_origin(s) == 5);
    link_destroy(s);
}
/** test2_link_get_origin tests
  * link_origin getting
  */
void test2_link_get_origin(){
    Link *s = NULL;
    PRINT_TEST_RESULT(link_get_origin(s) == NO_ID);
}

/** test1_link_get_destination tests
  * link_destination getting
  */
void test1_link_get_destination(){
    Link *s;
    s = link_create(25);
    link_set_destination(s, 5);
    PRINT_TEST_RESULT(link_get_destination(s) == 5);
    link_destroy(s);
}
/** test2_link_get_destination tests
  * link_destination getting
  */
void test2_link_get_destination(){
    Link *s = NULL;
    PRINT_TEST_RESULT(link_get_destination(s) == NO_ID);
}

/** test1_link_set_direction tests
  * link_direction setting
  */
void test1_link_set_direction(){
    Link *s;
    s = link_create(25);
    PRINT_TEST_RESULT(link_set_direction(s, N) == OK);
    link_destroy(s);
}
/** test2_link_set_direction tests
  * link_direction setting
  */
void test2_link_set_direction(){
    Link *s = NULL;
    PRINT_TEST_RESULT(link_set_direction(s, N) == ERROR);
}

/** test1_link_get_direction tests
  * link_direction getting
  */
void test1_link_get_direction(){
    Link *s;
    s = link_create(25);
    link_set_direction(s, N);
    PRINT_TEST_RESULT(link_get_direction(s) == N);
    link_destroy(s);
}
/** test2_link_get_direction tests
  * link_direction getting
  */
void test2_link_get_direction(){
    Link *s = NULL;
    PRINT_TEST_RESULT(link_get_direction(s) == I);
}

/** test1_link_set_status tests
  * link_status setting
  */
void test1_link_set_status(){
    Link *s;
    s = link_create(25);
    PRINT_TEST_RESULT(link_set_status(s, OPEN) == OK);
    link_destroy(s);
}
/** test2_link_set_status tests
  * link_status setting
  */
void test2_link_set_status(){
    Link *s = NULL;
    PRINT_TEST_RESULT(link_set_status(s, OPEN) == ERROR);
}

/** test1_link_get_status tests
  * link_status getting
  */
void test1_link_get_status(){
    Link *s;
    s = link_create(25);
    link_set_status(s, OPEN);
    PRINT_TEST_RESULT(link_get_status(s) == OPEN);
    link_destroy(s);
}
/** test2_link_get_status tests
  * link_status getting
  */
void test2_link_get_status(){
    Link *s = NULL;
    PRINT_TEST_RESULT(link_get_status(s) == NO_ID);
}

/** test1_link_print tests printing 
  * link information
  */
void test1_link_print(){
    Link *s;
    s = link_create(25);
    PRINT_TEST_RESULT(link_print(s) == OK);
    link_destroy(s);
}
/** test2_link_print tests printing 
  * link information
  */
void test2_link_print(){
    Link *s = NULL;
    PRINT_TEST_RESULT(link_print(s) == ERROR);
    link_destroy(s);
}



