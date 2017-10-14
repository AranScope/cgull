#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

#include <memory.h>
#include <string.h>
#include <netinet/in.h>



#include "server_base.h"
#include "server_defines.h"
#include "server_sockets.h"
#include "server_constants.h"
#include "server_handlers.h"
#include "server_parser.h"
#include "server_logger.h"
#include "server_signals.h"
#include "server_threading.h"

/*
    Called when you want to start the server, sets up the server
    socket and the signal handlers.
*/
 int start(int port) {

    debug("Setting up signal handlers");
    signal(SIGINT, signal_handler);
    signal(SIGSTOP, signal_handler);
    signal(SIGTERM, signal_handler);
    signal(SIGKILL, signal_handler);
    
    debug("Binding socket to port: %d", port);
    
    // use server_sockets to create a new server socket on the port
    int server_socket = get_server_socket(port);
    
    // make sure the port was opened successfully
    if(server_socket < 0) {
        debug("Failed to bind server socket to port: %d", port);
        return -1;
    }

    info("Listening on port: %d", port);

    // call the connection listener, this accepts connections and breaks
    // them out into client threads
    connection_listener(server_socket);
    return 0;
}

void connection_listener(int server_socket) {
    
    /* This would usually be a bad idea, but server_signals.c handles
       all of our signals so we can still exit cleanly */
    while(1) {
        struct sockaddr_in6 client_address;
        socklen_t client_address_size = sizeof(client_address);

        // grab a new client socket
        int client = accept(server_socket, (struct sockaddr *) &client_address, &client_address_size);
        
        // check that the socket was opened properly
        if(client < 0) {
            // don't exit because this could be a temporary issue
            debug("Failed to accept new client connection");
            perror("accept");
        }
        else {
            // multithreaded call
            debug("Calling client connection handler");
            handle_connection(client);
        }
    }
}