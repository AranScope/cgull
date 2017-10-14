#include <stdlib.h>
#include <string.h>

#include "server_defines.h"
#include "server_logger.h"

// struct for mapping between extension and content-type
// inspired by -> https://github.com/labcoder/simple-webserver/blob/master/server.c
struct {
    char *extension;
    char *content_type;
} extensions[] = {
    {"html", "text/html"},
    {"html", "text/html"},
    {"js", "text/js"},
    {"css", "text/css"},
    {"png", "image/png"},
    {"jpg", "image/jpeg"},
    {"jpeg", "image/jpeg"},
    {"txt", "text/plain"},
    {"md", "text/plain"},
    {"pdf", "application/pdf"},
    {0, 0}
};

/*
    Parse a HTTP request header string and
    return a HTTP request struct.

    This extracts the request path, http verb and should also
    extract all of the key: value pairs.
*/
struct request *parse(char *http_header) {

    struct request *request;
    request = malloc(sizeof(struct request));
    request->content_type = "text/html"; // sensible default

    char *line_ptr;
    char *token_ptr;
    char *ext_ptr;

    // grab the first line, this has most of the information we need
    char *first_line = strtok_r(http_header, "\n", &line_ptr);

    // extract the http verb i.e. GET / HEAD etc.
    char *http_verb = strtok_r(first_line, " ", &token_ptr);

    debug("Parsing, found http verb %s", http_verb);

    if(strcmp(http_verb, GET_STR) == 0) {
        // this is a get request
        debug("Assigned get method to request");
        debug("Http verb value %d", GET);
        request->method = GET;
    }
    else if(strcmp(http_verb, HEAD_STR) == 0) {
        // this is a head request
        debug("Assigned head method to request");
        request->method = HEAD;
    }
    
    // extract the requested path
    char *path = strtok_r(NULL, " ", &token_ptr);
    
    // assign it to the request struct
    request->path = path;

    // perform null url -> index.html rewriting, this should later be broken
    // out into a rewrite(from, to) directive.
    char null_uri[] = "/";
    if(strncmp(request->path, null_uri, sizeof(null_uri)) == 0) {
        debug("Internally rewriting null uri to /index.html");
        request->path = "/index.html";
    }

    debug("The path: %s was requested", request->path);

    // copy the request path as strtok_r does in place modifications
    char *dup_path = strdup(request->path);

    // remove the basename from the path as we're only checking if this is a file
    strtok_r(dup_path, ".", &ext_ptr);
    debug("Calculated the base name");

    // grab the extension (if one exists)
    char *ext = strtok_r(NULL, ".", &ext_ptr);

    if(ext) {
        request->file_request = true;

        for(int i = 0; extensions[i].extension != 0; i++) {
            int len = strlen(extensions[i].extension);

            if(strncmp(ext, extensions[i].extension, len) == 0) {
                request->content_type = extensions[i].content_type;
                break;
            }
        }

    }
    else {
        request->file_request = false;
    }
    
    debug("The extension is: %s", ext);

    // clean up the memory
    free(dup_path);

    return request;

    // char *key;
    // char *value;

    // while((line_ptr = strtok_r(line_ptr, "\n", &line_ptr))) {
    //     key = strtok_r(line_ptr, ":", &token_ptr);
    //     value = strtok_r(line_ptr, ":", &token_ptr);
        
        
    // }
}