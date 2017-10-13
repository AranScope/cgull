#include "server_router.h"
#include "server_handlers.h"
#include "server_constants.h"
#include "server_logger.h"

#include <unistd.h>
#include <stdlib.h>

void serve(char *dir) {
    int result = chdir(dir);

    if(result != 0) {
        info("Could not set custom web root, defaulting to .");
    }
}

void route(enum method method, char *path, struct response *response) {
    struct request *request;
    request = malloc(sizeof(struct request));

    request->method = method;
    request->path = path;
    request->type = response->type;

    register_handler(request, response);
}

struct response *make_response(enum response_type resp_type, char *data) {
    struct response *resp;
    resp = malloc(sizeof(struct response));
    resp->type = resp_type;
    resp->data = data;
    resp->status = 200;
    resp->status_message = "OK";
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