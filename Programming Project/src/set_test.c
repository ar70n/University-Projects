/** 
 * @brief It tests set module
 * 
 * @file set_test.c
 * @author Sergio Saúco
 * @version 1.0
 * @date 07-03-2023
 * @copyright GNU Public License
 */

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "set.h"
#include "set_test.h"
#include "test.h"

#define MAX_TESTS 15 /*!< The maximum number of tests */

/** 
 * @brief Main function for SET unit tests. 
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
    printf("Running all test for module Set:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 && test > MAX_TESTS) {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
    }
  }


  if (all || test == 1) test1_set_create();
  if (all || test == 2) test2_set_create();
  if (all || test == 3) test1_set_destroy();
  if (all || test == 4) test2_set_destroy();
  if (all || test == 5) test1_set_add();
  if (all || test == 6) test2_set_add();
  if (all || test == 7) test1_set_del();
  if (all || test == 8) test2_set_del();
  if (all || test == 9) test3_set_del();
  if (all || test == 10) test1_set_get_n_ids();
  if (all || test == 11) test2_set_get_n_ids();
  if (all || test == 12) test1_set_get_ids();
  if (all || test == 13) test2_set_get_ids();
  if (all || test == 14) test1_set_print();
  if (all || test == 15) test2_set_print();

  PRINT_PASSED_PERCENTAGE;

  return 1;
}

/** test1_set_create tests set creation
 */
void test1_set_create() {
  int result;
  Set *s;
  s = set_create();
  result=s!=NULL ;
  PRINT_TEST_RESULT(result);
  set_destroy(s);
}

/** test2_set_create tests set creation initialization
 */
void test2_set_create() {
  Set *s;
  s = set_create();
  PRINT_TEST_RESULT(set_get_n_ids(s) == 0);
  set_destroy(s);
}

/** test1_set_destroy tests set destruction with a valid set
  */
void test1_set_destroy() {
  Set *s;
  s = set_create();
  PRINT_TEST_RESULT(set_destroy(s) == OK);
}

/** test2_set_destroy tests set destruction with a null set
  */
void test2_set_destroy() {
  Set *s = NULL;
  PRINT_TEST_RESULT(set_destroy(s) == ERROR);
}

/** test1_set_add tests adding an id to a valid set
  */
void test1_set_add() {
  Set *s;
  s = set_create();
  PRINT_TEST_RESULT(set_add(s, 4) == OK);
  set_destroy(s);
}

/** test2_set_add tests adding an id to a null set
  */
void test2_set_add() {
  Set *s = NULL;
  PRINT_TEST_RESULT(set_add(s, 4) == ERROR);
}

/** test1_set_del tests deleting an id from a valid set with elements
  */
void test1_set_del() {
  Set *s;
  s = set_create();
  set_add(s, 4);
  PRINT_TEST_RESULT(set_del(s, 4) == OK);
  set_destroy(s);
}

/** test2_set_del tests deleting an id from an empty set
  */
void test2_set_del() {
  Set *s;
  s = set_create();
  PRINT_TEST_RESULT(set_del(s, 4) == ERROR);
  set_destroy(s);
}

/** test3_set_del tests deleting an id from a null set
  */
void test3_set_del() {
  Set *s = NULL;
  PRINT_TEST_RESULT(set_del(s, 4) == ERROR);
}

/** test1_set_get_n_ids tests getting the number of id's from a valid set
  */
void test1_set_get_n_ids() {
  Set *s;
  long i;
  s = set_create();
  for (i=0;i<4;i++)
  {
  	set_add(s,(Id)i);
  }
  PRINT_TEST_RESULT(set_get_n_ids(s) == 4);
  set_destroy(s);
}

/** test2_set_get_n_ids tests getting the number of id's from a null set
  */
void test2_set_get_n_ids() {
  Set *s = NULL;
  PRINT_TEST_RESULT(set_get_n_ids(s) == -1);
}

/** test1_set_get_ids tests getting the id's in a valid set
  */
void test1_set_get_ids() {
  Set *s;
  Id id[1] = {4}, *ids;
  int flag = 0;
  s = set_create(1);
  set_add(s, 4);
  ids = set_get_ids(s);
  if (id[0] == ids[0]) {
    flag = 1;
  }
  PRINT_TEST_RESULT(flag == 1);
  set_destroy(s); 
}

/** test2_set_get_ids tests getting the id's in an invalid set (null)
  */
void test2_set_get_ids() {
  Set *s = NULL;
  PRINT_TEST_RESULT(set_get_ids(s) == NULL);
}

/** test1_set_print tests printing the set information from a valid set
  */
void test1_set_print() {
  Set *s;
  s = set_create();
  PRINT_TEST_RESULT(set_print(s) == OK);
  set_destroy(s);
}

/** test2_set_print tests printing the set information from a null set
  */
void test2_set_print() {
  Set *s = NULL;
  PRINT_TEST_RESULT(set_print(s) == ERROR);
}
