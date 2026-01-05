/**
 * @file block.c
 * @authors Manuel Fernández y Antonio Moroño
 * @brief Implementación de las funciones para la manipulación de una cola de bloques.
 *
 * Este archivo contiene la implementación de las funciones necesarias para la manipulación de una cola de bloques.
 * La cola de bloques se utiliza para almacenar y gestionar bloques de datos.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "block.h"

/**
 * @brief Inicializa una cola de bloques.
 *
 * Esta función inicializa una cola de bloques, estableciendo los valores iniciales de los bloques y los índices de la cola.
 *
 * @param pq Puntero a la cola de bloques.
 * @return Estado de la operación (OK si se realizó correctamente, ERROR en caso contrario).
 */
Status queue_init(Cola *pq)
{
    int i;
    if (pq == NULL)
    {
        return ERROR;
    }
    for (i = 0; i < (N_BLOCKS); i++)
    {
        pq->blocks[i].objetivo = -1;
        pq->blocks[i].solucion = -1;
        pq->blocks[i].correcto = -1;
    }
    pq->front = 0;
    pq->rear = 0;
    return OK;
}

/**
 * @brief Verifica si la cola de bloques está vacía.
 *
 * Esta función verifica si la cola de bloques está vacía, es decir, si no contiene ningún bloque.
 *
 * @param pq Puntero a la cola de bloques.
 * @return Valor lógico que indica si la cola está vacía (TRUE) o no (FALSE).
 */
Bool queue_isEmpty(const Cola *pq)
{
    if (pq == NULL)
    {
        return TRUE;
    }
    if (pq->front == pq->rear)
    {
        return TRUE;
    }
    return FALSE;
}

/**
 * @brief Verifica si la cola de bloques está llena.
 *
 * Esta función verifica si la cola de bloques está llena, es decir, si no se pueden agregar más bloques a la cola.
 *
 * @param pq Puntero a la cola de bloques.
 * @return Valor lógico que indica si la cola está llena (TRUE) o no (FALSE).
 */
Bool queue_isFull(const Cola *pq)
{
    if (pq == NULL)
    {
        return TRUE;
    }

    if (pq->front == ((pq->rear + 1) % (N_BLOCKS)))
    {
        return TRUE;
    }
    return FALSE;
}

/**
 * @brief Agrega un bloque a la cola de bloques.
 *
 * Esta función agrega un bloque a la cola de bloques, siempre y cuando la cola no esté llena.
 *
 * @param pq Puntero a la cola de bloques.
 * @param e Bloque a agregar a la cola.
 * @return Estado de la operación (OK si se realizó correctamente, ERROR en caso contrario).
 */
Status queue_push(Cola *pq, const Bloque e)
{
    if (pq == NULL  || queue_isFull(pq) == TRUE)
    {
        return ERROR;
    }

    pq->blocks[pq->rear] = e;

    pq->rear = (pq->rear + 1) % (N_BLOCKS);
    return OK;
}

/**
 * @brief Elimina y devuelve el bloque del frente de la cola de bloques.
 *
 * Esta función elimina y devuelve el bloque del frente de la cola de bloques, siempre y cuando la cola no esté vacía.
 *
 * @param pq Puntero a la cola de bloques.
 * @return Bloque del frente de la cola (si la cola no está vacía) o un bloque con valores -1 en caso contrario.
 */
Bloque queue_pop(Cola *pq)
{
    Bloque e, aux;
    e.objetivo = -1;
    e.solucion = -1;
    e.correcto = -1;
    if (pq == NULL || queue_isEmpty(pq) == TRUE)
    {
        return e;
    }
    e = pq->blocks[pq->front];
    aux = e;
    aux.correcto = -1;
    pq->blocks[pq->front] = aux;
    pq->front = (pq->front + 1) % (N_BLOCKS);
    return e;
}
