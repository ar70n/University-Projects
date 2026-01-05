/**
 * @file miner.c
 * @authors Manuel Fernández y Antonio Moroño
 * @brief Este archivo contiene el código fuente del programa principal "miner".
 * El programa genera bloques y los envía a una cola de mensajes.
 * Cada bloque se genera mediante un proceso de minería que busca una solución
 * que cumpla con un objetivo dado.
 * El número de bloques generados y el retraso entre cada generación se especifican
 * como argumentos de línea de comandos al ejecutar el programa.
 */
#include <stdio.h>
#include <mqueue.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "pow.h"
#include "block.h"

int main(int argc, char *argv[])
{
    long int i = 0, j = 0;
    struct mq_attr attributes;
    mqd_t mq;
    Bloque block;
    Bool flag = TRUE;
    int rounds, lag;
    if (argc != 3)
    {
        fprintf(stderr, "Error: Invalid arguments\n");
        return 1;
    }
    rounds = atoi(argv[1]);
    lag = atoi(argv[2]);
    if (rounds < 0 || lag < 0)
    {
        fprintf(stderr, "Error: Invalid arguments\n");
        return 1;
    }
    if (rounds < 0 || lag < 0)
    {
        fprintf(stderr, "Error: Invalid arguments\n");
        return 1;
    }
    attributes.mq_maxmsg = 7;
    attributes.mq_msgsize = sizeof(Bloque);
    if ((mq = mq_open(MQ_NAME, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR, &attributes)) == (mqd_t)-1)
    {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }
    fprintf(stdout, "[%d] Generating blocks...\n", getpid());

    block.solucion = 0;
    block.correcto = 0;
    block.objetivo = 0;
    while (j < rounds)
    {
        while (flag == TRUE)
        {   
            if (block.objetivo == pow_hash(i))
            {
                block.correcto = 1;
                block.solucion = i;
                if (mq_send(mq, (char *)&block, sizeof(block), 1) == -1)
                {
                    perror("mq_send");
                    mq_close(mq);
                    exit(EXIT_FAILURE);
                }
                usleep(lag);
                block.objetivo = i;
                flag = FALSE;
            }
            i++;
        }
        i = 0;
        block.solucion = 0;
        block.correcto = 0;
        flag = TRUE;
        j++;
    }

    block.correcto = -1;
    if (mq_send(mq, (char *)&block, sizeof(Bloque), 1) == -1)
    {
        perror("mq_send");
        mq_close(mq);
        exit(EXIT_FAILURE);
    }

    mq_close(mq);
    fprintf(stdout, "[%d] Finishing\n", getpid());

    return 0;
}