#ifndef SERVER_HANDLERS_H
#define SERVER_HANDLERS_H

#include "server_defines.h"

void register_handler(struct request *request, struct response *response);
struct response *handle(struct request *request);

#endif