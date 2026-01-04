/** 
 * @brief It tests object module
 * 
 * @file object_test.c
 * @author Sergio Saúco
 * @version 1.0
 * @date 10-04-2023
 * @copyright GNU Public License
 */

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "object.h"
#include "object_test.h"
#include "test.h"

#define MAX_TESTS 43 /*!< The maximum number of tests */

/** 
 * @brief Main function for OBJECT unit tests. 
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
    printf("Running all test for module Object:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 && test > MAX_TESTS) {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
    }
  }


  if (all || test == 1) test1_object_create();
  if (all || test == 2) test2_object_create();
  if (all || test == 3) test3_object_create();
  if (all || test == 4) test1_object_destroy();
  if (all || test == 5) test2_object_destroy();
  if (all || test == 6) test1_object_get_id();
  if (all || test == 7) test2_object_get_id();
  if (all || test == 8) test1_object_set_name();
  if (all || test == 9) test2_object_set_name();
  if (all || test == 10) test3_object_set_name();
  if (all || test == 11) test1_object_get_name();
  if (all || test == 12) test2_object_get_name();
  if (all || test == 13) test1_object_set_description();
  if (all || test == 14) test2_object_set_description();
  if (all || test == 15) test3_object_set_description();
  if (all || test == 16) test1_object_get_description();
  if (all || test == 17) test2_object_get_description();
  if (all || test == 18) test1_object_print();
  if (all || test == 19) test2_object_print();
  if (all || test == 20) test1_object_set_open();
  if (all || test == 21) test2_object_set_open();
  if (all || test == 22) test1_object_get_open();
  if (all || test == 23) test2_object_get_open();
  if (all || test == 24) test1_object_set_dependency();
  if (all || test == 25) test2_object_set_dependency();
  if (all || test == 26) test1_object_get_dependency();
  if (all || test == 27) test2_object_get_dependency();
  if (all || test == 28) test1_object_set_movable();
  if (all || test == 29) test2_object_set_movable();
  if (all || test == 30) test1_object_get_movable();
  if (all || test == 31) test2_object_get_movable();
  if (all || test == 32) test1_object_set_hidden();
  if (all || test == 33) test2_object_set_hidden();
  if (all || test == 34) test1_object_get_hidden();
  if (all || test == 35) test2_object_get_hidden();
  if (all || test == 36) test1_object_set_turnedon();
  if (all || test == 37) test2_object_set_turnedon();
  if (all || test == 38) test1_object_get_turnedon();
  if (all || test == 39) test2_object_get_turnedon();
  if (all || test == 40) test1_object_set_illuminate();
  if (all || test == 41) test2_object_set_illuminate();
  if (all || test == 42) test1_object_get_illuminate();
  if (all || test == 43) test2_object_get_illuminate();


  PRINT_PASSED_PERCENTAGE;

  return 1; 
}

/** tet1_object_create tests object creation
  */
void test1_object_create() {
  int result;
  Object *o;
  o = object_create(12);
  result=o!=NULL ;
  PRINT_TEST_RESULT(result);
  object_destroy(o);
}
/** tet2_object_create tests object creation
  */
void test2_object_create() {
  Object *o;
  o = object_create(12);
  PRINT_TEST_RESULT(object_get_id(o) == 12);
  object_destroy(o);
}
/** tet3_object_create tests object creation
  */
void test3_object_create() {
  Object *o;
  o = object_create(NO_ID);
  PRINT_TEST_RESULT(o == NULL);
  object_destroy(o);
}

/** test1_object_destroy tests object destruction 
  */
void test1_object_destroy() {
    Object *o;
    o = object_create(12);
    PRINT_TEST_RESULT(object_destroy(o) == OK);
}
/** test2_object_destroy tests object destruction 
  */
void test2_object_destroy() {
    Object *o = NULL;
    PRINT_TEST_RESULT(object_destroy(o) == ERROR);
}

/** test1_object_get_id tests object_id getting
  */
void test1_object_get_id() {
    Object *o;
    Id id;
    o = object_create(12);
    id = object_get_id(o);
    PRINT_TEST_RESULT(id == 12);
    object_destroy(o);
}
/** test2_object_get_id tests object_id getting
  */
void test2_object_get_id() {
    Object *o = NULL;
    Id id;
    id = object_get_id(o);
    PRINT_TEST_RESULT(id == NO_ID);
}

/** test1_object_set_name tests object_name setting
  */
void test1_object_set_name() {
    Object *o;
    o = object_create(12);
    PRINT_TEST_RESULT(object_set_name(o, "hola") == OK);
    object_destroy(o);
}
/** test2_object_set_name tests object_name setting
  */
void test2_object_set_name() {
    Object *o = NULL;
    PRINT_TEST_RESULT(object_set_name(o, "hola") == ERROR);
}
/** test3_object_set_name tests object_name setting
  */
void test3_object_set_name() {
    Object *o;
    o = object_create(12);
    PRINT_TEST_RESULT(object_set_name(o, NULL) == ERROR);
    object_destroy(o);
}

/** test1_object_get_name tests object_name getting
  */
void test1_object_get_name() {
    Object *o;
    o = object_create(12);
    object_set_name(o, "hola");
    PRINT_TEST_RESULT(strcmp(object_get_name(o), "hola") == 0);
    object_destroy(o);
}
/** test2_object_get_name tests object_name getting
  */
void test2_object_get_name() {
    Object *o = NULL;
    PRINT_TEST_RESULT(object_get_name(o) == NULL);
}

/** test1_object_set_description tests object_description setting
  */
void test1_object_set_description() {
    Object *o;
    o = object_create(12);
    PRINT_TEST_RESULT(object_set_description(o, "hola") == OK);
    object_destroy(o);
}
/** test2_object_set_description tests object_description setting
  */
void test2_object_set_description() {
    Object *o = NULL;
    PRINT_TEST_RESULT(object_set_description(o, "hola") == ERROR);
}
/** test3_object_set_description tests object_description setting
  */
void test3_object_set_description() {
    Object *o;
    o = object_create(12);
    PRINT_TEST_RESULT(object_set_description(o, NULL) == ERROR);
    object_destroy(o);
}

/** test1_object_get_description tests object_description getting
  */
void test1_object_get_description() {
    Object *o;
    o = object_create(12);
    object_set_description(o, "hola");
    PRINT_TEST_RESULT(strcmp(object_get_description(o), "hola") == 0);
    object_destroy(o);
}
/** test2_object_get_description tests object_description getting
  */
void test2_object_get_description() {
    Object *o = NULL;
    PRINT_TEST_RESULT(object_get_description(o) == NULL);
}

/** test1_object_print tests object printing
  */
void test1_object_print() {
    Object *o;
    o = object_create(12);
    PRINT_TEST_RESULT(object_print(o) == OK);
    object_destroy(o);
}
/** test2_object_print tests object printing
  */
void test2_object_print() {
    Object *o = NULL;
    PRINT_TEST_RESULT(object_print(o) == ERROR);
}

/** test1_object_set_open tests open status setting
*/
void test1_object_set_open(){
  Object *o = NULL;
  PRINT_TEST_RESULT(object_set_open(o, 34) == ERROR);
}

/** test2_object_set_open tests open status setting
*/
void test2_object_set_open(){
  Object *o = object_create(1);
  PRINT_TEST_RESULT(object_set_open(o, 34) == OK);
  object_destroy(o);
}

/** test1_object_get_open tests open status getting
*/
void test1_object_get_open(){
  Object *o = NULL;
  PRINT_TEST_RESULT(object_get_open(o) == NO_ID);
}

/** test2_object_get_open tests open status getting
*/
void test2_object_get_open(){
  Object *o = object_create(1);
  object_set_open(o, 34);
  PRINT_TEST_RESULT(object_get_open(o) == 34);
  object_destroy(o);
}

/** test1_object_set_dependency tests dependency setting
*/
void test1_object_set_dependency(){
  Object *o = NULL;
  PRINT_TEST_RESULT(object_set_dependency(o, 34) == ERROR);
}

/** test2_object_set_dependency tests dependency setting
*/
void test2_object_set_dependency(){
  Object *o = object_create(1);
  PRINT_TEST_RESULT(object_set_dependency(o, 34) == OK);
  object_destroy(o);
}

/** test1_object_get_dependency tests dependency getting
*/
void test1_object_get_dependency(){
  Object *o = NULL;
  PRINT_TEST_RESULT(object_get_dependency(o) == NO_ID);
}

/** test2_object_get_dependency tests dependency getting
*/
void test2_object_get_dependency(){
  Object *o = object_create(1);
  object_set_dependency(o, 34);
  PRINT_TEST_RESULT(object_get_dependency(o) == 34);
  object_destroy(o);
}

/** test1_object_set_movable tests movility status setting
*/
void test1_object_set_movable(){
  Object *o = NULL;
  PRINT_TEST_RESULT(object_set_movable(o, TRUE) == ERROR);
}

/** test2_object_set_movable tests movility status setting
*/
void test2_object_set_movable(){
  Object *o = object_create(1);
  PRINT_TEST_RESULT(object_set_movable(o, TRUE) == OK);
  object_destroy(o);
}

/** test1_object_get_movable tests movility status getting
*/
void test1_object_get_movable(){
  Object *o = NULL;
  PRINT_TEST_RESULT(object_get_movable(o) == FALSE);
}

/** test2_object_get_movable tests movility status getting
*/
void test2_object_get_movable(){
  Object *o = object_create(1);
  object_set_movable(o, TRUE);
  PRINT_TEST_RESULT(object_get_movable(o) == TRUE);
  object_destroy(o);
}

/** test1_object_set_hidden tests hidden status setting
*/
void test1_object_set_hidden(){
  Object *o = NULL;
  PRINT_TEST_RESULT(object_set_hidden(o, TRUE) == ERROR);
}

/** test2_object_set_hidden tests hidden status setting
*/
void test2_object_set_hidden(){
  Object *o = object_create(1);
  PRINT_TEST_RESULT(object_set_hidden(o, TRUE) == OK);
  object_destroy(o);
}

/** test1_object_get_hidden tests hidden status getting
*/
void test1_object_get_hidden(){
  Object *o = NULL;
  PRINT_TEST_RESULT(object_get_hidden(o) == TRUE);
}

/** test2_object_get_hidden tests hidden status getting
*/
void test2_object_get_hidden(){
  Object *o = object_create(1);
  object_set_hidden(o, FALSE);
  PRINT_TEST_RESULT(object_get_hidden(o) == FALSE);
  object_destroy(o);
}

/** test1_object_set_turnedon tests turnedon status setting
*/
void test1_object_set_turnedon(){
  Object *o = NULL;
  PRINT_TEST_RESULT(object_set_turnedon(o, TRUE) == ERROR);
}

/** test2_object_set_turnedon tests turnedon status setting
*/
void test2_object_set_turnedon(){
  Object *o = object_create(1);
  PRINT_TEST_RESULT(object_set_turnedon(o, TRUE) == OK);
  object_destroy(o);
}

/** test1_object_get_turnedon tests turnedon status getting
*/
void test1_object_get_turnedon(){
  Object *o = NULL;
  PRINT_TEST_RESULT(object_get_turnedon(o) == FALSE);
}

/** test2_object_get_turnedon tests turnedon status getting
*/
void test2_object_get_turnedon(){
  Object *o = object_create(1);
  object_set_turnedon(o, TRUE);
  PRINT_TEST_RESULT(object_get_turnedon(o) == TRUE);
  object_destroy(o);
}

/** test1_object_set_illuminate tests illumination status setting
*/
void test1_object_set_illuminate(){
  Object *o = NULL;
  PRINT_TEST_RESULT(object_set_illuminate(o, TRUE) == ERROR);
}

/** test2_object_set_illuminate tests illumination status setting
*/
void test2_object_set_illuminate(){
  Object *o = object_create(1);
  PRINT_TEST_RESULT(object_set_illuminate(o, TRUE) == OK);
  object_destroy(o);
}

/** test1_object_get_illuminate tests illumination status getting
*/
void test1_object_get_illuminate(){
  Object *o = NULL;
  PRINT_TEST_RESULT(object_get_illuminate(o) == FALSE);
}

/** test2_object_get_illuminate tests illumination status getting
*/
void test2_object_get_illuminate(){
  Object *o = object_create(1);
  object_set_illuminate(o, TRUE);
  PRINT_TEST_RESULT(object_get_illuminate(o) == TRUE);
  object_destroy(o);
}

