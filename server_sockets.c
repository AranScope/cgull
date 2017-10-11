#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>

#include <memory.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <assert.h>

#include "server_sockets.h"

int get_server_socket(int port) {
    struct sockaddr_in6 address;
    address.sin6_family = AF_INET6;
    address.sin6_addr = in6addr_any;
    address.sin6_port = htons(port);

    int sock = socket(PF_INET6, SOCK_STREAM, 0);

    if(sock < 0) {
        perror("socket");
        return -1;
    }

    // kill the existing socket
    const int one = 1;
    
      if (setsockopt (sock, SOL_SOCKET, SO_REUSEADDR, &one, sizeof (one)) != 0) {
        perror ("setsocket");
        /* but carry on, as it is only a 'nice to have' */
      }

    if(bind(sock, (struct sockaddr *) &address, sizeof(address)) != 0) {
        perror("bind");
        return -1;
    }

    if(listen(sock, 5) != 0) {
        perror("listen");
        return -1;
    }

    return sock;
}