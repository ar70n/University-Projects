/**
 * @file misc.c
 * @brief Implementación de funciones misceláneas.
 */
#include "misc.h"



/**
 * @brief Pausa la ejecución del programa hasta que se reciba una señal específica.
 * 
 * Esta función bloquea la ejecución del programa hasta que se reciba una de las señales
 * especificadas en el arreglo `SIG`. La función utiliza `sigsuspend` para suspender la
 * ejecución y espera a que la variable global `got_signal` sea verdadera.
 * 
 * @param SIG Arreglo de enteros que contiene las señales a esperar.
 * @param num Número de señales en el arreglo `SIG`.
 * @param init Índice inicial del arreglo `SIG` desde donde comenzar a esperar señales.
 */
void suspend_for(int *SIG, int num, int init)
{
	int i;
	sigset_t mask, oldmask;
	extern sig_atomic_t got_signal;
	
	sigemptyset(&mask);

	for(i=init;i<num+init;i++){
		sigaddset(&mask, SIG[i]);
	}
	sigprocmask(SIG_BLOCK, &mask, &oldmask);
	

	while (!got_signal)
		sigsuspend(&oldmask);
	sigprocmask(SIG_UNBLOCK, &mask, NULL);
}


/**
 * @brief Configura la acción a tomar cuando se recibe una señal específica.
 * 
 * Esta función configura la acción a tomar cuando se recibe la señal `SIG`. La acción
 * puede ser un manejador de señal (`handler`) o una función de manejo de señal con
 * información adicional (`handler_sa_sigaction`). El parámetro `flags` indica si se
 * utiliza `handler` o `handler_sa_sigaction`.
 * 
 * @param act Puntero a una estructura `struct sigaction` que representa la acción a configurar.
 * @param handler Puntero a una función de manejo de señal.
 * @param handler_sa_sigaction Puntero a una función de manejo de señal con información adicional.
 * @param SIG Señal a la que se le va a configurar la acción.
 * @param flags Indica si se utiliza `handler` o `handler_sa_sigaction`. Puede ser `SA_SIGINFO` o `0`.
 */
void config_action(struct sigaction *act, handler_t handler,handler_sa_sigaction_t handler_sa_sigaction, int SIG, int flags)
{
	sigemptyset(&(act->sa_mask));
	act->sa_flags = flags;

	if (flags==SA_SIGINFO && handler==NULL)
	{
		act->sa_sigaction = handler_sa_sigaction;
	}
	else
	{
		act->sa_handler = handler;
	}
	
	

	if (sigaction(SIG, act, NULL) < 0)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
}


/**
 * @brief Ignora una señal específica.
 * 
 * Esta función configura la acción a tomar cuando se recibe la señal `SIG` para que sea ignorada.
 * 
 * @param SIG Señal a la que se le va a configurar la acción de ignorar.
 * @param act Puntero a una estructura `struct sigaction` que representa la acción a configurar.
 */
void ignore_signal(int SIG,struct sigaction *act) {
	
	act->sa_handler = SIG_IGN;
	sigemptyset(&(act->sa_mask));
	act->sa_flags = 0;
	
	if (sigaction(SIG, act, NULL) < 0) {
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
}
