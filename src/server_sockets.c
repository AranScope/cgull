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

/*
    Helper function to create a new server socket and return it's identifier.
*/
int get_server_socket(int port) {
    struct sockaddr_in6 address;
    address.sin6_family = AF_INET6; // ipv6
    address.sin6_addr = in6addr_any; // ipv6 on local ips
    address.sin6_port = htons(port); // byte conversion :(

    // create the socket
    int sock = socket(PF_INET6, SOCK_STREAM, 0);

    // check if it was created successfully
    if(sock < 0) {
        perror("socket");
        return -1;
    }

    // kill the existing socket, used for instant reboot (not massively sure how this works) attribution to Ian.
    const int one = 1;
    
      if (setsockopt (sock, SOL_SOCKET, SO_REUSEADDR, &one, sizeof (one)) != 0) {
        perror ("setsocket");
        /* but carry on, as it is only a 'nice to have' */
      }

    // Bind the socket and make sure there are no errors.
    if(bind(sock, (struct sockaddr *) &address, sizeof(address)) != 0) {
        perror("bind");
        return -1;
    }

    // Listen for client connections and again make sure there are no errors.
    if(listen(sock, 5) != 0) {
        perror("listen");
        return -1;
    }

    return sock;
}