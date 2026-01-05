#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include "socket_manager.h"
#include "thread_manager.h"
#include "http_manager.h"
#include "conf_manager.h"
#include <semaphore.h>
#include <pthread.h>
#include <errno.h>
#include <signal.h>
#include "log.h"

#define CLIENT_QUEUE_SIZE 10
#define BUFF_LENGTH 4096

int thread_termination = 0;

/*******************************************************************************
 * FUNCIÓN: 	void *handle_client_connection(void *args)
 *
 * ARGS_IN: 	void *args: estructura con el descriptor del socket de la conexión
 *              y el semáforo
 *
 * DESCRIPCIÓN: Función que maneja la conexión con un cliente. Recibe mensajes
 *              del cliente y los imprime en pantalla.
 *
 * ARGS_OUT: void*: puntero nulo
 * *****************************************************************************/
void *handle_client_connection(void *args);

/*******************************************************************************
 * FUNCIÓN: 	void handle_sigint(int sig)
 *
 * ARGS_IN: 	int sig: señal recibida
 *
 * DESCRIPCIÓN: Función manejadora de la señal SIGINT. Establece la variable global
 *              thread_termination a 1, lo que provoca que los hilos terminen
 *              su ejecución.
 * *****************************************************************************/
void handle_sigint(int sig);

/*******************************************************************************
 * FUNCIÓN: 	int main(int argc, char **argv)
 *
 * ARGS_IN: 	int argc: número de argumentos pasados por línea de comandos
 *           char **argv: argumentos pasados por línea de comandos
 *
 * DESCRIPCIÓN: Función principal del servidor concurrente. Crea un socket, lo
 *               enlaza a un puerto, lo pone a escuchar y acepta conexiones
 *               entrantes. Por cada conexión entrante, crea un hilo que
 *               se encarga de manejar la conexión.
 *
 * ARGS_OUT: int: código de salida
 *********************************************************************************/
int main(int argc, char **argv)
{    
    char *server_root, *server_signature; // Cambiar a
    int max_clients, port;
    int socket_fd, connection_socket;
    pthread_t thread_id;
    thread_args_t *thread_args;

    printf("Inicializando...\n");

    // Configurar el manejador de señales
    struct sigaction sa;
    sa.sa_handler = handle_sigint;
    sa.sa_flags = 0; // No flags
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGINT, &sa, NULL) == -1)
    {
        log_message(ERROR, "Error setting SIGINT handler");
        exit(EXIT_FAILURE);
    }

    init_log();

    if (load_config(&server_root, &server_signature, &max_clients, &port) < 0)
    {
        log_message(ERROR, "Error loading configuration");
        return -1;
    }    

    init_thread_manager(max_clients);
    init_http_manager(server_root, server_signature);

    socket_fd = s_create(AF_INET, SOCK_STREAM, 0); // Create socket

    // Bind socket to port
    if (s_bind(socket_fd, port) < 0)
    { 
        log_message(ERROR, "Error binding socket");
        finish_threads();
        close_http_manager();
        return -1;
    }

    // Listen
    if (s_listen(socket_fd, CLIENT_QUEUE_SIZE) < 0)
    {
        log_message(ERROR, "Error listening on socket");
        finish_threads();
        close_http_manager();
        return -1;
    }

    wait_for_available_thread();
    printf("Servidor iniciado en el puerto %d\n", port);

    while (thread_termination == 0)
    {        
        connection_socket = s_accept(socket_fd); // Accept

        if (errno == EINTR) break; // SIGINT
        if (connection_socket < 0) continue; // Error en la conexión        

        wait_for_available_thread(); // Esperar a que haya un hilo disponible

        if (errno == EINTR) break; // SIGINT

        thread_args = init_thread_args(connection_socket);

        if (pthread_create(&thread_id, NULL, handle_client_connection, (void *)thread_args) == 0)
        {
            increase_threads_created_count();
            pthread_detach(thread_id); // Detach el hilo para no tener que hacer join
        }
        else // Error creando el hilo
        {
            log_message(ERROR, "Failed to create thread");
            free(thread_args);
        }
    }

    log_message(INFO, "SIGINT received, finishing threads");
    finish_threads();
    log_message(INFO, "All threads have finished");
    s_close(socket_fd);
    close_http_manager();
    exit(0);
}

/*******************************************************************************
 * FUNCIÓN: 	void *handle_client_connection(void *args)
 *
 * ARGS_IN: 	void *args: estructura con el descriptor del socket de la conexión
 *              y el semáforo
 *
 * DESCRIPCIÓN: Función que maneja la conexión con un cliente. Recibe mensajes
 *              del cliente y los imprime en pantalla.
 *
 * ARGS_OUT: void*: puntero nulo
 * *****************************************************************************/
void *handle_client_connection(void *args)
{
    int connection_socket = get_thread_args_connection_socket((thread_args_t *)args);
    char buff[BUFF_LENGTH];
    http_response *reply;
    int receive;

    log_message(INFO, "Connection accepted, thread created");
    
    if(register_thread(pthread_self()) != 0)
    {
        log_message(ERROR, "Error registering thread");
        s_close(connection_socket);
        free(args);
        
        return NULL;
    }

    while (thread_termination == 0)
    {
        receive = s_recv(connection_socket, buff, BUFF_LENGTH);

        if (receive <= 0 || errno == EINTR) // Check for SIGINT
        {
            finish_thread(connection_socket, args);
            return NULL;
        }
        
        reply = http_parse_petition(buff); //Devuelve la peticion a enviar
        http_respond(connection_socket, reply);
        
        memset(buff, 0, BUFF_LENGTH);
    }

    finish_thread(connection_socket, args);
    log_message(INFO, "Thread finished");
    return NULL;
}

void handle_sigint(int sig)
{
    thread_termination = 1;
    log_message(INFO, "SIGINT received");
}