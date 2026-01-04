/** 
 * @brief It declares the tests for the link module
 * 
 * @file link_test.h
 * @author Miguel Campo
 * @version 1.0
 * @date 24-03-2023
 * @copyright GNU Public License
 */

#ifndef LINK_TEST_H
#define LINK_TEST_H

/**
 * @test Test link creation
 * @pre  Link ID 
 * @post Non NULL pointer to link
 */
void test1_link_create();

/**
 * @test Test link creation
 * @pre  Link ID 
 * @post Link_id == supplied id
 */
void test2_link_create();

/**
 * @test Test link_name setting
 * @pre  String with link name
 * @post STATUS == OK
 */
void test1_link_set_name();

/**
 * @test Test link_name setting
 * @pre  Pointer to link == NULL
 * @post STATUS == ERROR
 */
void test2_link_set_name();

/**
 * @test Test link_name setting
 * @pre  Name string == NULL
 * @post STATUS == ERROR;
 */
void test3_link_set_name();

/**
 * @test Test function for link_name getting
 * @pre  String with link name set
 * @post strcmp==0 (comparision between the
 * string that has been set and the link_name)
 */
void test1_link_get_name();

/**
 * @test Test function for link_name getting
 * @pre  Link pointer == NULL
 * @post link_name == NULL
 */
void test2_link_get_name();

/**
 * @test Test function for link_id getting
 * @pre  Id to be set
 * @post set_id == link_id
 */
void test1_link_get_id();

/**
 * @test Test function for link_id getting
 * @pre  Link pointer == NULL
 * @post link_id == NO_ID
 */
void test2_link_get_id();

/**
 * @test Test function for link_id destroying
 * @pre  Link pointer
 * @post STATUS == OK 
 */
void test1_link_destroy();

/**
 * @test Test function for link_id destroying
 * @pre  Link pointer == NULL
 * @post STATUS == ERROR
 */
void test2_link_destroy();

/**
 * @test Test function for link_origin getting
 * @pre  Link pointer, id to be set as origin
 * @post link_origin == id
 */
void test1_link_get_origin();

/**
 * @test Test function for link_origin getting
 * @pre  NULL link
 * @post Output = NO_ID
 */
void test2_link_get_origin();

/**
 * @test Test function for link_origin setting
 * @pre  Valid link
 * @post Output == OK
 */
void test1_link_set_origin();

/**
 * @test Test function for link_origin setting
 * @pre  Null link
 * @post Output == ERROR
 */
void test2_link_set_origin();

/**
 * @test Test function for link_destination getting
 * @pre  Link pointer, id to be set as destination
 * @post link_destination == id
 */
void test1_link_get_destination();

/**
 * @test Test function for link_destination getting
 * @pre  NULL link
 * @post Output = NO_ID
 */
void test2_link_get_destination();

/**
 * @test Test function for link_destination setting
 * @pre  Valid link
 * @post Output == OK
 */
void test1_link_set_destination();

/**
 * @test Test function for link_destination setting
 * @pre  Null link
 * @post Output == ERROR
 */
void test2_link_set_destination();

/**
 * @test Test function for link_direction getting
 * @pre  Link pointer, direction to be set
 * @post link_direction == given direction
 */
void test1_link_get_direction();

/**
 * @test Test function for link_direction getting
 * @pre  NULL link
 * @post Output = U
 */
void test2_link_get_direction();

/**
 * @test Test function for link_direction setting
 * @pre  Valid link and direction
 * @post Output == OK
 */
void test1_link_set_direction();

/**
 * @test Test function for link_direction setting
 * @pre  Null link
 * @post Output == ERROR
 */
void test2_link_set_direction();

/**
 * @test Test function for link_status getting
 * @pre  Link pointer, status to be set
 * @post link_status == given status
 */
void test1_link_get_status();

/**
 * @test Test function for link_status getting
 * @pre  NULL link
 * @post Output = NO_ID
 */
void test2_link_get_status();

/**
 * @test Test function for link_status setting
 * @pre  Valid link and status
 * @post Output == OK
 */
void test1_link_set_status();

/**
 * @test Test function for link_status setting
 * @pre  Null link
 * @post Output == ERROR
 */
void test2_link_set_status();

/**
  * @test Test function for printing link information
  * 
  * @pre Print information from link
  * @post prints information correctly, STATUS==OK
  */
void test1_link_print();

/**
  * @test Test function for printing link information
  * 
  * @pre Print information from null link
  * @post STATUS==ERROR
  */
void test2_link_print();


#endif
