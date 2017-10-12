#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include "server_logger.h"
#include "server_constants.h"

char *read_file(char *file_url) {
    char web_root[] = ".";
    char file_path[MAX_BUFFER_SIZE] = {0};

    strncat(file_path, web_root, sizeof(web_root));
    strncat(file_path, file_url, sizeof(file_path)); // TODO probably fix this

    debug("Reading file at path: %s", file_path);
    
    char *buffer = malloc(sizeof(char) * MAX_BUFFER_SIZE);
 
    FILE *fp = fopen(file_path, "rb");

    if(!fp) {
        perror("file");
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    fread(buffer, fsize, 1, fp);
    fclose(fp);
    
    buffer[fsize] = '\0';

    return buffer;
}
