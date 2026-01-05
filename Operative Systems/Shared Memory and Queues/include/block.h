/**
 * @file block.h
 * @authors Manuel Fernández y Antonio Moroño
 * @brief Implementación de las funciones para la manipulación de una cola de bloques.
 *
 * Este archivo contiene la declaracion de las funciones necesarias para la manipulación de una cola de bloques.
 * La cola de bloques se utiliza para almacenar y gestionar bloques de datos.
 */

#ifndef STRUCTS_H
#define STRUCTS_H

#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <semaphore.h>

#include "types.h"


#define N_SEMS 3
#define N_BLOCKS 6+1 //Esto es para que haya 6 posiciones que se usan en la cola y 1 que se queda libre.
//No se si en el enunciado s refieren a 6 bloques efecivos (como lo tenemos) o a 6 en total (5 efectivos)

#define MQ_NAME "/miner_control"

//Estructura de un bloque
typedef struct{
    long int objetivo;
    long int solucion;
    int correcto; // 1 si es correcto, 0 si no
} Bloque;

typedef struct{
    Bloque blocks[N_BLOCKS];
    int front;
    int rear;
} Cola;

//Estructura de la memoria compartida
typedef struct {
    Cola cola; //Se implementará como una "cola circular"
    sem_t sems[N_SEMS]; // sems[0]->sem_empty, sems[1]->sem_fill, sems[2]->sem_mutex
} ShmStruct;


Status queue_init(Cola *pq);
Bool queue_isEmpty(const Cola *pq);
Bool queue_isFull(const Cola *pq);
Status queue_push(Cola *pq, const Bloque e);
Bloque queue_pop(Cola *pq);

#endif