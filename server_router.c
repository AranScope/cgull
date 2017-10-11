#include "server_router.h"
#include "server_handlers.h"
#include <stdlib.h>


void route(enum method method, char *path, struct response *response) {
    struct request *request;
    request = malloc(sizeof(struct request));

    request->method = method;
    request->path = path;
    request->type = response->type;

    register_handler(request, response);
}

struct response *make_response(enum response_type type, char *data) {
    struct response *resp;
    resp = malloc(sizeof(struct response));
    resp->type = type;
    resp->data = data;
    return resp;
}

struct response *json(char *data) {
    enum response_type type = JSON;
    return make_response(type, data);
}

struct response *text(char *data) {
    enum response_type type = TEXT;
    return make_response(TEXT, data);
}

struct response *html(char *data) {
    enum response_type type = TEXTHTML;
    return make_response(TEXTHTML, data);
}

void serve(char *path) {

}