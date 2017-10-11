#include <stdlib.h>
#include <stdio.h>
#include "server_handlers.h"
#include "server_parser.c"
#include "server_logger.h"

struct node *handler_list = NULL;

void append_handler(struct handler *handler) {
    if(handler_list == NULL) {
        handler_list = malloc(sizeof(struct node));
        handler_list->next = NULL;
        handler_list->handler = handler;
        return;
    }

    struct node *head = handler_list;
    
    while(head->next != NULL) {
        head = head->next;
    }

    head->next = malloc(sizeof(struct node));
    head->next->handler = handler;
    head->next->next = NULL;
    
    return;
}

void register_handler(struct request *request, struct response *response) {
    printf("\nCalling debug\n");
    debug("Registering handler for path: ", request->path);
    printf("\nCalled\n");
    struct handler *handler;
    handler = malloc(sizeof(struct handler));
    handler->request = request;
    handler->response = response;
    append_handler(handler);
}

char *handle(struct request *request) {
    if(handler_list == NULL) {
        error("Handler list was not initialized");
        exit(-1);
    }

    struct node *head = handler_list;

    while(head != NULL) {
        struct request *req_node = head->handler->request;

        if(req_node->method == request->method && strncmp(req_node->path, request->path, sizeof(request->path)) == 0) {
            return head->handler->response->data;
        }

        head = head->next;
    }

    error("Request for resource at path: %s does not have a handler", request->path);
    return NULL;
}