
#include "server_defines.h"

void serve(char *dir);

void route(enum method m, char *path, struct response *resp);

struct response *json(char *data);

struct response *text(char *data);

struct response *html(char *data);

void connect(void(*callback)());

void serve(char *path);

// struct header {
//     enum type type;
//     char *accept;
// };