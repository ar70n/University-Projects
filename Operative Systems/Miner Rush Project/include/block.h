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

#define MAX_MINERS 100
#define MAX_TRIES 10
#define N_SEMS 3
#define N_BLOCKS 5+1 //Esto es para que haya 6 posiciones que se usan en la cola y 1 que se queda libre.
//No se si en el enunciado s refieren a 6 bloques efecivos (como lo tenemos) o a 6 en total (5 efectivos)

#define MQ_NAME "/miner_control"
#define SEM_NAME "/semaforo" //Este semaforo es para enviar el bloque resuelto al monitor




typedef struct{
    pid_t id;
    int monedas;
}Wallet;


//Estructura de un bloque
typedef struct{
    long int id;
    long int target;
    long int solucion;
    long int idGanador;
    Wallet wallets[MAX_MINERS];
    int numVotosTotales;
    int numVotosPositivos;
    int correcto; //Creo que nos lo podemos fumar pq si hay mas de la mitad  de votos positivos ya se considera correcto
} Bloque;


typedef struct{
    pid_t pidMineros[MAX_MINERS];
    int votosMineros[MAX_MINERS];
    int monedasMineros[MAX_MINERS];
    int minerosActivos; 
    Bloque resolviendo;
    Bloque lastResuelto;
    sem_t sem; //Un semaforo para controlar la escritura. (Podriamos hacer un modelo lectores-escritors pero paso)
    sem_t sem_winner;
}Memoria;

typedef struct{
    Bloque blocks[N_BLOCKS];
    int front;
    int rear;
} Cola;

//Estructura de la memoria compartida de monitor comprobador
typedef struct {
    Cola cola; //Se implementará como una "cola circular"
    sem_t sems[N_SEMS]; // sems[0]->sem_empty, sems[1]->sem_fill, sems[2]->sem_mutex
} ShmStruct;

typedef struct {
    long int inicio;
    long int fin;
} Miner_data;

Status queue_init(Cola *pq);
Bool queue_isEmpty(const Cola *pq);
Bool queue_isFull(const Cola *pq);
Status queue_push(Cola *pq, const Bloque e);
Bloque queue_pop(Cola *pq);

#endif