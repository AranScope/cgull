#include <stdlib.h>
#include <string.h>

#include "server_defines.h"
#include "server_logger.h"

// returns a response type, path given a request
// 
struct request *parse(char *http_header) {

    struct request *request;
    request = malloc(sizeof(struct request));

    char *line_ptr;
    char *token_ptr;
    char *ext_ptr;

    char *first_line = strtok_r(http_header, "\n", &line_ptr);

    char *http_verb = strtok_r(first_line, " ", &token_ptr);

    debug("Parsing, found http verb %s", http_verb);

    if(strncmp(http_verb, GET_STR, sizeof(http_verb)) == 0) {
        debug("Assigned get method to request");
        debug("Http verb value %d", GET);
        request->method = GET;
    }
    else if(strncmp(http_verb, HEAD_STR, sizeof(http_verb)) == 0) {
        debug("Assigned head method to request");
        request->method = HEAD;
    }
    
    char *path = strtok_r(NULL, " ", &token_ptr);
    
    request->path = path;

    debug("The path: %s was requested", request->path);

    strtok_r(strdup(path), ".", &ext_ptr); // Remove the basename

    debug("Calculated the base name");
    char *ext = strtok_r(NULL, ".", &ext_ptr);

    if(ext) request->file_request = true;
    else request->file_request = false;
    
    debug("The extension is: %s", ext);

    return request;

    // char *key;
    // char *value;

    // while((line_ptr = strtok_r(line_ptr, "\n", &line_ptr))) {
    //     key = strtok_r(line_ptr, ":", &token_ptr);
    //     value = strtok_r(line_ptr, ":", &token_ptr);
        
        
    // }

}