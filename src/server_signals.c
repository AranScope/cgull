#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

#include "server_signals.h"
#include "server_logger.h"
#include "server_handlers.h"


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

void free_server() {
    free_handlers();
}
