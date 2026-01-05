#ifndef SOCKET_MANAGER_H
#define SOCKET_MANAGER_H

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int s_create(int domain, int type, int protocol);
int s_bind(int sockfd, int port);
int s_listen(int sockfd, int max_clients);
int s_accept(int sockfd);
int s_recv(int sockfd, char *buffer, int len);
int s_send(int sockfd, unsigned char *buffer, int len);
int s_close(int sockfd);

#endif