#ifndef SERVER_LOGGER_H
#define SERVER_LOGGER_H

void loglevel(enum log_level level);

void info(const char *fmt, ...);
void debug(const char *fmt, ...);
void error(const char *fmt, ...);

#endif