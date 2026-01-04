/** 
 * @brief It declares the tests for the game rules module
 * 
 * @file game_rules_test.h
 * @author Sergio Saúco
 * @version 1.0
 * @date 01-05-2023
 * @copyright GNU Public License
 */

#ifndef GAME_RULES_TEST_H
#define GAME_RULES_TEST_H

/**
 * @test Test running game rules
 * @pre  NULL pointer to game
 * @post Output==ERROR
 */
void test1_game_rules_run();

/**
 * @test Test running game rules
 * @pre  NULL pointer to aditional_info
 * @post Output==ERROR
 */
void test2_game_rules_run();

/**
 * @test Test running game rules
 * @pre  Created game from file
 * @post Output==OK
 */
void test3_game_rules_run(char *filename);

#endif
