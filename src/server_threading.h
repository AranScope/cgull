#ifndef SERVER_THREADING_H
#define SERVER_THREADING_H

#include "server_defines.h"

void handle_connection(int client_socket);
static void *client_thread(void *data);


#endif