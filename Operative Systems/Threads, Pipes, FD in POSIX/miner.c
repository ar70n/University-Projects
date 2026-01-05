/**
 * @brief Implements the miner process
 *
 * @file miner.c
 * @author Manuel Fernández
 * @author Antonio Moroño
 * @date 1-03-2024
 */

#include <stdio.h>
#include <stdlib.h>
#include "pow.h"
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * @brief Miner_data
 *
 * This struct stores the start and end intervals where the threads will search for the solution
 */
typedef struct
{
    long int inicio;
    long int fin;
} Miner_data;

/**
 * This global variables store the solution we may find and the objective we are looking for
 */
long int flag, objective;

/**
 * @brief Function executed by the thread.
 * 
 * @param args The arguments passed to the thread.
 * @return void* The return value of the thread.
 */
void *threadf(void *args);

/**
 * @brief Function to monitor the communication between the father and son processes.
 * 
 * @param father_to_son The communication channel from father to son.
 * @param son_to_father The communication channel from son to father.
 */
void monitor(int *father_to_son, int *son_to_father);

/**
 * @brief Function to perform mining operations.
 * 
 * @param argv The command line arguments passed to the program.
 */
void miner(char *argv[]);

/**
 * @brief Main function
 *
 * This function is the main function of the miner process
 *
 * @param argc number of arguments
 * @param argv arguments
 *
 * @return EXIT_SUCCESS if the program ends correctly, EXIT_FAILURE otherwise
 */
int main(int argc, char *argv[])
{

    int pid_miner;
    if (argc < 3)
    {
        printf("Not enough arguments were passed");
        exit(EXIT_FAILURE);
    }

    /*Creacion proceso minero*/
    pid_miner = fork();
    if (pid_miner == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    /*Miner process*/
    if (pid_miner == 0)
    {
        miner(argv);
    }
    waitpid(pid_miner, NULL, 0);
    printf("Miner exited with status %d\n", WEXITSTATUS(pid_miner));
    exit(EXIT_SUCCESS);
}


void *threadf(void *miners)
{
    long int i;
    Miner_data *aux = miners;

    if (!miners)
    {
        pthread_exit(NULL);
    }
    i = aux->inicio;

    while (i <= aux->fin)
    {
        if (objective == pow_hash(i))
        {

            if (flag == -1)
            {
                flag = i;
            }
            pthread_exit(NULL);
        }
        i++;
    }
    pthread_exit(NULL);
}

void miner(char *argv[])
{
    int i, j = 0, error, rounds, threads, counter, pid_monitor, father_to_son[2], son_to_father[2], pipe_status;
    pthread_t *h;
    Miner_data *miners;
    long int space, result[2];

    int check;

    /*Creacion de la tuberia*/
    pipe_status = pipe(father_to_son);
    if (pipe_status == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pipe_status = pipe(son_to_father);
    if (pipe_status == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    /*Creacion proceso monitor*/
    pid_monitor = fork();
    if (pid_monitor == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    /*Monitor process*/

    if (pid_monitor != 0)
    {
        close(father_to_son[0]);
        close(son_to_father[1]);

        objective = atol(argv[1]);
        printf("Objective: %ld\n", objective);
        rounds = atoi(argv[2]);
        printf("Rounds: %d\n", rounds);
        threads = atoi(argv[3]);
        printf("Threads: %d\n", threads);

        flag = 0;

        h = (pthread_t *)malloc(sizeof(pthread_t) * threads);
        if (!h)
        {
            exit(EXIT_FAILURE);
        }
        miners = (Miner_data *)malloc(sizeof(Miner_data) * threads);
        if (!miners)
        {
            free(h);
            exit(EXIT_FAILURE);
        }

        /*Divides each space*/
        space = POW_LIMIT / threads;
        counter = 0;
        for (i = 0; i < threads; i++)
        {
            miners[i].inicio = counter;
            miners[i].fin = space + counter + 1;
            counter += space;
        }

        while (j < rounds)
        {

            flag = -1;
            /*Crea los hilos*/
            for (i = 0; i < threads; i++)
            {
                error = pthread_create(&h[i], NULL, threadf, &miners[i]);
                if (error != 0)
                {
                    fprintf(stderr, "pthread_create: %s\n", strerror(error));
                    exit(EXIT_FAILURE);
                }
            }

            for (i = 0; i < threads; i++)
            {
                pthread_join(h[i], NULL);
            }

            /*Escribimos en la tuberia*/
            result[0] = flag;
            result[1] = objective;
            write(father_to_son[1], &result, sizeof(result));

            read(son_to_father[0], &check, sizeof(check));

            if (check == 0)
            {
                printf("The solution has been invalidated\n");
                exit(EXIT_FAILURE);
            }

            /*Reasignamos argumentos*/
            objective = flag;
            j++;
        }
        close(father_to_son[1]);


        waitpid(pid_monitor, NULL, 0);

        printf("Monitor exited with status %d\n", WEXITSTATUS(pid_monitor));

        exit(EXIT_SUCCESS);
        free(miners);
        free(h);
    }
    if (pid_monitor == 0)
    {
        monitor(father_to_son, son_to_father);
    }
}

void monitor(int *father_to_son, int *son_to_father)
{
    int open = 1, check;
    long int result[2];

    close(son_to_father[0]);
    close(father_to_son[1]);
    while (1)
    {
        open = read(father_to_son[0], &result, sizeof(result));
        if (open == -1)
        {
            perror("read");
            exit(EXIT_FAILURE);
        }
        else if (open == 0)
        {
            exit(EXIT_SUCCESS);
        }
        if (pow_hash(result[0]) == result[1])
        {
            printf("Solución accepted: %08ld -> %08ld\n", result[1], result[0]);
            check = 1;
        }
        else
        {
            printf("Solución rejected: %08ld !-> %08ld\n", result[1], result[0]);
            check = 0;
        }
        write(son_to_father[1], &check, sizeof(int));
    }
}