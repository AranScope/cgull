#include <stdio.h>
#include <string.h>
#include "server_defines.h"
#include "server_constants.h"
#include <stdarg.h>

enum log_level current_log_level = DEBUG;

void loglevel(enum log_level level) {
    current_log_level = level;
}

void info(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    char buffer[MAX_BUFFER_SIZE] = "INFO: ";
    strncat(buffer, fmt, sizeof(buffer));
    
    if(current_log_level == DEBUG) {
        vprintf(buffer, args);
    }

    va_end(args);
}

void debug(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    char buffer[MAX_BUFFER_SIZE] = "DEBUG: ";
    strncat(buffer, fmt, sizeof(buffer));
    printf("\n%s\n\n", buffer);
    
    
    if(current_log_level == DEBUG) {
        vprintf(buffer, args);
    }

    va_end(args);
}

void error(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    char buffer[MAX_BUFFER_SIZE] = "ERROR: ";
    
    strncat(buffer, fmt, sizeof(buffer));
    
    if(current_log_level == ERROR) {
        vprintf(buffer, args);
    }

    va_end(args);
}