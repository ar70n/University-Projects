#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

typedef enum {
    INFO,
    WARNING,
    ERROR
} LogType;

void init_log();
void log_message(LogType logtype, char *format, ...);

#endif // LOGL_H