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
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <semaphore.h>
#include <signal.h>

#define SHM_NAME "/shm_monitor"

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
 * @param shm_struct Puntero a la estructura de memoria compartida.
 */
void monitor(ShmStruct *shm_struct);

/**
 * @brief Función del comprobador.
 *
 * La función comprobador se encarga de recibir mensajes de una cola de mensajes y realizar
 * las comprobaciones correspondientes sobre los bloques recibidos. Luego, los almacena en
 * la memoria compartida para que el monitor los lea.
 *
 * @param shm_struct Puntero a la estructura de memoria compartida.
 */
void comprobator(ShmStruct *shm_struct);



Bool volatile flag = TRUE;

// Signal handling
void handler(int signum)
{
    flag = FALSE;
}
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

    int fd_shm;
    ShmStruct *shm_struct;

    // Cuando un proceso crea un segmento de memoria compartida y luego crea un proceso hijo con la función fork, el proceso hijo hereda el segmento de memoria compartida.
    fd_shm = shm_open(SHM_NAME, O_RDWR | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR); // TODO Esto lo hace el comprobador (puede que haya que pasarlo abajo, no se)
    if (fd_shm == -1)
    {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }
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
    shm_unlink(SHM_NAME);

    // Inicializamos los semaforos

    sem_init(&(shm_struct->sems[0]), 1, N_BLOCKS - 1); // SEM EMPTY
    sem_init(&(shm_struct->sems[1]), 1, 0);            // SEM FILL
    sem_init(&(shm_struct->sems[2]), 1, 1);            // SEM MUTEX

    /*Monitor*/
    if (fork() == 0)
    {
        monitor(shm_struct);
    }
    /*Comprobador*/
    else
    {
        comprobator(shm_struct);
    }

    exit(EXIT_SUCCESS);
}

// Consumidor
void monitor(ShmStruct *shm_struct)
{
    Bloque block;
    int i;

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

        if (block.correcto == -1)
        {
            flag = FALSE;
            break;
        }

        fprintf(stdout, "Id:\t  %04ld\n", block.id);
        fprintf(stdout, "Winner:\t  %04ld\n", block.idGanador);
        fprintf(stdout, "Target:\t  %08ld\n", block.target);
        if (block.correcto == 1)
        {
            fprintf(stdout, "Solution: %08ld (validated)\n", block.solucion);
        }
        else if (block.correcto == 0)
        {
            fprintf(stdout, "Solution: %08ld (rejected)\n", block.solucion);
        }
        else
        {
            flag = FALSE;
        }
        fprintf(stdout, "Votes:\t  %d/%d\n", block.numVotosPositivos, block.numVotosTotales);
        fprintf(stdout, "Wallets:  ");
        for (i = 0; i < block.numVotosTotales; i++)
        {
            if (block.wallets[i].id != -1)
            {
                fprintf(stdout, "%04d:%02d\t", block.wallets[i].id, block.wallets[i].monedas);
            }
        }
        fprintf(stdout, "\n\n");
    }
    /*Unmapping la memoria compartida y cerrando semaforos*/
    for (i = 0; i < N_SEMS; i++)
    {
        sem_destroy(&(shm_struct->sems[i]));
    }
    munmap(shm_struct, sizeof(ShmStruct));
}

void comprobator(ShmStruct *shm_struct)
{

    mqd_t queue;
    Bloque msg;
    struct sigaction act;
    sem_t *sem;
    struct mq_attr attributes;
    Bool end = FALSE;

    // Configuramos la gestion de señales
    act.sa_handler = handler;
    sigemptyset(&(act.sa_mask));
    act.sa_flags = 0;

    if (sigaction(SIGINT, &act, NULL) < 0)
    {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    if ((sem = sem_open(SEM_NAME, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 0)) == SEM_FAILED)
    {
        sem = sem_open(SEM_NAME, O_RDWR);
        if (sem == SEM_FAILED)
        {
            munmap(shm_struct, sizeof(ShmStruct));
            shm_unlink(SHM_NAME);
            perror("sem_open");
            exit(EXIT_FAILURE);
        }
    }

    attributes.mq_maxmsg = 7;
    attributes.mq_msgsize = sizeof(Bloque);
    if ((queue = mq_open(MQ_NAME, O_CREAT | O_EXCL | O_RDONLY, S_IRUSR | S_IWUSR, &attributes)) == (mqd_t)-1)
    {
        queue = mq_open(MQ_NAME, O_RDONLY, S_IRUSR);
        if (queue == (mqd_t)-1)
        {
            munmap(shm_struct, sizeof(ShmStruct));
            shm_unlink(SHM_NAME);
            perror("mq_open");
            exit(EXIT_FAILURE);
        }
    }

    // Inicializamos la cola
    queue_init(&(shm_struct->cola));

    while (end == FALSE)
    {
        sem_post(sem);
        if (mq_receive(queue, (char *)&msg, sizeof(msg), NULL) == -1 || flag==FALSE)
        {
            msg.correcto = -1;
            sem_wait(&(shm_struct->sems[0])); // down sem_empty
            sem_wait(&(shm_struct->sems[2])); // down sem_mutex
            if (queue_isFull(&(shm_struct->cola)))
            {
                fprintf(stderr, "Error: Full queue\n");
                end = TRUE;
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
            msg.target = -1;
            msg.solucion = -1;
            end = TRUE;
        }
        else
        {
            if (pow_hash(msg.solucion) == msg.target)
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
            end = TRUE;
        }
        else
        {
            queue_push(&(shm_struct->cola), msg);
        }
        sem_post(&(shm_struct->sems[2])); // up sem_mutex
        sem_post(&(shm_struct->sems[1])); // up sem_fill
    }

    sem_trywait(sem);
    /*Unmapping la memoria compartida*/
    munmap(shm_struct, sizeof(ShmStruct));
    mq_close(queue);
    sem_close(sem);
    sem_unlink(SEM_NAME);
    mq_unlink(MQ_NAME);
}
