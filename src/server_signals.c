#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

#include "server_signals.h"
#include "server_logger.h"
#include "server_handlers.h"

/*
    Handle the few signals we're going to encounter. This is necessary
    for debugging purposes, for memory cleanup and because of the 'voodoo' way that Docker handlers
    signals.
*/
void signal_handler(int signo) {
    if(signo == SIGINT) {
        debug("Received SIGINT");
        free_server();
        exit(signo);
    }
    else if(signo == SIGKILL) {
        debug("Received SIGKILL");
        free_server();
        exit(signo);
    }
    else if(signo == SIGTERM) {
        debug("Received SIGTERM");
        free_server();
        exit(signo);        
    }
    else if(signo == SIGSTOP) {
        debug("Received SIGSTOP");
        free_server();
        exit(signo);
    }
}

/*
    Clean up all the request handlers, any anything
    else that needs to be free'd.
*/
void free_server() {
    free_handlers();
}
