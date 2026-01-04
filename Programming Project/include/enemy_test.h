/**
 * @brief It defines the enemy test  interface
 *
 * @file enemy_test.h
 * @author Antonio Moroño
 * @version 1.0
 * @date 3-03-2023
 * @copyright GNU Public License
 */

#ifndef ENEMY_TEST_H
#define ENEMY_TEST_H



/**
  * @test Test enemy creation
  * 
  * @pre Enemy ID
  * @post Non NULL pointer to enemy
  */
void test1_enemy_create();

/**
  * @test Test enemy creation
  * 
  * @pre NO_ID
  * @post NULL pointer 
  */
void test2_enemy_create();

/**
  * @test  Test function for destroying enemy
  * 
  * @pre Destroy an initialized enemy
  * @post Outpu==OK
  */
void  test1_enemy_destroy();

/**
  * @test  Test function for destroying enemy
  * 
  * @pre Destroy an enemy ponter to null
  * @post Output==ERROR
  */
void  test2_enemy_destroy();

/**
  * @test Test enemy get id function 
  * 
  * @pre Enemy non NULL pointer to Enemy
  * @post Enemy ID == ID of the Enemy supplied
  */
void  test1_enemy_get_id();

/**
  * @test Test enemy get id function 
  * 
  * @pre  NULL pointer to Enemy
  * @post Enemy ID == NO_ID 
  */
void  test2_enemy_get_id();

/**
  * @test Test enemy get id function 
  * 
  * @pre  pointer to Enemy != Enemy
  * @post Enemy ID == NO_ID 
  */
void  test3_enemy_get_id();

/**
 * @test Test function for enemy_name setting
 * @pre String with enemy name
 * @post Ouput==OK 
 */
void test1_enemy_set_name();

/**
 * @test Test function for enemy_name setting
 * @pre pointer to enemy = NULL 
 * @post Output==ERROR
 */
void test2_enemy_set_name();

/**
 * @test Test function for enemy_name setting
 * @pre pointer to enemy_name = NULL (point to enemy = NON NULL) 
 * @post Output==ERROR
 */
void test3_enemy_set_name();


/**
  * @test Test function for getting enemy name
  * 
  * @pre Get name with proper params
  * @post Output is a char pointer to enemy's name
  */
void  test1_enemy_get_name();

/**
  * @test Test function for getting enemy name
  * 
  * @pre Get name from NULL enemy
  * @post Output==NULL
  */
void  test2_enemy_get_name();


/**
  * @test Test function for setting enemy location
  * 
  * @pre Set enemy location with proper params
  * @post Output==OK
  */
void  test1_enemy_set_location();

/**
  * @test Test function for setting enemy location
  * 
  * @pre Set enemy location to NO_ID
  * @post Output==OK
  */
void  test2_enemy_set_location();


/**
  * @test Test function for getting enemy location
  * 
  * @pre Get enemy location from an enemy without location
  * @post Output==NO_ID
  */
void  test1_enemy_get_location();


/**
  * @test Test function for getting enemy location
  * 
  * @pre Get enemy location from an enemy with a location
  * @post Output==enemy's location ID
  */
void  test2_enemy_get_location();

/**
  * @test Test function for getting enemy location
  * 
  * @pre Get enemy location from a null enemy
  * @post Output==NO_ID
  */
void  test3_enemy_get_location();


/**
  * @test Test function for setting enemy health
  * 
  * @pre Set health higher than 0 with proper params
  * @post Output==OK
  */
void  test1_enemy_set_health();


/**
  * @test Test function for setting enemy health
  * 
  * @pre Set enemy heath to 0
  * @post Output==OK
  */
void  test2_enemy_set_health();


/**
  * @test Test function for getting enemy health
  * 
  * @pre Get enemy health with proper params
  * @post Output==enemy's health 
  */
void  test1_enemy_get_health();



/**
  * @test Test function for getting enemy health
  * 
  * @pre Get health from null enemy
  * @post Output==-1
  */
void  test2_enemy_get_health();



/**
  * @test Test function for printing enemy information
  * 
  * @pre Print information from enemy 
  * @post prints information correctly, STATUS==OK
  */
void  test1_enemy_print();

/**
  * @test Test function for printing enemy information
  * 
  * @pre Print information from null enemy
  * @post Output==ERROR
  */
void  test2_enemy_print();


#endif
