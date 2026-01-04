/** 
 * @brief It tests space module
 * 
 * @file space_test.c
 * @author Profesores Pprog and Sergio Saúco and Antonio Moroño
 * @version 3.1 
 * @date 07-03-2023
 * @copyright GNU Public License
 */

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "space.h"
#include "space_test.h"
#include "test.h"

#define MAX_TESTS 39 /*!< The maximum number of tests */

/** 
 * @brief Main function for SPACE unit tests. 
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
    printf("Running all test for module Space:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 && test > MAX_TESTS) {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
    }
  }


  if (all || test == 1) test1_space_create();
  if (all || test == 2) test2_space_create();
  if (all || test == 3) test1_space_set_name();
  if (all || test == 4) test2_space_set_name();
  if (all || test == 5) test3_space_set_name();
  if (all || test == 6) test1_space_get_name();
  if (all || test == 7) test2_space_get_name();
  if (all || test == 8) test1_space_get_object();
  if (all || test == 9) test2_space_get_object();
  if (all || test == 10) test3_space_get_object();
  if (all || test == 11) test1_space_get_id();
  if (all || test == 12) test2_space_get_id();
  if (all || test == 13) test1_space_search_object();
  if (all || test == 14) test2_space_search_object();
  if (all || test == 15) test3_space_search_object();
  if (all || test == 16) test4_space_search_object();
  if (all || test == 17) test5_space_search_object();
  if (all || test == 18) test6_space_search_object();
  if (all || test == 19) test1_space_set_gdesc();
  if (all || test == 20) test2_space_set_gdesc();
  if (all || test == 21) test1_space_get_gdesc_row();
  if (all || test == 22) test2_space_get_gdesc_row();
  if (all || test == 23) test1_space_unset_object();
  if (all || test == 24) test2_space_unset_object();
  if (all || test == 25) test3_space_unset_object();
  if (all || test == 26) test1_space_set_description();
  if (all || test == 27) test2_space_set_description();
  if (all || test == 28) test3_space_set_description();
  if (all || test == 29) test1_space_get_description();
  if (all || test == 30) test2_space_get_description();
  if (all || test == 31) test1_space_set_detailed_desc();
  if (all || test == 32) test2_space_set_detailed_desc();
  if (all || test == 33) test3_space_set_detailed_desc();
  if (all || test == 34) test1_space_get_detailed_desc();
  if (all || test == 36) test1_space_set_light();
  if (all || test == 37) test2_space_set_light();
  if (all || test == 38) test1_space_get_light();
  if (all || test == 39) test2_space_get_light();


  PRINT_PASSED_PERCENTAGE;

  return 1;
}

/** tet1_space_create tests space creation
  */
void test1_space_create() {
  int result;
  Space *s;
  s = space_create(5);
  result=s!=NULL ;
  PRINT_TEST_RESULT(result);
  space_destroy(s);
}

/** tet2_space_create tests space creation
  */
void test2_space_create() {
  Space *s;
  s = space_create(4);
  PRINT_TEST_RESULT(space_get_id(s) == 4);
  space_destroy(s);
}

/** test1_space_set_name test function for space_name setting
  */
void test1_space_set_name() {
  Space *s;
  s = space_create(5);
  PRINT_TEST_RESULT(space_set_name(s, "hola") == OK);
  space_destroy(s);
}

/** test2_space_set_name test function for space_name setting
  */
void test2_space_set_name() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_set_name(s, "hola") == ERROR);
}

/** test3_space_set_name test function for space_name setting
  */
void test3_space_set_name() {
  Space *s;
  s = space_create(5);
  PRINT_TEST_RESULT(space_set_name(s, NULL) == ERROR);
  space_destroy(s);
}

/** test1_space_set_object test function for space_object setting
  */
void test1_space_set_object() {
  Space *s;
  s = space_create(1);
  PRINT_TEST_RESULT(space_set_object(s, 4) == OK);
  space_destroy(s);
}

/** test2_space_set_object test function for space_object setting
  */
void test2_space_set_object() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_set_object(s, 4) == ERROR);
}

/** test1_space_get_name test function for space_name getting
  */
void test1_space_get_name() {
  Space *s;
  s = space_create(1);
  space_set_name(s, "adios");
  PRINT_TEST_RESULT(strcmp(space_get_name(s), "adios") == 0);
  space_destroy(s);
}

/** test2_space_get_name test function for space_name getting
  */
void test2_space_get_name() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_name(s) == NULL);
}

/** test1_space_get_object test function for space_objects getting
  */
void test1_space_get_object() {
  Space *s;
  Id *ids;
  int flag = 0;
  s = space_create(1);
  ids = space_get_objects(s);
  if (ids[0] == NO_ID) {
    flag = 1;
  }
  PRINT_TEST_RESULT(flag == 1);
  space_destroy(s);
}

/** test2_space_get_object test function for space_objects getting
  */
void test2_space_get_object() {
  Space *s;
  Id id[1] = {4}, *ids;
  int flag = 0;
  s = space_create(1);
  space_set_object(s, 4);
  ids = space_get_objects(s);
  if (id[0] == ids[0]) {
    flag = 1;
  }
  PRINT_TEST_RESULT(flag == 1);
  space_destroy(s);  
}

/** test3_space_get_object test function for space_objects getting
  */
void test3_space_get_object() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_objects(s) == NULL);
}

/** test1_space_get_id test function for space_id getting
  */
void test1_space_get_id() {
  Space *s;
  s = space_create(25);
  PRINT_TEST_RESULT(space_get_id(s) == 25);
  space_destroy(s);
}

/** test2_space_get_id test function for space_id getting
  */
void test2_space_get_id() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_id(s) == NO_ID);
}

/** test1_space_search_object test function for searching an object in the space
  */
void test1_space_search_object() {
  Space *s;
  s = space_create(5);
  space_set_object(s, 4);
  PRINT_TEST_RESULT(space_search_object(s, 4) == TRUE);
  space_destroy(s);
}

/** test2_space_search_object test function for searching an object in the space
  */
void test2_space_search_object() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_search_object(s, 4) == FALSE);
}

/** test3_space_search_object test function for searching an object in the space
  */
void test3_space_search_object() {
  Space *s;
  s = space_create(5);
  PRINT_TEST_RESULT(space_search_object(s, NO_ID) == FALSE);
  space_destroy(s);
}

/** test4_space_search_object test function for searching an object in the space
  */
void test4_space_search_object() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_search_object(s, NO_ID) == FALSE);
}

/** test5_space_search_object test function for searching an object in the space
  */
void test5_space_search_object() {
  Space *s;
  s = space_create(5);
  PRINT_TEST_RESULT(space_search_object(s, 4) == FALSE);
  space_destroy(s);
}

/** test6_space_search_object test function for searching an object in the space
  */
void test6_space_search_object() {
  Space *s;
  s = space_create(5);
  space_set_object(s,4);
  PRINT_TEST_RESULT(space_search_object(s, 6) == FALSE);
  space_destroy(s);
}

/** test1_space_set_gdesc tests that a valid gdesc is set correctly
  */
void test1_space_set_gdesc(){
	Space *s;
	char desc[LENGTH_GDESC][MAX_STR];
	int i, j;

	for (i = 0; i < LENGTH_GDESC; i++)
	{
		for (j = 0; j < MAX_STR; j++)
		{
			desc[i][j] = '$';
		}
		desc[i][j]='\0';
	}

	s = space_create(25);
	PRINT_TEST_RESULT(space_set_gdesc(s, desc)==OK);
  space_destroy(s);
}

/** test2_space_set_gdesc tests that a valid gdesc can not be set in a null space (= it throws an error)
  */
void test2_space_set_gdesc(){
	Space *s = NULL;
	char desc[LENGTH_GDESC][MAX_STR];
	int i, j;

	for (i = 0; i < LENGTH_GDESC; i++)
	{
		for (j = 0; j < MAX_STR; j++)
		{
			desc[i][j] = '$';
		}
	}
	PRINT_TEST_RESULT(space_set_gdesc(s, desc)==ERROR);
}

/** test1_space_get_gdesc_row tests that getting a gdesc row from a space with a valid gdesc returns something not null
  */
void test1_space_get_gdesc_row(){
	Space *s;
	char desc[LENGTH_GDESC][MAX_STR];
	int i,j;

	for(i = 0; i < LENGTH_GDESC; i++) {
		for(j = 0; j < MAX_STR; j++) {
			desc[i][j] = '$';
		}
		desc[i][j]='\0';
	}

	s = space_create(25);
	space_set_gdesc(s, desc);
	PRINT_TEST_RESULT(space_get_gdesc_row(s, 1) != NULL);
  space_destroy(s);
}

/** test2_space_get_gdesc_row tests that you can not get a row from a null space
  */
void test2_space_get_gdesc_row(){
	Space *s = NULL;
	PRINT_TEST_RESULT(space_get_gdesc_row(s, 1) == NULL);
}

/** test1_space_unset_object test function for unsetting an object from the space
  */
void test1_space_unset_object() {
  Space *s;
  
  s = space_create(25);
  space_set_object(s, 4);
  PRINT_TEST_RESULT(space_unset_object(s, 4) == OK);
  space_destroy(s);
}

/** test2_space_unset_object test function for unsetting an object from the space
  */
void test2_space_unset_object() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_unset_object(s, 4) == ERROR);
}

/** test3_space_unset_object test function for unsetting an object from the space
  */
void test3_space_unset_object() {
  Space *s;

  s = space_create(25);
  PRINT_TEST_RESULT(space_unset_object(s, NO_ID) == ERROR);
  space_destroy(s);
}

/** test1_space_set_description test function for space_description setting
  */
void test1_space_set_description() {
  Space *s;
  s = space_create(5);
  PRINT_TEST_RESULT(space_set_description(s, "hola") == OK);
  space_destroy(s);
}

/** test2_space_set_description test function for space_description setting
  */
void test2_space_set_description() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_set_description(s, "hola") == ERROR);
}

/** test3_space_set_description test function for space_description setting
  */
void test3_space_set_description() {
  Space *s;
  s = space_create(5);
  PRINT_TEST_RESULT(space_set_description(s, NULL) == ERROR);
  space_destroy(s);
}

/** test1_space_get_description test function for space_description getting
  */
void test1_space_get_description() {
  Space *s;
  s = space_create(1);
  space_set_description(s, "adios");
  PRINT_TEST_RESULT(strcmp(space_get_description(s), "adios") == 0);
  space_destroy(s);
}

/** test2_space_get_description test function for space_desription getting
  */
void test2_space_get_description() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_description(s) == NULL);
}

/** test1_space_set_detailed_desc test function for space_detailed_desc setting
  */
void test1_space_set_detailed_desc() {
  Space *s;
  s = space_create(5);
  PRINT_TEST_RESULT(space_set_detailed_desc(s, "hola") == OK);
  space_destroy(s);
}

/** test2_space_set_detailed_desc test function for space_detailed_desc setting
  */
void test2_space_set_detailed_desc() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_set_detailed_desc(s, "hola") == ERROR);
}

/** test3_space_set_detailed_desc test function for space_detailed_desc setting
  */
void test3_space_set_detailed_desc() {
  Space *s;
  s = space_create(5);
  PRINT_TEST_RESULT(space_set_detailed_desc(s, NULL) == ERROR);
  space_destroy(s);
}

/** test1_space_get_detailed_desc test function for space_detailed_desc getting
  */
void test1_space_get_detailed_desc() {
  Space *s;
  s = space_create(1);
  space_set_detailed_desc(s, "adios");
  PRINT_TEST_RESULT(strcmp(space_get_detailed_desc(s), "adios") == 0);
  space_destroy(s);
}

/** test2_space_get_detailed_desc test function for space_detailed_desc getting
  */
void test2_space_get_detailed_desc() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_detailed_desc(s) == NULL);
}

/** test1_space_set_light test function for space_light setting
  */
void test1_space_set_light() {
  Space *s;
  s = space_create(12);
  PRINT_TEST_RESULT(space_set_light(s, FALSE) == OK);
  space_destroy(s);
}

/** test2_space_set_light test function for space_light setting
  */
void test2_space_set_light() {
  PRINT_TEST_RESULT(space_set_light(NULL, FALSE) == ERROR);
}

/** test1_space_get_light test function for space_light getting
  */
void test1_space_get_light() {
  Space *s;
  s = space_create(12);
  space_set_light(s, TRUE);
  PRINT_TEST_RESULT(space_get_light(s) == TRUE);
  space_destroy(s);
}

/** test2_space_get_light test function for space_light getting
  */
void test2_space_get_light() {
  PRINT_TEST_RESULT(space_get_light(NULL) == FALSE);
}

