#include <stdio.h>
#include <stdlib.h>

#include "server_base.h"
#include "server_router.h"
#include "server_defines.h"
#include "server_logger.h"

int main(int argc, char *argv[]) {

    // default serving directory is ./content
    loglevel(INFO);
    
    serve("./content");
    debug("Attempted to root in .contnet");
    route(GET, "/hello", text("Hello World!"));
    route(GET, "/world", text("World!"));

    // port specified
    if(argc == 2) {
        int port = atoi(argv[1]);
        start(port);
    }
    else {
        start(9001);
    }

    return 0;
}