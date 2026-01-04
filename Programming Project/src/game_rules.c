/** 
 * @brief It implements the game rules
 * @file game_rules.c
 * @author Jorge Jiménez
 * @version 1.0
 * @date 27-03-2023 
 * @copyright GNU Public License
 */
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "command.h"
#include "types.h"
#include "game_rules.h"
#include "set.h"

/** game_rules_rule_1_condition checks the first rule condition
  */
BOOL game_rules_rule_1_condition(Game *game);
/** game_rules_rule_1 your laptop is stolen if you enter cafetería
  */
void game_rules_rule_1(Game *game);
/** game_rules_rule_2_condition checks the second rule condition
  */
BOOL game_rules_rule_2_condition();
/** game_rules_rule_2 the psychologist moves randomly
  */
void game_rules_rule_2(Game *game);
/** game_rules_rule_3_condition checks the third rule condition
  */
BOOL game_rules_rule_3_condition(Game *game);
/** game_rules_rule_3 Sr. Valgrind appears if you take asistencia
  */
void game_rules_rule_3(Game *game);
/** game_rules_rule_4_condition checks the fourth rule condition
  */
BOOL game_rules_rule_4_condition(Game *game);
/** game_rules_rule_4 A linuxmafioso appears where you are looking for help, link to sede linuxmafia is opened, 
  * the dialogue of the linm.1 is changed, and Bill Gates appears there
  */
void game_rules_rule_4(Game *game);
/** game_rules_rule_5_condition checks the fifth rule condition
  */
BOOL game_rules_rule_5_condition(Game *game);
/** game_rules_rule_5 moves the linux maf. that is looking 
  * for help to the player's space if Bill Gates hasn't been defeated
  */
void game_rules_rule_5(Game *game);
/** game_rules_rule_6_condition checks the sixth rule condition
  */
BOOL game_rules_rule_6_condition(Game *game);
/** game_rules_rule_6 Changes linm.1 and linm.2 dialogue after defeating bill gates
  */
void game_rules_rule_6(Game *game);
/** game_rules_rule_7_condition checks the seventh rule condition
  */
BOOL game_rules_rule_7_condition(Game *game, char *aditional_info);
/** game_rules_rule_7 Spawns cepo after defeating 
  * Bill Gates and talking with the linuxm.2
  */
void game_rules_rule_7(Game *game);
/** game_rules_rule_8_condition checks the eighth rule condition
  */
BOOL game_rules_rule_8_condition(Game *game);
/** game_rules_rule_8 Makes the girl in the third floor always ran away from you
  */
void game_rules_rule_8(Game *game);
/** game_rules_rule_9_condition checks the nineth rule condition
  */
BOOL game_rules_rule_9_condition(Game *game);
/** game_rules_rule_9 Makes the girl get trapped if she 
  * is in the same room as the cepo
  */
void game_rules_rule_9(Game *game);
/** game_rules_rule_10_condition checks the tenth rule condition
  */
BOOL game_rules_rule_10_condition(Game *game);
/** game_rules_rule_10 Eliminates the unconcius girl and opens a secret tunnel, giving you the title
  */
void game_rules_rule_10(Game *game);
/** game_rules_rule_11_condition checks the eleventh rule condition
  */
BOOL game_rules_rule_11_condition(Game *game);
/** game_rules_rule_11 Gives the matricula to the player if bosses were defeated
  */
void game_rules_rule_11(Game *game);
/** game_rules_rule_12_condition checks the twelveth rule condition
  */
BOOL game_rules_rule_12_condition(Game *game);
/** game_rules_rule_12 Substitutes the demente with the programmer if man.py. is in the celda
  */
void game_rules_rule_12(Game *game);
/** game_rules_rule_13_condition checks the thirteenth rule condition
  */
BOOL game_rules_rule_13_condition(Game *game);
/** game_rules_rule_13 Ends the game if player reaches calle atrás
  */
void game_rules_rule_13(Game *game);
/** game_rules_rule_14_condition checks the fourteenth rule condition
  */
BOOL game_rules_rule_14_condition(Game *game);
/** game_rules_rule_14 Ends the game if player reaches entrada EPS
  */
void game_rules_rule_14(Game *game);

/** game_rules_run runs the game rules of the game 
  */
STATUS game_rules_run(Game *game, char *aditional_info){
    /*Error control*/
    if(!game || !aditional_info){
        return ERROR;
    }

    /*Game rules*/
    if(game_rules_rule_1_condition(game)){
        game_rules_rule_1(game);
    }

    if(game_rules_rule_2_condition()){
        game_rules_rule_2(game);
    }

    if(game_rules_rule_3_condition(game)){
        game_rules_rule_3(game);
    }

    if(game_rules_rule_4_condition(game)){
        game_rules_rule_4(game);
    }

    if(game_rules_rule_5_condition(game)){
        game_rules_rule_5(game);
    }

    if(game_rules_rule_6_condition(game)){
        game_rules_rule_6(game);
    }

    if(game_rules_rule_7_condition(game, aditional_info)){
        game_rules_rule_7(game);
    }

    if(game_rules_rule_8_condition(game)){
        game_rules_rule_8(game);
    }

    if(game_rules_rule_9_condition(game)){
        game_rules_rule_9(game);
    }

    if(game_rules_rule_10_condition(game)){
        game_rules_rule_10(game);
    }

    if(game_rules_rule_11_condition(game)){
        game_rules_rule_11(game);
    }

    if(game_rules_rule_12_condition(game)){
        game_rules_rule_12(game);
    }

    if(game_rules_rule_13_condition(game)){
        game_rules_rule_13(game);
    }

    if(game_rules_rule_14_condition(game)){
        game_rules_rule_14(game);
    }

    return OK;
}

/** game_rules_rule_1_condition checks the first rule condition
  */
BOOL game_rules_rule_1_condition(Game *game){
    Inventory *inv = NULL;
    Id *ids = NULL;
    Object *obj;
    int n_obs = 0;
    int i;

    if(game_get_player_location(game) != 104){ /*104 is cafetería*/
        return FALSE;
    }

    inv = player_get_inventory(game_get_player(game));
    ids = inventory_get_objects(inv);
    n_obs = inventory_get_n_objects(inv);

    for (i = 0; i < n_obs; i++){
        obj = game_get_object_from_id(game, ids[i]);
        if(obj != NULL && object_get_id(obj) == 1){
            return TRUE;
        }
    }

    return FALSE;
}

/** game_rules_rule_1 your laptop is stolen if you enter cafetería
  */
void game_rules_rule_1(Game *game){
    Inventory *inv = player_get_inventory(game_get_player(game));
    Id *ids = inventory_get_objects(inv);
    Object *obj;
    Space *space;
    int n_obs = inventory_get_n_objects(inv);
    int i;

    /*Remove the laptop from player's inventory*/
    for (i = 0; i < n_obs; i++)
    {
        obj = game_get_object_from_id(game, ids[i]);
        if(obj != NULL && object_get_id(obj) == 1){
            inventory_del_object(inv, ids[i]);
            break;
        }
    }

    /*Set laptop space to comedor*/
    space = game_get_space(game, 103);
    if(space != NULL){
        space_set_object(space, object_get_id(obj));
    }
}

/** game_rules_rule_2_condition checks the second rule condition
  */
BOOL game_rules_rule_2_condition(){
    return TRUE;
}

/** game_rules_rule_2 the psychologist moves randomly
  */
void game_rules_rule_2(Game *game){
    Object *psyc = NULL;
    Id location;
    int i;

    srand(time(NULL));

    if(rand()%3 != 0) return; /*The psyc doesnt move always*/

    /*Get the psyc obj*/
    for (i = 0; i < MAX_OBJECTS && game_get_object(game, i) != NULL; i++)
    {
        psyc = game_get_object(game, i);
        if(object_get_id(psyc) == 101){
            break;
        }
    }

    if(!psyc) return;

    location = game_get_object_location(game, object_get_id(psyc));
    if(location == NO_ID) return;

    /*Move the psyc*/
    if(rand() % 2 == 0 && game_get_connection(game, location, W) != NO_ID){
        space_unset_object(game_get_space(game, location), object_get_id(psyc));
        space_set_object(game_get_space(game, game_get_connection(game, location, W)) , object_get_id(psyc));
    }
    else if(game_get_connection(game, location, E) != NO_ID){
        space_unset_object(game_get_space(game, location), object_get_id(psyc));
        space_set_object(game_get_space(game, game_get_connection(game, location, E)) , object_get_id(psyc));
    }
}

/** game_rules_rule_3_condition checks the third rule condition
  */
BOOL game_rules_rule_3_condition(Game *game){
    Inventory *inv = NULL;
    Id *ids;
    Object *obj;
    int n_obs = 0;
    int i;

    if(game_get_player_location(game) != 105){
        return FALSE;
    }

    inv = player_get_inventory(game_get_player(game));
    ids = inventory_get_objects(inv);
    n_obs = inventory_get_n_objects(inv);

    for (i = 0; i < n_obs; i++){
        obj = game_get_object_from_id(game, ids[i]);
        if(obj != NULL && object_get_id(obj) == 2){
            return TRUE;
        }
    }
    
    return FALSE;
}

/** game_rules_rule_3 Sr. Valgrind appears if you take asistencia
  */
void game_rules_rule_3(Game *game){
    Inventory *inv = player_get_inventory(game_get_player(game));
    Enemy *sr_valgrind = NULL;
    Id *ids = inventory_get_objects(inv);
    Object *obj;
    int n_obs = inventory_get_n_objects(inv);
    int i;

    for (i = 0; i < n_obs; i++)
    {
        obj = game_get_object_from_id(game, ids[i]);
        if(obj != NULL && object_get_id(obj) == 2){
            inventory_del_object(inv, ids[i]);
            break;
        }
    }

    for (i = 0; i < MAX_ENEMIES && game_get_enemy(game, i) != NULL; i++)
    {
        if(enemy_get_id(game_get_enemy(game, i)) == 2){ /*Id 2 is Sr. Valgrind*/
            sr_valgrind = game_get_enemy(game, i);
        }
    }    

    enemy_set_location(sr_valgrind, 105);
}

/** game_rules_rule_4_condition checks the fourth rule condition
  */
BOOL game_rules_rule_4_condition(Game *game){
    if(game_get_connection_status(game, 109, N) == OPEN){ /*109 is sala extraña, previous to sede linuxmafia*/
        return FALSE;
    }

    srand(time(NULL));

    if(rand() % 12 == 0) return TRUE;
    else return FALSE;
}

/** game_rules_rule_4 A linuxmafioso appears where you are looking for help, link to sede linuxmafia is opened, 
  * the dialogue of the linm.1 is changed, and Bill Gates appears there
  */
void game_rules_rule_4(Game *game){
    Object *maf = NULL;
    Enemy *bill_gates = NULL;
    int i = 0;

    maf = game_get_object_from_id(game, 103); /*Id linux mafioso*/
    if(maf == NULL) return;

    space_unset_object(game_get_space(game, 999), 103);
    space_set_object(game_get_space(game, game_get_player_location(game)), 103);

    for (i = 0; i < MAX_LINKS && game_get_link_from_index(game, i) != NULL; i++)
    {
        if(link_get_origin(game_get_link_from_index(game, i)) == 109 && /*Id sala extraña*/
        link_get_destination(game_get_link_from_index(game, i)) == 110){ /*Id sede linuxmafia*/
            link_set_status(game_get_link_from_index(game, i), OPEN);
        }
    }

    for (i = 0; i < MAX_ENEMIES && game_get_enemy(game, i) != NULL; i++)
    {
        if(enemy_get_id(game_get_enemy(game, i)) == 4){ /*Id 4 is Bill Gates*/
            bill_gates = game_get_enemy(game, i);
        }
    }

    object_set_description(game_get_object_from_id(game, 102), "Linux mafioso 1: Debes ayudarnos a derrotarle! Yo no puedo enfrentarme a el porque mi entrenamiento de combate es open-source, por lo que podria predecirme!");

    enemy_set_location(bill_gates, 110);
}

/** game_rules_rule_5_condition checks the fifth rule condition
  */
BOOL game_rules_rule_5_condition(Game *game){
    int bill_health = 1;
    int i;

    if(game_get_connection_status(game, 109, N) == CLOSE){ /*109 is sala extraña, previous to sede linuxmafia*/
        return FALSE;
    }

    if(game_get_object_location(game, 103) == game_get_player_location(game)){
        return FALSE;
    }

    for (i = 0; i < MAX_ENEMIES && game_get_enemy(game, i) != NULL; i++)
    {
        if(enemy_get_id(game_get_enemy(game, i)) == 4){
            bill_health = enemy_get_health(game_get_enemy(game, i));
            break;
        }
    } 

    if(bill_health <= 0){
        return FALSE;
    }

    return TRUE;
}

/** game_rules_rule_5 moves the linux maf. that is looking 
  * for help to the player's space if Bill Gates hasn't been defeated
  */
void game_rules_rule_5(Game *game){
    space_unset_object( game_get_space(game, game_get_object_location(game, 103) ), 103);
    space_set_object( game_get_space(game, game_get_player_location(game) ), 103);
}

/** game_rules_rule_6_condition checks the sixth rule condition
  */
BOOL game_rules_rule_6_condition(Game *game){
    int bill_health = 1, i;

    if(game_get_connection_status(game, 109, N) == CLOSE){ /*109 is sala extraña, previous to sede linuxmafia*/
        return FALSE;
    }      

    for (i = 0; i < MAX_ENEMIES && game_get_enemy(game, i) != NULL; i++)
    {
        if(enemy_get_id(game_get_enemy(game, i)) == 4){
            bill_health = enemy_get_health(game_get_enemy(game, i));
            break;
        }
    } 

    if(bill_health > 0){
        return FALSE;
    }

    if(game_get_last_command(game) != ATTACK){
        return FALSE;
    }

    if(game_get_last_command_status(game) != OK){
        return FALSE;
    }

    return TRUE;
}

/** game_rules_rule_6 Changes linm.1 and linm.2 dialogue after defeating bill gates
  */
void game_rules_rule_6(Game *game){
    object_set_description(game_get_object_from_id(game, 102), "Linux mafioso 1: Gracias por salvar a la linuxmafia. Imagina un mundo sin linuxmafia: como podrian las tres personas que quieren instalar archlinux solicitar ayuda?");
    object_set_description(game_get_object_from_id(game, 103), "Linux mafioso 2: Gracias por derrotar a este tirano, que quiere cobrar por su trabajo. Toma este cepo, es open-source pero se cierra firmemente");
}

/** game_rules_rule_7_condition checks the seventh rule condition
  */
BOOL  game_rules_rule_7_condition(Game *game, char *aditional_info){
    int bill_health = 1, i;

    if(game_get_connection_status(game, 109, N) == CLOSE){ /*109 is sala extraña, previous to sede linuxmafia*/
        return FALSE;
    }      

    if(game_get_object_location(game, 103) != game_get_player_location(game)){
        return FALSE;
    }

    for (i = 0; i < MAX_ENEMIES && game_get_enemy(game, i) != NULL; i++)
    {
        if(enemy_get_id(game_get_enemy(game, i)) == 4){
            bill_health = enemy_get_health(game_get_enemy(game, i));
            break;
        }
    } 

    if(bill_health > 0){
        return FALSE;
    }

    if(game_get_last_command(game) != INSPECT){
        return FALSE;
    }

    if(strcmp(aditional_info, object_get_name(game_get_object_from_id(game, 103))) != 0){
        return FALSE;
    }

    if(game_get_object_location(game, 4) != 999){
        return FALSE;
    }

    if(game_get_object_location(game, 104) == 999){
        return FALSE;
    }

    return TRUE;
}

/** game_rules_rule_7 Spawns cepo after defeating 
  * Bill Gates and talking with the linuxm.2
  */
void game_rules_rule_7(Game *game){
    /*space_unset_object( game_get_space(game, game_get_object_location(game, 103) ), 103);*/ /*Removes linm.2*/
    object_set_description(game_get_object_from_id(game, 103), "Linux mafioso 2: Rezo a Linus Torvald para renacer como un nuevo ser compuesto de ODN, la alternativa open-source al ADN");

    space_unset_object(game_get_space(game, 999), 4); /*999 id of pool, 4 id of cepo*/
    space_set_object(game_get_space(game, 110), 4);
}

/** game_rules_rule_8_condition checks the eighth rule condition
  */
BOOL game_rules_rule_8_condition(Game *game){
    if(game_get_player_location(game) == game_get_object_location(game, 104)){ /*104 id chica*/
        return TRUE;
    }
    else{
        return FALSE;
    }
}

/** game_rules_rule_8 Makes the girl in the third floor always ran away from you
  */
void game_rules_rule_8(Game *game){
    DIRECTION available_dirs[6];
    DIRECTION dir = U;
    Id des_space_id = NO_ID;
    int n_available_dir = 0;
    int i;

    for (i = 0; i < 6; i++)
    {
        if(game_get_connection( game, game_get_object_location(game, 104), i) != NO_ID && 
        game_get_connection_status( game, game_get_object_location(game, 104), i) == OPEN){
            available_dirs[n_available_dir] = i;
            n_available_dir++;
        }
    }

    if(n_available_dir == 0) return;

    srand(time(NULL));

    for (i = n_available_dir; i > 0; i--)
    {
        if(rand() % i == 0){
            dir = available_dirs[i-1];
            break;
        }
    }
    
    if(dir == U){
        dir = available_dirs[0];
    }

    des_space_id = game_get_connection(game, game_get_object_location(game, 104), dir);

    space_unset_object( game_get_space(game, game_get_object_location(game, 104) ), 104);
    space_set_object( game_get_space(game, des_space_id), 104);
}

/** game_rules_rule_9_condition checks the nineth rule condition
  */
BOOL game_rules_rule_9_condition(Game *game){
    if(game_get_object_location(game, 104) == 999 || game_get_object_location(game, 104) != game_get_object_location(game, 4)){ /*104: chica, 4: cepo*/
        return FALSE;
    }

    return TRUE;
}

/** game_rules_rule_9 Makes the girl get trapped if she 
  * is in the same room as the cepo
  */
void game_rules_rule_9(Game *game){
    /*Put the unconcious girl where the girl was*/
    space_unset_object( game_get_space(game, 999), 105);
    space_set_object( game_get_space(game, game_get_object_location(game, 104)), 105);

    /*Remove the girl and the cepo*/
    space_unset_object( game_get_space(game, game_get_object_location(game, 104)) , 4);
    space_set_object(game_get_space(game, 999), 4);
    space_unset_object( game_get_space(game, game_get_object_location(game, 104)) , 104);
    space_set_object(game_get_space(game, 999), 104);
}

/** game_rules_rule_10_condition checks the tenth rule condition
  */
BOOL game_rules_rule_10_condition(Game *game){
    if(game_get_object_location(game, 105) != 001){ /*105: chica i. , 001: altar*/
        return FALSE;
    }

    return TRUE;
}

/** game_rules_rule_10 Eliminates the unconcius girl and opens a secret tunnel, giving you the title
  */
void game_rules_rule_10(Game *game){
    Link *link = NULL;

    space_unset_object( game_get_space(game, 001) , 105);
    space_set_object(game_get_space(game, 999), 105);

    if(game_get_object_location(game, 5) == 999){
        space_unset_object( game_get_space(game, 999) , 5);
        space_set_object( game_get_space(game, 001) , 5);
    }
    
    link = link_create(006);
    link_set_name(link, "Link006");
    link_set_status(link, OPEN);
    link_set_origin(link, 001); /*001: altar*/
    link_set_destination(link, 003); /*003: pasadizo*/
    link_set_direction(link, W);

    game_add_link(game, link);

    link = link_create(007);
    link_set_name(link, "Link007");
    link_set_status(link, OPEN);
    link_set_origin(link, 003);
    link_set_destination(link, 001);
    link_set_direction(link, E);

    game_add_link(game, link);
}

/** game_rules_rule_11_condition checks the eleventh rule condition
  */
BOOL game_rules_rule_11_condition(Game *game){
    if(game_get_object_location(game, 5) != 999){ /*5: matricula*/
      return FALSE;
    }

    if(enemy_get_health(game_get_enemy(game, 0)) > 0 ||
    enemy_get_health(game_get_enemy(game, 1)) > 0 ||
    enemy_get_health(game_get_enemy(game, 2)) > 0){
      return FALSE;
    }
    
    return TRUE;
}

/** game_rules_rule_11 Gives the matricula to the player if bosses were defeated
  */
void game_rules_rule_11(Game *game){
  space_unset_object( game_get_space(game, 999) , 5);
  space_set_object( game_get_space(game, game_get_player_location(game)) , 5);
}

/** game_rules_rule_12_condition checks the twelveth rule condition
  */
BOOL game_rules_rule_12_condition(Game *game){
    if(game_get_object_location(game, 10) != 002){ /*10: man. py. , 002: celda*/
        return FALSE;
    }

    if(game_get_object_location(game, 106) != 002){
        return FALSE;
    }

    return TRUE;
}

/** game_rules_rule_12 Substitutes the demente with the programmer if man.py. is in the celda
  */
void game_rules_rule_12(Game *game){
    space_unset_object(game_get_space(game, 002), 106);
    space_set_object(game_get_space(game, 999), 106);
    space_unset_object(game_get_space(game, 999), 108);
    space_set_object(game_get_space(game, 002), 108);    
}

/** game_rules_rule_13_condition checks the thirdteenth rule condition
  */
BOOL game_rules_rule_13_condition(Game *game){
    if(game_get_player_location(game) != 111){
        return FALSE;
    }

    if(game_get_last_command(game) == MOVE && game_get_last_command_status(game) == OK){
        return FALSE;
    }

    if(game_get_last_command(game) == INSPECT && game_get_last_command_status(game) == OK){
        return FALSE;
    }

    return TRUE;
}

/** game_rules_rule_13 Ends the game if player reaches calle atrás
  */
void game_rules_rule_13(Game *game){
    printf("\n\n\n\n\n                          _____ _                           _ \n                         |_   _| |__   ___    ___ _ __   __| |\n                           | | | '_ \\ / _ \\  / _ \\ '_ \\ / _` |\n                           | | | | | |  __/ |  __/ | | | (_| |\n                           |_| |_| |_|\\___|  \\___|_| |_|\\__,_|\n\n");
    printf("                                      FINAL OSCURO\n\n\n\n\n\n");
    player_set_health(game_get_player(game), 0); /*This is an easy way to end the game*/
}


BOOL game_rules_rule_14_condition(Game *game){
    if(game_get_player_location(game) != 112){
        return FALSE;
    }

    if(game_get_last_command(game) == MOVE && game_get_last_command_status(game) == OK){
        return FALSE;
    }

    if(game_get_last_command(game) == INSPECT && game_get_last_command_status(game) == OK){
        return FALSE;
    }

    return TRUE;
}

/** game_rules_rule_14 Ends the game if player reaches entrada EPS
  */
void game_rules_rule_14(Game *game){
    printf("\n\n\n\n\n                          _____ _                           _ \n                         |_   _| |__   ___    ___ _ __   __| |\n                           | | | '_ \\ / _ \\  / _ \\ '_ \\ / _` |\n                           | | | | | |  __/ |  __/ | | | (_| |\n                           |_| |_| |_|\\___|  \\___|_| |_|\\__,_|\n\n");
    printf("                                      FINAL BUENO\n\n\n\n\n\n");
    player_set_health(game_get_player(game), 0); /*This is an easy way to end the game*/
}

