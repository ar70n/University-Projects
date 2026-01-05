/**
 * @file handler.c
 * @brief Implementación de las funciones de manejo de señales.
 *
 * Este archivo contiene la implementación de las funciones de manejo de señales
 * utilizadas en el programa principal.
 */

#include "handler.h"

/**
 * @brief Manejador de señal genérico.
 *
 * Esta función se encarga de manejar una señal genérica. Actualiza una variable
 * global indicando que se ha recibido la señal.
 *
 * @param signum El número de la señal recibida.
 */
void handler(int signum)
{
	extern volatile sig_atomic_t got_signal;
	got_signal = 1;
}

/**
 * @brief Manejador de la señal SIGINT (Ctrl+C).
 *
 * Esta función se encarga de manejar la señal SIGINT (Ctrl+C). Actualiza una variable
 * global indicando que se ha recibido la señal.
 *
 * @param signum El número de la señal recibida.
 */
void handler_ctrlc(int signum)
{
    extern volatile sig_atomic_t got_signal;
	got_signal = 1;
}

/**
 * @brief Manejador de la señal SIGTERM.
 *
 * Esta función se encarga de manejar la señal SIGTERM. Actualiza una variable
 * global indicando que se ha recibido la señal.
 *
 * @param signum El número de la señal recibida.
 */
void handler_term(int signum)
{
    extern volatile sig_atomic_t termination;
	termination = 1;
}

/**
 * @brief Manejador de la señal SIGALRM.
 *
 * Esta función se encarga de manejar la señal SIGALRM. Actualiza una variable
 * global indicando que se ha recibido la señal.
 *
 * @param signum El número de la señal recibida.
 */
void handler_alrm(int signum)
{
    extern volatile sig_atomic_t got_signal_alarm;
	got_signal_alarm = 1;
}
