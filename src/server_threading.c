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

void handle_connection(int client_socket) {
    // create a new pthread

    struct thread_block *t_block = malloc(sizeof(struct thread_block));
    t_block->client_socket = client_socket;

    pthread_t thread;

    debug("Creating new client thread");
    int result = pthread_create(&thread, 0, &client_thread, (void *) t_block);
    if(result != 0) {
        debug("Failed to create client thread");
        perror("pthread_create");
        exit(-1);
    }
}

static void *client_thread(void *data) {
    struct thread_block *t_block = (struct thread_block*) data;
    int client = t_block->client_socket;

    char receive_buffer[MAX_BUFFER_SIZE];
    
    debug("Reading buffer from client");
    read(client, receive_buffer, MAX_BUFFER_SIZE - 1);

    debug("Parsing HTTP request from client");
    struct request *request = parse(receive_buffer);

    info("Client requested resource: %s", request->path);

    debug("Handling HTTP request from client");
    struct response *resp = handle(request);

    debug("The body from the handler is: %s", resp->data);        
    
    char send_buffer[MAX_BUFFER_SIZE];
    char header[] = "HTTP/1.x %d %s\r\n"
                    "Content-Type: text/html\r\n\r\n%s";

    size_t response_size = snprintf(send_buffer, sizeof(send_buffer), header, resp->status, resp->status_message, resp->data);
    
    debug("Sending http response to client, content: \n------\n%s\n------\n", send_buffer);  

    write(client, send_buffer, response_size);      
    close(client);

    free(request);
    free(resp);

    pthread_exit(0);
}

// create a new thread control block

// accept a connection from a client
// create a pthread
// pass the pthread the handling function handler