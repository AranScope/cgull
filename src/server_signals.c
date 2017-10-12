#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

#include "server_signals.h"
#include "server_logger.h"


void signal_handler(int signo) {
    if(signo == SIGINT) {
        debug("Received SIGINT");
        exit(signo);
    }
    else if(signo == SIGKILL) {
        debug("Received SIGKILL");
        exit(signo);
    }
    else if(signo == SIGTERM) {
        debug("Received SIGTERM");
        exit(signo);        
    }
    else if(signo == SIGSTOP) {
        debug("Received SIGSTOP");
        exit(signo);
    }
}
