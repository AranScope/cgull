#include <stdio.h>
#include "server_base.h"
#include "server_router.h"
#include "server_defines.h"
#include "server_logger.h"

int main(int argc, char *argv[]) {

    // default serving directory is ./web
    loglevel(DEBUG);
    
    serve("./web");
    route(GET, "/hello", text("Hello World!"));
    route(GET, "/world", text("World!"));

    start(9001);

    return 0;
}