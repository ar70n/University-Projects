#include "thread_manager.h"

pthread_t *threads;
int threads_created; // NO necesariamente igual al número de posiciones no nulas en threads
int max_clients;
sem_t thread_mutex; // Para acceder a threads y threads_created
sem_t available_sem; // Para esperar a que haya un hilo disponible

struct _thread_args_t {
    int connection_socket;
};

/*******************************************************************************
 * FUNCIÓN: 	thread_state_t get_state()
 *
 * ARGS_IN: 	
 *
 * DESCRIPCIÓN: Retorna si el array de hilos está vacío, disponible o lleno
 * 
 * ARGS_OUT: void
 * *****************************************************************************/
thread_state_t get_state();


void init_thread_manager(int _max_clients)
{
    threads_created = 0;
    max_clients = _max_clients;

    threads = malloc(sizeof(pthread_t) * max_clients);

    if (sem_init(&thread_mutex, 0, 1) != 0 || sem_init(&available_sem, 0, 1) != 0) // Inicializa el semáforo 
        log_message(ERROR, "Error initializing semaphores\n");

    for (int i = 0; i < max_clients; i++)
        threads[i] = -1;
}

void increase_threads_created_count()
{
    sem_wait(&thread_mutex); // Espera a que el semáforo esté disponible
    threads_created++;

    if (threads_created == max_clients)
        sem_wait(&available_sem);

    sem_post(&thread_mutex); // Libera el semáforo
}

int register_thread(pthread_t thread_id)
{
    int i;
  
    sem_wait(&thread_mutex); // Espera a que el semáforo esté disponible
    
    //Find free index
    for (i = 0; i < max_clients; i++)
    {
        if (threads[i] == -1)
        {
            threads[i] = thread_id;
            sem_post(&thread_mutex);
            return 0;
        }
    }

    log_message(ERROR, "Can't register thread: threads array is full\n");
    sem_post(&thread_mutex); // Libera el semáforo
    return -1;    
}

void forget_thread(pthread_t thread_id)
{
    int i;

    sem_wait(&thread_mutex); // Espera a que el semáforo esté disponible
    
    for (i = 0; i < max_clients; i++)
    {
        if (threads[i] == thread_id)
        {
            if(threads_created == max_clients)
                sem_post(&available_sem);                

            threads[i] = -1;
            threads_created--;
            sem_post(&thread_mutex);
            return;
        }
    }

    log_message(ERROR, "Thread not found in threads array\n");
    sem_post(&thread_mutex); // Libera el semáforo
}

void finish_threads()
{
    if (get_state() == EMPTY)
        sem_destroy(&thread_mutex);   

    sem_wait(&thread_mutex); // Espera a que el semáforo esté disponible

    for (int i = 0; i < max_clients; i++)
    {
        if (threads[i] != -1)
        {
            pthread_kill(threads[i], SIGINT);
        }
    }

    sem_post(&thread_mutex); // Libera el semáforo

    while (get_state() != EMPTY) 
    {
        sem_wait(&thread_mutex); 
        log_message(INFO, "Waiting for all threads to finish... Remaining; %d", threads_created);
        sem_post(&thread_mutex);
        sleep(1);
    }

    sem_destroy(&thread_mutex); // Destruye el semáforo

    free(threads);
}

void finish_thread(int socket_fd, thread_args_t *thread_args)
{
    forget_thread(pthread_self());
    s_close(socket_fd);
    free(thread_args);
}

thread_state_t get_state()
{
    sem_wait(&thread_mutex); // Espera a que el semáforo esté disponible

    thread_state_t state;

    if(threads_created == EMPTY)
    {
        state = EMPTY;
    }
    else if(threads_created == max_clients)
    {
        state = FULL;
    }
    else
    {
        state = AVAILABLE;
    }

    sem_post(&thread_mutex); // Libera el semáforo
    return state;
}

thread_args_t* init_thread_args(int connection_socket)
{
    thread_args_t *thread_args = malloc(sizeof(thread_args_t));
    thread_args->connection_socket = connection_socket;
    return thread_args;
}

int get_thread_args_connection_socket(thread_args_t *args)
{
    return args->connection_socket;
}

void print_threads()
{
    printf("\tThreads: ");
    for (int i = 0; i < max_clients; i++)
    {
        printf(" | [i:%d]: %ld", i, threads[i]);
    }
    printf("\n");
}

void wait_for_available_thread()
{
    sem_wait(&available_sem);
    sem_post(&available_sem);
}