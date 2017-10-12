#include <stdio.h>
#include <string.h>
#include "server_defines.h"
#include "server_constants.h"
#include <stdarg.h>

enum log_level current_log_level = INFO;

void loglevel(enum log_level level) {
    current_log_level = level;
}

void info(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    char buffer[MAX_BUFFER_SIZE];
    vsprintf(buffer, fmt, args);
    va_end(args);
    
    printf("INFO: %s\n", buffer);
}

void debug(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    char buffer[MAX_BUFFER_SIZE];
    vsprintf(buffer, fmt, args);
    va_end(args);

    if(current_log_level == DEBUG) {
        printf("DEBUG: %s\n", buffer);
    }
}

void error(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    // char buffer[MAX_BUFFER_SIZE];
    char buffer[MAX_BUFFER_SIZE];
    vsprintf(buffer, fmt, args);
    va_end(args);
    
    if(current_log_level == ERROR) {
        printf("ERROR: %s\n", buffer);
    }
}