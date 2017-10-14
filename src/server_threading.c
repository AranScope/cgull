#include "server_defines.h"
#include "server_logger.h"
#include "server_constants.h"
#include "server_parser.h"
#include "server_handlers.h"
#include "server_threading.h"

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <memory.h>
#include <string.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>

static void *client_thread(void *data);

/*
    Handle a new client connection, this sets up and create a new thread
    for the client.

    TODO: Should explore the request handlers to make sure they're thread safe.
*/
void handle_connection(int client_socket) {

    // the data we need to pass to the new thread
    struct thread_block *t_block = malloc(sizeof(struct thread_block));
    t_block->client_socket = client_socket;

    pthread_t thread;

    // create the new thread and make sure there aren't any errors
    debug("Creating new client thread");

    int result = pthread_create(&thread, 0, &client_thread, (void *) t_block);
    
    if(result != 0) {
        // there is probably a big issue if we fail to create a thread so exit.

        debug("Failed to create client thread");
        perror("pthread_create");
        exit(-1);
    }
}

/*
    The client thread, this is the meat of multithreading.

    This is passed as a function pointer to pthread_create and handles the lifetime of the 
    clients connection to the server.
*/
static void *client_thread(void *data) {
    struct thread_block *t_block = (struct thread_block*) data;
    int client = t_block->client_socket;

    // grab the request header from the client
    char receive_buffer[MAX_BUFFER_SIZE];
    
    debug("Reading buffer from client");
    read(client, receive_buffer, MAX_BUFFER_SIZE - 1);

    // parse the request
    debug("Parsing HTTP request from client");
    struct request *request = parse(receive_buffer);

    info("Client requested resource: %s", request->path);

    // handle the request, either grabbing a file or response handler text
    debug("Handling HTTP request from client");
    struct response *resp = handle(request);

    debug("The body from the handler is: %s", resp->data);        
    
    // set up the response TODO: correct content type
    char send_buffer[MAX_BUFFER_SIZE];
    char header[] = "HTTP/1.x %d %s\r\n"
                    "Content-Type: text/html\r\n" // TODO: Get the bloody content type right
                    "Content-Length: %d\r\n"
                    "\r\n%s";

    size_t response_size;
    
    // if it's a get request send the data
    if(request->method == GET) {
        response_size = snprintf(send_buffer, sizeof(send_buffer), header, resp->status, resp->status_message, strlen(resp->data), resp->data);
    }
    // otherwise just send the content length
    else if(request->method == HEAD) {
        response_size = snprintf(send_buffer, sizeof(send_buffer), header, resp->status, resp->status_message, strlen(resp->data), "");
    }


    // write the response to the client thread
    debug("Sending http response to client, content: \n------\n%s\n------\n", send_buffer);  
    write(client, send_buffer, response_size);
    
    // clean everything up
    close(client);
    free(request);
    free(resp);

    pthread_exit(0);
}