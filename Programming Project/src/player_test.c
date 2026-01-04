/** 
 * @brief It tests player module
 * 
 * @file player_test.c
 * @author Miguel Campo
 * @version 1.0 
 * @date 22-03-2023
 * @copyright GNU Public License
 */

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "player.h"
#include "player_test.h"
#include "test.h"

#define MAX_TESTS 35 /*!< The maximum number of tests */

/** 
 * @brief Main function for PLAYER unit tests. 
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
    printf("Running all test for module Player:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 && test > MAX_TESTS) {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
    }
  }


  if (all || test == 1) test1_player_create();
  if (all || test == 2) test2_player_create();
  if (all || test == 3) test1_player_destroy();
  if (all || test == 4) test2_player_destroy(); 
  if (all || test == 5) test1_player_get_id();
  if (all || test == 6) test2_player_get_id();
  if (all || test == 7) test1_player_set_name();
  if (all || test == 8) test2_player_set_name();
  if (all || test == 9) test3_player_set_name();
  if (all || test == 10) test1_player_get_name();
  if (all || test == 11) test2_player_get_name(); 
  if (all || test == 12) test1_player_set_location();
  if (all || test == 13) test2_player_set_location(); 
  if (all || test == 14) test1_player_get_location();
  if (all || test == 15) test2_player_get_location(); 
  if (all || test == 16) test3_player_get_location(); 
  if (all || test == 17) test1_player_set_health(); 
  if (all || test == 18) test2_player_set_health();
  if (all || test == 19) test1_player_get_health();
  if (all || test == 20) test2_player_get_health(); 
  if (all || test == 21) test1_player_print();
  if (all || test == 22) test2_player_print(); 
  if (all || test == 23) test1_player_add_object_to_inventory();
  if (all || test == 24) test2_player_add_object_to_inventory();
  if (all || test == 25) test3_player_add_object_to_inventory();
  if (all || test == 26) test1_player_del_object_from_inventory(); 
  if (all || test == 27) test2_player_del_object_from_inventory();
  if (all || test == 28) test1_player_get_objects();
  if (all || test == 29) test2_player_get_objects();
  if (all || test == 30) test1_player_inventory_stores();
  if (all || test == 31) test2_player_inventory_stores();
  if (all || test == 32) test1_player_get_n_objects();
  if (all || test == 33) test2_player_get_n_objects(); 
  if (all || test == 34) test1_player_get_inventory();
  if (all || test == 35) test2_player_get_inventory(); 
  

  PRINT_PASSED_PERCENTAGE;

  return 1;
}

/** test1_player_create tests player creation
  */
void test1_player_create() {
  int result;
  Player *s;
  s = player_create(5);
  result=s!=NULL ;
  PRINT_TEST_RESULT(result);
  player_destroy(s);
}
/** test2_player_create tests player creation
  */
void test2_player_create() {
  Player *s;
  s = player_create(4);
  PRINT_TEST_RESULT(player_get_id(s) == 4);
  player_destroy(s);
}

/** test1_player_set_name tests player_name setting
  */
void test1_player_set_name() {
  Player *s;
  s = player_create(5);
  PRINT_TEST_RESULT(player_set_name(s, "hola") == OK);
  player_destroy(s);
}
/** test2_player_set_name tests player_name setting
  */
void test2_player_set_name() {
  Player *s = NULL;
  PRINT_TEST_RESULT(player_set_name(s, "hola") == ERROR);
}
/** test3_player_set_name tests player_name setting
  */
void test3_player_set_name() {
  Player *s;
  s = player_create(5);
  PRINT_TEST_RESULT(player_set_name(s, NULL) == ERROR);
  player_destroy(s);
}

/** test1_player_get_name tests getting player name
  */
void test1_player_get_name() {
  Player *s;
  s = player_create(1);
  player_set_name(s, "adios");
  PRINT_TEST_RESULT(strcmp(player_get_name(s), "adios") == 0);
  player_destroy(s);
}
/** test2_player_get_name tests getting player name
  */
void test2_player_get_name() {
  Player *s = NULL;
  PRINT_TEST_RESULT(player_get_name(s) == NULL);
}

/** test1_player_get_location tests getting 
  * player location
  */
void test1_player_get_location() {
  Player *s;
  s = player_create(1);
  PRINT_TEST_RESULT(player_get_location(s) == NO_ID);
  player_destroy(s);
}
/** test2_player_get_location tests getting 
  * player location
  */
void test2_player_get_location() {
  Player *s;
  s = player_create(1);
  player_set_location(s,122);
  PRINT_TEST_RESULT(player_get_location(s) == 122);
  player_destroy(s);    
}
/** test3_player_get_location tests getting 
  * player location
  */
void test3_player_get_location() {
  Player *s = NULL;
  PRINT_TEST_RESULT(player_get_location(s) == NO_ID);
}

/** test1_player_get_id tests getting 
  * player id
  */
void test1_player_get_id() {
  Player *s;
  s = player_create(25);
  PRINT_TEST_RESULT(player_get_id(s) == 25);
  player_destroy(s);
}
/** test2_player_get_id tests getting 
  * player id
  */
void test2_player_get_id() {
  Player *s = NULL;
  PRINT_TEST_RESULT(player_get_id(s) == NO_ID);
}

/** test1_player_set_location tests 
  * setting player location
  */
void test1_player_set_location(){
	Player *s;
	s = player_create(25);
	PRINT_TEST_RESULT(player_set_location(s,11)==OK);
	player_destroy(s);

}
/** test2_player_set_location tests 
  * setting player location
  */
void test2_player_set_location(){
	Player *s = NULL;
	PRINT_TEST_RESULT(player_set_location(s,11)==ERROR);
}

/** test1_player_get_health tests 
  * getting player health 
  */
void test1_player_get_health(){
	Player *s;
	s = player_create(25);
	player_set_health(s,2);
	PRINT_TEST_RESULT(player_get_health(s)==2);
	player_destroy(s);
}
/** test2_player_get_health tests 
  * getting player health 
  */
void test2_player_get_health(){
	Player *s = NULL;
	PRINT_TEST_RESULT(player_get_health(s)==-1);
}

/** test1_player_print tests 
  * printing player information
  */
void test1_player_print()
{
	Player *s;
	s = player_create(25);
	PRINT_TEST_RESULT(player_print(s)==OK);
	player_destroy(s);
}
/** test1_player_print tests 
  * printing player information
  */
void test2_player_print()
{
	Player *s = NULL;
	PRINT_TEST_RESULT(player_print(s)==ERROR);
}

/** test1_player_destroy tests destroying player
  */
void test1_player_destroy(){
	Player *s;
	s = player_create(25);
	PRINT_TEST_RESULT(player_destroy(s)==OK);
}
/** test2_player_destroy tests destroying player
  */
void test2_player_destroy(){
	Player *s=NULL;
	
	PRINT_TEST_RESULT(player_destroy(s)==ERROR);
}

/** test1_player_set_health tests 
  * setting player health
  */
void test1_player_set_health(){
	Player *s;
	s = player_create(25);
	PRINT_TEST_RESULT(player_set_health(s,1)==OK);
	player_destroy(s);
}
/** test2_player_set_health tests 
  * setting player health
  */
void test2_player_set_health(){
	Player *s;
	s = player_create(25);
	PRINT_TEST_RESULT(player_set_health(s,0)==OK);
	player_destroy(s);
}
/** test3_player_set_health tests 
  * setting player health
  */
void test3_player_get_health(){
	Player *s=NULL;
	PRINT_TEST_RESULT(player_get_health(s)==-1);
}

/** test1_player_add_object_to_inventory
  * tests adding objects to inventory
  */
void test1_player_add_object_to_inventory(){
  Player *s;
  s = player_create(25);
  PRINT_TEST_RESULT(player_add_object_to_inventory(s, 1) == OK);
  player_destroy(s);
}
/** test2_player_add_object_to_inventory
  * tests adding objects to inventory
  */
void test2_player_add_object_to_inventory(){
  Player *s = NULL;
  PRINT_TEST_RESULT(player_add_object_to_inventory(s, 1) == ERROR);
  player_destroy(s);
}
/** test3_player_add_object_to_inventory
  * tests adding objects to inventory
  */
void test3_player_add_object_to_inventory(){
  Player *s;
  s = player_create(25);
  PRINT_TEST_RESULT(player_add_object_to_inventory(s, NO_ID) == ERROR);
  player_destroy(s);
}

/** test1_player_del_object_from_inventory 
  * tests deleting objects from inventory
  */
void test1_player_del_object_from_inventory(){
  Player *s;
  s = player_create(25);
  inventory_set_max_objs(player_get_inventory(s), 2);
  player_add_object_to_inventory(s, 1);
  PRINT_TEST_RESULT(player_del_object_from_inventory(s, 1) == OK);
  player_destroy(s);
}
/** test2_player_del_object_from_inventory 
  * tests deleting objects from inventory
  */
void test2_player_del_object_from_inventory(){
  Player *s;
  s = player_create(25);
  PRINT_TEST_RESULT(player_del_object_from_inventory(s, 1) == ERROR);
  player_destroy(s);
}

/** test1_player_get_objects tests
  * getting inventory array
  */
void test1_player_get_objects(){
  Player *s;
  s = player_create(25);
  inventory_set_max_objs(player_get_inventory(s), 2);
  player_add_object_to_inventory(s, 1);
  player_add_object_to_inventory(s, 2);
  PRINT_TEST_RESULT(player_get_objects(s)[0] == 1 && player_get_objects(s)[1] == 2);
  player_destroy(s);
}
/** test2_player_get_objects tests
  * getting inventory array
  */
void test2_player_get_objects(){
  Player *s = NULL;
  PRINT_TEST_RESULT(player_get_objects(s) == NULL);
}

/** test1_player_inventory_stores
  * tests checking inventory for an id
  */
void test1_player_inventory_stores(){
  Player *s;
  s = player_create(25);
  inventory_set_max_objs(player_get_inventory(s), 2);
  player_add_object_to_inventory(s, 1);
  PRINT_TEST_RESULT(player_inventory_stores(s, 1) == TRUE);
  player_destroy(s);
}
/** test2_player_inventory_stores
  * tests checking inventory for an id
  */
void test2_player_inventory_stores(){
  Player *s;
  s = player_create(25);
  PRINT_TEST_RESULT(player_inventory_stores(s, 1) == FALSE);
  player_destroy(s);
}

/** test1_player_get_n_objects
  * tests getting number of objects in inventory
  */
void test1_player_get_n_objects(){
  Player *s;
  s = player_create(25);
  inventory_set_max_objs(player_get_inventory(s), 2);
  player_add_object_to_inventory(s, 1);
  PRINT_TEST_RESULT(player_get_n_objects(s) == 1);
  player_destroy(s);
}
/** test2_player_get_n_objects
  * tests getting number of objects in inventory
  */
void test2_player_get_n_objects(){
  Player *s;
  s = player_create(25);
  PRINT_TEST_RESULT(player_get_n_objects(s) == 0);
  player_destroy(s);
}

/** test1_player_get_inventory tests
  * getting inventory
  */
void test1_player_get_inventory(){
  Player *s;
  s = player_create(1);
  inventory_set_max_objs(player_get_inventory(s), 2);
  player_add_object_to_inventory(s, 33);
  PRINT_TEST_RESULT(inventory_stores_object(player_get_inventory(s), 33) == TRUE && inventory_get_n_objects(player_get_inventory(s)) == 1);
  player_destroy(s);
}
/** test2_player_get_inventory tests
  * getting inventory
  */
void test2_player_get_inventory(){
  Player *s = NULL;
  PRINT_TEST_RESULT(player_get_inventory(s) == NULL);
  player_destroy(s);
}
