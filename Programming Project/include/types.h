/**
 * @brief It defines common types for the whole project
 *
 * @file types.h
 * @author Profesores PPROG
 * @version 2.0
 * @date 29-11-2021
 * @copyright GNU Public License
 */

#ifndef TYPES_H
#define TYPES_H

#define WORD_SIZE 1000 /*!< The maximum number of characters */
#define NO_ID -1 /*!< No identification number */

/**
 * @brief Identification
 *
 * Param Id of type long
 */
typedef long Id;

/**
 * @brief Boolean variables
 *
 * Stores TRUE and FALSE
 */
typedef enum {
  FALSE, /*!< Boolean false */
  TRUE /*!< Boolean true */
} BOOL;

/**
 * @brief Status
 *
 * Stores OK and ERROR
 */
typedef enum {
  ERROR, /*!< Status error */
  OK /*!< Status ok */
} STATUS;

/**
 * @brief Direction
 *
 * Stores all the directions (North, South, 
 * East, West, Up, Down and Unknown)
 */
typedef enum {
  N, /*!< Direction north */
  E, /*!< Direction east */
  S, /*!< Direction south */
  W, /*!< Direction west */
  U, /*!< Direction up */
  D, /*!< Direction down */
  I /*!< Direction unknown */
} DIRECTION;

/**
 * @brief Connection
 *
 * Stores OPEN and CLOSE 
 * 
 */
typedef enum {
  OPEN, /*!< Connection openned */
  CLOSE /*!< Connection closed */
} CONNECTION;

#endif
