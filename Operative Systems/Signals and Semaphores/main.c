/**
 * @file main.c
 * @brief Programa principal que simula una elección de candidato.
 *
 * Este programa crea un número determinado de procesos votantes que compiten por ser candidato.
 * Cada votante genera un voto aleatorio y lo guarda en un archivo de votos.
 * El programa principal espera una señal SIGINT o una alarma para finalizar la elección.
 * Al finalizar, se muestra si el candidato ha sido aceptado o rechazado basado en los votos recibidos.
 *
 * El programa utiliza semáforos para sincronizar el acceso al archivo de votos y a la información de los votantes.
 *
 * El programa consta de las siguientes funciones:
 * - principal: función principal que coordina la ejecución de los votantes y el proceso principal.
 * - votante: función que representa a un votante individual.
 * - random_num: función que genera un número aleatorio en un rango dado.
 *
 * @param argc Cantidad de argumentos pasados al programa.
 * @param argv Arreglo de cadenas de caracteres que contienen los argumentos pasados al programa.
 *
 * @return Devuelve EXIT_SUCCESS si el programa se ejecuta correctamente, de lo contrario, devuelve EXIT_FAILURE.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>
#include "misc.h"
#include "handler.h"
#include <time.h>

#define SEM_NAME "/semaforo"
#define SEM_NAME_VOT "/semaforo_vot"

int random_num(int inf, int sup);

volatile sig_atomic_t got_signal = 0, termination = 0, got_signal_alarm = 0;
volatile pid_t candidato = 0;
volatile int selec_candidato = 0;

/**
 * @brief Función principal del programa.
 *
 * Esta función se encarga de ejecutar la lógica principal del programa.
 * Recibe como parámetros un arreglo de identificadores de procesos (voters),
 * el número de procesos (n_procs), el número de segundos (n_secs) y un semáforo (sem).
 *
 * @param voters Arreglo de identificadores de procesos.
 * @param n_procs Número de procesos.
 * @param n_secs Número de segundos.
 * @param sem Puntero al semáforo.
 */
void principal( int n_procs, int n_secs, sem_t *sem)
{
	int i, valor, file;
	int signals[2] = {SIGINT, SIGALRM};
	sigset_t set, oset;

	struct sigaction act_sigint, act_sigalrm, act_sigusr2, act_sigusr1, act_sigterm;
	config_action(&act_sigint, handler_ctrlc, NULL, SIGINT, 0);
	config_action(&act_sigalrm, handler_alrm, NULL, SIGALRM, 0);

	ignore_signal(SIGUSR1, &act_sigusr1);
	ignore_signal(SIGUSR2, &act_sigusr2);
	ignore_signal(SIGTERM, &act_sigterm);

	/*Mandamos señal a los hijos para que luchen por ser candidato*/
	do
	{
		valor = sem_getvalue(sem, &valor);
	} while (valor != 0);
	kill(0, SIGUSR1);
	sem_post(sem);

	/*Empezamos el temporizador*/
	if (alarm(n_secs))
	{
		perror("alarm");
		exit(EXIT_FAILURE);
	}

	/*Esperamos SIGINT o SIGALARM*/

	while (got_signal == 0 && got_signal_alarm == 0)
	{
		sigsuspend(&oset);
	}

	kill(0, SIGTERM);

	for (i = 0; i < n_procs; i++)
	{
		wait(NULL);
	}

	if (got_signal_alarm)
	{
		printf("Finishing by alarm\n");
	}
	else
	{
		printf("Finishing by signal\n");
	}
}

/**
 * @brief Función que simula el comportamiento de un votante.
 *
 * @param n_procs Número de procesos votantes.
 * @param voters Arreglo de identificadores de los procesos votantes.
 * @param file Descriptor de archivo para escribir los resultados de la votación.
 * @param sem Semáforo para controlar el acceso al archivo de resultados.
 * @param sem_vot Semáforo para controlar el acceso a la votación.
 */
void votante(int n_procs, sem_t *sem, sem_t *sem_vot)
{
	int i, semaforo, read_file, valor, file_vot, voto, voto_recibido, first_write, exito, pid;
	int signals[2] = {SIGUSR1, SIGUSR2};

	struct sigaction act, act_sigusr2, act_sigterm;

	srand(time(NULL) ^ (getpid() << 10));

	/*Configuracion del manejo de la señal SIGUSR1y SIGUSR2*/
	config_action(&act, handler, NULL, SIGUSR1, 0);
	config_action(&act_sigusr2, handler, NULL, SIGUSR2, 0);
	config_action(&act_sigterm, handler_term, NULL, SIGTERM, 0);

	/*Mascara para esperar SIGUSR1*/
	sem_wait(sem);
	//suspend_for(signals, 1, 0);
	got_signal = 0;
	while (termination == 0)
	{
		suspend_for(signals, 1, 0);
		got_signal = 0;
		voto = random_num(0, 1);

		if (sem_trywait(sem) == 0)
		{
			/*El candidato*/

			/*Leemos la info*/
			read_file = open("data.bin", O_RDONLY);
			if (read_file == -1)
			{
				perror("open");
				exit(EXIT_FAILURE);
			}
			for (i = 0; i < n_procs; i++)
            {
                read(read_file, &pid, sizeof(int));
                kill(pid, SIGUSR2);
            }
			close(read_file);

			sem_wait(sem_vot);
			file_vot = open("votos.bin", O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (file_vot < 0)
			{
				perror("open");
				exit(EXIT_FAILURE);
			}
			if (write(file_vot, &voto, sizeof(int)) == -1)
			{

				perror("write");
				exit(EXIT_FAILURE);
			}
			first_write = 0;
			close(file_vot);

			sem_post(sem_vot);

			got_signal = 0;
			file_vot = open("votos.bin", O_RDONLY | O_CREAT, 0644);
			if (file_vot < 0)
			{
				perror("open");
				exit(EXIT_FAILURE);
			}

			printf("Candidate %d => [ ", getpid());
			lseek(file_vot, 0, SEEK_SET);
			exito = 0;
			for (int i = 0; i < n_procs; i++)
			{
				read(file_vot, &voto_recibido, sizeof(int));
				usleep(1000);
				if (voto_recibido == 1)
				{
					printf("Y ");
					exito += 1;
				}
				else
				{
					printf("N ");
				}
			}
			close(file_vot);
			if (exito > n_procs / 2)
			{
				printf("] => Accepted\n");
			}
			else
			{
				printf("] => Rejected\n");
			}

			remove("votos.bin");

			/*Penalizacion al candidato para que no se repita*/
			usleep(250000);

			sem_post(sem);
			kill(0, SIGUSR1);
		}
		else
		{
			sem_wait(sem_vot);
			file_vot = open("votos.bin", O_WRONLY | O_CREAT | O_APPEND, 0664);
			if (file_vot < 0)
			{
				perror("open");
				exit(EXIT_FAILURE);
			}
			if (write(file_vot, &voto, sizeof(int)) == -1)
			{
				perror("write");
				exit(EXIT_FAILURE);
			}
			close(file_vot);
			sem_post(sem_vot);
		}
	}
}

/**
 * @file main.c
 * @brief Archivo principal del programa.
 *
 * Este archivo contiene la función principal del programa.
 * La función main se encarga de iniciar la ejecución del programa.
 *
 * @param argc Cantidad de argumentos pasados por línea de comandos.
 * @param argv Arreglo de cadenas de caracteres que representan los argumentos pasados por línea de comandos.
 * @return Valor de retorno del programa.
 */
int main(int argc, char *argv[])
{

	int i = 0, file;
	int n_procs, n_secs;
	pid_t *voters;
	sem_t *sem, *sem_vot;
	sigset_t mask;

	if (argc < 2)
	{
		printf("Not enough arguments were passed\n");
		exit(EXIT_FAILURE);
	}
	/*Lectura de argumentos*/
	n_procs = atoi(argv[1]);
	/*printf("Numero de procesos: %d\n", n_procs);*/
	n_secs = atoi(argv[2]);
	/*printf("Numero de segundos: %d\n", n_secs);*/

	/*Creamos el semaforo*/
	if ((sem = sem_open(SEM_NAME, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, n_procs)) == SEM_FAILED)
	{
		perror("sem_open");
		exit(EXIT_FAILURE);
	}
	sem_unlink(SEM_NAME);

	/*Creamos el semaforo*/
	if ((sem_vot = sem_open(SEM_NAME_VOT, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 1)) == SEM_FAILED)
	{
		perror("sem_open");
		exit(EXIT_FAILURE);
	}
	sem_unlink(SEM_NAME_VOT);

	file = open("data.bin", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (file < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	/*El proceso principal crea n_procs procesos*/
	voters = (pid_t *)malloc(sizeof(pid_t) * n_procs);
	if (!voters)
	{
		printf("Error allocating memory for voters");
		exit(EXIT_FAILURE);
	}
	while ((voters[i] = fork()) != 0 && i < n_procs - 1)
	{
		/*printf("Votante:%d--%d\n", voters[i], i);*/
		i++;
	}

	if (voters[i] == 0)
	{
		close(file);
		votante(n_procs, sem, sem_vot);
		// printf("Exit Votante:%d\n",getpid());
	}
	else
	{
		/*printf("Votante:%d--%d\n", voters[i], i);*/
		write(file, &voters[i], sizeof(pid_t));
		close(file);
		principal( n_procs, n_secs, sem);
	}
	free(voters);
	sem_close(sem);
	sem_close(sem_vot);
	exit(EXIT_SUCCESS);
}

/**
 * @brief Genera un número aleatorio dentro de un rango dado.
 *
 * Esta función toma dos números enteros, `inf` y `sup`, y genera un número aleatorio
 * dentro del rango [inf, sup]. El número generado incluye tanto `inf` como `sup`.
 *
 * @param inf El límite inferior del rango.
 * @param sup El límite superior del rango.
 * @return Un número aleatorio dentro del rango [inf, sup].
 */
int random_num(int inf, int sup)
{
	if (inf < 0 || sup < 0 || inf > sup)
	{
		return -1;
	}

	return inf + (int)((float)(sup - inf + 1) * (rand() / (RAND_MAX + 1.0)));
}