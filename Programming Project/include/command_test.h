/** 
 * @brief It declares the tests for the command module
 * 
 * @file command_test.h
 * @author Miguel Campo
 * @version 2.1 
 * @date 07-03-2023
 * @copyright GNU Public License
 */

#ifndef COMMAND_TEST_H
#define COMMAND_TEST_H

/**
 * @test Test command
 * @pre  Null information
 * @post Output == NULL 
 */
void test1_command_get_user_input(FILE *f);

/**
 * @test Test command
 * @pre  file 
 * @post Output == Command
 */
void test2_command_get_user_input(FILE *f);

#endif

