/** 
 * @brief It declares the tests for the inventory module
 * 
 * @file inventory_test.h
 * @author Antonio Moroño
 * @version 2.1 
 * @date 27-03-2023
 * @copyright GNU Public License
 */

#ifndef INVENTORY_TEST_H
#define INVENTORY_TEST_H

/**
 * @test Test inventory creation
 * @pre  Inventory ID 
 * @post Non NULL pointer to inventory 
 */
void test1_inventory_create();

/**
 * @test Test inventory creation
 * @pre  Inventory ID 
 * @post Inventory_ID == Supplied Inventory Id
 */
void test2_inventory_create();

/**
 * @test Test inventory destruction
 * @pre  Non NULL pointer to inventory
 * @post Output==OK 
 */
void test1_inventory_destroy();

/**
 * @test Test inventory destruction
 * @pre  NULL pointer to Inventory
 * @post Output==ERROR
 */
void test2_inventory_destroy();


/**
 * @test Test function for inventory_objects adding
 * @pre  Non NULL pointer to Inventory and object ID
 * @post Ouput==OK
 */
void test1_inventory_add_object();


/**
 * @test Test function for inventory_objects adding
 * @pre  Non NULL pointer to Inventory and object ID==NO_ID
 * @post Ouput==ERROR
 */
void test2_inventory_add_object();


/**
 * @test Test function for inventory_objects deleting
 * @pre  Non NULL pointer to Inventory and ID from object in Inventory
 * @post Ouput==OK
 */
void test1_inventory_del_object();


/**
 * @test Test function for inventory_objects deleting
 * @pre  Non NULL pointer to Inventory and ID from object not in Inventory
 * @post Ouput==ERROR
 */
void test2_inventory_del_object();


/**
 * @test Test function for inventory_object getting
 * @pre  Pointer to Inventory with at least one object
 * @post Output==array of ids
 */
void test1_inventory_get_objects();


/**
 * @test Test function for inventory_object getting
 * @pre  NULL pointer to inventory
 * @post Output==NULL
 */
void test2_inventory_get_objects();


/**
 * @test Test function for searching a object in inventory
 * @pre  Pointer to Inventory and ID from object in Inventory
 * @post Output==TRUE
 */
void test1_inventory_stores_object();


/**
 * @test Test function for searching a object in inventory
 * @pre  Pointer to Inventory and ID from object not in Inventory
 * @post Output==FALSE
 */
void test2_inventory_get_object();

/**
 * @test Test function for searching a object in inventory
 * @pre  Pointer to Inventory and ID from object in Inventory
 * @post Output==TRUE
 */
void test1_inventory_stores_object();


/**
 * @test Test function for searching a object in inventory
 * @pre  Pointer to Inventory and ID from object not in Inventory
 * @post Output==FALSE
 */
void test2_inventory_stores_object();

/**
 * @test Test function for getting number of objects
 * @pre  Pointer to Inventory with objects
 * @post Output==Correct number of objects in Inventory
 */
void test1_inventory_get_n_objects();


/**
 * @test Test function for getting number of objects
 * @pre  Pointer to empty Inventory
 * @post Output==0
 */
void test2_inventory_get_n_objects();


/**
 * @test Test function for setting max number of objects
 * @pre  Pointer to Inventory and postive number
 * @post Output==OK
 */
void test1_inventory_set_max_objs();


/**
 * @test Test function for setting max number of objects
 * @pre  Pointer to Inventory and negative number
 * @post Output==ERROR
 */
void test2_inventory_set_max_objs();



/**
 * @test Test function for getting max number of objects
 * @pre  Pointer to Inventory without setting max number of objects
 * @post -1
 */
void test1_inventory_get_max_objs();


/**
 * @test Test function for getting max number of objects
 * @pre  Pointer to Inventory with max number of objects
 * @post The supplied max number
 */
void test2_inventory_get_max_objs();

/**
 * @test Test function for printing inventory
 * @pre  Non NULL pointer to Inventory 
 * @post Output==OK
 */
void test1_inventory_print();


/**
 * @test Test function for printing inventory
 * @pre  NULL pointer to Inventory
 * @post Output==ERROR
 */
void test2_inventory_print();



#endif
