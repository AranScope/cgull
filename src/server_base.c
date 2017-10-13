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
    
    /* This would usually be a bad idea, but server_signals.c handles
       all of our signals so we can still exit cleanly */
    while(1) {
        struct sockaddr_in6 client_address;
        socklen_t client_address_size = sizeof(client_address);
        int client = accept(server_socket, (struct sockaddr *) &client_address, &client_address_size);
        
        if(client < 0) {
            perror("accept");
        }
        else {
            // multithreaded call
            handle_connection(client);
        }
    }
}