#ifndef THREAD_MANAGER_H
#define THREAD_MANAGER_H

#include <pthread.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include "socket_manager.h"
#include "log.h"

// Enum to represent the state of a thread
typedef enum {
    EMPTY,      // Thread slot is empty
    AVAILABLE,  // Thread slot is available
    FULL        // Thread slot is full
} thread_state_t;

typedef struct _thread_args_t thread_args_t;

/*******************************************************************************
 * FUNCIÓN: 	void init_thread_manager()
 *
 * ARGS_IN: 	int _max_clients: el máximo de clientes simultáneos
 *
 * DESCRIPCIÓN: Inicializa las variables pertinentes
 *
 * ARGS_OUT: void
 * *****************************************************************************/
void init_thread_manager(int _max_clients);

/*******************************************************************************
 * FUNCIÓN: 	void increase_threads_created_count()
 *
 * ARGS_IN: 	
 *
 * DESCRIPCIÓN: Incrementa en 1 el contador de hilos activos
 *
 * ARGS_OUT: void
 * *****************************************************************************/
void increase_threads_created_count();

/*******************************************************************************
 * FUNCIÓN: 	int register_thread(pthread_t thread_id)
 *
 * ARGS_IN: 	pthread_t thread_id: el id del hilo a registrar
 *
 * DESCRIPCIÓN: Registra en el array de hilos el id del hilo.
 *				NO incrementa el contador de hilos, ya que, para
 *				evitar condiciones de carrera, esto se hace por
 *				separado llamando a increase_threads_created_count()
 *
 * ARGS_OUT: int: 0 si la ejecución es correcta, -1 en caso de error
 * *****************************************************************************/
int register_thread(pthread_t thread_id);

/*******************************************************************************
 * FUNCIÓN: 	void forget_thread(pthread_t thread_id)
 *
 * ARGS_IN: 	pthread_t thread_id: el id del hilo a olvidar
 *
 * DESCRIPCIÓN: Elimina del array de hilos el id del hilo a olvidar,
 *              sustituyendolo por un -1
 *
 * ARGS_OUT: void
 * *****************************************************************************/
void forget_thread(pthread_t thread_id);

/*******************************************************************************
 * FUNCIÓN: 	void finish_threads()
 *
 * ARGS_IN: 	
 *
 * DESCRIPCIÓN: Envía SIGINT a todos los hilos registrados en threads
 *              y espera a que terminen
 * 
 * ARGS_OUT: void
 * *****************************************************************************/
void finish_threads();

/*******************************************************************************
 * FUNCIÓN: 	void finish_thread(int socket_fd, thread_args_t *thread_args)
 *
 * ARGS_IN:     int socket_fd: el descriptor del socket a cerrar
 *              thread_args_t *thread_args: la estructura de argumentos del hilo
 *
 * DESCRIPCIÓN: Olvida el hilo y libera sus recursos
 * 
 * ARGS_OUT: void
 * *****************************************************************************/
void finish_thread(int socket_fd, thread_args_t *thread_args);

/*******************************************************************************
 * FUNCIÓN: 	thread_args_t* init_thread_args(int connection_socket)
 *
 * ARGS_IN: 	int connection_socket : el descriptor del socket de la conexión
 *
 * DESCRIPCIÓN: Inicializa la estructura de argumentos del hilo
 * 
 * ARGS_OUT:    thread_args_t*: la estructura de argumentos del hilo
 * *****************************************************************************/
thread_args_t* init_thread_args(int connection_socket);

/*******************************************************************************
 * FUNCIÓN: 	int get_thread_args_connection_socket(thread_args_t *args)
 *
 * ARGS_IN: 	thread_args_t *args: la estructura de argumentos del hilo
 *
 * DESCRIPCIÓN: Retorna el descriptor del socket de la conexión
 * 
 * ARGS_OUT:    int: el descriptor del socket de la conexión
 * *****************************************************************************/
int get_thread_args_connection_socket(thread_args_t *args);

/*******************************************************************************
 * FUNCIÓN: 	void wait_for_available_thread()
 *
 * ARGS_IN: 	
 *
 * DESCRIPCIÓN: Espera al semáforo available_sem y hace post inmediatamente
 * 
 * ARGS_OUT: void
 * *****************************************************************************/
void wait_for_available_thread();

/*******************************************************************************
 * FUNCIÓN: 	void print_threads()
 *
 * ARGS_IN: 	
 *
 * DESCRIPCIÓN: Imprime en pantalla los hilos registrados
 * 
 * ARGS_OUT: void
 * *****************************************************************************/
void print_threads();

#endif // THREAD_MANAGER_H