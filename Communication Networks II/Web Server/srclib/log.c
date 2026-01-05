#include "log.h"

#define LOG_FILE "./log/server.log"

char *logtype_to_string(LogType logtype);

// Función para inicializar el archivo de log
void init_log() 
{
    FILE *file = fopen(LOG_FILE, "w");

    if (file == NULL) {
        log_message(ERROR, "Error opening log file");
        exit(EXIT_FAILURE);
    }

    fclose(file);
}

// Función para registrar un mensaje en el archivo de log
void log_message(LogType logtype, char *format, ...) 
{
    FILE *file = fopen(LOG_FILE, "a");
    if (file == NULL) {
        log_message(ERROR, "Error opening log file");
        exit(EXIT_FAILURE);
    }

    // Obtener la hora actual
    time_t now = time(NULL);
    char *time_str = ctime(&now);
    time_str[strlen(time_str) - 1] = '\0'; // Eliminar el salto de línea

    // Escribir la hora en el archivo de log
    fprintf(file, "[%s] [thread id %ld] [%s]: ", time_str, pthread_self(), logtype_to_string(logtype));

    // Manejar los argumentos variables
    va_list args;
    va_start(args, format);
    vfprintf(file, format, args);
    va_end(args);

    fprintf(file, "\n");
    fclose(file);
}

//Logtype to string
char *logtype_to_string(LogType logtype)
{
    switch (logtype)
    {
    case INFO:
        return "INFO";
    case WARNING:
        return "WARNING";
    case ERROR:
        return "ERROR";
    default:
        return "UNKNOWN";
    }
}