/** 
 * @brief It declares the tests for the game_management module
 * 
 * @file game_management_test.h
 * @author Sergio Saúco
 * @version 1.0 
 * @date 13-04-2023
 * @copyright GNU Public License
 */

#ifndef GAME_MANAGEMENT_TEST_H
#define GAME_MANAGEMENT_TEST_H



/**
 * @test Test loading spaces from a specific file
 * @pre Game data file
 * @post Output==OK
 */
void test1_game_management_load_spaces(char *filename);

/**
 * @test Test loading spaces from a specific file
 * @pre NULL pointer to char (filename)
 * @post Output==ERROR
 */
void test2_game_management_load_spaces();

/**
 * @test Test loading objects from a specific file
 * @pre Game data file
 * @post Output==OK
 */
void test1_game_management_load_objects(char *filename);

/**
 * @test Test loading objects from a specific file
 * @pre NULL pointer to char (filename)
 * @post Output==ERROR
 */
void test2_game_management_load_objects();

/**
 * @test Test loading player from a specific file
 * @pre Game data file
 * @post Output==OK
 */
void test1_game_management_load_player(char *filename);

/**
 * @test Test loading player from a specific file
 * @pre NULL pointer to char (filename)
 * @post Output==ERROR
 */
void test2_game_management_load_player();

/**
 * @test Test loading enemy from a specific file
 * @pre Game data file
 * @post Output==OK
 */
void test1_game_management_load_enemies(char *filename);

/**
 * @test Test loading enemy from a specific file
 * @pre NULL pointer to char (filename)
 * @post Output==ERROR
 */
void test2_game_management_load_enemies();

/**
 * @test Test loading links from a specific file
 * @pre Game data file
 * @post Output==OK
 */
void test1_game_management_load_links(char *filename);

/**
 * @test Test loading links from a specific file
 * @pre NULL pointer to char (filename)
 * @post Output==ERROR
 */
void test2_game_management_load_links();

/**
 * @test Test saving a game
 * @pre NULL pointer to game
 * @post Output==ERROR
 */
void test1_game_management_save();

/**
 * @test Test saving a game
 * @pre created game from file
 * @post Output==OK
 */
void test2_game_management_save(char *filename);

/**
 * @test Test loading a game
 * @pre saved game in file
 * @post Output==OK
 */
void test1_game_management_load(char *filename);

/**
 * @test Test loading a game
 * @pre NULL pointer to filename
 * @post Output==ERROR
 */
void test2_game_management_load();

#endif
