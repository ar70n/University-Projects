/**
 * @file monitor.c
 * @authors Antonio Moroño y Manuel Fernández
 * @brief Implementación de un monitor para la gestión de bloques en memoria compartida.
 *
 * Este archivo contiene la implementación de un monitor que se encarga de gestionar
 * la lectura y escritura de bloques en memoria compartida. El monitor se encarga de
 * imprimir los bloques leídos y realizar comprobaciones sobre ellos.
 */

#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <errno.h>
#include <unistd.h>
#include <semaphore.h>

#define SHM_NAME "/shm_monitor"
#define LAG 1000 * lag

#include "types.h"
#include "block.h"
#include "pow.h"

/**
 * @brief Función del monitor.
 *
 * La función monitor se encarga de leer los bloques de la memoria compartida y realizar
 * las comprobaciones correspondientes. Imprime los bloques leídos y finaliza cuando se
 * encuentra un bloque con el campo "correcto" igual a -1.
 *
 * @param lag Retardo en microsegundos entre la lectura de bloques.
 * @param shm_struct Puntero a la estructura de memoria compartida.
 */
void monitor(int lag, ShmStruct *shm_struct);

/**
 * @brief Función del comprobador.
 *
 * La función comprobador se encarga de recibir mensajes de una cola de mensajes y realizar
 * las comprobaciones correspondientes sobre los bloques recibidos. Luego, los almacena en
 * la memoria compartida para que el monitor los lea.
 *
 * @param lag Retardo en microsegundos entre la recepción de mensajes.
 * @param shm_struct Puntero a la estructura de memoria compartida.
 */
void comprobator(int lag, ShmStruct *shm_struct);

/**
 * @brief Función principal del programa.
 *
 * La función principal del programa se encarga de crear o abrir la memoria compartida,
 * inicializar los semáforos y llamar a las funciones monitor() o comprobator() dependiendo
 * de si la memoria compartida ya existe o no.
 *
 * @param argc Cantidad de argumentos pasados por línea de comandos.
 * @param argv Arreglo de cadenas de caracteres que representan los argumentos pasados por línea de comandos.
 * @return Devuelve EXIT_SUCCESS si el programa se ejecuta correctamente, o EXIT_FAILURE en caso de error.
 */
int main(int argc, char *argv[])
{

    int fd_shm, lag;
    ShmStruct *shm_struct;
    if (argc != 2)
    {
        printf("Usage: %s <LAG>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    lag = atoi(argv[1]);
    if (lag < 0)
    {
        fprintf(stderr, "Error: LAG must be a positive integer\n");
        exit(EXIT_FAILURE);
    }

    // El primer proceso que abrá la memoria compartida será el comprobador
    fd_shm = shm_open(SHM_NAME, O_RDWR | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR);
    if (fd_shm == -1)
    {
        if (errno == EEXIST)
        {
            fd_shm = shm_open(SHM_NAME, O_RDWR, 0);
            if (fd_shm == -1)
            {
                perror("shm_open");
                exit(EXIT_FAILURE);
            }
            shm_struct = mmap(NULL, sizeof(ShmStruct), PROT_READ | PROT_WRITE, MAP_SHARED, fd_shm, 0);
            close(fd_shm);
            if (shm_struct == MAP_FAILED)
            {
                perror("mmap");
                exit(EXIT_FAILURE);
            }
            monitor(lag, shm_struct);
        }
        else
        {
            perror("shm_open");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        // El tamaño es el de 6 bloques y 3 semaforos
        if (ftruncate(fd_shm, sizeof(ShmStruct)) == -1)
        {
            perror("ftruncate");
            exit(EXIT_FAILURE);
        }
        shm_struct = mmap(NULL, sizeof(ShmStruct), PROT_READ | PROT_WRITE, MAP_SHARED, fd_shm, 0);
        close(fd_shm);
        if (shm_struct == MAP_FAILED)
        {
            perror("mmap");
            shm_unlink(SHM_NAME);
            exit(EXIT_FAILURE);
        }

        // Inicializamos los semaforos

        sem_init(&(shm_struct->sems[0]), 1, N_BLOCKS - 1); // SEM EMPTY
        sem_init(&(shm_struct->sems[1]), 1, 0);            // SEM FILL
        sem_init(&(shm_struct->sems[2]), 1, 1);            // SEM MUTEX

        comprobator(lag, shm_struct);
    }

    exit(EXIT_SUCCESS);
}

// Consumidor
void monitor(int lag, ShmStruct *shm_struct)
{
    Bloque block;
    Bool flag = TRUE;
    int i;

    fprintf(stdout, "[%d] Printing blocks...\n", getpid());

    while (flag)
    {
        // SEGMENTATION FAULT AQUI
        sem_wait(&(shm_struct->sems[1])); // Down sem_fill
        sem_wait(&(shm_struct->sems[2])); // Down sem_mutex

        if (queue_isEmpty(&(shm_struct->cola)))
        {
            fprintf(stderr, "Error: Empty queue\n");
            flag = FALSE;
        }
        else
        {
            block = queue_pop(&(shm_struct->cola));
        }
        sem_post(&(shm_struct->sems[2])); // Up sem_mutex
        sem_post(&(shm_struct->sems[0])); // Up sem_empty

        if (block.correcto == 1)
        {
            fprintf(stdout, "Solution accepted: %08ld --> %08ld\n", block.objetivo, block.solucion);
        }
        else if (block.correcto == 0)
        {
            fprintf(stdout, "Solution rejected: %08ld !-> %08ld\n", block.objetivo, block.solucion);
        }
        else
        {
            flag = FALSE;
        }

        usleep(LAG);
    }
    /*Unmapping la memoria compartida y cerrando semaforos*/
    for (i = 0; i < N_SEMS; i++)
    {
        sem_destroy(&(shm_struct->sems[i]));
    }
    munmap(shm_struct, sizeof(ShmStruct));
    shm_unlink(SHM_NAME);
    fprintf(stdout, "[%d] Finishing\n", getpid());
}

void comprobator(int lag, ShmStruct *shm_struct)
{

    mqd_t queue;
    Bloque msg;
    Bool flag = TRUE;
    // Recibimos mensaje de la cola del sistema
    queue = mq_open(MQ_NAME, O_RDONLY, S_IRUSR);

    if (queue == (mqd_t)-1)
    {
        munmap(shm_struct, sizeof(ShmStruct));
        shm_unlink(SHM_NAME);
        fprintf(stderr, "Error opening the queue. Comprobator\n");
        exit(EXIT_FAILURE);
    }
    mq_unlink(MQ_NAME);

    // Inicializamos la cola
    queue_init(&(shm_struct->cola));

    fprintf(stdout, "[%d] Checking blocks...\n", getpid());

    while (flag) // No definido todavia
    {
        if (mq_receive(queue, (char *)&msg, sizeof(msg), NULL) == -1)
        {
            msg.correcto = -1;
            fprintf(stderr, "Error recieveng the message\n");
            sem_wait(&(shm_struct->sems[0])); // down sem_empty
            sem_wait(&(shm_struct->sems[2])); // down sem_mutex
            if (queue_isFull(&(shm_struct->cola)))
            {
                fprintf(stderr, "Error: Full queue\n");
                flag = FALSE;
            }
            else
            {
                queue_push(&(shm_struct->cola), msg);
            }
            sem_post(&(shm_struct->sems[2])); // up sem_mutex
            sem_post(&(shm_struct->sems[1])); // up sem_fill

            munmap(shm_struct, sizeof(ShmStruct));

            mq_close(queue);

            exit(EXIT_FAILURE);
        }

        if (msg.correcto == -1)
        {
            msg.objetivo = -1;
            msg.solucion = -1;
            flag = FALSE;
        }
        else
        {
            if (pow_hash(msg.solucion) == msg.objetivo)
            {
                msg.correcto = 1;
            }
            else
            {
                msg.correcto = 0;
            }
        }
        // Productor
        sem_wait(&(shm_struct->sems[0])); // down sem_empty
        sem_wait(&(shm_struct->sems[2])); // down sem_mutex
        if (queue_isFull(&(shm_struct->cola)))
        {
            fprintf(stderr, "Error: Full queue\n");
            flag = FALSE;
        }
        else
        {
            queue_push(&(shm_struct->cola), msg);
        }
        sem_post(&(shm_struct->sems[2])); // up sem_mutex
        sem_post(&(shm_struct->sems[1])); // up sem_fill

        usleep(LAG);
    }

    /*Unmapping la memoria compartida*/
    munmap(shm_struct, sizeof(ShmStruct));

    mq_close(queue);

    fprintf(stdout, "[%d] Finishing\n", getpid());
    exit(EXIT_SUCCESS);
}