/**
 * @brief It defines the player test  interface
 *
 * @file player_test.h
 * @author Miguel Campo
 * @version 1.0
 * @date 22-03-2023
 * @copyright GNU Public License
 */

#ifndef PLAYER_TEST_H
#define PLAYER_TEST_H



/**
  * @test Test player creation
  * 
  * @pre Player ID
  * @post Non NULL pointer to player
  */
void test1_player_create();

/**
  * @test Test player creation
  * 
  * @pre NO_ID
  * @post NULL pointer 
  */
void test2_player_create();

/**
  * @test  Test function for destroying player
  * 
  * @pre Destroys an initialized player
  * @post Outpu==OK
  */
void  test1_player_destroy();

/**
  * @test  Test function for destroying player
  * 
  * @pre Destroys a player pointer to null
  * @post Output==ERROR
  */
void  test2_player_destroy();

/**
  * @test Test player get id function 
  * 
  * @pre Player non NULL pointer to Player
  * @post Player ID == ID of the Player supplied
  */
void  test1_player_get_id();

/**
  * @test Test player get id function 
  * 
  * @pre  NULL pointer to Player
  * @post Player ID == NO_ID 
  */
void  test2_player_get_id();

/**
  * @test Test player get id function 
  * 
  * @pre  pointer to Player != Player
  * @post Player ID == NO_ID 
  */
void  test3_player_get_id();

/**
 * @test Test function for player_name setting
 * @pre String with player name
 * @post Ouput==OK 
 */
void test1_player_set_name();

/**
 * @test Test function for player_name setting
 * @pre pointer to player = NULL 
 * @post Output==ERROR
 */
void test2_player_set_name();

/**
 * @test Test function for player_name setting
 * @pre pointer to player_name = NULL (point to player = NON NULL) 
 * @post Output==ERROR
 */
void test3_player_set_name();


/**
  * @test Test function for getting player name
  * 
  * @pre Get name with proper params
  * @post Output is a char pointer to player's name
  */
void  test1_player_get_name();

/**
  * @test Test function for getting player name
  * 
  * @pre Get name from NULL player
  * @post Output==NULL
  */
void  test2_player_get_name();


/**
  * @test Test function for setting player location
  * 
  * @pre Set player location with proper params
  * @post Output==OK
  */
void  test1_player_set_location();

/**
  * @test Test function for setting player location
  * 
  * @pre Set player location to NO_ID
  * @post Output==OK
  */
void  test2_player_set_location();


/**
  * @test Test function for getting player location
  * 
  * @pre Get player location from an player without location
  * @post Output==NO_ID
  */
void  test1_player_get_location();


/**
  * @test Test function for getting player location
  * 
  * @pre Get player location from an player with a location
  * @post Output==player's location ID
  */
void  test2_player_get_location();

/**
  * @test Test function for getting player location
  * 
  * @pre Get player location from a null player
  * @post Output==NO_ID
  */
void  test3_player_get_location();


/**
  * @test Test function for setting player health
  * 
  * @pre Set health higher than 0 with proper params
  * @post Output==OK
  */
void  test1_player_set_health();


/**
  * @test Test function for setting player health
  * 
  * @pre Set player heath to 0
  * @post Output==OK
  */
void  test2_player_set_health();


/**
  * @test Test function for getting player health
  * 
  * @pre Get player health with proper params
  * @post Output==player's health 
  */
void  test1_player_get_health();



/**
  * @test Test function for getting player health
  * 
  * @pre Get health from null player
  * @post Output==-1
  */
void  test2_player_get_health();



/**
  * @test Test function for printing player information
  * 
  * @pre Print information from player 
  * @post prints information correctly, STATUS==OK
  */
void  test1_player_print();

/**
  * @test Test function for printing player information
  * 
  * @pre Print information from null player
  * @post Output==ERROR
  */
void  test2_player_print();

/**
  * @test Test function for adding objects to inventory
  * 
  * @pre Valid player and id
  * @post Output==OK
  */
void test1_player_add_object_to_inventory();

/**
  * @test Test function for adding objects to inventory
  * 
  * @pre Null player
  * @post Output==ERROR
  */
void test2_player_add_object_to_inventory();

/**
  * @test Test function for adding objects to inventory
  * 
  * @pre NO_ID
  * @post Output==ERROR
  */
void test3_player_add_object_to_inventory();

/**
  * @test Test function for deleting objects from inventory
  * 
  * @pre Valid player and id
  * @post Output==OK
  */
void test1_player_del_object_from_inventory(); 

/**
  * @test Test function for deleting objects from inventory
  * 
  * @pre Id not in inventory
  * @post Output==ERROR
  */
void test2_player_del_object_from_inventory();

/**
  * @test Test function for getting inventory array
  * 
  * @pre Valid player and valid inventory
  * @post given array == player inventory
  */
void test1_player_get_objects();

/**
  * @test Test function for getting inventory array
  * 
  * @pre Valid player and empty inventory
  * @post Player array == NULL
  */
void test2_player_get_objects();

/**
  * @test Test function for checking inventory for an id
  * 
  * @pre Valid player and valid inventory
  * @post Output==TRUE
  */
void test1_player_inventory_stores();

/**
  * @test Test function for checking inventory for an id
  * 
  * @pre inventory doesn't have id
  * @post Output==FALSE
  */
void test2_player_inventory_stores();

/**
  * @test Test function for getting number of objects in inventory
  * 
  * @pre Valid player and inventory
  * @post Output==1
  */
void test1_player_get_n_objects();

/**
  * @test Test function for getting number of objects in inventory
  * 
  * @pre Empty inventory
  * @post Output==0
  */
void test2_player_get_n_objects(); 

/**
  * @test Test function for getting inventory
  * 
  * @pre Valid player and inventory
  * @post player_inventory == given inventory
  */
void test1_player_get_inventory();

/**
  * @test Test function for getting inventory
  * 
  * @pre NULL player
  * @post player_inventory == -1
  */
void test2_player_get_inventory(); 

#endif
