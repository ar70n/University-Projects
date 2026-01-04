/** 
 * @brief It declares the tests for the game_reader module
 * 
 * @file game_reader_test.h
 * @author Sergio Saúco
 * @version 1.0 
 * @date 13-04-2023
 * @copyright GNU Public License
 */

#ifndef GAME_READER_TEST_H
#define GAME_READER_TEST_H


/**
 * @test Test loading spaces from a specific file
 * @pre Game data file
 * @post Output==OK
 */
void test1_game_reader_load_spaces(char *filename);

/**
 * @test Test loading spaces from a specific file
 * @pre NULL pointer to char (filename)
 * @post Output==ERROR
 */
void test2_game_reader_load_spaces();

/**
 * @test Test loading objects from a specific file
 * @pre Game data file
 * @post Output==OK
 */
void test1_game_reader_load_objects(char *filename);

/**
 * @test Test loading objects from a specific file
 * @pre NULL pointer to char (filename)
 * @post Output==ERROR
 */
void test2_game_reader_load_objects();

/**
 * @test Test loading player from a specific file
 * @pre Game data file
 * @post Output==OK
 */
void test1_game_reader_load_player(char *filename);

/**
 * @test Test loading player from a specific file
 * @pre NULL pointer to char (filename)
 * @post Output==ERROR
 */
void test2_game_reader_load_player();

/**
 * @test Test loading enemy from a specific file
 * @pre Game data file
 * @post Output==OK
 */
void test1_game_reader_load_enemy(char *filename);

/**
 * @test Test loading enemy from a specific file
 * @pre NULL pointer to char (filename)
 * @post Output==ERROR
 */
void test2_game_reader_load_enemy();

/**
 * @test Test loading links from a specific file
 * @pre Game data file
 * @post Output==OK
 */
void test1_game_reader_load_links(char *filename);

/**
 * @test Test loading links from a specific file
 * @pre NULL pointer to char (filename)
 * @post Output==ERROR
 */
void test2_game_reader_load_links();

#endif