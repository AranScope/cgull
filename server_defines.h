#ifndef SERVER_DEFINES_H
#define SERVER_DEFINES_H

#define GET_STR "GET"
#define HEAD_STR "HEAD"

enum method {
    GET,
    HEAD
};

enum log_level {
    INFO,
    DEBUG,
    ERROR
};

enum response_type {
    JSON,
    TEXT,
    TEXTHTML
};

struct response {
    enum response_type type;
    char *data;
};

struct request {
    enum method method;
    enum response_type type;
    char *path;
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