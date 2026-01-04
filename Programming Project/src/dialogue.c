/**
 * @brief It implements the dialogue module
 *
 * @file dialogue.c
 * @author Sergio Saúco and Antonio Moroño
 * @version 1.0
 * @date 27-04-2023
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dialogue.h"

/**
 * @brief Dialogue
 *
 * This struct stores all the information of the dialogue.
 */
struct _Dialogue {
  char command_result[WORD_SIZE + 1]; /*!< String with the result of the command */
  T_Command previous_command; /*!< Previous command input */
  STATUS previous_command_status; /*!< Previous command status */
  char previous_aditional_information[WORD_SIZE + 1]; /*!< Previous additional information */
  Id previous_player_location; /*!< Previous player location */
};

/** dialogue_create creates a new dialogue, 
  * allocating memory and initializing its memebers
  */
Dialogue *dialogue_create() {
    Dialogue *newDialogue = NULL;

    newDialogue = (Dialogue *)malloc(sizeof(Dialogue));
    if (newDialogue == NULL) {
        return NULL;
    }

    newDialogue->command_result[0] = '\0';
    newDialogue->previous_command = NO_CMD;
    newDialogue->previous_command_status = OK;
    newDialogue->previous_aditional_information[0] = '\0';
    newDialogue->previous_player_location = NO_ID;

    return newDialogue;
}

/** dialogue_destroy destroys a dialogue, 
  * freeing the allocated memory
  */
STATUS dialogue_destroy(Dialogue *dialogue) {
    if (!dialogue) {
        return ERROR;
    }
    free(dialogue);
    dialogue = NULL;
    return OK;
}

/** dialogue_set_command_result sets the command result of a command
  */
STATUS dialogue_set_command_result(Dialogue *dialogue, char *information) {
    if(!dialogue || !information) {
        return ERROR;
    }
    strcpy(dialogue->command_result, information);
    return OK;
}
/** dialogue_get_command_result gets the command result of a command
  */
char *dialogue_get_command_result(Dialogue *dialogue) {
    if (!dialogue) {
        return NULL;
    }
    return dialogue->command_result;
}

/** dialogue_set_previous_command sets the previous command
  */
STATUS dialogue_set_previous_command(Dialogue *dialogue, T_Command command) {
    if (!dialogue || command == NO_CMD) {
        return ERROR;
    }
    dialogue->previous_command = command;
    return OK;
}
/** dialogue_get_previous_command gets the previous command
  */
T_Command dialogue_get_previous_command(Dialogue *dialogue) {
    if (!dialogue) {
        return NO_CMD;
    }
    return dialogue->previous_command;
}

/** dialogue_set_previous_command_status sets the previous command status
  */
STATUS dialogue_set_previous_command_status(Dialogue *dialogue, STATUS st) {
    if (!dialogue) {
        return ERROR;
    }
    dialogue->previous_command_status = st;
    return OK;
}
/** dialogue_get_previous_command_status gets the previous command status
  */
STATUS dialogue_get_previous_command_status(Dialogue *dialogue) {
    if (!dialogue) {
        return ERROR;
    }
    return dialogue->previous_command_status;
}

/** dialogue_set_previous_additional_information sets the 
  * previous additional information of a command input
  */
STATUS dialogue_set_previous_additional_information(Dialogue *dialogue, char *information) {
    if (!dialogue || !information) {
        return ERROR;
    }
    strcpy(dialogue->previous_aditional_information, information);
    return OK;
}
/** dialogue_get_previous_additional_information gets the 
  * previous additional information of a command input
  */
char *dialogue_get_previous_additional_information(Dialogue *dialogue) {
    if (!dialogue) {
        return NULL;
    }
    return dialogue->previous_aditional_information;
}

/** dialogue_set_previous_player_location sets the previous player location
  */
STATUS dialogue_set_previous_player_location(Dialogue *dialogue, Id player_location) {
    if (!dialogue || player_location == NO_ID) {
        return ERROR;
    }
    dialogue->previous_player_location = player_location;
    return OK;
}
/** dialogue_get_previous_player_location gets the previous player location
  */
Id dialogue_get_previous_player_location(Dialogue *dialogue) {
    if (!dialogue) {
        return NO_ID;
    }
    return dialogue->previous_player_location;
}

/** dialogue_print prints the dialogue information
  */
STATUS dialogue_print(Dialogue *dialogue) {
    if (!dialogue) {
        return ERROR;
    }

    /* 1. Print the command result */
    fprintf(stdout, "Command result: %s\n", dialogue_get_command_result(dialogue));

    /* 2. Print the previous command */
    fprintf(stdout, "Previous command: %d\n", dialogue_get_previous_command(dialogue));

    /* 3. Print the previous command status */
    fprintf(stdout, "Previous command status; %d\n", dialogue_get_previous_command_status(dialogue));

    /* 4. Print the previous additional information */
    fprintf(stdout, "Previous additional information: %s\n", dialogue_get_previous_additional_information(dialogue));

    /* 5. Print the previous player location */
    fprintf(stdout, "Previous player location: %ld\n", dialogue_get_previous_player_location(dialogue));

    return OK;
}
