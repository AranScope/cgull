#include <stdio.h>
#include <stdlib.h>

#include "server_base.h"
#include "server_router.h"
#include "server_defines.h"
#include "server_logger.h"

int main(int argc, char *argv[]) {

    loglevel(DEBUG);

    // default serving directory is ./content but specify it anyway
    serve("./content");
    
    // some custom routing, inspired by nodejs
    route(GET, "/hello", text("Hello World!"));
    route(GET, "/world", text("World!"));

    // grab the port from the command line
    if(argc == 2) {
        int port = atoi(argv[1]);
        start(port);
    }
    else {
        start(9001);
    }

    return 0;
}