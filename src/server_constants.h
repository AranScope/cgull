#ifndef SERVER_CONSTANTS_H
#define SERVER_CONSTANTS_H

/*
     This is the maximum buffer size, used so we can stack allocate our buffers
     which is a little faster and much simpler for memory management.

     We need to be careful here, as if we add support for binary types such as images
     we should probably look into malloc or dramatically increasing this buffer size.

     TODO: arbitrary length inputs
*/

#define MAX_HEADER_SIZE 8192
#define PRINT_BUFFER_SIZE 8192
#define MAX_URI_SIZE 8192
#define MAX_FILE_SIZE 1000000

#endif