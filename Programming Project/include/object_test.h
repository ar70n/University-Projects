/** 
 * @brief It declares the tests for the object module
 * 
 * @file object_test.h
 * @author Sergio Saúco
 * @version 1.0 
 * @date 10-04-2023
 * @copyright GNU Public License
 */

#ifndef OBJECT_TEST_H
#define OBJECT_TEST_H

/**
  * @test Test object creation
  * @pre Object ID
  * @post Non NULL pointer to object
  */
void test1_object_create();

/**
  * @test Test object creation
  * @pre Object ID
  * @post The object id
  */
void test2_object_create();

/**
  * @test Test object creation 
  * @pre NO_ID
  * @post NULL pointer
  */
void test3_object_create();

/**
  * @test Test object destruction 
  * @pre Destroys an initialized object
  * @post Output==OK
  */
void test1_object_destroy();

/**
  * @test Test object destruction
  * @pre NULL pointer to object
  * @post Output==ERROR 
  */
void test2_object_destroy();

/**
  * @test Test object_id getting 
  * @pre Object creation with ID
  * @post The set object id
  */
void test1_object_get_id();

/**
  * @test Test object_id getting 
  * @pre NULL pointer to object
  * @post NO_ID
  */
void test2_object_get_id();

/**
  * @test Test object_name setting 
  * @pre String with object name
  * @post Output==OK
  */
void test1_object_set_name();

/**
  * @test Test object_name setting 
  * @pre pointer to object = NULL
  * @post Output==ERROR
  */
void test2_object_set_name();

/**
  * @test Test object_name setting 
  * @pre pointer to object_name = NULL (point to object = NON NULL) 
  * @post Output==ERROR
  */
void test3_object_set_name();

/**
  * @test Test object_name getting 
  * @pre String with object name set
  * @post strcmp==0 (comparision between the
  * string that has been set and the object_name)
  */
void test1_object_get_name();

/**
  * @test Test object_name getting 
  * @pre NULL pointer to object
  * @post object_name==NULL
  */
void test2_object_get_name();

/**
  * @test Test object_description setting 
  * @pre String with object description
  * @post Output==OK
  */
void test1_object_set_description();

/**
  * @test Test object_description setting 
  * @pre pointer to object = NULL
  * @post Output==ERROR
  */
void test2_object_set_description();

/**
  * @test Test object_description setting 
  * @pre pointer to object_description = NULL (point to object = NON NULL) 
  * @post Output==ERROR
  */
void test3_object_set_description();

/**
  * @test Test object_description getting 
  * @pre String with object description set
  * @post strcmp==0 (comparision between the
  * string that has been set and the object_description)
  */
void test1_object_get_description();

/**
  * @test Test object_description getting 
  * @pre NULL pointer to object
  * @post object_description==NULL
  */
void test2_object_get_description();

/**
  * @test Test object printing 
  * @pre Object created
  * @post Output==OK
  */
void test1_object_print();

/**
  * @test Test object printing 
  * @pre NULL pointer to object
  * @post Output==ERROR
  */
void test2_object_print();

/**
  * @test Test object open setting 
  * @pre NULL pointer to object
  * @post Output==ERROR
  */
void test1_object_set_open();

/**
  * @test Test object open setting 
  * @pre Valid input
  * @post Output==OK
  */
void test2_object_set_open();

/**
  * @test Test object open getting 
  * @pre NULL pointer to object
  * @post Output==NO_ID
  */
void test1_object_get_open();

/**
  * @test Test object open getting 
  * @pre Valid input
  * @post Output==provided id
  */
void test2_object_get_open();

/**
  * @test Test object dependency setting 
  * @pre NULL pointer to object
  * @post Output==ERROR
  */
void test1_object_set_dependency();

/**
  * @test Test object dependency setting 
  * @pre Valid input
  * @post Output==OK
  */
void test2_object_set_dependency();

/**
  * @test Test object dependency getting 
  * @pre NULL pointer to object
  * @post Output==NO_ID
  */
void test1_object_get_dependency();

/**
  * @test Test object dependency getting 
  * @pre Valid input
  * @post Output==provided id
  */
void test2_object_get_dependency();

/**
  * @test Test object movable setting 
  * @pre NULL pointer to object
  * @post Output==ERROR
  */
void test1_object_set_movable();

/**
  * @test Test object movable setting 
  * @pre Valid input
  * @post Output==OK
  */
void test2_object_set_movable();

/**
  * @test Test object movable getting 
  * @pre NULL pointer to object
  * @post Output==FALSE
  */
void test1_object_get_movable();

/**
  * @test Test object movable getting 
  * @pre Valid input
  * @post Output==provided state
  */
void test2_object_get_movable();

/**
  * @test Test object hidden setting 
  * @pre NULL pointer to object
  * @post Output==ERROR
  */
void test1_object_set_hidden();

/**
  * @test Test object hidden setting 
  * @pre Valid input
  * @post Output==OK
  */
void test2_object_set_hidden();

/**
  * @test Test object hidden getting 
  * @pre NULL pointer to object
  * @post Output==FALSE
  */
void test1_object_get_hidden();

/**
  * @test Test object hidden getting 
  * @pre Valid input
  * @post Output==provided state
  */
void test2_object_get_hidden();

/**
  * @test Test object turnedon setting 
  * @pre NULL pointer to object
  * @post Output==ERROR
  */
void test1_object_set_turnedon();

/**
  * @test Test object turnedon setting 
  * @pre Valid input
  * @post Output==OK
  */
void test2_object_set_turnedon();

/**
  * @test Test object turnedon getting 
  * @pre NULL pointer to object
  * @post Output==FALSE
  */
void test1_object_get_turnedon();

/**
  * @test Test object turnedon getting 
  * @pre Valid input
  * @post Output==provided state
  */
void test2_object_get_turnedon();

/**
  * @test Test object illuminate setting 
  * @pre NULL pointer to object
  * @post Output==ERROR
  */
void test1_object_set_illuminate();

/**
  * @test Test object illuminate setting 
  * @pre Valid input
  * @post Output==OK
  */
void test2_object_set_illuminate();

/**
  * @test Test object illuminate getting 
  * @pre NULL pointer to object
  * @post Output==FALSE
  */
void test1_object_get_illuminate();

/**
  * @test Test object illuminate getting 
  * @pre Valid input
  * @post Output==provided state
  */
void test2_object_get_illuminate();


#endif 
