#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "server_handlers.h"
#include "server_logger.h"
#include "server_static.h"
#include "server_constants.h"
#include "server_router.h"

struct node *handler_list = NULL;

struct response *file_not_exist_response = NULL;
struct response *handler_not_found_response = NULL;

void init_handlers(struct handler *first_handler) {
    handler_list = malloc(sizeof(struct node));
    handler_list->next = NULL;
    handler_list->handler = first_handler;

    file_not_exist_response = make_response(TEXT, "The requested file does not exist");
    file_not_exist_response->status = 404;
    file_not_exist_response->status_message = "Not Found";

    handler_not_found_response = make_response(TEXT, "The requested handler could not be found");
    handler_not_found_response->status = 404;
    handler_not_found_response->status_message = "Not Found";
}

void append_handler(struct handler *handler) {
    if(handler_list == NULL) {
        init_handlers(handler);
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
    debug("Registering handler for path: %s", request->path);

    struct handler *handler;
    handler = malloc(sizeof(struct handler));
    handler->request = request;
    handler->response = response;
    append_handler(handler);
}

struct response *handle(struct request *request) {

    if(request->file_request) {
        debug("Calling file reader to read file at path: %s", request->path);
        char *buffer = read_file(request->path);
        
        if(!buffer) {
            return file_not_exist_response;
        }

        return make_response(TEXT, buffer);
    }
    
   
    else {
        if(handler_list == NULL) {
            error("Request for resource at path: %s does not have a handler", request->path);
            return handler_not_found_response;
        }
        
        struct node *head = handler_list;

        while(head != NULL) {
            struct request *req_node = head->handler->request;

            if(req_node->method == request->method && strncmp(req_node->path, request->path, sizeof(request->path)) == 0) {
                return head->handler->response;
            }

            head = head->next;
        }

        error("Request for resource at path: %s does not have a handler", request->path);
        return handler_not_found_response;
    }
}