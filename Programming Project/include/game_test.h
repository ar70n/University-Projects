/** 
 * @brief It declares the tests for the game module
 * 
 * @file game_test.h
 * @author Antonio Moroño
 * @version 1.0
 * @date 11-04-2023
 * @copyright GNU Public License
 */

#ifndef GAME_TEST_H
#define GAME_TEST_H

/**
 * @test Test game creation
 * @pre Initialized game
 * @post Output==OK
 */
void test1_game_create();

/**
 * @test Test game creation
 * @pre NULL pointer to game
 * @post Output==ERROR
 */
void test2_game_create();

/**
 * @test Test game creation from a specific file
 * @pre Initialized game and a file
 * @post Output==OK
 */
void test1_game_create_from_file(char *filename);

/**
 * @test Test game creation from a specific file
 * @pre Initialized game and filename = NULL
 * @post Output==ERROR
 */
void test2_game_create_from_file();

/**
 * @test Test game destruction
 * @pre Created game
 * @post Output==OK
 */
void test1_game_destroy();

/**
 * @test Test game destruction
 * @pre NULL pointer to game
 * @post Output==ERROR
 */
void test2_game_destroy();

/**
 * @test Test getting the game over
 * @pre Created game
 * @post Output==FALSE
 */
void test1_game_is_over();

/**
 * @test Test getting the game over
 * @pre Created game with player set (player_health = 0)
 * @post Output==TRUE
 */
void test2_game_is_over();

/**
 * @test Test game getting space from id
 * @pre Initialized and added space to the game 
 * @post Pointer to the added space 
 */
void test1_game_get_space();

/**
 * @test Test game getting space from id
 * @pre NO_ID
 * @post NULL pointer to space 
 */
void test2_game_get_space();

/**
 * @test Test game getting space from id
 * @pre Initialized and added space to the game
 * and searched different ID
 * @post NULL pointer to space 
 */
void test3_game_get_space();

/**
 * @test Test game getting player location
 * @pre Initialized and added player to the game 
 * in a space
 * @post Player location (space ID) 
 */
void test1_game_get_player_location();

/**
 * @test Test game getting player location
 * @pre Created game (NULL pointer to player)
 * @post NO_ID
 */
void test2_game_get_player_location();

/**
 * @test Test game getting object location
 * @pre Initialized and added object to the game 
 * in a space
 * @post Object location (space ID) 
 */
void test1_game_get_object_location();

/**
 * @test Test game getting object location
 * @pre Created game (NULL pointer to player)
 * @post NO_ID 
 */
void test2_game_get_object_location();

/**
 * @test Test game getting enemy location
 * @pre Initialized and added enemy to the game 
 * in a space
 * @post Enemy location (space ID) 
 */
void test1_game_get_enemy_location();

/**
 * @test Test game getting enemy location
 * @pre Created game (NULL pointer to enemy)
 * @post NO_ID 
 */
void test2_game_get_enemy_location();

/**
 * @test Test game getting player health
 * @pre Initialized and added player to the game 
 * with a number of health points (from file)
 * @post Player health 
 */
void test1_game_get_player_health();

/**
 * @test Test game getting player health
 * @pre Created game (NULL pointer to player)
 * @post -1
 */
void test2_game_get_player_health();

/**
 * @test Test game getting enemy health
 * @pre Initialized and added enemy to the game 
 * with a number of health points (from file)
 * @post Enemy health 
 */
void test1_game_get_enemy_health();

/**
 * @test Test game getting enemy health
 * @pre Created game (NULL pointer to enemy)
 * @post -1
 */
void test2_game_get_enemy_health();

/**
 * @test Test game setting last command
 * @pre last_cmd = TAKE
 * @post Output==OK
 */
void test1_game_set_last_command();

/**
 * @test Test game setting last command
 * @pre last_cmd = TAKE
 * @post last_cmd==TAKE
 */
void test2_game_set_last_command();

/**
 * @test Test game getting last command
 * @pre Created game (last_cmd = NO_CMD)
 * @post Last command
 */
void test1_game_get_last_command();

/**
 * @test Test game getting last command
 * @pre last_cmd = TAKE
 * @post Last command
 */
void test2_game_get_last_command();

/**
 * @test Test game getting last command status
 * @pre Created game (last_cmd_status = ERROR)
 * @post Last command status
 */
void test1_game_get_last_command_status();

/**
 * @test Test game getting last command status
 * @pre last_cmd_status = OK
 * @post Last command status
 */
void test2_game_get_last_command_status();

/**
 * @test Test game adding a space to the game
 * @pre Created space with ID
 * @post Output==OK
 */
void test1_game_add_space();

/**
 * @test Test game adding a space to the game
 * @pre NULL pointer to space
 * @post Output==ERROR
 */
void test2_game_add_space();

/**
 * @test Test game adding a link to the game
 * @pre Created link with ID
 * @post Output==OK
 */
void test1_game_add_link();

/**
 * @test Test game adding a link to the game
 * @pre NULL pointer to link
 * @post Output==ERROR
 */
void test2_game_add_link();

/**
 * @test Test game adding an object to the game
 * @pre Created object with ID
 * @post Output==OK
 */
void test1_game_add_object();

/**
 * @test Test game adding a link to the game
 * @pre NULL pointer to object
 * @post Output==ERROR
 */
void test2_game_add_object();

/**
 * @test Test game adding a link to the game
 * @pre location = NO_ID
 * @post Output==ERROR
 */
void test3_game_add_object();

/**
 * @test Test game setting the player of the game
 * @pre Created player with ID
 * @post Output==OK
 */
void test1_game_set_player();

/**
 * @test Test game setting the player of the game
 * @pre NULL pointer to player
 * @post Output==ERROR
 */
void test2_game_set_player();

/**
 * @test Test game setting the enemy of the game
 * @pre Created enemy with ID
 * @post Output==OK
 */
void test1_game_add_enemy();

/**
 * @test Test game setting the enemy of the game
 * @pre NULL pointer to enemy
 * @post Output==ERROR
 */
void test2_game_add_enemy();

/**
 * @test Test game geting all spaces id's
 * @pre NULL pointer to game and/or NULL
 * pointer to the array of id's
 * @post Output==ERROR and correct ids
 */
void test1_game_get_all_space_ids();

/**
 * @test Test game geting all spaces id's
 * @pre Created game with 2 spaces added to it
 * @post Output==OK
 */
void test2_game_get_all_space_ids();

/**
 * @test Test game geting all objects id's
 * @pre NULL pointer to game and/or NULL
 * pointer to the array of id's
 * @post Output==ERROR
 */
void test1_game_get_objects();

/**
 * @test Test game geting all objects id's
 * @pre Created game with 2 objects added to it
 * @post Output==OK and correct ids
 */
void test2_game_get_objects();

/**
 * @test Test game geting player
 * @pre NULL pointer to game
 * @post NULL pointer to player
 */
void test1_game_get_player();

/**
 * @test Test game geting player
 * @pre Created game and player set
 * @post The player
 */
void test2_game_get_player();

/**
 * @test Test game geting enemy
 * @pre NULL pointer to game
 * @post NULL pointer to enemy
 */
void test1_game_get_enemy();

/**
 * @test Test game geting enemy
 * @pre Created game and enemy set
 * @post The enenemy
 */
void test2_game_get_enemy();

/**
 * @test Test game geting an object
 * @pre NULL pointer to game and/or wrong index (-1)
 * @post NULL pointer to object
 */
void test1_game_get_object();

/**
 * @test Test game geting an object
 * @pre Created game and object added to it
 * @post The object
 */
void test2_game_get_object();

/**
 * @test Test game setting last command status
 * @pre NULL pointer to game
 * @post Output==ERROR
 */
void test1_game_set_last_command_status();

/**
 * @test Test game setting last command status
 * @pre Created game and status = ERROR
 * @post Output==OK
 */
void test2_game_set_last_command_status();

/**
 * @test Test game initialization
 * @pre Game init
 * @post Non NULL pointer to game 
 */
void test1_game_init();

/**
 * @test Test game getting connection status
 * @pre NULL pointer to game and space_id = NO_ID
 * @post -1
 */
void test1_game_get_connection_status();

/**
 * @test Test game getting connection status
 * @pre Created game with link closed
 * between 2 spaces added to it, opened after check
 * @post result == 1
 */
void test2_game_get_connection_status();

/**
 * @test Test game getting the id of
 * the space connected to a space
 * @pre NULL pointer to game and space_id = NO_ID
 * @post NO_ID
 */
void test1_game_get_connection();

/**
 * @test Test game getting the id of
 * the space connected to a space
 * @pre Created game with a link: link_origin = 12
 * link_destination = 13 added to it
 * @post space_id==13
 */
void test2_game_get_connection();

/**
 * @test Test game getting wether a link
 * exists or not between 2 spaces
 * @pre NULL pointer to game and space_id = NO_ID
 * @post Output==FALSE
 */
void test1_game_link_exists();

/**
 * @test Test game getting wether a link
 * exists or not between 2 spaces
 * @pre Created game with a link: link_origin = 12
 * link_destination = 13 and status = OPEN added to it
 * @post Output==TRUE
 */
void test2_game_link_exists();

/**
 * @test Test game printing data
 * @pre Created game
 * @post Output==OK
 */
void test1_game_print_data();

/**
 * @test Test game printing data
 * @pre NULL pointer to game
 * @post Output==ERROR
 */
void test2_game_print_data();

/**
 * @test Test game getting the 
 * name of an object with its id
 * @pre NULL pointer to game
 * @post NULL pointer to char
 */
void test1_object_id_to_name();

/**
 * @test Test game getting the 
 * name of an object with its id
 * @pre Created game and id = NO_ID
 * @post NULL pointer to char
 */
void test2_object_id_to_name();

/**
 * @test Test game getting the 
 * name of an object with its id
 * @pre Created game with object with 
 * name = "Grain"
 * @post strcmp==0 (comparision between the
 * string that has been set and the object_name)
 */
void test3_object_id_to_name();

/**
 * @test Test game getting the 
 * an object from an id
 * @pre Created game with object with 
 * id = 12
 * @post object_pointer==get_object
 */
void test1_game_get_object_from_id();

/**
 * @test Test game getting the 
 * an object from an id
 * @pre NULL pointer to game
 * @post NULL pointer to Object
 */
void test2_game_get_object_from_id();

/**
 * @test Test game getting the space 
 * from a game with some index
 * @pre Added space to the game (index: 0)
 * @post space_pointer==get_space_index_0
 */
void test1_game_get_space_from_index();

/**
 * @test Test game getting the space 
 * from a game with some index
 * @pre NULL pointer to game
 * @post NULL pointer to space
 */
void test2_game_get_space_from_index();

/**
 * @test Test game getting the link 
 * from a game with some index
 * @pre Added link to the game (index: 0)
 * @post link_pointer==get_link_index_0
 */
void test1_game_get_link_from_index();

/**
 * @test Test game getting the link 
 * from a game with some index
 * @pre NULL pointer to game
 * @post NULL pointer to link
 */
void test2_game_get_link_from_index();


/**
 * @test Test game getting the description of the space
 * @pre Created game with space with 
 * description = "hola"
 * @post strcmp==0 (comparision between the
 * string that has been set and the space_description)
 */
void test1_game_get_space_description();

/**
 * @test Test game getting the description of the space
 * @pre NULL pointer to game
 * @post NULL pointer to space_description
 */
void test2_game_get_space_description();

/**
 * @test Test game getting the name of the space
 * @pre Created game with space with 
 * name = "adios"
 * @post strcmp==0 (comparision between the
 * string that has been set and the space_name)
 */
void test1_game_get_space_name();

/**
 * @test Test game getting the name of the space
 * @pre NULL pointer to game
 * @post NULL pointer to space_name
 */
void test2_game_get_space_name();

/**
 * @test Test game getting the dialogue 
 * string with command result
 * @pre Created game with its dialogue
 * @post strcmp==0 (comparision between the
 * string that has been set and the dialogue_command_result)
 */
void test1_game_get_dialogue_command_result();

/**
 * @test Test game getting the dialogue 
 * string with command result
 * @pre NULL pointer to game
 * @post NULL pointer to dialogue_command_result
 */
void test2_game_get_dialogue_command_result();

/**
 * @test Test game getting wether the player 
 * has a turnedon object to illuminate
 * @pre Added object (turnedon = TRUE) to player inventory
 * @post Output==TRUE
 */
void test1_game_player_can_illuminate();

/**
 * @test Test game getting wether the player 
 * has a turnedon object to illuminate
 * @pre NULL pointer to game
 * @post Output==FALSE
 */
void test2_game_player_can_illuminate();


#endif

