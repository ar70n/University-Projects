/**
 * @brief It defines a textual graphic engine
 *
 * @file graphic_engine.c
 * @author Profesores PPROG
 * @version 2.0
 * @date 29-11-2021
 * @copyright GNU Public License
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graphic_engine.h"
#include "libscreen.h"
#include "command.h"
#include "space.h"
#include "inventory.h"
#include "types.h"
#include "link.h"

#define ROWS 35 /*!< The number of rows in screen */
#define COLUMNS 110 /*!< The number of columns in screen */

/**
 * @brief Graphic_engine
 *
 * This struct stores all the information of the graphic_engine.
 */
struct _Graphic_engine
{
  Area *map;      /*!< Pointer to the screen map area */
  Area *descript; /*!< Pointer to the screen description area */
  Area *banner;   /*!< Pointer to the screen banner area */
  Area *help;     /*!< Pointer to the screen help area */
  Area *feedback; /*!< Pointer to the screen feedback area */
  Area *map_east; /*!< Pointer to the screen map_east area */
  Area *map_west; /*!< Pointer to the screen map_west area */
};

/** graphic_engine_create creates
 * the graphic engine
 */
Graphic_engine *graphic_engine_create()
{
  static Graphic_engine *ge = NULL;

  if (ge)
  {
    return ge;
  }

  screen_init(ROWS, COLUMNS);
  ge = (Graphic_engine *)malloc(sizeof(Graphic_engine));
  if (ge == NULL)
  {
    return NULL;
  }

  ge->map_west = screen_area_init(1, 1, 10, 24);
  ge->map = screen_area_init(11, 1, 22, 24);
  ge->map_east = screen_area_init(32, 1, 17, 24);
  ge->descript = screen_area_init(50, 1, 59, 24);
  ge->banner = screen_area_init(43, 26, 23, 1);
  ge->help = screen_area_init(1, 27, 108, 3);
  ge->feedback = screen_area_init(1, 31, 108, 3);

  return ge;
}

/** graphic_engine_destroy destroys
 * the graphic engine
 */
void graphic_engine_destroy(Graphic_engine *ge)
{
  if (!ge)
    return;

  screen_area_destroy(ge->map);
  screen_area_destroy(ge->map_east);
  screen_area_destroy(ge->map_west);
  screen_area_destroy(ge->descript);
  screen_area_destroy(ge->banner);
  screen_area_destroy(ge->help);
  screen_area_destroy(ge->feedback);

  screen_destroy();
  free(ge);
}

/** graphic_engine_paint_game paints the game
 */
void graphic_engine_paint_game(Graphic_engine *ge, Game *game)
{
  Id id_act = NO_ID, id_back = NO_ID, id_next = NO_ID, obj_loc = NO_ID, player_loc = NO_ID, id_west, id_east;
  Id *player_objects = NULL;
  char obj[5], left = '\0', right = '\0', up, down, up_arrow, down_arrow, north, south;
  char str[255], enemy[7], *obj_in_space_char[4], gdesc[6][10];
  T_Command last_cmd = UNKNOWN;
  extern char *cmd_to_str[N_CMD][N_CMDT];
  int health = 0, i, n_obj, power;
  char *desc = NULL;
  char *dialogue = NULL;
  Space *space;

  /*Id object_id_aux_BORRAR = NO_ID;*/

  /* Paint the in the map area */
  screen_area_clear(ge->map);
  screen_area_clear(ge->map_east);
  screen_area_clear(ge->map_west);
  if ((id_act = game_get_player_location(game)) != NO_ID)
  {

    id_back = game_get_connection(game, id_act, N);
    id_next = game_get_connection(game, id_act, S);

    if (id_back != NO_ID)
    {

      for (i = 0; i < MAX_SPACES && game_get_space_from_index(game, i); i++)
      {
        if (space_get_id(game_get_space_from_index(game, i)) == id_back)
        {
          space = game_get_space_from_index(game, i);
        }
      }
      strcpy(obj, "    ");
      if (space_get_light(space) == TRUE)
      {

        for (i = 0, n_obj = 0; i < MAX_OBJECTS && game_get_object(game, i) != NULL; i++)
        {
          /*printf("\n[DEBUG]: 2-[Object is null? %d] [Object id: %ld] [Object name: %s]\n\n\n", game->objects[i] == NULL, object_get_id(game->objects[i]), object_get_name(game->objects[i]));*/
          if (game_get_object_location(game, object_get_id(game_get_object(game, i))) == id_back && object_get_hidden(game_get_object(game, i)) == FALSE)
          {
            obj_in_space_char[n_obj] = object_get_name(game_get_object(game, i));
            n_obj++;
          }
        }
        for (i = 0; i < MAX_ENEMIES && game_get_enemy(game, i) != NULL; i++)
        {
          if (enemy_get_location(game_get_enemy(game, i)) == id_back && (enemy_get_health(game_get_enemy(game, i)) > 0))
          {
            strcpy(enemy, "(@_@)");
            break;
          }
          else
          {
            strcpy(enemy, "      ");
          }
        }
        strcpy(gdesc[0], space_get_gdesc_row(game_get_space(game, id_back), 3));
        strcpy(gdesc[1], space_get_gdesc_row(game_get_space(game, id_back), 4));
        strcpy(gdesc[2], space_get_gdesc_row(game_get_space(game, id_back), 5));
      }
      else
      {
        strcpy(enemy, "      ");
        strcpy(gdesc[0], "         ");
        strcpy(gdesc[1], "         ");
        strcpy(gdesc[2], "         ");
      }

      id_west = game_get_connection(game, id_back, W);
      if (game_link_exists(game, id_back, W) == TRUE)
      {
        left = '<';
      }
      else
      {
        left = ' ';
      }

      id_east = game_get_connection(game, id_back, E);
      if (game_link_exists(game, id_back, E) == TRUE)
      {
        right = '>';
      }
      else
      {
        right = ' ';
      }

      if (game_link_exists(game, id_act, U) == TRUE)
      {
        up_arrow = '^';
        up = '|';
      }
      else
      {
        up_arrow = ' ';
        up = ' ';
      }

      if (game_link_exists(game, id_act, D) == TRUE)
      {
        down_arrow = 'V';
        down = '|';
      }
      else
      {
        down_arrow = ' ';
        down = ' ';
      }

      sprintf(str, "  |%s      |", gdesc[0]);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |%s      |", gdesc[1]);
      screen_area_puts(ge->map, str);
      sprintf(str, "%c |%s      | %c", left, gdesc[2], right);
      screen_area_puts(ge->map, str);
      switch (n_obj)
      {
      case 0:
        sprintf(str, "  |               |");
        break;
      case 1:
        sprintf(str, "  |%s          |", obj_in_space_char[0]);
        break;
      case 2:
        sprintf(str, "  |%s %s    |", obj_in_space_char[0], obj_in_space_char[1]);
        break;
      case 3:
        sprintf(str, "  |%s %s... |", obj_in_space_char[0], obj_in_space_char[1]);
        break;
      case 4:
        sprintf(str, "  |%s %s... |", obj_in_space_char[0], obj_in_space_char[1]);
        break;
      default:
        sprintf(str, "  |               |");
        break;
      }
      screen_area_puts(ge->map, str);
      sprintf(str, "  +---------------+");
      screen_area_puts(ge->map, str);
      if (game_link_exists(game, id_act, N) == TRUE)
      {
        sprintf(str, "          ^");
      }
      else
      {
        sprintf(str, "           ");
      }
      screen_area_puts(ge->map, str);

      /*WEST*/

      id_west = game_get_connection(game, id_back, W);
      if (id_west == NO_ID)
      {
        id_west = game_get_connection(game, game_get_connection(game, id_act, W), N);
      }
      if (id_west != NO_ID)
      {
        for (i = 0; i < MAX_SPACES && game_get_space_from_index(game, i); i++)
        {
          if (space_get_id(game_get_space_from_index(game, i)) == id_west)
          {
            space = game_get_space_from_index(game, i);
          }
        }
        strcpy(obj, "    ");
        if (space_get_light(space) == TRUE)
        {

          for (i = 0, n_obj = 0; i < MAX_OBJECTS && game_get_object(game, i) != NULL; i++)
          {
            /*printf("\n[DEBUG]: 2-[Object is null? %d] [Object id: %ld] [Object name: %s]\n\n\n", game->objects[i] == NULL, object_get_id(game->objects[i]), object_get_name(game->objects[i]));*/
            if (game_get_object_location(game, object_get_id(game_get_object(game, i))) == id_west && object_get_hidden(game_get_object(game, i)) == FALSE)
            {
              obj_in_space_char[n_obj] = object_get_name(game_get_object(game, i));
              n_obj++;
            }
          }
        }

        sprintf(str, "        |");
        screen_area_puts(ge->map_west, str);
        sprintf(str, "        |");
        screen_area_puts(ge->map_west, str);
        sprintf(str, "        |");
        screen_area_puts(ge->map_west, str);
        switch (n_obj)
        {
        case 0:
          sprintf(str, "       |");
          break;
        case 1:
          sprintf(str, "  %s |", obj_in_space_char[0]);
          break;
        case 2:
          sprintf(str, "%s..|", obj_in_space_char[0]);
          break;
        case 3:
          sprintf(str, "%s..|", obj_in_space_char[0]);
          break;
        case 4:
          sprintf(str, "%s..|", obj_in_space_char[0]);
          break;
        default:
          sprintf(str, "       |");
          break;
        }
        screen_area_puts(ge->map_west, str);
        sprintf(str, "--------+");
        screen_area_puts(ge->map_west, str);
      }
      else
      {
        sprintf(str, " ");
        screen_area_puts(ge->map_west, str);
        sprintf(str, " ");
        screen_area_puts(ge->map_west, str);
        sprintf(str, " ");
        screen_area_puts(ge->map_west, str);
        sprintf(str, " ");
        screen_area_puts(ge->map_west, str);
        sprintf(str, " ");
        screen_area_puts(ge->map_west, str);
      }

      /*EAST*/

      id_east = game_get_connection(game, id_back, E);
      if (id_east == NO_ID)
      {
        id_east = game_get_connection(game, game_get_connection(game, id_act, E), N);
      }
      if (id_east != NO_ID)
      {

        for (i = 0; i < MAX_SPACES && game_get_space_from_index(game, i); i++)
        {
          if (space_get_id(game_get_space_from_index(game, i)) == id_east)
          {
            space = game_get_space_from_index(game, i);
          }
        }
        strcpy(obj, "    ");
        if (space_get_light(space) == TRUE)
        {

          for (i = 0, n_obj = 0; i < MAX_OBJECTS && game_get_object(game, i) != NULL; i++)
          {
            /*printf("\n[DEBUG]: 2-[Object is null? %d] [Object id: %ld] [Object name: %s]\n\n\n", game->objects[i] == NULL, object_get_id(game->objects[i]), object_get_name(game->objects[i]));*/
            if (game_get_object_location(game, object_get_id(game_get_object(game, i))) == id_east && object_get_hidden(game_get_object(game, i)) == FALSE)
            {
              obj_in_space_char[n_obj] = object_get_name(game_get_object(game, i));
              n_obj++;
            }
          }
          strcpy(gdesc[0], space_get_gdesc_row(game_get_space(game, id_east), 3));
          strcpy(gdesc[1], space_get_gdesc_row(game_get_space(game, id_east), 4));
          strcpy(gdesc[2], space_get_gdesc_row(game_get_space(game, id_east), 5));
        }
        else
        {
          strcpy(gdesc[0], "         ");
          strcpy(gdesc[1], "         ");
          strcpy(gdesc[2], "         ");
        }

        sprintf(str, " |%s", gdesc[0]);
        screen_area_puts(ge->map_east, str);
        sprintf(str, " |%s", gdesc[1]);
        screen_area_puts(ge->map_east, str);
        sprintf(str, " |%s", gdesc[2]);
        screen_area_puts(ge->map_east, str);
        switch (n_obj)
        {
        case 0:
          sprintf(str, " |        ");
          break;
        case 1:
          sprintf(str, " |%s", obj_in_space_char[0]);
          break;
        case 2:
          sprintf(str, " |%s %s", obj_in_space_char[0], obj_in_space_char[1]);
          break;
        case 3:
          sprintf(str, " |%s %s", obj_in_space_char[0], obj_in_space_char[1]);
          break;
        case 4:
          sprintf(str, " |%s %s", obj_in_space_char[0], obj_in_space_char[1]);
          break;
        default:
          sprintf(str, " |");
          break;
        }
        screen_area_puts(ge->map_east, str);
        sprintf(str, " +---------");
        screen_area_puts(ge->map_east, str);
      }
      else
      {
        sprintf(str, " ");
        screen_area_puts(ge->map_east, str);
        sprintf(str, " ");
        screen_area_puts(ge->map_east, str);
        sprintf(str, " ");
        screen_area_puts(ge->map_east, str);
        sprintf(str, " ");
        screen_area_puts(ge->map_east, str);
        sprintf(str, " ");
        screen_area_puts(ge->map_east, str);
      }
    }
  }

  for (i = 0; i < MAX_SPACES && game_get_space_from_index(game, i); i++)
  {
    if (space_get_id(game_get_space_from_index(game, i)) == id_act)
    {
      space = game_get_space_from_index(game, i);
    }
  }
  strcpy(obj, "    ");
  if (space_get_light(space) == TRUE || game_player_can_illuminate(game) == TRUE)
  {
    for (i = 0, n_obj = 0; i < MAX_OBJECTS && game_get_object(game, i) != NULL; i++)
    {
      /*printf("\n[DEBUG]: 2-[Object is null? %d] [Object id: %ld] [Object name: %s]\n\n\n", game->objects[i] == NULL, object_get_id(game->objects[i]), object_get_name(game->objects[i]));*/
      if (game_get_object_location(game, object_get_id(game_get_object(game, i))) == id_act && object_get_hidden(game_get_object(game, i)) == FALSE)
      {
        obj_in_space_char[n_obj] = object_get_name(game_get_object(game, i));
        n_obj++;
      }
    }
    for (i = 0; i < MAX_ENEMIES && game_get_enemy(game, i) != NULL; i++)
    {
      if (enemy_get_location(game_get_enemy(game, i)) == id_act && (enemy_get_health(game_get_enemy(game, i)) > 0))
      {
        strcpy(enemy, "(@_@)");
        break;
      }
      else
      {
        strcpy(enemy, "      ");
      }
    }
    strcpy(gdesc[0], space_get_gdesc_row(game_get_space(game, id_act), 1));
    strcpy(gdesc[1], space_get_gdesc_row(game_get_space(game, id_act), 2));
    strcpy(gdesc[2], space_get_gdesc_row(game_get_space(game, id_act), 3));
    strcpy(gdesc[3], space_get_gdesc_row(game_get_space(game, id_act), 4));
    strcpy(gdesc[4], space_get_gdesc_row(game_get_space(game, id_act), 5));
  }
  else
  {
    strcpy(enemy, "      ");
    strcpy(gdesc[0], "         ");
    strcpy(gdesc[1], "         ");
    strcpy(gdesc[2], "         ");
    strcpy(gdesc[3], "         ");
    strcpy(gdesc[4], "         ");
  }

  if (game_link_exists(game, id_act, W) == TRUE)
  {
    left = '<';
  }
  else
  {
    left = ' ';
  }

  if (game_link_exists(game, id_act, E) == TRUE)
  {
    right = '>';
  }
  else
  {
    right = ' ';
  }

  if (game_link_exists(game, id_act, U) == TRUE)
  {
    up_arrow = '^';
    up = '|';
  }
  else
  {
    up_arrow = ' ';
    up = ' ';
  }

  if (game_link_exists(game, id_act, D) == TRUE)
  {
    down_arrow = 'V';
    down = '|';
  }
  else
  {
    down_arrow = ' ';
    down = ' ';
  }

  if (id_act != NO_ID)
  {
    if (game_link_exists(game, id_act, N) == FALSE)
    {
      sprintf(str, " ");
      screen_area_puts(ge->map, str);
    }
    sprintf(str, "  +---------------+");
    screen_area_puts(ge->map, str);
    sprintf(str, "  | 0_0 %s %2d|", enemy, (int)id_act);
    screen_area_puts(ge->map, str);
    sprintf(str, "  |%s      |", gdesc[0]);
    screen_area_puts(ge->map, str);
    sprintf(str, "  |%s  %c %c |", gdesc[1], up_arrow, down);
    screen_area_puts(ge->map, str);
    sprintf(str, "  |%s  %c %c |", gdesc[2], up, down);
    screen_area_puts(ge->map, str);
    sprintf(str, "  |%s  %c %c |", gdesc[3], up, down_arrow);
    screen_area_puts(ge->map, str);
    sprintf(str, "%c |%s      | %c", left, gdesc[4], right);
    screen_area_puts(ge->map, str);
    switch (n_obj)
    {
    case 0:
      sprintf(str, "  |               |");
      break;
    case 1:
      sprintf(str, "  |%s          |", obj_in_space_char[0]);
      break;
    case 2:
      sprintf(str, "  |%s %s    |", obj_in_space_char[0], obj_in_space_char[1]);
      break;
    case 3:
      sprintf(str, "  |%s %s... |", obj_in_space_char[0], obj_in_space_char[1]);
      break;
    case 4:
      sprintf(str, "  |%s %s... |", obj_in_space_char[0], obj_in_space_char[1]);
      break;
    default:
      sprintf(str, "  |               |");
      break;
    }
    screen_area_puts(ge->map, str);
    sprintf(str, "  +---------------+");
    screen_area_puts(ge->map, str);

    /*WEST*/

    id_west = game_get_connection(game, id_act, W);
    if (id_west != NO_ID)
    {

      for (i = 0; i < MAX_SPACES && game_get_space_from_index(game, i); i++)
      {
        if (space_get_id(game_get_space_from_index(game, i)) == id_west)
        {
          space = game_get_space_from_index(game, i);
        }
      }
      strcpy(obj, "    ");
      if (space_get_light(space) == TRUE)
      {
        for (i = 0, n_obj = 0; i < MAX_OBJECTS && game_get_object(game, i) != NULL; i++)
        {
          /*printf("\n[DEBUG]: 2-[Object is null? %d] [Object id: %ld] [Object name: %s]\n\n\n", game->objects[i] == NULL, object_get_id(game->objects[i]), object_get_name(game->objects[i]));*/
          if (game_get_object_location(game, object_get_id(game_get_object(game, i))) == id_west && object_get_hidden(game_get_object(game, i)) == FALSE)
          {
            obj_in_space_char[n_obj] = object_get_name(game_get_object(game, i));
            n_obj++;
          }
        }
      }

      if (game_link_exists(game, id_west, N) == TRUE)
      {
        north = '^';
      }
      else
      {
        north = ' ';
      }

      if (game_link_exists(game, id_west, S) == TRUE)
      {
        south = 'V';
      }
      else
      {
        south = ' ';
      }

      if (game_link_exists(game, id_west, U) == TRUE)
      {
        up_arrow = '^';
        up = '|';
      }
      else
      {
        up_arrow = ' ';
        up = ' ';
      }

      if (game_link_exists(game, id_west, D) == TRUE)
      {
        up_arrow = 'V';
        up = '|';
      }
      else
      {
        up_arrow = ' ';
        up = ' ';
      }
      sprintf(str, "   %c", north);
      screen_area_puts(ge->map_west, str);
      sprintf(str, "--------+");
      screen_area_puts(ge->map_west, str);
      sprintf(str, "     %2d|", (int)id_west);
      screen_area_puts(ge->map_west, str);
      sprintf(str, "        |");
      screen_area_puts(ge->map_west, str);
      sprintf(str, "        |");
      screen_area_puts(ge->map_west, str);
      sprintf(str, "        |");
      screen_area_puts(ge->map_west, str);
      sprintf(str, "        |");
      screen_area_puts(ge->map_west, str);
      sprintf(str, "        |");
      screen_area_puts(ge->map_west, str);

      switch (n_obj)
      {
      case 0:
        sprintf(str, "       |");
        break;
      case 1:
        sprintf(str, "  %s |", obj_in_space_char[0]);
        break;
      case 2:
        sprintf(str, "%s..|", obj_in_space_char[0]);
        break;
      case 3:
        sprintf(str, "%s..|", obj_in_space_char[0]);
        break;
      case 4:
        sprintf(str, "%s..|", obj_in_space_char[0]);
        break;
      default:
        sprintf(str, "       |");
        break;
      }
      screen_area_puts(ge->map_west, str);
      sprintf(str, "--------+");
      screen_area_puts(ge->map_west, str);
      sprintf(str, "   %c", south);
      screen_area_puts(ge->map_west, str);
    }
    else
    {
      sprintf(str, " ");
      screen_area_puts(ge->map_west, str);
      sprintf(str, " ");
      screen_area_puts(ge->map_west, str);
      sprintf(str, " ");
      screen_area_puts(ge->map_west, str);
      sprintf(str, " ");
      screen_area_puts(ge->map_west, str);
      sprintf(str, " ");
      screen_area_puts(ge->map_west, str);
      sprintf(str, " ");
      screen_area_puts(ge->map_west, str);
      sprintf(str, " ");
      screen_area_puts(ge->map_west, str);
      sprintf(str, " ");
      screen_area_puts(ge->map_west, str);
      sprintf(str, " ");
      screen_area_puts(ge->map_west, str);
      sprintf(str, " ");
      screen_area_puts(ge->map_west, str);
      sprintf(str, " ");
      screen_area_puts(ge->map_west, str);
    }

    /*EAST*/

    id_east = game_get_connection(game, id_act, E);
    if (id_east != NO_ID)
    {

      for (i = 0; i < MAX_SPACES && game_get_space_from_index(game, i); i++)
      {
        if (space_get_id(game_get_space_from_index(game, i)) == id_east)
        {
          space = game_get_space_from_index(game, i);
        }
      }
      strcpy(obj, "    ");
      if (space_get_light(space) == TRUE)
      {
        for (i = 0, n_obj = 0; i < MAX_OBJECTS && game_get_object(game, i) != NULL; i++)
        {
          /*printf("\n[DEBUG]: 2-[Object is null? %d] [Object id: %ld] [Object name: %s]\n\n\n", game->objects[i] == NULL, object_get_id(game->objects[i]), object_get_name(game->objects[i]));*/
          if (game_get_object_location(game, object_get_id(game_get_object(game, i))) == id_east && object_get_hidden(game_get_object(game, i)) == FALSE)
          {
            obj_in_space_char[n_obj] = object_get_name(game_get_object(game, i));
            n_obj++;
          }
        }
        for (i = 0; i < MAX_ENEMIES && game_get_enemy(game, i) != NULL; i++)
        {
          if (enemy_get_location(game_get_enemy(game, i)) == id_east && (enemy_get_health(game_get_enemy(game, i)) > 0))
          {
            strcpy(enemy, "(@_@)");
            break;
          }
          else
          {
            strcpy(enemy, "      ");
          }
        }
        strcpy(gdesc[0], space_get_gdesc_row(game_get_space(game, id_east), 1));
        strcpy(gdesc[1], space_get_gdesc_row(game_get_space(game, id_east), 2));
        strcpy(gdesc[2], space_get_gdesc_row(game_get_space(game, id_east), 3));
        strcpy(gdesc[3], space_get_gdesc_row(game_get_space(game, id_east), 4));
        strcpy(gdesc[4], space_get_gdesc_row(game_get_space(game, id_east), 5));
      }
      else
      {
        strcpy(enemy, "      ");
        strcpy(gdesc[0], "         ");
        strcpy(gdesc[1], "         ");
        strcpy(gdesc[2], "         ");
        strcpy(gdesc[3], "         ");
        strcpy(gdesc[4], "         ");
      }

      if (game_link_exists(game, id_east, N) == TRUE)
      {
        north = '^';
      }
      else
      {
        north = ' ';
      }

      if (game_link_exists(game, id_east, S) == TRUE)
      {
        south = 'V';
      }
      else
      {
        south = ' ';
      }

      sprintf(str, "      %c", north);
      screen_area_puts(ge->map_east, str);
      sprintf(str, " +----------");
      screen_area_puts(ge->map_east, str);
      sprintf(str, " |  %s   ", enemy);
      screen_area_puts(ge->map_east, str);
      sprintf(str, " |%s", gdesc[0]);
      screen_area_puts(ge->map_east, str);
      sprintf(str, " |%s", gdesc[1]);
      screen_area_puts(ge->map_east, str);
      sprintf(str, " |%s", gdesc[2]);
      screen_area_puts(ge->map_east, str);
      sprintf(str, " |%s", gdesc[3]);
      screen_area_puts(ge->map_east, str);
      sprintf(str, " |%s", gdesc[4]);
      screen_area_puts(ge->map_east, str);
      switch (n_obj)
      {
      case 0:
        sprintf(str, " | ");
        break;
      case 1:
        sprintf(str, " |%s", obj_in_space_char[0]);
        break;
      case 2:
        sprintf(str, " |%s %s", obj_in_space_char[0], obj_in_space_char[1]);
        break;
      case 3:
        sprintf(str, " |%s %s", obj_in_space_char[0], obj_in_space_char[1]);
        break;
      case 4:
        sprintf(str, " |%s %s", obj_in_space_char[0], obj_in_space_char[1]);
        break;
      default:
        sprintf(str, " |");
        break;
      }
      screen_area_puts(ge->map_east, str);
      sprintf(str, " +---------");
      screen_area_puts(ge->map_east, str);
      sprintf(str, "      %c", south);
      screen_area_puts(ge->map_east, str);
    }
    else
    {
      sprintf(str, " ");
      screen_area_puts(ge->map_east, str);
      sprintf(str, " ");
      screen_area_puts(ge->map_east, str);
      sprintf(str, " ");
      screen_area_puts(ge->map_east, str);
      sprintf(str, " ");
      screen_area_puts(ge->map_east, str);
      sprintf(str, " ");
      screen_area_puts(ge->map_east, str);
      sprintf(str, " ");
      screen_area_puts(ge->map_east, str);
      sprintf(str, " ");
      screen_area_puts(ge->map_east, str);
      sprintf(str, " ");
      screen_area_puts(ge->map_east, str);
      sprintf(str, " ");
      screen_area_puts(ge->map_east, str);
      sprintf(str, " ");
      screen_area_puts(ge->map_east, str);
      sprintf(str, " ");
      screen_area_puts(ge->map_east, str);
    }
  }

  strcpy(obj, "    ");

  for (i = 0; i < MAX_SPACES && game_get_space_from_index(game, i); i++)
  {
    if (space_get_id(game_get_space_from_index(game, i)) == id_next)
    {
      space = game_get_space_from_index(game, i);
    }
  }

  if (game_link_exists(game, id_next, W) == TRUE)
  {
    left = '<';
  }
  else
  {
    left = ' ';
  }

  if (game_link_exists(game, id_next, E) == TRUE)
  {
    right = '>';
  }
  else
  {
    right = ' ';
  }

  if (game_link_exists(game, id_act, U) == TRUE)
  {
    up_arrow = '^';
    up = '|';
  }
  else
  {
    up_arrow = ' ';
    up = ' ';
  }

  if (game_link_exists(game, id_act, D) == TRUE)
  {
    down_arrow = 'V';
    down = '|';
  }
  else
  {
    down_arrow = ' ';
    down = ' ';
  }

  if (id_next != NO_ID)
  {
    if (space_get_light(space) == TRUE)
    {
      for (i = 0, n_obj = 0; i < MAX_OBJECTS && game_get_object(game, i) != NULL; i++)
      {
        /*printf("\n[DEBUG]: 2-[Object is null? %d] [Object id: %ld] [Object name: %s]\n\n\n", game->objects[i] == NULL, object_get_id(game->objects[i]), object_get_name(game->objects[i]));*/
        if (game_get_object_location(game, object_get_id(game_get_object(game, i))) == id_next && object_get_hidden(game_get_object(game, i)) == FALSE)
        {
          obj_in_space_char[n_obj] = object_get_name(game_get_object(game, i));
          n_obj++;
        }
      }
      for (i = 0; i < MAX_ENEMIES && game_get_enemy(game, i) != NULL; i++)
      {
        if (enemy_get_location(game_get_enemy(game, i)) == id_next && (enemy_get_health(game_get_enemy(game, i)) > 0))
        {
          strcpy(enemy, "(@_@)");
          break;
        }
        else
        {
          strcpy(enemy, "      ");
        }
      }
      strcpy(gdesc[0], space_get_gdesc_row(game_get_space(game, id_next), 1));
      strcpy(gdesc[1], space_get_gdesc_row(game_get_space(game, id_next), 2));
      strcpy(gdesc[2], space_get_gdesc_row(game_get_space(game, id_next), 3));
      strcpy(gdesc[3], space_get_gdesc_row(game_get_space(game, id_next), 4));
      strcpy(gdesc[4], space_get_gdesc_row(game_get_space(game, id_next), 5));
    }
    else
    {
      strcpy(enemy, "      ");
      strcpy(gdesc[0], "         ");
      strcpy(gdesc[1], "         ");
      strcpy(gdesc[2], "         ");
      strcpy(gdesc[3], "         ");
      strcpy(gdesc[4], "         ");
    }
    if (game_link_exists(game, id_act, S) == TRUE)
    {
      sprintf(str, "          v");
    }
    else
    {
      sprintf(str, "           ");
    }
    screen_area_puts(ge->map, str);
    sprintf(str, "  +---------------+");
    screen_area_puts(ge->map, str);
    sprintf(str, "  |  %s    %2d|", enemy, (int)id_next);
    screen_area_puts(ge->map, str);
    sprintf(str, "  |%s      |", gdesc[0]);
    screen_area_puts(ge->map, str);
    sprintf(str, "  |%s      |", gdesc[1]);
    screen_area_puts(ge->map, str);
    sprintf(str, "  |%s      |", gdesc[2]);
    screen_area_puts(ge->map, str);
    sprintf(str, "  |%s      |", gdesc[3]);
    screen_area_puts(ge->map, str);
    sprintf(str, "%c |%s      | %c", left, gdesc[4], right);
    screen_area_puts(ge->map, str);
    switch (n_obj)
    {
    case 0:
      sprintf(str, "  |               |");
      break;
    case 1:
      sprintf(str, "  |%s     |", obj_in_space_char[0]);
      break;
    case 2:
      sprintf(str, "  |%s %s   |", obj_in_space_char[0], obj_in_space_char[1]);
      break;
    case 3:
      sprintf(str, "  |%s %s...|", obj_in_space_char[0], obj_in_space_char[1]);
      break;
    case 4:
      sprintf(str, "  |%s %s...|", obj_in_space_char[0], obj_in_space_char[1]);
      break;
    default:
      sprintf(str, "  |               |");
      break;
    }
    screen_area_puts(ge->map, str);

    /*WEST*/

    id_west = game_get_connection(game, id_next, W);
    if (id_west == NO_ID)
    {
      id_west = game_get_connection(game, game_get_connection(game, id_act, W), S);
    }
    if (id_west != NO_ID)
    {
      for (i = 0; i < MAX_SPACES && game_get_space_from_index(game, i); i++)
      {
        if (space_get_id(game_get_space_from_index(game, i)) == id_west)
        {
          space = game_get_space_from_index(game, i);
        }
      }
      strcpy(obj, "    ");
      if (space_get_light(space) == TRUE)
      {
        for (i = 0, n_obj = 0; i < MAX_OBJECTS && game_get_object(game, i) != NULL; i++)
        {
          /*printf("\n[DEBUG]: 2-[Object is null? %d] [Object id: %ld] [Object name: %s]\n\n\n", game->objects[i] == NULL, object_get_id(game->objects[i]), object_get_name(game->objects[i]));*/
          if (game_get_object_location(game, object_get_id(game_get_object(game, i))) == id_west && object_get_hidden(game_get_object(game, i)) == FALSE)
          {
            obj_in_space_char[n_obj] = object_get_name(game_get_object(game, i));
            n_obj++;
          }
        }
      }

      sprintf(str, "--------+");
      screen_area_puts(ge->map_west, str);
      sprintf(str, "     %2d|", (int)id_west);
      screen_area_puts(ge->map_west, str);
      sprintf(str, "        |");
      screen_area_puts(ge->map_west, str);
      sprintf(str, "        |");
      screen_area_puts(ge->map_west, str);
      sprintf(str, "        |");
      screen_area_puts(ge->map_west, str);
      sprintf(str, "        |");
      screen_area_puts(ge->map_west, str);
      sprintf(str, "        |");
      screen_area_puts(ge->map_west, str);
      switch (n_obj)
      {
      case 0:
        sprintf(str, "       |");
        break;
      case 1:
        sprintf(str, "  %s |", obj_in_space_char[0]);
        break;
      case 2:
        sprintf(str, "%s..|", obj_in_space_char[0]);
        break;
      case 3:
        sprintf(str, "%s..|", obj_in_space_char[0]);
        break;
      case 4:
        sprintf(str, "%s..|", obj_in_space_char[0]);
        break;
      default:
        sprintf(str, "       |");
        break;
      }
      screen_area_puts(ge->map_west, str);
    }
    /*EAST*/

    id_east = game_get_connection(game, id_next, E);
    if (id_east == NO_ID)
    {
      id_east = game_get_connection(game, game_get_connection(game, id_act, E), S);
    }
    if (id_east != NO_ID)
    {
      strcpy(obj, "    ");

      for (i = 0; i < MAX_SPACES && game_get_space_from_index(game, i); i++)
      {
        if (space_get_id(game_get_space_from_index(game, i)) == id_east)
        {
          space = game_get_space_from_index(game, i);
        }
      }

      if (space_get_light(space) == TRUE)
      {
        for (i = 0, n_obj = 0; i < MAX_OBJECTS && game_get_object(game, i) != NULL; i++)
        {
          /*printf("\n[DEBUG]: 2-[Object is null? %d] [Object id: %ld] [Object name: %s]\n\n\n", game->objects[i] == NULL, object_get_id(game->objects[i]), object_get_name(game->objects[i]));*/
          if (game_get_object_location(game, object_get_id(game_get_object(game, i))) == id_east && object_get_hidden(game_get_object(game, i)) == FALSE)
          {
            obj_in_space_char[n_obj] = object_get_name(game_get_object(game, i));
            n_obj++;
          }
        }
        for (i = 0; i < MAX_ENEMIES && game_get_enemy(game, i) != NULL; i++)
        {
          if (enemy_get_location(game_get_enemy(game, i)) == id_east && (enemy_get_health(game_get_enemy(game, i)) > 0))
          {
            strcpy(enemy, "(@_@)");
            break;
          }
          else
          {
            strcpy(enemy, "      ");
          }
        }
        strcpy(gdesc[0], space_get_gdesc_row(game_get_space(game, id_east), 1));
        strcpy(gdesc[1], space_get_gdesc_row(game_get_space(game, id_east), 2));
        strcpy(gdesc[2], space_get_gdesc_row(game_get_space(game, id_east), 3));
        strcpy(gdesc[3], space_get_gdesc_row(game_get_space(game, id_east), 4));
        strcpy(gdesc[4], space_get_gdesc_row(game_get_space(game, id_east), 5));
      }
      else
      {
        strcpy(enemy, "      ");
        strcpy(gdesc[0], "         ");
        strcpy(gdesc[1], "         ");
        strcpy(gdesc[2], "         ");
        strcpy(gdesc[3], "         ");
        strcpy(gdesc[4], "         ");
      }

      sprintf(str, " +----------");
      screen_area_puts(ge->map_east, str);
      sprintf(str, " |  %s   ", enemy);
      screen_area_puts(ge->map_east, str);
      sprintf(str, " |%s", gdesc[0]);
      screen_area_puts(ge->map_east, str);
      sprintf(str, " |%s", gdesc[1]);
      screen_area_puts(ge->map_east, str);
      sprintf(str, " |%s", gdesc[2]);
      screen_area_puts(ge->map_east, str);
      sprintf(str, " |%s", gdesc[3]);
      screen_area_puts(ge->map_east, str);
      sprintf(str, " |%s", gdesc[4]);
      screen_area_puts(ge->map_east, str);
      switch (n_obj)
      {
      case 0:
        sprintf(str, " |    ");
        break;
      case 1:
        sprintf(str, " |%s", obj_in_space_char[0]);
        break;
      case 2:
        sprintf(str, " |%s %s", obj_in_space_char[0], obj_in_space_char[1]);
        break;
      case 3:
        sprintf(str, " |%s %s", obj_in_space_char[0], obj_in_space_char[1]);
        break;
      case 4:
        sprintf(str, " |%s %s", obj_in_space_char[0], obj_in_space_char[1]);
        break;
      default:
        sprintf(str, " |  ");
        break;
      }
      screen_area_puts(ge->map_east, str);
    }
  }

  /* Paint in the description area */
  screen_area_clear(ge->descript);

  for (i = 0; i < MAX_SPACES && game_get_space_from_index(game, i); i++)
  {
    if (space_get_id(game_get_space_from_index(game, i)) == id_act)
    {
      space = game_get_space_from_index(game, i);
    }
  }

  sprintf(str, "  Objetos en el espacio %ld:", game_get_player_location(game));
  screen_area_puts(ge->descript, str);

  if (space_get_light(space) == TRUE || game_player_can_illuminate(game) == TRUE)
  {
    for (i = 0; i < MAX_OBJECTS && game_get_object(game, i) != NULL; i++)
    {

      /*printf("\n[DEBUG]: 4-[Object is null? %d] [Object id: %ld] [Object name: %s]\n\n\n", game->objects[i] == NULL, object_get_id(game->objects[i]), object_get_name(game->objects[i]));*/
      obj_loc = game_get_object_location(game, object_get_id(game_get_object(game, i)));
      if (obj_loc == game_get_player_location(game) && object_get_id(game_get_object(game, i)) < 100 && object_get_hidden(game_get_object(game, i)) == FALSE) /*Objs with id over 100 are NPCS*/
      {
        sprintf(str, "   %s", object_get_name(game_get_object(game, i)));

        screen_area_puts(ge->descript, str);
      }
    }
  }

  sprintf(str, "  NPCs en el espacio %ld:", game_get_player_location(game));
  screen_area_puts(ge->descript, str);

  for (i = 0; i < MAX_OBJECTS && game_get_object(game, i) != NULL; i++)
  {

    /*printf("\n[DEBUG]: 4-[Object is null? %d] [Object id: %ld] [Object name: %s]\n\n\n", game->objects[i] == NULL, object_get_id(game->objects[i]), object_get_name(game->objects[i]));*/
    obj_loc = game_get_object_location(game, object_get_id(game_get_object(game, i)));
    if (obj_loc == game_get_player_location(game) && object_get_id(game_get_object(game, i)) >= 100 && object_get_hidden(game_get_object(game, i)) == FALSE) /*Objs with id over 100 are NPCS*/
    {
      sprintf(str, "   %s", object_get_name(game_get_object(game, i)));

      screen_area_puts(ge->descript, str);
    }
  }

  sprintf(str, " ");
  screen_area_puts(ge->descript, str);

  player_loc = player_get_location(game_get_player(game));
  if (player_loc)
  {
    sprintf(str, "  Localizacion: %d", (int)player_loc);
    screen_area_puts(ge->descript, str);
  }

  health = player_get_health(game_get_player(game));
  if (health)
  {
    sprintf(str, "  Salud: %d", health);
    screen_area_puts(ge->descript, str);
  }

  power = player_get_power(game_get_player(game));
  if (power)
  {
    sprintf(str, "  Poder: %d", power);
    screen_area_puts(ge->descript, str);
  }

  sprintf(str, "  Inventario: ");
  screen_area_puts(ge->descript, str);
  player_objects = player_get_objects(game_get_player(game));
  if (player_get_n_objects(game_get_player(game)) == 0)
  {
    sprintf(str, "   Nada");
    screen_area_puts(ge->descript, str);
  }
  else
  {
    for (i = 0; i < inventory_get_n_objects(player_get_inventory(game_get_player(game))); i++)
    {
      if (player_objects[i] != NO_ID)
      {
        sprintf(str, "   %s", game_object_id_to_name(game, player_objects[i]));
        screen_area_puts(ge->descript, str);
      }
    }
  }

  if (space_get_light(space) == TRUE || game_player_can_illuminate(game) == TRUE)
  {
    sprintf(str, " ");
    screen_area_puts(ge->descript, str);
    sprintf(str, "  %s: %s ", game_get_space_name(game, player_loc), game_get_space_description(game, player_loc));
    screen_area_puts(ge->descript, str);
  }
  
  sprintf(str, " ");
  screen_area_puts(ge->descript, str);

  sprintf(str, "  Enemigos:");
  screen_area_puts(ge->descript, str);

  for (i = 0; game_get_enemy(game, i) != NULL; i++)
  {
    if (game_get_enemy_location(game, i) == player_loc)
    {
      health = game_get_enemy_health(game, i);
      if (health)
      {
        sprintf(str, "   %s: %d", enemy_get_name(game_get_enemy(game, i)), health);
        screen_area_puts(ge->descript, str);
      }
    }
  }

  sprintf(str, " ");
  screen_area_puts(ge->descript, str);
  sprintf(str, "  Descripciones:");
  screen_area_puts(ge->descript, str);
  for (i = 0; i < game_get_n_descriptions(game); i++)
  {
    desc = game_get_description(game, i);
    if (desc != NULL)
    {
      sprintf(str, "  %s", desc);
      screen_area_puts(ge->descript, str);
    }
  }

  /* Paint in the banner area */
  screen_area_puts(ge->banner, "   Escapar de la EPS ");

  /* Paint in the help area */
  screen_area_clear(ge->help);
  sprintf(str, " Puedes usar:");
  screen_area_puts(ge->help, str);
  sprintf(str, "     move o m, take o t, drop o d, attack o a, inspect o i, turnon o n, turnoff o f, open u o, save o s,         load o l, exit o e.");
  screen_area_puts(ge->help, str);

  /* Paint in the feedback area */
  last_cmd = game_get_last_command(game);
  dialogue = game_get_dialogue_command_result(game);

  sprintf(str, " %s (%s): %s", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS], dialogue);

  screen_area_puts(ge->feedback, str);

  /* Dump to the terminal */
  screen_paint();
  printf("prompt:> ");
}
