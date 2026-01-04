/** 
 * @brief It tests inventory module
 * 
 * @file inventory_test.c
 * @author Antonio Moroño
 * @version 3.1 
 * @date 27-03-2023
 * @copyright GNU Public License
 */

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "inventory.h"
#include "inventory_test.h"
#include "set.h"
#include "test.h"

#define MAX_TESTS 20 /*!< The maximum number of tests */

/** 
 * @brief Main function for INVENTORY unit tests. 
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
    printf("Running all test for module Inventory:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 && test > MAX_TESTS) {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
    }
  }


  if (all || test == 1) test1_inventory_create();
  if (all || test == 2) test2_inventory_create();
  if (all || test == 3) test1_inventory_destroy();
  if (all || test == 4) test2_inventory_destroy();
  if (all || test == 5) test1_inventory_add_object();
  if (all || test == 6) test2_inventory_add_object();
  if (all || test == 7) test1_inventory_del_object();
  if (all || test == 8) test2_inventory_del_object();
  if (all || test == 9) test1_inventory_get_objects();
  if (all || test == 10) test2_inventory_get_objects();
  if (all || test == 11) test1_inventory_stores_object();
  if (all || test == 12) test2_inventory_stores_object();
  if (all || test == 13) test1_inventory_get_n_objects();
  if (all || test == 14) test2_inventory_get_n_objects();
  if (all || test == 15) test1_inventory_set_max_objs();
  if (all || test == 16) test2_inventory_set_max_objs();
  if (all || test == 17) test1_inventory_get_max_objs();
  if (all || test == 18) test2_inventory_get_max_objs();
  if (all || test == 19) test1_inventory_print();
  if (all || test == 20) test2_inventory_print();

  PRINT_PASSED_PERCENTAGE;

  return 1;
}

/** tet1_inventory_create tests inventory creation
  */
void test1_inventory_create() {
  int result;
  Inventory *s;
  s = inventory_create();
  result=s!=NULL ;
  PRINT_TEST_RESULT(result);
  inventory_destroy(s);
}

/** tet2_inventory_create tests inventory creation
  */
void test2_inventory_create() {
  void *s=NULL;
  int result;
  s = inventory_create();
  result=s!=NULL ;
  PRINT_TEST_RESULT(result);
  inventory_destroy(s);
}


/** tet1_inventory_destroy tests inventory destruction
  */
void test1_inventory_destroy() {
  Inventory *s;
  s = inventory_create(5);
  PRINT_TEST_RESULT(inventory_destroy(s)==OK);
}

/** tet2_inventory_destroy tests inventory destruction
  */
void test2_inventory_destroy() {
  Inventory *s;
  s = NULL;
  PRINT_TEST_RESULT(inventory_destroy(s)==ERROR);
}



/** test1_inventory_add_object test function for inventory_objects adding
  */
void test1_inventory_add_object() {
  Inventory *s;
  s = inventory_create(5);
  inventory_set_max_objs(s, 1);
  PRINT_TEST_RESULT(inventory_add_object(s, 69) == OK);
  inventory_destroy(s);
}


/** test2_inventory_add_object test function for inventory_objects adding
  */
void test2_inventory_add_object() {
  Inventory *s;
  s = inventory_create(5);
  PRINT_TEST_RESULT(inventory_add_object(s, NO_ID) == ERROR);
  inventory_destroy(s);
}




/** test1_inventory_del_object test function for inventory_objects deleting
  */
void test1_inventory_del_object() {
  Inventory *s;
  s = inventory_create(5);
  inventory_set_max_objs(s, 1);
  inventory_add_object(s, 69);
  PRINT_TEST_RESULT(inventory_del_object(s, 69) == OK);
  inventory_destroy(s);
}


/** test2_inventory_del_object test function for inventory_objects deleting
  */
void test2_inventory_del_object() {
  Inventory *s;
  s = inventory_create(5);
  PRINT_TEST_RESULT(inventory_del_object(s, 69) == ERROR);
  inventory_destroy(s);
}


/** test1_inventory_get_objects test function for inventory_object getting
  */
void test1_inventory_get_objects() {
  Inventory *s;
  s = inventory_create(4);
  inventory_set_max_objs(s, 1);
  inventory_add_object(s,69);
  PRINT_TEST_RESULT(inventory_get_objects(s) != NULL);
  inventory_destroy(s);
}

/** test2_inventory_get_objects test function for inventory_object getting
  */
void test2_inventory_get_objects() {
  Inventory *s = NULL;
  PRINT_TEST_RESULT(inventory_get_objects(s) == ERROR);
}


/** test1_inventory_stores_object test function for searching a object in inventory
  */
void test1_inventory_stores_object() {
  Inventory *s;
  s = inventory_create(4);
  inventory_set_max_objs(s, 1);
  inventory_add_object(s,69);
  PRINT_TEST_RESULT(inventory_stores_object(s,69)==TRUE);
  inventory_destroy(s);
}

/** test2_inventory_stores_object test function for searching a object in inventory
  */
void test2_inventory_stores_object() {
  Inventory *s = NULL;
  s = inventory_create(4);
  PRINT_TEST_RESULT(inventory_stores_object(s, 69) == FALSE);
  inventory_destroy(s);
}


/** test1_inventory_get_n_objects test function for getting number of objects
  */
void test1_inventory_get_n_objects() {
  Inventory *s;
  s = inventory_create(4);
  inventory_set_max_objs(s, 1);
  inventory_add_object(s,69);
  PRINT_TEST_RESULT(inventory_get_n_objects(s)==1);
  inventory_destroy(s);
}

/** test2_inventory_get_n_objects test function for getting number of objects
  */
void test2_inventory_get_n_objects() {
  Inventory *s = NULL;
  s = inventory_create(4);
  PRINT_TEST_RESULT(inventory_get_n_objects(s) == 0);
  inventory_destroy(s);
}



/** test1_inventory_set_max_objs test function for setting max number of objects
  */
void test1_inventory_set_max_objs() {
  Inventory *s;
  s = inventory_create(4);
  PRINT_TEST_RESULT(inventory_set_max_objs(s,1)==OK);
  inventory_destroy(s);
}


/** test2_inventory_set_max_objs test function for setting max number of objects
  */
void test2_inventory_set_max_objs() {
  Inventory *s;
  s = inventory_create(4);
  PRINT_TEST_RESULT(inventory_set_max_objs(s,-5)==ERROR);
  inventory_destroy(s);
}



/** test1_inventory_get_max_objs test function for getting max number of objects
  */
void test1_inventory_get_max_objs() {
  Inventory *s;
  s = inventory_create(4);
  PRINT_TEST_RESULT(inventory_get_max_objs(s)==-1);
  inventory_destroy(s);
}


/** test2_inventory_get_max_objs test function for getting max number of objects
  */
void test2_inventory_get_max_objs() {
  Inventory *s;
  s = inventory_create(4);
  inventory_set_max_objs(s,6);
  PRINT_TEST_RESULT(inventory_get_max_objs(s)==6);
  inventory_destroy(s);
}

/** test1_inventory_print test function for printing inventory
  */
void test1_inventory_print() {
  Inventory *s;
  s = inventory_create(4);
  inventory_set_max_objs(s, 2);
  PRINT_TEST_RESULT(inventory_print(s)==OK);
  inventory_destroy(s);
}


/**  test2_inventory_print test function for printing inventory
  */
void test2_inventory_print() {
  Inventory *s;
  s = NULL;
  PRINT_TEST_RESULT(inventory_print(s)==ERROR);
  inventory_destroy(s);
}





