#include <stdio.h>
#include "server_base.h"
#include "server_router.h"
#include "server_defines.h"
#include "server_logger.h"

int main(int argc, char *argv[]) {
    loglevel(DEBUG);

    route(GET, "/hello", text("Hello World!"));
    route(GET, "/world", text("World!"));
    route(GET, "/json/hello", json("{'hello': 'world'}"));
    
    start(8080);
}