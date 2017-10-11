#include <stdlib.h>
#include <string.h>

#include "server_defines.h"

// returns a response type, path given a request
// 
struct request *parse(char *http_header) {

    struct request *request;
    request = malloc(sizeof(struct request));

    char *line_ptr;
    char *token_ptr;

    char *first_line = strtok_r(http_header, "\n", &line_ptr);

    char *http_verb = strtok_r(first_line, " ", &token_ptr);

    printf("Parsing, found http verb %s\n", http_verb);

    if(strncmp(http_verb, GET_STR, sizeof(http_verb)) == 0) {
        printf("Assigned get method to request\n");
        printf("Http verb value %d\n", GET);
        request->method = GET;
    }
    else if(strncmp(http_verb, HEAD_STR, sizeof(http_verb)) == 0) {
        printf("Assigned head method to request\n");
        request->method = HEAD;
    }

    char *path = strtok_r(NULL, " ", &token_ptr);
    request->path = path;

    return request;

    // char *key;
    // char *value;

    // while((line_ptr = strtok_r(line_ptr, "\n", &line_ptr))) {
    //     key = strtok_r(line_ptr, ":", &token_ptr);
    //     value = strtok_r(line_ptr, ":", &token_ptr);
        
        
    // }

}