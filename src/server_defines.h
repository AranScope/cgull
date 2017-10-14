#ifndef SERVER_DEFINES_H
#define SERVER_DEFINES_H

#define GET_STR "GET"
#define HEAD_STR "HEAD"

#include <stdbool.h>

// HTTP request method
enum method {
    GET,
    HEAD
};

// Log granularity levels for custom logger
typedef enum {
    INFO,
    DEBUG,
    ERROR
} log_level;

// HTTP response type
enum response_type {
    JSON,
    TEXT,
    TEXTHTML
};

// HTTP response struct
struct response {
    enum response_type type;
    int status;
    char *status_message;
    char *data;
};

// HTTP request struct
struct request {
    enum method method;
    enum response_type type;
    char *path;
    bool file_request;
    char *content_type;
};

// HTTP request handler struct
struct handler {
    struct request *request;
    struct response *response;
};

// List node for http handlers
struct node {
    struct handler *handler;
    struct node *next;
};

// struct for passing information when creating new threads
struct thread_block {
    int client_socket;
};

#endif