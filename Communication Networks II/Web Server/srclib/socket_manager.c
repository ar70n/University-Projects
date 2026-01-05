/*******************************************************
* Práctica 1 redes II
* Autores:
* Jorge Jiménez Oropesa y Antonio Moroño Moreno
* Descripcion:
* Librería que contiene las funciones necesarias para
* la creación de sockets y la comunicación entre ellos.
********************************************************/

#include "socket_manager.h"

/*******************************************************************************
* FUNCIÓN: 	int s_create(int domain, int type, int protocol)

* ARGS_IN: 	int domain: dominio del socket, normalmente AF_INET
            int type: tipo del socket, normalmente SOCK_STREAM
            int protocol: protocolo del socket, normalmente 0

* DESCRIPCIÓN: Crea un socket con los parámetros pasados por argumento.

* ARGS_OUT: int: descriptor del socket creado
*********************************************************************************/
int s_create(int domain, int type, int protocol) {
    return socket(domain, type, protocol);
}


//Bind
int s_bind(int sockfd, int port) {    
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    return bind(sockfd, (struct sockaddr*)&addr, (socklen_t)sizeof(addr));
}

//Listen
int s_listen(int sockfd, int max_clients) {
    if (sockfd < 0 || max_clients < 0)
        return -1;

    return listen(sockfd, max_clients);
}

//Accept
int s_accept(int sockfd) {
    struct sockaddr addr; //Aqui vamos a guardar la direccion entrante.
    socklen_t addr_len = sizeof(addr);
    int newsockfd = accept(sockfd, (struct sockaddr*)&addr, &addr_len);
    if (newsockfd < 0) {
        return -1;
    }
    return newsockfd;
}

//Recv
int s_recv(int sockfd, char *buffer, int len) {
    if (!buffer)
        return -1;

    return recv(sockfd, buffer, len, 0);
}

//Send
int s_send(int sockfd, unsigned char *buffer, int len) {
    if (!buffer)
        return -1;

    return send(sockfd, buffer, len, 0);
}

//Close
int s_close(int sockfd){
    return close(sockfd);
}