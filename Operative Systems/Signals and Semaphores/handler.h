/**
 * @file handler.h
 * @brief Archivo de cabecera que contiene las declaraciones de las funciones de manejo de señales.
 */

#ifndef HANDLER_H
#define HANDLER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>
#include "misc.h"

/**
 * @brief Función de manejo de señales.
 *
 * Esta función se encarga de manejar las señales recibidas por el programa.
 *
 * @param signum El número de la señal recibida.
 */
void handler(int signum);

/**
 * @brief Función de manejo de la señal SIGINT (Ctrl+C).
 *
 * Esta función se encarga de manejar la señal SIGINT (Ctrl+C) recibida por el programa.
 *
 * @param signum El número de la señal recibida.
 */
void handler_ctrlc(int signum);

/**
 * @brief Función de manejo de la señal SIGALRM.
 *
 * Esta función se encarga de manejar la señal SIGALRM recibida por el programa.
 *
 * @param signum El número de la señal recibida.
 */
void handler_alrm(int signum);

/**
 * @brief Función de manejo de la señal SIGTERM.
 *
 * Esta función se encarga de manejar la señal SIGTERM recibida por el programa.
 *
 * @param signum El número de la señal recibida.
 */
void handler_term(int signum);

#endif
