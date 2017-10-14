#include "server_router.h"
#include "server_handlers.h"
#include "server_constants.h"
#include "server_logger.h"

#include <unistd.h>
#include <stdlib.h>

/*
    The serve directive.

    This changes the web root directory from which files are served.
    Instead of doing lots of string manipulation we just use chdir, this
    is probably better for security also.
*/
void serve(char *dir) {
    int result = chdir(dir);

    if(result != 0) {
        info("Could not set custom web root, defaulting to .");
    }
}

/*
    The route directive.

    This sets up a request handler for a given path and http verb.
    A request handler is simply a struct that specifies what should
    be returned when this path is requested.

    This is overridden by serve, so for example trying to route(somefile.txt) will
    not work.
*/
void route(enum method method, char *path, struct response *response) {
    struct request *request;
    request = malloc(sizeof(struct request));

    request->method = method;
    request->path = path;
    request->type = response->type;

    register_handler(request, response);
}

/*
    Helper function to create a quick HTTP response.
    
    TODO: This should actually use the response type properly
    i.e. to add TEXT/HTML to the response header.
*/
struct response *make_response(enum response_type resp_type, char *data) {
    struct response *resp;
    resp = malloc(sizeof(struct response));
    resp->type = resp_type;
    resp->data = data;
    resp->status = 200;
    resp->status_message = "OK";
    return resp;
}

/*
    Create a response of the JSON type.

    TODO: This doesn't actually change the response type.
*/
struct response *json(char *data) {
    enum response_type type = JSON;
    return make_response(type, data);
}

/*
    Create a response of the TEXT type.

    TODO: This doesn't actually change the response type.
*/
struct response *text(char *data) {
    enum response_type type = TEXT;
    return make_response(TEXT, data);
}

/*
    Create a response of the TEXT/HTML type.

    TODO: This doesn't actually change the response type.
*/
struct response *html(char *data) {
    enum response_type type = TEXTHTML;
    return make_response(TEXTHTML, data);
}