/** 
 * @brief It declares the tests for the space module
 * 
 * @file space_test.h
 * @author Profesores Pprog and Sergio Saúco
 * @version 2.1 
 * @date 07-03-2023
 * @copyright GNU Public License
 */

#ifndef SPACE_TEST_H
#define SPACE_TEST_H

/**
 * @test Test space creation
 * @pre  Space ID 
 * @post Non NULL pointer to space 
 */
void test1_space_create();

/**
 * @test Test space creation
 * @pre  Space ID 
 * @post Space_ID == Supplied Space Id
 */
void test2_space_create();

/**
 * @test Test function for space_name setting
 * @pre  String with space name
 * @post Ouput==OK 
 */
void test1_space_set_name();

/**
 * @test Test function for space_name setting
 * @pre  pointer to space = NULL 
 * @post Output==ERROR
 */
void test2_space_set_name();

/**
 * @test Test function for space_name setting
 * @pre  pointer to space_name = NULL (point to space = NON NULL) 
 * @post Output==ERROR
 */
void test3_space_set_name();

/**
 * @test Test function for space_object setting
 * @pre  Object ID
 * @post Output==OK
 */
void test1_space_set_object();

/**
 * @test Test function for space_object setting
 * @pre  pointer to space = NULL
 * @post Output==ERROR
 */
void test2_space_set_object();

/**
 * @test Test function for space_name getting
 * @pre  String with space name set
 * @post strcmp==0 (comparision between the
 * string that has been set and the space_name)
 */
void test1_space_get_name();

/**
 * @test Test function for space_name getting
 * @pre  pointer to space = NULL 
 * @post space_name==NULL
 */
void test2_space_get_name();

/**
 * @test Test function for space_objects getting
 * @pre  Object set id's = NO_ID and flag = 0
 * @post flag==1 (the id's in the set are NO_ID)
 */
void test1_space_get_object();

/**
 * @test Test function for space_objects getting
 * @pre  Object ID set in the space and flag = 0
 * @post flag==1 (set object found in the space)
 */
void test2_space_get_object();

/**
 * @test Test function for space_objects getting
 * @pre  pointer to space = NULL 
 * @post Objects==NULL
 */
void test3_space_get_object();

/**
 * @test Test function for space_id getting
 * @pre  Space ID 
 * @post space_id==Supplied id
 */
void test1_space_get_id();

/**
 * @test Test function for space_id getting
 * @pre  pointer to space = NULL
 * @post space_id==NO_ID
 */
void test2_space_get_id();

/**
 * @test Test function for searching an object in the space
 * @pre  Object ID 
 * @post Output==TRUE
 */
void test1_space_search_object();

/**
 * @test Test function for searching an object in the space
 * @pre  pointer to space = NULL
 * @post Output==FALSE
 */
void test2_space_search_object();

/**
 * @test Test function for searching an object in the space
 * @pre  Object NO_ID
 * @post Output==FALSE
 */
void test3_space_search_object();

/**
 * @test Test function for searching an object in the space
 * @pre  pointer to space = NULL and object NO_ID
 * @post Output==FALSE
 */
void test4_space_search_object();

/**
 * @test Test function for searching an object in the space
 * @pre  Object ID (but that ID not set in the space)
 * @post Output==FALSE
 */
void test5_space_search_object();

/**
 * @test Test function for searching an object in the space
 * @pre  Two objects ID's (one set in the space and another not,
 * the one that is not set is searched)
 * @post Output==FALSE
 */
void test6_space_search_object();

/**
 * @test Test function for setting gdesc to a space
 * @pre  Set gdesc with proper params
 * @post Output==OK
 */
void test1_space_set_gdesc();

/**
 * @test Test function for for setting gdesc to a space
 * @pre  Set gdesc to a null space
 * @post Output==ERROR
 */
void test2_space_set_gdesc();

/**
 * @test Test function for getting a gdesc row from a space
 * @pre  Get gdesc with proper params
 * @post Output==OK
 */
void test1_space_get_gdesc_row();

/**
 * @test Test function for getting gdesc from a space
 * @pre  Get gdesc from a null space
 * @post Output==NULL
 */
void test2_space_get_gdesc_row();

/**
 * @test Test function for unsetting an object from the space
 * @pre  Set object with id 4 in the space
 * @post Output==OK
 */
void test1_space_unset_object();
/**
 * @test Test function for unsetting an object from the space
 * @pre  pointer to space = NULL
 * @post Output==ERROR
 */
void test2_space_unset_object();
/**
 * @test Test function for unsetting an object from the space
 * @pre  Object_ID = NO_ID
 * @post Output==ERROR
 */
void test3_space_unset_object();

/**
 * @test Test function for space_description setting
 * @pre  String with space description
 * @post Ouput==OK 
 */
void test1_space_set_description();

/**
 * @test Test function for space_description setting
 * @pre  pointer to space = NULL 
 * @post Output==ERROR
 */
void test2_space_set_description();

/**
 * @test Test function for space_description setting
 * @pre  pointer to space_descrption = NULL (point to space = NON NULL) 
 * @post Output==ERROR
 */
void test3_space_set_description();

/**
 * @test Test function for space_description getting
 * @pre  String with space description set
 * @post strcmp==0 (comparision between the
 * string that has been set and the space_description)
 */
void test1_space_get_description();

/**
 * @test Test function for space_description getting
 * @pre  pointer to space = NULL 
 * @post space_description==NULL
 */
void test2_space_get_description();

/**
 * @test Test function for space_detailed_desc setting
 * @pre  String with space detailed description
 * @post Ouput==OK 
 */
void test1_space_set_detailed_desc();

/**
 * @test Test function for space_detailed_desc setting
 * @pre  pointer to space = NULL 
 * @post Output==ERROR
 */
void test2_space_set_detailed_desc();

/**
 * @test Test function for space_detailed_desc setting
 * @pre  pointer to space_descrption = NULL (point to space = NON NULL) 
 * @post Output==ERROR
 */
void test3_space_set_detailed_desc();

/**
 * @test Test function for space_detailed_desc getting
 * @pre  String with space detailed description set
 * @post strcmp==0 (comparision between the
 * string that has been set and the space_detailed_desc)
 */
void test1_space_get_detailed_desc();

/**
 * @test Test function for space_detailed_desc getting
 * @pre  pointer to space = NULL 
 * @post space_detailed_desc==NULL
 */
void test2_space_get_detailed_desc();

/**
 * @test Test function for space_light setting
 * @pre  space_light = FALSE
 * @post Output==OK
 */
void test1_space_set_light();

/**
 * @test Test function for space_light setting
 * @pre  pointer to space = NULL 
 * @post Output==ERROR
 */
void test2_space_set_light();

/**
 * @test Test function for space_light getting
 * @pre  space_light = TRUE
 * @post space_light==TRUE
 */
void test1_space_get_light();

/**
 * @test Test function for space_light getting
 * @pre  pointer to space = NULL 
 * @post Output==FALSE
 */
void test2_space_get_light();


#endif
