#ifndef CONF_MANAGER_H
#define CONF_MANAGER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "log.h"

#define CONF_BUFF_LENGTH 200

/*******************************************************************************
 * FUNCIÓN: 	load_config(char **server_root, char **server_signature, int *max_clients, int* listen_port)
 *
 * ARGS_IN:     char **server_root: Puntero a la cadena de caracteres que contendrá la ruta del servidor
 *              char **server_signature: Puntero a la cadena de caracteres que contendrá la firma del servidor
 *              int *max_clients: Puntero al entero que contendrá el número máximo de clientes
 *              int* listen_port: Puntero al entero que contendrá el puerto de escucha
 *
 * DESCRIPCIÓN: Carga la configuración del servidor desde el archivo de configuración
 *
 * ARGS_OUT: int : 0 si se ha cargado la configuración correctamente, -1 en caso contrario
 * *****************************************************************************/
int load_config(char **server_root, char **server_signature, int *max_clients, int* listen_port);

#endif