#ifndef HTTP_MANAGER_H
#define HTTP_MANAGER_H

#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <sys/wait.h>
#include "socket_manager.h"
#include "log.h"

typedef struct _http_response http_response;
typedef struct _http_args http_args;
typedef struct _http_parse http_parse;

typedef enum {
    HTTP_OK = 200,
    HTTP_BAD_REQUEST = 400,
    HTTP_NOT_FOUND = 404,
    HTTP_SERVER_ERROR = 500
} http_response_codes;

typedef enum{
    GET,
    POST,
    OPTIONS
} http_verbs;

typedef enum{
    html,
    gif,
    jpeg,
    png,
    css,
    js,
    py,
    php,
    txt,
    unrecognized
} http_file_extensions;

/*******************************************************************************
 * FUNCIÓN: 	init_http_manager(char *root, char *signature)
 *
 * ARGS_IN:     char *root: directorio raíz del servidor
 *              char *signature: firma del servidor
 *
 * DESCRIPCIÓN: Inicializa las variables pertinentes
 *
 * ARGS_OUT: void
 * *****************************************************************************/
void init_http_manager(char *root, char *signature);

/*******************************************************************************
 * FUNCIÓN: 	close_http_manager()
 *
 * DESCRIPCIÓN: Libera los recursos utilizados por el módulo
 *
 * ARGS_OUT: void
 * *****************************************************************************/
void close_http_manager();

/*******************************************************************************
 * FUNCIÓN: 	http_parse_petition(char *buff)
 *
 * ARGS_IN:     char *buff: buffer con la petición HTTP
 *
 * DESCRIPCIÓN: Parsea la petición HTTP y la responde. 
 *              Retorna el código de la respuesta
 *
 * ARGS_OUT: char*: path solicitado
 * *****************************************************************************/
http_response* http_parse_petition(char *buff);

/*******************************************************************************
 * FUNCIÓN: 	http_respond(int connection_socket,char* reply)
 *
 * ARGS_IN:     int connection_socket: socket de conexión
 *              char* reply: respuesta a la petición
 *
 * DESCRIPCIÓN: Responde a la petición HTTP
 *
 * ARGS_OUT: void
 * *****************************************************************************/
void http_respond(int connection_socket, http_response* reply);

#endif