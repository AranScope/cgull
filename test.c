#include <stdio.h>
#include <stdlib.h>

#include "server_router.h"

int main() {
    route(GET, "/", text("Hello World!"));

    route(GET, "/apples", json("{'abra': 'cadabra'}"));
    serve("/var/www");
    
    return 0;
}