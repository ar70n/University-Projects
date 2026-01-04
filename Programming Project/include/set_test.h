/** 
 * @brief It declares the tests for the set module
 * 
 * @file set_test.h
 * @author Sergio Saúco
 * @version 1.0 
 * @date 07-03-2023
 * @copyright GNU Public License
 */

#ifndef SET_TEST_H
#define SET_TEST_H

/**
 * @test Test set creation 
 * @pre Set created is not null
 * @post Non NULL pointer to set 
 */
void test1_set_create();

/**
 * @test Test set creation initialization
 * @pre  0 id's in the set (set initialized)
 * @post Number of id's in the set == 0
 */
void test2_set_create();

/** 
  * @test  Test set destruction with a valid set
  * @pre   Set creation
  * @post  Output==OK
  */
void test1_set_destroy();

/**
  * @test  Test set destruction with a null set
  * @pre   Pointer to set = NULL
  * @post  Output==ERROR 
  */
void test2_set_destroy();

/**
  * @test Test adding an id to a valid set
  * @pre  Id 4 added to the set
  * @post Output==OK
  */
void test1_set_add();

/**
  * @test Test adding an id to a null set
  * @pre  Pointer to set = NULL
  * @post Output==ERROR
  */
void test2_set_add();

/** 
  * @test Test deleting an id from a valid set with elements
  * @pre  Id 4 added and deleted of the set
  * @post Output==OK
  */
void test1_set_del();

/**
  * @test Test deleting an id from an empty set
  * @pre  Id 4 deleted of the set
  * @post Output==ERROR
  */
void test2_set_del();

/**
  * @test Test deleting an id from a null set
  * @pre  Pointer to set = NULL
  * @post Output==ERROR
  */
void test3_set_del();

/**
  * @test Test getting the number of id's from a valid set
  * @pre  Number of id's in the set = 4
  * @post Number of id's in the set == Supplied number of id's in the set
  */
void test1_set_get_n_ids();

/**
  * @test Test getting the number of id's from a null set
  * @pre  Pointer to set = NULL
  * @post Number of id's in the set == -1
  */
void test2_set_get_n_ids();

/**
  * @test Test getting the id's in a valid set
  * @pre  Adding id 4 to the set (and flag = 0)
  * @post flag == 1 (found id 4 in the array with the id's)
  */
void test1_set_get_ids();

/**
  * @test Test getting the id's in an invalid set (null)
  * @pre  Pointer to set = NULL 
  * @post Array with the id's == NULL
  */
void test2_set_get_ids();

/**
  * @test Test printing the set information from a valid set
  * @pre  Set created (initialized)
  * @post Output==OK 
  */
void test1_set_print();

/**
  * @test Test printing the set information from a null set
  * @pre  Pointer to set = NULL
  * @post Output==ERROR
  */
void test2_set_print();


#endif
