/**
 * @file misc.h
 * @brief Archivo de encabezado que contiene la declaración de funciones y tipos de datos relacionados con operaciones misceláneas.
 */

#ifndef MISC_H
#define MISC_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * @brief Tipo de dato para un puntero a función de manejo de señales.
 */
typedef void (*handler_t)(int si);

/**
 * @brief Tipo de dato para un puntero a función de manejo de señales utilizando sigaction.
 */
typedef void (*handler_sa_sigaction_t)(int, siginfo_t *, void *);

/**
 * @brief Pone en espera la ejecución del programa durante un tiempo determinado.
 * 
 * @param SIG Puntero a un entero que representa la señal a suspender.
 * @param num Número de veces que se suspenderá la señal.
 * @param init Valor inicial del puntero a entero SIG.
 */
void suspend_for(int *SIG, int num, int init);

/**
 * @brief Configura la acción a tomar cuando se recibe una señal determinada.
 * 
 * @param act Puntero a una estructura sigaction que representa la acción a configurar.
 * @param handler Puntero a una función de manejo de señales.
 * @param handler_sa_sigaction Puntero a una función de manejo de señales utilizando sigaction.
 * @param SIG Número de la señal a configurar.
 * @param flags Opciones adicionales para la configuración de la acción.
 */
void config_action(struct sigaction *act, handler_t handler, handler_sa_sigaction_t handler_sa_sigaction, int SIG, int flags);

/**
 * @brief Ignora la señal especificada.
 * 
 * @param SIG Número de la señal a ignorar.
 * @param act Puntero a una estructura sigaction que representa la acción a configurar.
 */
void ignore_signal(int SIG, struct sigaction *act);

#endif