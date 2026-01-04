/** 
 * @brief It tests enemy module
 * 
 * @file enemy_test.c
 * @author Antonio Moroño
 * @version 1.0 
 * @date 09-03-2021
 * @copyright GNU Public License
 */

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "enemy.h"
#include "enemy_test.h"
#include "test.h"

#define MAX_TESTS 22 /*!< The maximum number of tests */

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

  if (argc < 2) {
    printf("Running all test for module Enemy:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 && test > MAX_TESTS) {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
    }
  }


  if (all || test == 1) test1_enemy_create();
  if (all || test == 2) test2_enemy_create();
  if (all || test == 3) test1_enemy_destroy();
  if (all || test == 4) test2_enemy_destroy(); 
  if (all || test == 5) test1_enemy_get_id();
  if (all || test == 6) test2_enemy_get_id();
  if (all || test == 7) test1_enemy_set_name();
  if (all || test == 8) test2_enemy_set_name();
  if (all || test == 9) test3_enemy_set_name();
  if (all || test == 10) test1_enemy_get_name();
  if (all || test == 11) test2_enemy_get_name(); 
  if (all || test == 12) test1_enemy_set_location();
  if (all || test == 13) test2_enemy_set_location(); 
  if (all || test == 14) test1_enemy_get_location();
  if (all || test == 15) test2_enemy_get_location(); 
  if (all || test == 16) test3_enemy_get_location(); 
  if (all || test == 17) test1_enemy_set_health(); 
  if (all || test == 18) test2_enemy_set_health();
  if (all || test == 19) test1_enemy_get_health();
  if (all || test == 20) test2_enemy_get_health(); 
  if (all || test == 21) test1_enemy_print();
  if (all || test == 22) test2_enemy_print(); 
  

  PRINT_PASSED_PERCENTAGE;

  return 1;
}

/** test1_enemy_create tests enemy creation
  */
void test1_enemy_create() {
  int result;
  Enemy *s;
  s = enemy_create(5);
  result=s!=NULL ;
  PRINT_TEST_RESULT(result);
  enemy_destroy(s);
}
/** test2_enemy_create tests enemy creation
  */
void test2_enemy_create() {
  Enemy *s;
  s = enemy_create(4);
  PRINT_TEST_RESULT(enemy_get_id(s) == 4);
  enemy_destroy(s);
}

/** test1_enemy_set_name tests enemy_name setting
  */
void test1_enemy_set_name() {
  Enemy *s;
  s = enemy_create(5);
  PRINT_TEST_RESULT(enemy_set_name(s, "hola") == OK);
  enemy_destroy(s);
}
/** test2_enemy_set_name tests enemy_name setting
  */
void test2_enemy_set_name() {
  Enemy *s = NULL;
  PRINT_TEST_RESULT(enemy_set_name(s, "hola") == ERROR);
}
/** test3_enemy_set_name tests enemy_name setting
  */
void test3_enemy_set_name() {
  Enemy *s;
  s = enemy_create(5);
  PRINT_TEST_RESULT(enemy_set_name(s, NULL) == ERROR);
  enemy_destroy(s);
}

/** test1_enemy_get_name tests getting enemy name
  */
void test1_enemy_get_name() {
  Enemy *s;
  s = enemy_create(1);
  enemy_set_name(s, "adios");
  PRINT_TEST_RESULT(strcmp(enemy_get_name(s), "adios") == 0);
  enemy_destroy(s);
}
/** test2_enemy_get_name tests getting enemy name
  */
void test2_enemy_get_name() {
  Enemy *s = NULL;
  PRINT_TEST_RESULT(enemy_get_name(s) == NULL);
}

/** test1_enemy_get_location tests getting 
  * enemy location
  */
void test1_enemy_get_location() {
  Enemy *s;
  s = enemy_create(1);
  PRINT_TEST_RESULT(enemy_get_location(s) == NO_ID);
  enemy_destroy(s);
}
/** test2_enemy_get_location tests getting 
  * enemy location
  */
void test2_enemy_get_location() {
  Enemy *s;
  s = enemy_create(1);
  enemy_set_location(s,122);
  PRINT_TEST_RESULT(enemy_get_location(s) == 122);
  enemy_destroy(s);    
}
/** test3_enemy_get_location tests getting 
  * enemy location
  */
void test3_enemy_get_location() {
  Enemy *s = NULL;
  PRINT_TEST_RESULT(enemy_get_location(s) == NO_ID);
}

/** test1_enemy_get_id tests enemy getting id
  */
void test1_enemy_get_id() {
  Enemy *s;
  s = enemy_create(25);
  PRINT_TEST_RESULT(enemy_get_id(s) == 25);
  enemy_destroy(s);
}
/** test2_enemy_get_id tests enemy getting id
  */
void test2_enemy_get_id() {
  Enemy *s = NULL;
  PRINT_TEST_RESULT(enemy_get_id(s) == NO_ID);
}

/** test1_enemy_set_location tests setting enemy location
  */
void test1_enemy_set_location(){
	Enemy *s;
	s = enemy_create(25);
	PRINT_TEST_RESULT(enemy_set_location(s,11)==OK);
	enemy_destroy(s);

}

/** test1_enemy_get_health tests getting enemy health
  */
void test1_enemy_get_health(){
	Enemy *s;
	s = enemy_create(25);
	enemy_set_health(s,2);
	PRINT_TEST_RESULT(enemy_get_health(s)==2);
	enemy_destroy(s);
}

/** test1_enemy_print tests printing enemy information
  */
void test1_enemy_print()
{
	Enemy *s;
	s = enemy_create(25);
	PRINT_TEST_RESULT(enemy_print(s)==OK);
	enemy_destroy(s);
}

/** test1_enemy_destroy tests destroying enemy
  */
void test1_enemy_destroy(){
	Enemy *s;
	s = enemy_create(25);
	PRINT_TEST_RESULT(enemy_destroy(s)==OK);
}
/** test2_enemy_destroy tests destroying enemy
  */
void test2_enemy_destroy(){
	Enemy *s=NULL;
	
	PRINT_TEST_RESULT(enemy_destroy(s)==ERROR);
}

/** test2_enemy_set_location setting enemy location
  */
void test2_enemy_set_location(){
	Enemy*s;
	s = enemy_create(25);
	PRINT_TEST_RESULT(enemy_set_location(s, NO_ID)==OK);
	enemy_destroy(s);
}

/** test1_enemy_set_health tests setting enemy health
  */
void test1_enemy_set_health(){
	Enemy *s;
	s = enemy_create(25);
	PRINT_TEST_RESULT(enemy_set_health(s,1)==OK);
	enemy_destroy(s);
}
/** test2_enemy_set_health tests setting enemy health
  */
void test2_enemy_set_health(){
	Enemy *s;
	s = enemy_create(25);
	PRINT_TEST_RESULT(enemy_set_health(s,0)==OK);
	enemy_destroy(s);
}

/** test2_enemy_get_health tests getting enemy health
  */
void test2_enemy_get_health(){
	Enemy *s=NULL;
	PRINT_TEST_RESULT(enemy_get_health(s)==-1);
}

/** test2_enemy_print tests printing enemy information
  */
void test2_enemy_print(){
	Enemy *s=NULL;
	PRINT_TEST_RESULT(enemy_print(s)==ERROR);
}
