/** 
 * @brief It declares the tests for the dialogue module
 * 
 * @file dialogue_test.h
 * @author Antonio Moroño
 * @version 1.0
 * @date 24-03-2023
 * @copyright GNU Public License
 */

#ifndef DIALOGUE_TEST_H
#define DIALOGUE_TEST_H

/**
 * @test Test dialogue creation
 * @pre  Creation of a dialogue
 * @post Non NULL pointer to dialogue
 */
void test1_dialogue_create();

/**
 * @test Test dialogue creation
 * @pre  Creation of a dialogue
 * @post previous_command==NO_CMD
 */
void test2_dialogue_create();

/**
 * @test Test function for dialogue destroying
 * @pre  Creation of a dialogue
 * @post Output==OK 
 */
void test1_dialogue_destroy();

/**
 * @test Test function for dialogue_id destroying
 * @pre  NULL pointer to dialogue
 * @post Output==ERROR
 */
void test2_dialogue_destroy();

/**
 * @test Test function for setting the command result
 * @pre  String with command result
 * @post Output== OK
 */
void test1_dialogue_set_command_result();

/**
 * @test Test function for setting the command result
 * @pre  NULL pointer to information (non NULL pointer to dialogue)
 * @post Output== ERROR
 */
void test2_dialogue_set_command_result();

/**
 * @test Test function for getting the command result
 * @pre  String with command result set
 * @post strcmp==0 (comparision between the
 * string that has been set and the command_result)
 */
void test1_dialogue_get_command_result();

/**
 * @test Test function for setting the command result
 * @pre  NULL pointer to dialogue
 * @post command_result==NULL
 */
void test2_dialogue_get_command_result();

/**
 * @test Test function for setting the previous command 
 * @pre  Previous_command=ATTACK
 * @post Output==OK
 */
void test1_dialogue_set_previous_command();

/**
 * @test Test function for setting the previous command 
 * @pre  Previous_command=NO_CMD
 * @post Output==ERROR
 */
void test2_dialogue_set_previous_command();

/**
 * @test Test function for getting the previous command 
 * @pre  Previous_command=ATTACK set
 * @post Previous_command==ATTACK
 */
void test1_dialogue_get_previous_command();

/**
 * @test Test function for setting the previous command 
 * @pre  NULL pointer to dialogue
 * @post Previous_command==NO_CMD
 */
void test2_dialogue_get_previous_command();

/**
 * @test Test function for setting the previous command status
 * @pre  Previous_command_status==ERROR
 * @post Output==OK
 */
void test1_dialogue_set_previous_command_status();

/**
 * @test Test function for setting the previous command status 
 * @pre NULL pointer to dialogue
 * @post Output==ERROR
 */
void test2_dialogue_set_previous_command_status();

/**
 * @test Test function for getting the previous command status
 * @pre  Previous_command_status=OK
 * @post Previous_command_status==OK
 */
void test1_dialogue_get_previous_command_status();

/**
 * @test Test function for getting the previous command status 
 * @pre NULL pointer to dialogue
 * @post previous_command_status==ERROR
 */
void test2_dialogue_get_previous_command_status();

/**
 * @test Test function for setting the previous command additional information
 * @pre  String with previous additional information
 * @post Output==OK
 */
void test1_dialogue_set_previous_additional_information();

/**
 * @test Test function for setting the previous command additional information
 * @pre  NULL pointer to previous additional information
 * @post Output==ERROR
 */
void test2_dialogue_set_previous_additional_information();

/**
 * @test Test function for getting the previous command additional information
 * @pre  NULL pointer to dialogue
 * @post previous_additional_information==NULL
 */
void test1_dialogue_get_previous_additional_information();

/**
 * @test Test function for getting the previous command additional information
 * @pre  String with previous additional information set
 * @post strcmp==0 (comparision between the
 * string that has been set and the previous_additional_information)
 */
void test2_dialogue_get_previous_additional_information();

/**
 * @test Test function for setting the previous player location
 * @pre  player_location=101
 * @post Output==OK
 */
void test1_dialogue_set_previous_player_location();

/**
 * @test Test function for setting the previous player location
 * @pre  NULL pointer to dialogue
 * @post Output==ERROR
 */
void test2_dialogue_set_previous_player_location();

/**
 * @test Test function for getting the previous player location
 * @pre  player_location=101
 * @post previous_player_location==101
 */
void test1_dialogue_get_previous_player_location();

/**
 * @test Test function for getting the previous player location
 * @pre  NULL pointer to dialogue
 * @post previous_player_location==NO_ID
 */
void test2_dialogue_get_previous_player_location();

/**
  * @test Test function for printing dialogue information
  * @pre Dialogue created and information set
  * @post Output==OK
  */
void test1_dialogue_print();

/**
  * @test Test function for printing dialogue information
  * @pre NULL pointer to dialogue
  * @post Output==ERROR
  */
void test2_dialogue_print();

#endif
