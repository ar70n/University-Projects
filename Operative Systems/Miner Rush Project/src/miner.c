#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <semaphore.h>
#include "block.h"
#include "pow.h"
#include <pthread.h>

#define SHM_NAME "/shm_miner"

volatile sig_atomic_t got_signal_usr1 = 0;
volatile sig_atomic_t got_signal_usr2 = 0;
volatile sig_atomic_t got_signal_fin = 0;
long int flag, objective;

void handler(int signum);
Status memory_init(Memoria *memoria);
void registrador(int *father_to_son);
void *threadf(void *miners);
void minar(int threads, int *father_to_son, int n_seconds);
void vote(Memoria *memoria, int my_id);
void exit_miner(Memoria *memoria, int my_id, int *father_to_son, sem_t *sem, mqd_t mq);

int main(int argc, char *argv[])
{
    int secs, hilos, father_to_son[2], pipe_status, i;
    pid_t pid;
    Bool end_votation = FALSE;

    int fd_shm, sem_value, my_id;
    struct stat sb;
    Memoria *memoria;
    sem_t *sem;
    mqd_t mq;
    struct mq_attr attributes;
    Bool ready = FALSE;
    struct sigaction act;
    sigset_t set_usr1, oset_usr1, set_usr2, oset_usr2;

    if (argc != 3)
    {
        fprintf(stderr, "Usage %s <N_SECONDS> <N_THREADS>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    secs = atoi(argv[1]);
    hilos = atoi(argv[2]);

    pipe_status = pipe(father_to_son);
    if (pipe_status == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // CREACION DEL REGISTRADOR
    /*Minero*/
    if ((pid = fork()) != 0)
    {
        // CONFIGURAMOS LOS MANEJADORES DE SEÑALES
        act.sa_handler = handler;
        sigemptyset(&(act.sa_mask));
        act.sa_flags = 0;

        if (sigaction(SIGUSR1, &act, NULL) < 0)
        {
            perror("sigaction");
            exit(EXIT_FAILURE);
        }

        if (sigaction(SIGUSR2, &act, NULL) < 0)
        {
            perror("sigaction");
            exit(EXIT_FAILURE);
        }

        if (sigaction(SIGALRM, &act, NULL) < 0)
        {
            perror("sigaction");
            exit(EXIT_FAILURE);
        }

        if (sigaction(SIGINT, &act, NULL) < 0)
        {
            perror("sigaction");
            exit(EXIT_FAILURE);
        }

        // bloqueamos las señales hasta que pasen la seccion critica
        sigemptyset(&set_usr1);
        sigaddset(&set_usr1, SIGUSR1);
        sigemptyset(&set_usr2);
        sigaddset(&set_usr2, SIGUSR2);
        
        if (pthread_sigmask(SIG_BLOCK, &set_usr1, &oset_usr1) < 0)
        {
            perror("pthread_sigmask");
            exit(EXIT_FAILURE);
        }

        if (pthread_sigmask(SIG_BLOCK, &set_usr2, &oset_usr2) < 0)
        {
            perror("pthread_sigmask");
            exit(EXIT_FAILURE);
        }

        alarm(secs);


        // CONEXION A MEMORIA
        fd_shm = shm_open(SHM_NAME, O_RDWR | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR);
        /*Aquí entran todos los que no son el primer minero*/
        if (fd_shm == -1)
        {
            fd_shm = shm_open(SHM_NAME, O_RDWR, 0);
            if (fd_shm == -1)
            {
                perror("shm_open");
                exit(EXIT_FAILURE);
            }

            while (ready == FALSE)
            {
                if (fstat(fd_shm, &sb) != 0)
                {
                    perror("fstat");
                    exit(EXIT_FAILURE);
                }

                if (sb.st_size != sizeof(Memoria))
                {
                    sleep(1);
                    continue;
                }
                memoria = mmap(NULL, sizeof(Memoria), PROT_READ | PROT_WRITE, MAP_SHARED, fd_shm, 0);
                if (memoria == MAP_FAILED)
                {
                    perror("mmap");
                    exit(EXIT_FAILURE);
                }
                sem_getvalue(&memoria->sem, &sem_value);
                if (sem_value != 1)
                {
                    munmap(memoria, sizeof(Memoria));
                    sleep(1);
                    continue;
                }
                ready = TRUE;
            }
            close(fd_shm);

            mq = mq_open(MQ_NAME, O_WRONLY);
            if (mq == (mqd_t)-1)
            {
                perror("mq_open");
                exit(EXIT_FAILURE);
            }

            sem = sem_open(SEM_NAME, O_RDWR);
            if (sem == SEM_FAILED)
            {
                perror("sem_open");
                exit(EXIT_FAILURE);
            }

            // REGISTRO DEL MINERO
            sem_wait(&memoria->sem);
            if (memoria->minerosActivos == MAX_MINERS)
            {
                fprintf(stderr, "No se pueden crear más mineros\n");
                sem_post(&memoria->sem);
                exit_miner(memoria, -1, father_to_son, sem, mq);
            }
            else
            {
                for (i = 0; i < MAX_MINERS; i++)
                {
                    if (memoria->pidMineros[i] == -1)
                    {
                        memoria->pidMineros[i] = getpid();
                        my_id = i;
                        memoria->resolviendo.wallets[my_id].id = getpid();
                        memoria->minerosActivos++;
                        break;
                    }
                }
            }
            sem_post(&memoria->sem);
        }
        else
        { // PRIMER MINERO

            // Inicializacon cola de mensajes y semaforo con nombre
            if ((sem = sem_open(SEM_NAME, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 0)) == SEM_FAILED)
            {
                sem = sem_open(SEM_NAME, O_RDWR);
                if (sem == SEM_FAILED)
                {
                    perror("sem_open");
                    exit(EXIT_FAILURE);
                }
            }

            attributes.mq_maxmsg = 7;
            attributes.mq_msgsize = sizeof(Bloque);
            if ((mq = mq_open(MQ_NAME, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR, &attributes)) == (mqd_t)-1)
            {
                sem_close(sem);
                perror("mq_open");
                exit(EXIT_FAILURE);
            }

            // Inicializacion de la memoria compartida
            if (ftruncate(fd_shm, sizeof(Memoria)) == -1)
            {
                perror("ftruncate");
                exit(EXIT_FAILURE);
            }
            memoria = mmap(NULL, sizeof(Memoria), PROT_READ | PROT_WRITE, MAP_SHARED, fd_shm, 0);
            close(fd_shm);
            if (memoria == MAP_FAILED)
            {
                perror("mmap");
                shm_unlink(SHM_NAME);
                exit(EXIT_FAILURE);
            }
            my_id = 0;
            memory_init(memoria);

            // PREPARACION
            sem_wait(&memoria->sem);
            memoria->resolviendo.target = 0;
            for (i = 0; i < MAX_MINERS; i++)
            {
                if (memoria->pidMineros[i] != -1)
                {
                    kill(memoria->pidMineros[i], SIGUSR1);
                }
                
            }
            sem_post(&memoria->sem);
        }
  
        while (1)
        {
            // Comprobamos si hemos recibido una señal de fin
            if (got_signal_fin == 1)
            {
                exit_miner(memoria, my_id, father_to_son, sem, mq);
            }

            // Si es el primer minero no entra en el bucle si no lo es, entra.
            while (!got_signal_usr1)
            {
                sigsuspend(&oset_usr1);
            }

            got_signal_usr1 = 0;

            // MINADO
            minar(hilos, father_to_son, secs);

            // PROCLAMACION DEL GANADOR
            if (sem_trywait(&memoria->sem_winner) == 0) // Si hemos encontrado la solucion mandamos la señal SIGUSR2
            {
                sem_wait(&memoria->sem);
                memoria->resolviendo.id = memoria->lastResuelto.id + 1;
                memoria->resolviendo.idGanador = getpid();
                memoria->resolviendo.solucion = flag;
                memoria->resolviendo.numVotosTotales = 0;
                memoria->resolviendo.numVotosPositivos = 0;
                for (i = 0; i < MAX_MINERS; i++)
                {
                    if (memoria->pidMineros[i] != -1)
                    {
                        kill(memoria->pidMineros[i], SIGUSR2);
                    }
                }

                vote(memoria, my_id);
                sem_post(&memoria->sem);

                i = 0;

                while (end_votation == FALSE)
                {
                    sem_wait(&memoria->sem);
                    if (memoria->resolviendo.numVotosTotales == memoria->minerosActivos || i >= MAX_TRIES)
                    {
                        end_votation = TRUE;
                    }
                    sem_post(&memoria->sem);
                    i++;
                    usleep(5000);
                }
                end_votation = FALSE;

                sem_wait(&memoria->sem);
                if (memoria->resolviendo.numVotosPositivos >= memoria->minerosActivos / 2)
                {
                    memoria->resolviendo.correcto = 1;
                    memoria->resolviendo.wallets[my_id].monedas++;
                }
                else
                {
                    memoria->resolviendo.correcto = 0;
                }
                sem_post(&memoria->sem);

                if (sem_trywait(sem) == 0)
                {
                    mq_send(mq, (const char *)&memoria->resolviendo, sizeof(Bloque), 0);
                }

                sem_wait(&memoria->sem);
                memoria->lastResuelto = memoria->resolviendo;
                memoria->resolviendo.target = memoria->lastResuelto.solucion;
                objective = memoria->resolviendo.target;

                for (i = 0; i < MAX_MINERS; i++)
                {
                    if (memoria->pidMineros[i] != -1)
                    {
                        kill(memoria->pidMineros[i], SIGUSR1);
                    }
                }
                sem_post(&memoria->sem);

                sem_post(&memoria->sem_winner);
            }
            else
            {
                while (!got_signal_usr2)
                {
                    sigsuspend(&oset_usr2);
                }

                got_signal_usr2 = 0;

                sem_wait(&memoria->sem);
                vote(memoria, my_id);
                sem_post(&memoria->sem);
            }

            write(father_to_son[1], &memoria->lastResuelto, sizeof(Bloque));
        }
        close(father_to_son[1]);
        waitpid(pid, NULL, 0);
    }
    /*Registrador*/
    else
    {
        registrador(father_to_son);
    }
}

void minar(int threads, int *father_to_son, int n_seconds)
{
    long int space, i, counter;
    pthread_t *h;
    Miner_data *miners;

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

    flag = -1;
    /*Crea los hilos*/
    for (i = 0; i < threads; i++)
    {
        if (pthread_create(&h[i], NULL, threadf, &miners[i]) != 0)
        {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    for (i = 0; i < threads; i++)
    {
        pthread_join(h[i], NULL);
    }

    free(miners);
    free(h);
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

    while (i <= aux->fin && flag == -1)
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

void registrador(int *father_to_son)
{
    char pid_str[10];
    int file, tube, i;
    Bloque result;

    close(father_to_son[1]);

    sprintf(pid_str, "%d", getpid());
    file = open(pid_str, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);

    while (1)
    {
        tube = read(father_to_son[0], &result, sizeof(result));

        if (tube == -1)
        {
            perror("read");
            exit(EXIT_FAILURE);
        }
        else if (tube == 0)
        {
            close(file);
            close(father_to_son[0]);
            exit(EXIT_SUCCESS);
        }

        if (result.correcto == 1)
        {
            dprintf(file, "Id:\t%04ld\nWinner:\t%04ld\nTarget:\t%08ld\nSolution:\t%08ld  (validated)\nVotes:\t%d/%d\nWallets:\t", result.id, result.idGanador, result.target, result.solucion, result.numVotosPositivos, result.numVotosTotales);
        }
        else if (result.correcto == 0)
        {
            dprintf(file, "Id:\t%04ld\nWinner:\t%04ld\nTarget:\t%08ld\nSolution:\t%08ld  (rejected)\nVotes:\t%d/%d\nWallets:\t", result.id, result.idGanador, result.target, result.solucion, result.numVotosPositivos, result.numVotosTotales);
        }

        for (i = 0; i < result.numVotosTotales; i++)
        {
            dprintf(file, "\t%04d:%02d", result.wallets[i].id, result.wallets[i].monedas);
        }
        dprintf(file, "\n");
    }
}

Status memory_init(Memoria *memoria)
{
    int i, my_id;
    if (memoria == NULL)
    {
        return ERROR;
    }
    memoria->pidMineros[0] = getpid();
    memoria->votosMineros[0] = 0;
    memoria->monedasMineros[0] = 0;
    for (i = 1; i < MAX_MINERS; i++)
    {
        memoria->pidMineros[i] = -1;
        memoria->votosMineros[i] = 0;
        memoria->monedasMineros[i] = 0;
        memoria->resolviendo.wallets[i].id = -1;
        memoria->resolviendo.wallets[i].monedas = 0;
    }
    memoria->resolviendo.id = 0;
    memoria->resolviendo.target = -1;
    memoria->resolviendo.solucion = -1;
    memoria->resolviendo.idGanador = -1;
    memoria->resolviendo.numVotosTotales = 0;
    memoria->resolviendo.numVotosPositivos = 0;
    memoria->resolviendo.correcto = -1;
    memoria->lastResuelto.id = 0;
    memoria->lastResuelto.target = -1;
    memoria->lastResuelto.solucion = -1;
    memoria->lastResuelto.idGanador = -1;
    memoria->lastResuelto.numVotosTotales = 0;
    memoria->lastResuelto.numVotosPositivos = 0;
    memoria->lastResuelto.correcto = -1;
    memoria->minerosActivos = 0;

    my_id = 0;
    memoria->resolviendo.wallets[my_id].id = getpid();
    memoria->pidMineros[my_id] = getpid();
    memoria->minerosActivos += 1;

    if (sem_init(&memoria->sem_winner, 1, 1))
    {
        return ERROR;
    }
    if (sem_init(&memoria->sem, 1, 1))
    {
        return ERROR;
    }
    return OK;
}

void handler(int signum)
{
    if (signum == SIGUSR1)
    {
        got_signal_usr1 = 1;
    }
    else if (signum == SIGUSR2)
    {
        got_signal_usr2 = 1;
    }
    else if (signum == SIGALRM || signum == SIGINT)
    {
        got_signal_fin = 1;
    }
}

void vote(Memoria *memoria, int my_id)
{
    if (pow_hash(memoria->resolviendo.solucion) == memoria->resolviendo.target)
    {
        memoria->votosMineros[my_id] = 1;
        memoria->resolviendo.numVotosPositivos++;
    }
    else
    {
        memoria->votosMineros[my_id] = 0;
    }
    memoria->resolviendo.numVotosTotales++;
}

void exit_miner(Memoria *memoria, int my_id, int *father_to_son, sem_t *sem, mqd_t mq)
{

    int i;
    if (my_id != -1)
    {
        sem_wait(&memoria->sem);
        memoria->pidMineros[my_id] = -1;
        memoria->votosMineros[my_id] = 0;
        memoria->monedasMineros[my_id] = 0;
        memoria->resolviendo.wallets[my_id].id = -1;
        memoria->resolviendo.wallets[my_id].monedas = 0;
        memoria->minerosActivos--;
        i = memoria->minerosActivos;
        if (i == 0)
        {
            memoria->resolviendo.correcto = -1;
            mq_send(mq, (const char *)&memoria->resolviendo, sizeof(Bloque), 0);
            sem_destroy(&memoria->sem_winner);
            sem_destroy(&memoria->sem);
        }
        else
        {
            sem_post(&memoria->sem);
        }
    }
    munmap(memoria, sizeof(Memoria));
    if (i == 0)
    {
        sem_close(sem);
        mq_close(mq);
        sem_unlink(SEM_NAME);
        mq_unlink(MQ_NAME);
        shm_unlink(SHM_NAME);
    }
    else
    {
        sem_close(sem);
        mq_close(mq);
    }
    close(father_to_son[1]);
    exit(EXIT_SUCCESS);
}
