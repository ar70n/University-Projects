#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include "socket_manager.h"
#include "thread_manager.h"
#include "http_manager.h"
#include "conf_manager.h"
#include <errno.h>
#include <signal.h>
#include "log.h"

#define MAX_CLIENTS 1
#define PORT 4444
#define BUFF_LENGTH 1024

int main(int argc, char **argv)
{
    char buff[BUFF_LENGTH];
    int socket_fd, connection_socket;
    
    socket_fd = s_create(AF_INET, SOCK_STREAM, 0); //Create socket
    
    if(s_bind(socket_fd, PORT) < 0) //Bind socket to port
        return -1;

    
    if(s_listen(socket_fd, MAX_CLIENTS) < 0) //Listen
        return -1;
    
    printf("Tamos ready to fight\n");

    while(1)
    {
        connection_socket = s_accept(socket_fd); //Accept

        while(1)
        {
            if (s_recv(connection_socket, buff, BUFF_LENGTH)<0) //Recv
                return -1;

            printf("%s", buff);
            memset(buff, 0, BUFF_LENGTH);
            break;
        }        
    }
}