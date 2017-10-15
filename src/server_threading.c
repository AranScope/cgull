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
    char receive_buffer[MAX_HEADER_SIZE] = {0};
    
    debug("Reading buffer from client");
    read(client, receive_buffer, MAX_HEADER_SIZE - 1);

    // parse the request
    debug("Parsing HTTP request from client");
    struct request *request = parse(receive_buffer);

    info("Client requested resource: %s", request->path);

    // handle the request, either grabbing a file or response handler text
    debug("Handling HTTP request from client");
    struct response *resp = handle(request);

    debug("The body from the handler is: %s", resp->data);     
    
    // set up the response TODO: correct content type
    char send_buffer[MAX_HEADER_SIZE] = {0};
    char header[] = "HTTP/1.x %d %s\r\n"
                    "Content-Type: %s\r\n" // TODO: Get the bloody content type right
                    "Content-Length: %d\r\n"
                    "\r\n";

    size_t header_size;
    
    // if it's a get request send the data
    if(request->method == GET) {
        header_size = snprintf(send_buffer, sizeof(send_buffer), header, resp->status, resp->status_message, resp->content_type, resp->length);
    }
    // otherwise just send the content length
    else if(request->method == HEAD) {
        header_size = snprintf(send_buffer, sizeof(send_buffer), header, resp->status, resp->status_message, resp->content_type, resp->length);
    }

    header[header_size] = '\0';
    // write the response to the client thread
    // debug("Size of HTTP header is: %d bytes", header_size);
    // debug("Sending http header to client, content: \n------\n%s\n------\n", send_buffer);

    write(client, send_buffer, header_size);

    // TODO: images aren't working because strlen doesn't work on binary types, this is because they may
    // contain null terminators that are not null characters, need to work this one out.
    // Images and pdf's are working, now HTML and txt messages are cut short
    // debug("Sending http data to client, content: \n------\n%s\n------\n", resp->data);
    
    // this points to unaddressable bytes apparently :(
    write(client, resp->data, resp->length);
    
    // clean everything up
    close(client);

    // only free the response if this is a file request,
    // because we don't want to delete responses for our handlers.
    if(request->file_request) {
        free(resp->data); // malloc'd string
        free(resp); 
    }

    free(request);
    free(t_block);

    pthread_exit(0);
}