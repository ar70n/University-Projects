/**
 * @brief It defines the textual graphic engine interface
 *
 * @file graphic_engine.h
 * @author Profesores PPROG
 * @version 2.0
 * @date 29-11-2021
 * @copyright GNU Public License
 */

#ifndef __GRAPHIC_ENGINE__
#define __GRAPHIC_ENGINE__

#include "game.h"

/**
 * @brief Graphic_engine
 *
 * Stores the information about
 * the graphic engine (map, description, banner,
 * help, feedback, map_east and map_west)
 */
typedef struct _Graphic_engine Graphic_engine;

/**
  * @brief It creates the graphic engine
  * @author Profesores PPROG
  * 
  * @return the graphic engine or NULL, if it fails the memory allocation
  */
Graphic_engine *graphic_engine_create();

/**
  * @brief It destroys the graphic engine
  * @author Profesores PPROG
  * 
  * @param ge a pointer to the graphic engine that must be destroyed
  */
void graphic_engine_destroy(Graphic_engine *ge);

/**
  * @brief It paints the game
  * @author Profesores PPROG
  * 
  * @param ge a pointer to the graphic engine
  * @param game a pointer to the game that must be painted
  */
void graphic_engine_paint_game(Graphic_engine *ge, Game *game);

#endif
