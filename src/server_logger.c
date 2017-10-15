#include <stdio.h>
#include <string.h>
#include "server_defines.h"
#include "server_constants.h"
#include <stdarg.h>

log_level current_log_level = INFO;

void loglevel(log_level level) {
    current_log_level = level;
}

/*
    Print to stdout at the 'info' level.

    This takes exactly the same arguments as printf.

    This should be used for generally informative but non-technical messages, so
    a non-technical user could understand the output and know roughly what state
    the program is in.
*/
void info(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    char buffer[PRINT_BUFFER_SIZE] = {0};
    vsnprintf(buffer, PRINT_BUFFER_SIZE, fmt, args);
    va_end(args);
    
    printf("INFO: %s\n", buffer);
}

/*
    Print to stdout at the 'debug' level.

    This takes exactly the same arguments as printf.

    This should be used for technical debugging information, excluding errors.
*/
void debug(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    char buffer[PRINT_BUFFER_SIZE] = {0};
    vsnprintf(buffer, PRINT_BUFFER_SIZE, fmt, args);
    va_end(args);

    if(current_log_level == DEBUG) {
        printf("DEBUG: %s\n", buffer);
    }
}

/*
    Print to stdout at the 'error' level.

    This takes exactly the same arguments as printf.

    This should be used for printing technical errors.
*/
void error(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    char buffer[PRINT_BUFFER_SIZE] = {0};
    vsnprintf(buffer, PRINT_BUFFER_SIZE, fmt, args);
    va_end(args);
    
    if(current_log_level == ERROR) {
        printf("ERROR: %s\n", buffer);
    }
}