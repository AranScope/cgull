#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>

#include <memory.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "server_base.h"
#include "server_defines.h"
#include "server_sockets.h"
#include "server_constants.h"
#include "server_handlers.h"
#include "server_parser.h"
#include "server_logger.h"
#include "server_signals.h"

int start(int port) {

    debug("Setting up signal handlers");
    signal(SIGINT, signal_handler);
    signal(SIGSTOP, signal_handler);
    signal(SIGTERM, signal_handler);
    signal(SIGKILL, signal_handler);
    
    debug("Binding socket to port: %d", port);
    
    int server_socket = get_server_socket(port);
    
    if(server_socket < 0) {
        debug("Failed to bind server socket to port: %d", port);
        return -1;
    }

    info("Listening on port: %d", port);
    connection_listener(server_socket);
    return 0;
}

void connection_listener(int server_socket) {
    
    char buffer[MAX_BUFFER_SIZE];

    while(1) {
        struct sockaddr_in6 client_address;
        socklen_t client_address_size = sizeof(client_address);
        int client = accept(server_socket, (struct sockaddr *) &client_address, &client_address_size);
        
        if(client < 0) {
            perror("accept");
        }

        debug("Reading buffer from client");
        read(client, buffer, MAX_BUFFER_SIZE - 1);

        debug("Parsing HTTP request from client");
        struct request *request = parse(buffer);

        info("Client requested resource: %s", request->path);

        debug("Handling HTTP request from client");
        struct response *resp = handle(request);

        debug("The body from the handler is: %s", resp->data);        
        
        char buffer[MAX_BUFFER_SIZE];
        char header[] = "HTTP/1.x %d %s\r\n"
                        "Content-Type: text/html\r\n\r\n%s";

        size_t response_size = snprintf(buffer, sizeof(buffer), header, resp->status, resp->status_message, resp->data);
        
        debug("Sending http response to client, content: \n------\n%s\n------\n", buffer);  

        write(client, buffer, response_size);      
        close(client);
    }
}