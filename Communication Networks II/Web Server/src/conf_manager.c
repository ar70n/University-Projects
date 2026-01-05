#include "conf_manager.h"


int load_config(char **server_root, char **server_signature, int *max_clients, int* listen_port)
{
    FILE* config_file = fopen("server.conf", "r");
    char line[CONF_BUFF_LENGTH];

    log_message(INFO, "Loading config...");

    if (!config_file)
    {
        return -1;
    }

    while (fgets(line, sizeof(line), config_file)) {
        // Ignorar líneas que empiezan por '#'
        if (line[0] == '#') {
            continue;
        }

        // Eliminar el salto de línea al final de la línea
        line[strcspn(line, "\n")] = 0;

        // Procesar la línea
        if (strncmp(line, "server_root = ", 14) == 0) 
        {
            *server_root = strdup(line + 14);
        } 
        else if (strncmp(line, "server_signature = ", 19) == 0) 
        {
            *server_signature = strdup(line + 19);
        } 
        else if (strncmp(line, "max_clients = ", 14) == 0) 
        {
            *max_clients = atoi(line + 14);
        } 
        else if (strncmp(line, "listen_port = ", 14) == 0) 
        {
            *listen_port = atoi(line + 14);
        }
    }

    fclose(config_file);

    if (max_clients < 0 || listen_port < 0)
    {
        log_message(ERROR, "Invalid configuration. max_clients and listen_port must be greater than 0");
        return -1;
    }

    log_message(INFO, "server_root: %s", *server_root);
    log_message(INFO, "server_signature: %s", *server_signature);
    log_message(INFO, "max_clients: %d", *max_clients);
    log_message(INFO, "listen_port: %d", *listen_port);
    log_message(INFO, "Config loaded!");    

    return 0;
}