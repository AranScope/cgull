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

/*
    Initialise the handler list.

    Handlers are functions that handle the route() directive, examples can
    be viewed in server_main.c

    They essentially handle a request for a given HTTP verb GET, HEAD etc. and
    have a predefined response. So for example ROUTE(GET, "/hello", text("hello world!")) would
    return "Hello World!" whenever a user visits /hello.

    This is mostly for a fun extension and some practice but could easily be extended to support
    function pointers and proper callbacks like seen in node js for example.
*/
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

/* 
    Clean up the memory use by the response handler list.
*/
void free_handlers() {
    struct node *current_node = handler_list;
    
    while(current_node->next != NULL) {
        struct node *next_node = current_node->next;
        free(current_node->handler->request);
        free(current_node->handler->response);
        free(current_node->handler);
        free(current_node);
        current_node = next_node;
    }
}

/*
    Append a new handler to the response handler list.
*/
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

/*
    Register a new response handler, this mallocs the handler and calls append.
*/
void register_handler(struct request *request, struct response *response) {
    debug("Registering handler for path: %s", request->path);

    struct handler *handler;
    handler = malloc(sizeof(struct handler));
    handler->request = request;
    handler->response = response;
    append_handler(handler);
}

/*
    Handle a given request, this first checks if the request is for a file based
    on having a file extension and serves this. If the request is not for a file
    it checks if there is an appropriate user defined request handler, if there
    is not it finally returns a 404 not found error.
*/
struct response *handle(struct request *request) {

    // Check if the user has requested a file
    if(request->file_request) {
        debug("Calling file reader to read file at path: %s", request->path);

        // read the file into a buffer
        char *buffer = read_file(request->path);
        
        // if the buffer is null then the file was not found so throw a 404
        if(!buffer) {
            return file_not_exist_response;
        }

        // otherwise make a new response with the file text.
        return make_response(TEXT, buffer);
    }
    
   
    else {
        // if there are no defined user handlers then return a 404 because we've run out of options
        if(handler_list == NULL) {
            error("Request for resource at path: %s does not have a handler", request->path);
            return handler_not_found_response;
        }

        // otherwise loop throught the handlers till we find one with a matching HTTP verb and
        // file path
        struct node *head = handler_list;

        while(head != NULL) {
            struct request *req_node = head->handler->request;

            if(req_node->method == request->method && strcmp(req_node->path, request->path) == 0) {
                return head->handler->response;
            }

            head = head->next;
        }

        // couldn't fine a handler, so again return a 404.
        error("Request for resource at path: %s does not have a handler", request->path);
        return handler_not_found_response;
    }
}