/**
 * @brief It implements the command interpreter interface
 *
 * @file command.h
 * @author Profesores PPROG
 * @version 2.0
 * @date 29-11-2021
 * @copyright GNU Public License
 */

#ifndef COMMAND_H
#define COMMAND_H

#include <stdio.h>

#define N_CMDT 2 /*!< The number of command types */
#define N_CMD 13 /*!< The number of commands */

/**
 * @brief Command Type
 *
 * Stores the command types
 */
typedef enum enum_CmdType {
  CMDS, /*!< Command string */
  CMDL /*!< Command letter */} T_CmdType;

/**
 * @brief Commands
 *
 * Stores all the commands (No command, Unknown, 
 * Exit, Move, Take, Drop, Inspect, Move, Turnon, Turnoff, Open
 * Save and Load)
 */
typedef enum enum_Command {
  NO_CMD = -1, /*!< Command No command */
  UNKNOWN, /*!< Command Unknown */
  EXIT, /*!< Command Exit */
  MOVE, /*!< Command Move */
  TAKE, /*!< Command Take */
  DROP, /*!< Command Drop */
  ATTACK, /*!< Command Attack */
  INSPECT, /*!< Command Inspect */
  SAVE, /*!< Command Save */
  LOAD, /*!< Command Load */
  TURNON, /*!< Command Turnon */
  TURNOFF, /*!< Command Turnoff */
  OPENC /*!< Command Open */} T_Command;

/**
  * @brief The command to get the user input
  * @author Profesores PPROG
  *
  * @param aditional_information string with the aditional information
  * that the command needs to be done successfully
  * @param f the file from which you the command gets the input
  * (stdin for the user)
  * @return the command
  */
T_Command command_get_user_input(char *aditional_information, FILE *f);

#endif
