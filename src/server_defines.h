#ifndef SERVER_DEFINES_H
#define SERVER_DEFINES_H

#define GET_STR "GET"
#define HEAD_STR "HEAD"

#include <stdbool.h>

enum method {
    GET,
    HEAD
};

typedef enum {
    INFO,
    DEBUG,
    ERROR
} log_level;

enum response_type {
    JSON,
    TEXT,
    TEXTHTML
};

struct response {
    enum response_type type;
    int status;
    char *status_message;
    char *data;
};

struct request {
    enum method method;
    enum response_type type;
    char *path;
    bool file_request;
};

struct handler {
    struct request *request;
    struct response *response;
};

struct node {
    struct handler *handler;
    struct node *next;
};

#endif