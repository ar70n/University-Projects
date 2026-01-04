/** 
 * @brief It implements the command interpreter
 * 
 * @file command.c
 * @author Profesores PPROG
 * @version 2.0 
 * @date 29-11-2021 
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <strings.h>
#include <string.h>
#include "command.h"

#define CMD_LENGHT 30 /*!< The maximum lenght of a the string of a command */

char *cmd_to_str[N_CMD]
[N_CMDT] = {{"", "No command"},
      {"", "Unknown"},
      {"e", "Exit"},
      {"m", "Move"},      
      {"t", "Take"},
      {"d", "Drop"},
      {"a", "Attack"},
      {"i", "Inspect"},
      {"s", "Save"},
      {"l", "Load"},
      {"n", "Turnon"},
      {"f", "Turnoff"},
      {"o", "Open"}
      };

/** command_get_user_input command to get the user input 
  */
T_Command command_get_user_input(char *aditional_information, FILE *f) {
  T_Command cmd = NO_CMD;
  char input[CMD_LENGHT] = "", command[CMD_LENGHT] = "";
  int i = UNKNOWN - NO_CMD + 1;
  int j, k;

  if(!aditional_information || !f){
    return UNKNOWN;
  }

  aditional_information[0] = '\0';
  
  if (fgets(input, CMD_LENGHT, f) != NULL) {
    cmd = UNKNOWN;

    if (input[(strlen(input))-1] == '\n') {
      input[(strlen(input))-1] = '\0';
    }
    
    if (!strncasecmp(input, "t ", 2)) {
      for (j = 2, k = 0; j < strlen(input); j++, k++) {
        aditional_information[k] = input[j];
      }
      aditional_information[k] = '\0';
      if (strcpy(command, "t") == NULL) {
        return cmd;
      }
    }
    else if (!strncasecmp(input, "take ", 5)) {
      for (j = 5, k = 0; j < strlen(input); j++, k++) {
        aditional_information[k] = input[j];
      }
      aditional_information[k] = '\0';
      if (strcpy(command, "take") == NULL) {
        return cmd;
      }
    }
    else if (!strncasecmp(input, "d ", 2)) {
      for (j = 2, k = 0; j < strlen(input); j++, k++) {
        aditional_information[k] = input[j];
      }
      aditional_information[k] = '\0';
      if (strcpy(command, "d") == NULL) {
        return cmd;
      }
    }
    else if (!strncasecmp(input, "m ", 2)) {
      for (j = 2, k = 0; j < strlen(input); j++, k++) {
        aditional_information[k] = input[j];
      }
      aditional_information[k] = '\0';
      if (strcpy(command, "m") == NULL) {
        return cmd;
      }
    }
    else if (!strncasecmp(input, "move ", 5)) {
      for (j = 5, k = 0; j < strlen(input); j++, k++) {
        aditional_information[k] = input[j];
      }
      aditional_information[k] = '\0';
      if (strcpy(command, "move") == NULL) {
        return cmd;
      }
    }    
    else if (!strncasecmp(input, "drop ", 5)) {
      for (j = 5, k = 0; j < strlen(input); j++, k++) {
        aditional_information[k] = input[j];
      }
      aditional_information[k] = '\0';
      if (strcpy(command, "drop") == NULL) {
        return cmd;
      }
    }
    else if (!strncasecmp(input, "inspect ", 8)) {
      for (j = 8, k = 0; j < strlen(input); j++, k++) {
        aditional_information[k] = input[j];
      }
      aditional_information[k] = '\0';
      if (strcpy(command, "inspect") == NULL) {
        return cmd;
      }
    }
    else if (!strncasecmp(input, "i ", 2)) {
      for (j = 2, k = 0; j < strlen(input); j++, k++) {
        aditional_information[k] = input[j];
      }
      aditional_information[k] = '\0';
      if (strcpy(command, "i") == NULL) {
        return cmd;
      }
    }
    else if (!strncasecmp(input, "save ", 5)) {
      for (j = 5, k = 0; j < strlen(input); j++, k++) {
        aditional_information[k] = input[j];
      }
      aditional_information[k] = '\0';
      if (strcpy(command, "save") == NULL) {
        return cmd;
      }
    }
    else if (!strncasecmp(input, "s ", 2)) {
      for (j = 2, k = 0; j < strlen(input); j++, k++) {
        aditional_information[k] = input[j];
      }
      aditional_information[k] = '\0';
      if (strcpy(command, "s") == NULL) {
        return cmd;
      }
    }
    else if (!strncasecmp(input, "load ", 5)) {
      for (j = 5, k = 0; j < strlen(input); j++, k++) {
        aditional_information[k] = input[j];
      }
      aditional_information[k] = '\0';
      if (strcpy(command, "load") == NULL) {
        return cmd;
      }
    }
    else if (!strncasecmp(input, "l ", 2)) {
      for (j = 2, k = 0; j < strlen(input); j++, k++) {
        aditional_information[k] = input[j];
      }
      aditional_information[k] = '\0';
      if (strcpy(command, "l") == NULL) {
        return cmd;
      }
    }
    else if (!strncasecmp(input, "turnon ", 7)) {
      for (j = 7, k = 0; j < strlen(input); j++, k++) {
        aditional_information[k] = input[j];
      }
      aditional_information[k] = '\0';
      if (strcpy(command, "turnon") == NULL) {
        return cmd;
      }
    }
    else if (!strncasecmp(input, "n ", 2)) {
      for (j = 2, k = 0; j < strlen(input); j++, k++) {
        aditional_information[k] = input[j];
      }
      aditional_information[k] = '\0';
      if (strcpy(command, "n") == NULL) {
        return cmd;
      }
    }
    else if (!strncasecmp(input, "turnoff ", 8)) {
      for (j = 8, k = 0; j < strlen(input); j++, k++) {
        aditional_information[k] = input[j];
      }
      aditional_information[k] = '\0';
      if (strcpy(command, "turnoff") == NULL) {
        return cmd;
      }
    }
    else if (!strncasecmp(input, "f ", 2)) {
      for (j = 2, k = 0; j < strlen(input); j++, k++) {
        aditional_information[k] = input[j];
      }
      aditional_information[k] = '\0';
      if (strcpy(command, "f") == NULL) {
        return cmd;
      }
    }
    else if (!strncasecmp(input, "open ", 5)) {
      for (j = 5, k = 0; j < strlen(input); j++, k++) {
        aditional_information[k] = input[j];
      }
      aditional_information[k] = '\0';
      if (strcpy(command, "open") == NULL) {
        return cmd;
      }
    }
    else if (!strncasecmp(input, "o ", 2)) {
      for (j = 2, k = 0; j < strlen(input); j++, k++) {
        aditional_information[k] = input[j];
      }
      aditional_information[k] = '\0';
      if (strcpy(command, "o") == NULL) {
        return cmd;
      }
    }
    else if (!strncasecmp(input, "attack ", 7)) {
      for (j = 5, k = 0; j < strlen(input); j++, k++) {
        aditional_information[k] = input[j];
      }
      aditional_information[k] = '\0';
      if (strcpy(command, "attack") == NULL) {
        return cmd;
      }
    }
    else if (!strncasecmp(input, "a ", 2)) {
      for (j = 2, k = 0; j < strlen(input); j++, k++) {
        aditional_information[k] = input[j];
      }
      aditional_information[k] = '\0';
      if (strcpy(command, "a") == NULL) {
        return cmd;
      }
    }
    else {
      if (strcpy(command, input) == NULL) {
        return cmd;
      }
    }
    
    
    while (cmd == UNKNOWN && i < N_CMD) {
      if (!strcasecmp(command, cmd_to_str[i][CMDS]) || !strcasecmp(command, cmd_to_str[i][CMDL])) {
        cmd = i + NO_CMD;
      }
      else {
        i++;
      }
    }
  }

  return cmd;
}



