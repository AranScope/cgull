#ifndef SERVER_LOGGER_H
#define SERVER_LOGGER_H

#include "server_defines.h"
void loglevel(log_level level);

void info(const char *fmt, ...);
void debug(const char *fmt, ...);
void error(const char *fmt, ...);

#endif